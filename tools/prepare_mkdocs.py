"""Prepare an isolated MkDocs source tree without editing teaching materials."""

from pathlib import Path
import html
import json
import re
import shutil
from urllib.parse import quote


ROOT = Path(__file__).resolve().parents[1]
DESTINATION = ROOT / ".mkdocs-docs"
GENERATED_CONFIG = ROOT / ".mkdocs.generated.yml"
MATERIALS = ROOT / "materials"
SOURCE_DIRECTORIES = ("APCS", "codecat", "CSES_problem_set", "TQC python", "ZeroJudge")
PUBLISHED_SUFFIXES = {".md", ".txt", ".jpg", ".jpeg", ".png", ".gif", ".svg", ".cpp", ".py"}
IMAGE_SUFFIXES = {".jpg", ".jpeg", ".png", ".gif", ".svg"}


def normalize_markdown_tables(path: Path) -> None:
    """Normalize Docsify-tolerated Markdown syntax in the isolated build copy."""
    text = path.read_text(encoding="utf-8")
    text = text.replace(
        '<div style="font-size: 18px; line-height: 2;">',
        '<div markdown="1" class="problem-list">',
    )
    text = text.replace('src="./resources\\', 'src="../resources/')
    text = text.replace('src="./resources/', 'src="../resources/')
    text = re.sub(
        r"(?<!\$)\$\$[ \t]*(.+?)[ \t]*\$\$(?!\$)",
        r"$\1$",
        text,
    )
    text = re.sub(r"(?m)^[*+-]\s+(\d+[.)]\s+)", r"\1", text)
    lines = text.splitlines(keepends=True)
    normalized: list[str] = []
    inside_display_math = False
    inside_code_fence = False

    for index, line in enumerate(lines):
        stripped = line.strip()
        next_line = lines[index + 1] if index + 1 < len(lines) else ""
        if stripped.startswith("```") or stripped.startswith("~~~"):
            normalized.append(line)
            inside_code_fence = not inside_code_fence
            continue

        if not inside_code_fence and stripped == "$$":
            if not inside_display_math and normalized and normalized[-1].strip():
                normalized.append("\n")
            normalized.append(line)
            inside_display_math = not inside_display_math
            if not inside_display_math and next_line.strip():
                normalized.append("\n")
            continue

        is_top_level_list = bool(re.match(r"^(?:[*+-]|\d+[.)])\s+", line))
        next_is_top_level_list = bool(re.match(r"^(?:[*+-]|\d+[.)])\s+", next_line))
        if not inside_code_fence and is_top_level_list:
            previous_line = lines[index - 1] if index > 0 else ""
            previous_is_top_level_list = bool(
                re.match(r"^(?:[*+-]|\d+[.)])\s+", previous_line)
            )
            if normalized and normalized[-1].strip() and not previous_is_top_level_list:
                normalized.append("\n")
            normalized.append(line)
            if next_line.strip() and not next_is_top_level_list:
                normalized.append("\n")
            continue

        is_table_header = line.lstrip().startswith("|") and next_line.lstrip().startswith("| :---")
        if is_table_header and normalized and normalized[-1].strip():
            normalized.append("\n")
        normalized.append(line)

    path.write_text("".join(normalized), encoding="utf-8")


def copy_published_files(source: Path, destination: Path) -> None:
    for path in source.rglob("*"):
        if not path.is_file() or path.suffix.lower() not in PUBLISHED_SUFFIXES:
            continue
        target = destination / path.relative_to(source)
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(path, target)
        if target.suffix.lower() == ".md":
            normalize_markdown_tables(target)


def source_page_title(path: Path, base: Path) -> str:
    relative = path.relative_to(base)
    return relative.parent.as_posix() if relative.parent != Path(".") else path.stem


def markdown_title(path: Path) -> str:
    text = path.read_text(encoding="utf-8", errors="replace")
    heading = re.search(r"(?m)^#\s+(.+?)\s*$", text)
    return heading.group(1) if heading else path.stem


