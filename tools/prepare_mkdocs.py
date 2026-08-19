"""Prepare an isolated MkDocs source tree without editing teaching materials."""

from pathlib import Path
import html
import re
import shutil


ROOT = Path(__file__).resolve().parents[1]
DESTINATION = ROOT / ".mkdocs-docs"
MATERIALS = ROOT / "materials"
SOURCE_DIRECTORIES = ("APCS", "TQC python", "ZeroJudge")
PUBLISHED_SUFFIXES = {".md", ".txt", ".jpg", ".jpeg", ".png", ".gif", ".svg", ".cpp", ".py"}


def normalize_markdown_tables(path: Path) -> None:
    """Normalize Docsify-tolerated Markdown syntax in the isolated build copy."""
    text = path.read_text(encoding="utf-8")
    text = text.replace(
        '<div style="font-size: 18px; line-height: 2;">',
        '<div markdown="1" class="problem-list">',
    )
    text = text.replace('src="./resources\\', 'src="../resources/')
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


def write_source_index(directory_name: str) -> None:
    """Create navigable source-code pages in the disposable build tree."""
    source_root = MATERIALS / directory_name
    destination_root = DESTINATION / directory_name
    source_files = sorted(
        (path for path in source_root.rglob("*") if path.suffix.lower() in {".cpp", ".py"}),
        key=lambda path: path.relative_to(source_root).as_posix().lower(),
    )
    groups: dict[Path, list[Path]] = {}
    for source_file in source_files:
        groups.setdefault(source_file.parent, []).append(source_file)

    overview = [
        f"# {directory_name} 程式索引\n\n",
        "選擇題目或章節，即可閱讀及下載原始程式碼。\n\n",
        '<label class="source-search">\n',
        '  <span>搜尋題號</span>\n',
        '  <input type="search" placeholder="例如：b923" autocomplete="off">\n',
        '</label>\n\n',
        '<p class="source-count" aria-live="polite"></p>\n\n',
        '<div class="source-index">\n',
    ]
    for source_directory in groups:
        relative_directory = source_directory.relative_to(source_root)
        label = source_page_title(groups[source_directory][0], source_root)
        target = "./" if relative_directory == Path(".") else f"{relative_directory.as_posix()}/"
        languages = sorted(
            {"C++" if path.suffix.lower() == ".cpp" else "Python" for path in groups[source_directory]}
        )
        language_badges = "".join(f"<span>{html.escape(language)}</span>" for language in languages)
        search_text = html.escape(f"{label} {' '.join(languages)}".lower(), quote=True)
        overview.extend(
            [
                f'  <a class="source-card" href="{html.escape(target, quote=True)}" data-source-search="{search_text}">\n',
                f'    <strong>{html.escape(label)}</strong>\n',
                f'    <span class="source-languages">{language_badges}</span>\n',
                "  </a>\n",
            ]
        )
    overview.extend(['</div>\n\n', '<p class="source-empty" hidden>找不到符合的題目。</p>\n'])
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
    write_source_index("TQC python")


if __name__ == "__main__":
    main()
