"""Prepare an isolated MkDocs source tree without editing teaching materials."""

from pathlib import Path
import shutil


ROOT = Path(__file__).resolve().parents[1]
DESTINATION = ROOT / ".mkdocs-docs"
SOURCE_DIRECTORIES = ("APCS", "TQC python", "ZeroJudge")
PUBLISHED_SUFFIXES = {".md", ".txt", ".jpg", ".jpeg", ".png", ".gif", ".svg", ".cpp", ".py"}


def copy_published_files(source: Path, destination: Path) -> None:
    for path in source.rglob("*"):
        if not path.is_file() or path.suffix.lower() not in PUBLISHED_SUFFIXES:
            continue
        target = destination / path.relative_to(source)
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(path, target)


def main() -> None:
    if DESTINATION.exists():
        shutil.rmtree(DESTINATION)
    DESTINATION.mkdir()

    # MkDocs expects the homepage to be named index.md. Keep README.md untouched.
    shutil.copy2(ROOT / "README.md", DESTINATION / "index.md")

    for directory_name in SOURCE_DIRECTORIES:
        source = ROOT / directory_name
        copy_published_files(source, DESTINATION / directory_name)


if __name__ == "__main__":
    main()