def write_source_index(directory_name: str, display_name: str | None = None) -> None:
    """Create navigable source-code pages in the disposable build tree."""
    display_name = display_name or directory_name
    source_root = MATERIALS / directory_name
    destination_root = DESTINATION / directory_name
    source_files = sorted(
        (path for path in source_root.rglob("*") if path.suffix.lower() in {".cpp", ".py"}),
        key=lambda path: path.relative_to(source_root).as_posix().lower(),
    )
    groups: dict[Path, list[Path]] = {}
    for source_file in source_files:
        groups.setdefault(source_file.parent, []).append(source_file)

    overview: list[str] = [
        f"# {display_name} 程式索引\n\n",
        "選擇題目或章節，即可閱讀及下載原始程式碼。\n\n",
        '<label class="source-search">\n',
        '  <span>搜尋題號</span>\n',
        '  <input type="search" placeholder="例如：b923" autocomplete="off">\n',
        '</label>\n\n',
        '<p class="source-count" aria-live="polite"></p>\n\n',
    ]

    entries: list[dict[str, str]] = []
    for source_directory in groups:
        relative_directory = source_directory.relative_to(source_root)
        label = source_page_title(groups[source_directory][0], source_root)
        target = "./" if relative_directory == Path(".") else f"{relative_directory.as_posix()}/"
        languages = sorted(
            {"C++" if path.suffix.lower() == ".cpp" else "Python" for path in groups[source_directory]}
        )
        language_badges = "".join(f"<span>{html.escape(language)}</span>" for language in languages)
        search_text = html.escape(f"{label} {' '.join(languages)}".lower(), quote=True)
        first_character = label[0].upper() if label and label[0].isalpha() else "#"
        entries.append(
            {
                "label": html.escape(label),
                "target": html.escape(target, quote=True),
                "languages": language_badges,
                "search": search_text,
                "letter": first_character,
            }
        )

    if directory_name == "ZeroJudge":
        letters = sorted({entry["letter"] for entry in entries})
        overview.extend(
            [
                '<nav class="source-alphabet" aria-label="按照題號首字母篩選">\n',
                f'  <button type="button" class="is-active" data-source-letter="all" aria-pressed="true">全部 <span>{len(entries)}</span></button>\n',
            ]
        )
        for letter in letters:
            count = sum(entry["letter"] == letter for entry in entries)
            overview.append(
                f'  <button type="button" data-source-letter="{html.escape(letter.lower(), quote=True)}" aria-pressed="false">{html.escape(letter)} <span>{count}</span></button>\n'
            )
        overview.extend(['</nav>\n\n', '<div class="source-groups">\n'])
        for letter in letters:
            letter_value = html.escape(letter.lower(), quote=True)
            overview.extend(
                [
                    f'  <section class="source-group" data-source-group="{letter_value}">\n',
                    f'    <h2 id="letter-{letter_value}" data-letter="{html.escape(letter, quote=True)}">{html.escape(letter)} 系列</h2>\n',
                    '    <div class="source-index">\n',
                ]
            )
            for entry in (item for item in entries if item["letter"] == letter):
                overview.extend(
                    [
                        f'      <a class="source-card" href="{entry["target"]}" data-source-search="{entry["search"]}" data-source-letter="{letter_value}">\n',
                        f'        <strong>{entry["label"]}</strong>\n',
                        f'        <span class="source-languages">{entry["languages"]}</span>\n',
                        "      </a>\n",
                    ]
                )
            overview.extend(["    </div>\n", "  </section>\n"])
        overview.append("</div>\n\n")
    else:
        overview.append('<div class="source-index">\n')
        for entry in entries:
            overview.extend(
                [
                    f'  <a class="source-card" href="{entry["target"]}" data-source-search="{entry["search"]}">\n',
                    f'    <strong>{entry["label"]}</strong>\n',
                    f'    <span class="source-languages">{entry["languages"]}</span>\n',
                    "  </a>\n",
                ]
            )
        overview.append("</div>\n\n")

    overview.append('<p class="source-empty" hidden>找不到符合的題目。</p>\n')
    destination_root.mkdir(parents=True, exist_ok=True)
    (destination_root / "index.md").write_text("".join(overview), encoding="utf-8")

    for source_directory, files in groups.items():
        relative_directory = source_directory.relative_to(source_root)
        if relative_directory == Path("."):
            # The overview already occupies the root index; root-level files are
            # linked there without replacing it.
            continue
        page_directory = destination_root / relative_directory
        page_directory.mkdir(parents=True, exist_ok=True)
        title = source_page_title(files[0], source_root)
        page = [f"# {title}\n\n", "[← 回到程式索引](../index.md)\n\n"]
        image_files = sorted(
            (
                path
                for path in source_directory.rglob("*")
                if path.is_file() and path.suffix.lower() in IMAGE_SUFFIXES
            ),
            key=lambda path: path.relative_to(source_directory).as_posix().lower(),
        )
        if image_files:
            page.extend(["## 題目圖片與解題筆記\n\n", '<div class="solution-images">\n'])
            for image_file in image_files:
                relative_image = image_file.relative_to(source_directory).as_posix()
                image_url = quote(relative_image)
                image_label = image_file.stem.replace("_", " ").replace("-", " ")
                escaped_label = html.escape(image_label)
                page.extend(
                    [
                        '  <figure class="solution-image">\n',
                        f'    <a href="{image_url}"><img src="{image_url}" alt="{escaped_label}" loading="lazy"></a>\n',
                        f"    <figcaption>{escaped_label}</figcaption>\n",
                        "  </figure>\n",
                    ]
                )
            page.extend(["</div>\n\n"])
        for source_file in files:
            copied_file = page_directory / source_file.name
            language = "cpp" if source_file.suffix.lower() == ".cpp" else "python"
            source_text = copied_file.read_text(encoding="utf-8", errors="replace").rstrip()
            page.extend(
                [
                    f"## `{source_file.name}`\n\n",
                    f"[開啟原始檔]({source_file.name}){{ .source-download }}\n\n",
                    f"````{language}\n{source_text}\n````\n\n",
                ]
            )
        (page_directory / "index.md").write_text("".join(page), encoding="utf-8")


