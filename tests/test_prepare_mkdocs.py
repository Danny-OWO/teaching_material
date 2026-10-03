import tempfile
import unittest
from contextlib import ExitStack
from pathlib import Path
from unittest.mock import patch

from tools import prepare_mkdocs


class FrontmatterTests(unittest.TestCase):
    def test_read_frontmatter_returns_mapping_and_body(self):
        with tempfile.TemporaryDirectory() as temporary_directory:
            note = Path(temporary_directory) / "lesson.md"
            note.write_text(
                "---\ntitle: Sample\ntopics:\n  - loops\n---\n# Lesson\n\nBody.\n",
                encoding="utf-8",
            )

            metadata, body = prepare_mkdocs.read_frontmatter(note)

            self.assertEqual(metadata, {"title": "Sample", "topics": ["loops"]})
            self.assertEqual(body, "# Lesson\n\nBody.\n")

    def test_read_frontmatter_rejects_non_mapping_yaml(self):
        with tempfile.TemporaryDirectory() as temporary_directory:
            note = Path(temporary_directory) / "lesson.md"
            note.write_text("---\n- first\n- second\n---\nBody\n", encoding="utf-8")

            with self.assertRaisesRegex(ValueError, "must be a mapping"):
                prepare_mkdocs.read_frontmatter(note)


class ProblemMetadataTests(unittest.TestCase):
    def write_problem(self, temporary_directory, frontmatter):
        problem_directory = Path(temporary_directory) / "problem"
        problem_directory.mkdir()
        (problem_directory / "problem.md").write_text(
            f"---\n{frontmatter}---\nExplanation.\n", encoding="utf-8"
        )
        return problem_directory

    def test_problem_metadata_requires_all_required_fields(self):
        with tempfile.TemporaryDirectory() as temporary_directory:
            problem_directory = self.write_problem(
                temporary_directory,
                "title: Missing patterns\ndifficulty: easy\ntopics: loops\n",
            )

            with self.assertRaisesRegex(ValueError, "missing required metadata: patterns"):
                prepare_mkdocs.problem_metadata(problem_directory)

    def test_problem_metadata_rejects_invalid_difficulty(self):
        with tempfile.TemporaryDirectory() as temporary_directory:
            problem_directory = self.write_problem(
                temporary_directory,
                "title: Invalid\ndifficulty: expert\ntopics: loops\npatterns: simulation\n",
            )

            with self.assertRaisesRegex(ValueError, "invalid difficulty: expert"):
                prepare_mkdocs.problem_metadata(problem_directory)

    def test_problem_metadata_normalizes_scalar_and_list_values(self):
        with tempfile.TemporaryDirectory() as temporary_directory:
            problem_directory = self.write_problem(
                temporary_directory,
                """title: Normalized
difficulty: MEDIUM
topics: loops
patterns:
  - simulation
  - counting
techniques: prefix sum
prerequisites:
  - arrays
pitfalls: off-by-one
""",
            )

            metadata, body = prepare_mkdocs.problem_metadata(problem_directory)

            self.assertEqual(metadata["difficulty"], "medium")
            self.assertEqual(metadata["topics"], ["loops"])
            self.assertEqual(metadata["patterns"], ["simulation", "counting"])
            self.assertEqual(metadata["techniques"], ["prefix sum"])
            self.assertEqual(metadata["prerequisites"], ["arrays"])
            self.assertEqual(metadata["pitfalls"], ["off-by-one"])
            self.assertEqual(body, "Explanation.\n")


class MainSmokeTests(unittest.TestCase):
    def test_main_builds_an_isolated_documentation_tree(self):
        with tempfile.TemporaryDirectory() as temporary_directory:
            temporary_root = Path(temporary_directory)
            root = temporary_root / "fixture-project"
            destination = temporary_root / "generated-docs"
            generated_config = temporary_root / "generated-mkdocs.yml"
            materials = root / "materials"

            (root / "website" / "assets").mkdir(parents=True)
            (root / "website" / "assets" / "fixture.txt").write_text(
                "website asset\n", encoding="utf-8"
            )
            (root / "README.md").write_text("# Fixture Home\n", encoding="utf-8")
            (root / "mkdocs.yml").write_text(
                "site_name: Fixture\ndocs_dir: .mkdocs-docs\nnav:\n  - Old: old.md\n",
                encoding="utf-8",
            )

            lesson_directory = materials / "Lessons"
            lesson_directory.mkdir(parents=True)
            (lesson_directory / "intro.md").write_text(
                "# Fixture Introduction\n\nWelcome.\n", encoding="utf-8"
            )

            problem_directory = materials / "Problems" / "sample"
            problem_directory.mkdir(parents=True)
            (problem_directory / "problem.md").write_text(
                """---
title: Fixture Challenge
difficulty: easy
topics: loops
patterns: simulation
---
## Approach

Repeat once per input.
""",
                encoding="utf-8",
            )
            (problem_directory / "solution.py").write_text(
                "for value in range(3):\n    print(value)\n", encoding="utf-8"
            )

            with ExitStack() as patches:
                patches.enter_context(patch.object(prepare_mkdocs, "ROOT", root))
                patches.enter_context(patch.object(prepare_mkdocs, "DESTINATION", destination))
                patches.enter_context(
                    patch.object(prepare_mkdocs, "GENERATED_CONFIG", generated_config)
                )
                patches.enter_context(patch.object(prepare_mkdocs, "MATERIALS", materials))
                prepare_mkdocs.main()

            self.assertEqual(
                (destination / "index.md").read_text(encoding="utf-8"),
                "# Fixture Home\n",
            )
            lesson_index = (destination / "Lessons" / "index.md").read_text(
                encoding="utf-8"
            )
            self.assertIn("# Lessons 教材索引", lesson_index)
            self.assertIn("Fixture Introduction", lesson_index)

            program_index = (destination / "programs" / "index.md").read_text(
                encoding="utf-8"
            )
            self.assertIn("# 程式標籤搜尋", program_index)
            self.assertIn("Fixture Challenge", program_index)

            problem_page = (destination / "Problems" / "sample" / "index.md").read_text(
                encoding="utf-8"
            )
            self.assertIn("# Fixture Challenge", problem_page)
            self.assertIn("Repeat once per input.", problem_page)
            self.assertIn("for value in range(3):", problem_page)

            config = generated_config.read_text(encoding="utf-8")
            self.assertIn('  - "首頁": "index.md"', config)
            self.assertIn('  - "程式標籤搜尋": "programs/index.md"', config)
            self.assertIn('"Fixture Challenge": "Problems/sample/index.md"', config)
            self.assertTrue((destination / "assets" / "fixture.txt").is_file())


if __name__ == "__main__":
    unittest.main()
