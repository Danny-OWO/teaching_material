"""Prepare an isolated MkDocs source tree without editing teaching materials."""

from pathlib import Path
import shutil


ROOT = Path(__file__).resolve().parents[1]
DESTINATION = ROOT / ".mkdocs-docs"
SOURCE_DIRECTORIES = ("APCS", "TQC python", "ZeroJudge")
PUBLISHED_SUFFIXES = {".md", ".txt", ".jpg", ".jpeg", ".png", ".gif", ".svg", ".cpp", ".py"}


def normalize_markdown_tables(path: Path) -> None:
    """Normalize Docsify-tolerated Markdown syntax in the isolated build copy."""
    text = path.read_text(encoding="utf-8")
    text = text.replace(
        '<div style="font-size: 18px; line-height: 2;">',
        '<div markdown="1" class="problem-list">',
    )
    lines = text.splitlines(keepends=True)
    normalized: list[str] = []

    for index, line in enumerate(lines):
        next_line = lines[index + 1] if index + 1 < len(lines) else ""
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


def main() -> None:
    if DESTINATION.exists():
        shutil.rmtree(DESTINATION)
    DESTINATION.mkdir()

    # MkDocs expects the homepage to be named index.md. Keep README.md untouched.
    shutil.copy2(ROOT / "README.md", DESTINATION / "index.md")
    normalize_markdown_tables(DESTINATION / "index.md")

    shutil.copytree(ROOT / "website", DESTINATION, dirs_exist_ok=True)

    for directory_name in SOURCE_DIRECTORIES:
        source = ROOT / directory_name
        copy_published_files(source, DESTINATION / directory_name)


if __name__ == "__main__":
    main()