def write_markdown_index(directory_name: str) -> None:
    """Create a searchable lesson index without editing source Markdown."""
    source_root = MATERIALS / directory_name
    destination_root = DESTINATION / directory_name
    markdown_files = sorted(
        source_root.glob("*.md"),
        key=lambda path: (not path.name.lower().startswith("learning route"), path.name.lower()),
    )

    overview = [
        f"# {directory_name} 教材索引\n\n",
        "所有教材都由建置程式自動整理；新增 Markdown 後，下次部署便會出現在這裡。\n\n",
        '<label class="source-search">\n',
        '  <span>搜尋教材</span>\n',
        '  <input type="search" placeholder="例如：二分搜尋" autocomplete="off">\n',
        '</label>\n\n',
        '<p class="source-count" aria-live="polite"></p>\n\n',
        '<div class="source-index lesson-index">\n',
    ]

    for markdown_file in markdown_files:
        title = markdown_title(markdown_file)
        target = f"{quote(markdown_file.stem)}/"
        search_text = html.escape(f"{title} {markdown_file.stem}".lower(), quote=True)
        overview.extend(
            [
                f'  <a class="source-card" href="{target}" data-source-search="{search_text}">\n',
                f'    <strong>{html.escape(title)}</strong>\n',
                f'    <span class="lesson-filename">{html.escape(markdown_file.name)}</span>\n',
                "  </a>\n",
            ]
        )

    overview.extend(['</div>\n\n', '<p class="source-empty" hidden>找不到符合的教材。</p>\n'])
    destination_root.mkdir(parents=True, exist_ok=True)
    (destination_root / "index.md").write_text("".join(overview), encoding="utf-8")


def write_generated_config() -> None:
    """Generate a collapsible sidebar that mirrors the material folders."""
    base_config = (ROOT / "mkdocs.yml").read_text(encoding="utf-8")
    base_config = re.sub(r"(?ms)^nav:\s*\n.*\Z", "", base_config).rstrip()

    nav = [
        "",
        "nav:",
        '  - "首頁": "index.md"',
    ]

    for directory_name, section_title in (("APCS", "APCS 課程"), ("codecat", "CodeCat")):
        markdown_files = sorted(
            (MATERIALS / directory_name).glob("*.md"),
            key=lambda path: (not path.name.lower().startswith("learning route"), path.name.lower()),
        )
        nav.extend(
            [
                f"  - {json.dumps(section_title, ensure_ascii=False)}:",
                f"      - \"教材索引\": {json.dumps(f'{directory_name}/index.md', ensure_ascii=False)}",
            ]
        )
        for markdown_file in markdown_files:
            title = json.dumps(markdown_title(markdown_file), ensure_ascii=False)
            target = json.dumps(f"{directory_name}/{markdown_file.name}", ensure_ascii=False)
            nav.append(f"      - {title}: {target}")

    cses_root = MATERIALS / "CSES_problem_set"
    cses_directories = sorted(
        (
            directory
            for directory in cses_root.rglob("*")
            if directory.is_dir()
            and any(path.suffix.lower() in {".cpp", ".py"} for path in directory.glob("*"))
        ),
        key=lambda path: path.relative_to(cses_root).as_posix().lower(),
    )
    nav.extend(
        [
            '  - "CSES Problem Set":',
            '      - "題目索引": "CSES_problem_set/index.md"',
        ]
    )
    for directory in cses_directories:
        relative_directory = directory.relative_to(cses_root).as_posix()
        label = json.dumps(relative_directory, ensure_ascii=False)
        target = json.dumps(f"CSES_problem_set/{relative_directory}/index.md", ensure_ascii=False)
        nav.append(f"      - {label}: {target}")

    zerojudge_root = MATERIALS / "ZeroJudge"
    problem_directories = sorted(
        (
            directory
            for directory in zerojudge_root.iterdir()
            if directory.is_dir()
            and any(path.suffix.lower() in {".cpp", ".py"} for path in directory.rglob("*"))
        ),
        key=lambda path: path.name.lower(),
    )
    nav.extend(['  - "ZeroJudge 題解":', '      - "題目索引": "ZeroJudge/index.md"'])
    for letter in sorted({directory.name[0].upper() for directory in problem_directories}):
        nav.append(f'      - "{letter} 系列":')
        for directory in (item for item in problem_directories if item.name[0].upper() == letter):
            label = json.dumps(directory.name, ensure_ascii=False)
            target = json.dumps(f"ZeroJudge/{directory.name}/index.md", ensure_ascii=False)
            nav.append(f"          - {label}: {target}")

    tqc_root = MATERIALS / "TQC python"
    tqc_directories = sorted(
        (
            directory
            for directory in tqc_root.rglob("*")
            if directory.is_dir()
            and any(path.suffix.lower() in {".cpp", ".py"} for path in directory.glob("*"))
        ),
        key=lambda path: path.relative_to(tqc_root).as_posix().lower(),
    )
    nav.extend(['  - "TQC Python":', '      - "程式索引": "TQC python/index.md"'])
    for directory in tqc_directories:
        relative_directory = directory.relative_to(tqc_root).as_posix()
        label = json.dumps(relative_directory, ensure_ascii=False)
        target = json.dumps(f"TQC python/{relative_directory}/index.md", ensure_ascii=False)
        nav.append(f"      - {label}: {target}")

    nav.append("")
    GENERATED_CONFIG.write_text(base_config + "\n" + "\n".join(nav), encoding="utf-8")


def main() -> None:
    if DESTINATION.exists():
        shutil.rmtree(DESTINATION)
    DESTINATION.mkdir()

    # MkDocs expects the homepage to be named index.md. Keep README.md untouched.
    shutil.copy2(ROOT / "README.md", DESTINATION / "index.md")
    normalize_markdown_tables(DESTINATION / "index.md")

    shutil.copytree(ROOT / "website", DESTINATION, dirs_exist_ok=True)

    for directory_name in SOURCE_DIRECTORIES:
        source = MATERIALS / directory_name
        copy_published_files(source, DESTINATION / directory_name)

    write_source_index("ZeroJudge")
    write_source_index("CSES_problem_set", "CSES Problem Set")
    write_source_index("TQC python")
    write_markdown_index("APCS")
    write_markdown_index("codecat")
    write_generated_config()


if __name__ == "__main__":
    main()
