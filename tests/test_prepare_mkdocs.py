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


class PerFileProblemMetadataTests(unittest.TestCase):
    def make_directory(self, temporary_directory, manifest, sources=("sample.py",)):
        directory = Path(temporary_directory) / "exercises"
        directory.mkdir()
        for source in sources:
            (directory / source).write_text("print(1)\n", encoding="utf-8")
        (directory / "_problems.yml").write_text(manifest, encoding="utf-8")
        return directory

    def test_manifest_metadata_is_shared_by_cpp_and_python_with_the_same_stem(self):
        with tempfile.TemporaryDirectory() as temporary_directory:
            directory = self.make_directory(
                temporary_directory,
                """sample:
  title: Shared Exercise
  difficulty: medium
  topics: arrays
  patterns:
    - simulation
  techniques: counting
""",
                sources=("sample.cpp", "sample.py"),
            )

            metadata = prepare_mkdocs.per_file_problem_metadata(directory)

            self.assertEqual(list(metadata), ["sample"])
            self.assertEqual(metadata["sample"]["title"], "Shared Exercise")
            self.assertEqual(metadata["sample"]["topics"], ["arrays"])
            self.assertEqual(metadata["sample"]["techniques"], ["counting"])

    def test_manifest_normalizes_an_unquoted_integer_key_to_a_source_stem(self):
        with tempfile.TemporaryDirectory() as temporary_directory:
            directory = self.make_directory(
                temporary_directory,
                """101:
  title: Numeric Exercise
  difficulty: easy
  topics: arithmetic
  patterns: simulation
""",
                sources=("101.py",),
            )

            metadata = prepare_mkdocs.per_file_problem_metadata(directory)

            self.assertEqual(list(metadata), ["101"])
            self.assertEqual(metadata["101"]["title"], "Numeric Exercise")

    def test_manifest_rejects_invalid_key_types_and_normalized_collisions(self):
        cases = (
            (
                "true:\n  title: Invalid\n  difficulty: easy\n  topics: loops\n  patterns: simulation\n",
                "Manifest key True.*must be a string or integer",
            ),
            (
                "1.5:\n  title: Invalid\n  difficulty: easy\n  topics: loops\n  patterns: simulation\n",
                "Manifest key 1.5.*must be a string or integer",
            ),
            (
                """101:
  title: First
  difficulty: easy
  topics: arithmetic
  patterns: simulation
"101":
  title: Second
  difficulty: medium
  topics: arithmetic
  patterns: counting
""",
                "duplicate source stem after key normalization: 101",
            ),
        )
        for manifest, message in cases:
            with self.subTest(manifest=manifest):
                with tempfile.TemporaryDirectory() as temporary_directory:
                    directory = self.make_directory(
                        temporary_directory, manifest, sources=("101.py",)
                    )
                    with self.assertRaisesRegex(ValueError, message):
                        prepare_mkdocs.per_file_problem_metadata(directory)

    def test_manifest_rejects_malformed_root_and_entry(self):
        cases = (
            ("- not\n- a mapping\n", "Manifest .* must be a mapping"),
            ("sample:\n  - not a mapping\n", "Entry 'sample'.* must be a mapping"),
        )
        for manifest, message in cases:
            with self.subTest(manifest=manifest):
                with tempfile.TemporaryDirectory() as temporary_directory:
                    directory = self.make_directory(temporary_directory, manifest)
                    with self.assertRaisesRegex(ValueError, message):
                        prepare_mkdocs.per_file_problem_metadata(directory)

    def test_manifest_reuses_required_fields_and_difficulty_validation(self):
        cases = (
            (
                "sample:\n  title: Missing\n  difficulty: easy\n  topics: loops\n",
                "missing required metadata: patterns",
            ),
            (
                "sample:\n  title: Invalid\n  difficulty: expert\n  topics: loops\n  patterns: simulation\n",
                "invalid difficulty: expert",
            ),
        )
        for manifest, message in cases:
            with self.subTest(manifest=manifest):
                with tempfile.TemporaryDirectory() as temporary_directory:
                    directory = self.make_directory(temporary_directory, manifest)
                    with self.assertRaisesRegex(ValueError, message):
                        prepare_mkdocs.per_file_problem_metadata(directory)

    def test_manifest_rejects_unknown_source_stem(self):
        with tempfile.TemporaryDirectory() as temporary_directory:
            directory = self.make_directory(
                temporary_directory,
                """missing:
  title: Missing Source
  difficulty: easy
  topics: loops
  patterns: simulation
""",
            )

            with self.assertRaisesRegex(ValueError, "unknown source stem: missing"):
                prepare_mkdocs.per_file_problem_metadata(directory)

    def test_directory_problem_note_takes_precedence_over_manifest(self):
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            materials = root / "materials"
            destination = root / "destination"
            directory = materials / "Collection" / "sample"
            directory.mkdir(parents=True)
            (directory / "sample.py").write_text("print(1)\n", encoding="utf-8")
            (directory / "problem.md").write_text(
                """---
title: Directory Title
difficulty: easy
topics: loops
patterns: simulation
---
Directory notes.
""",
                encoding="utf-8",
            )
            (directory / "_problems.yml").write_text(
                "- deliberately malformed and ignored\n", encoding="utf-8"
            )

            with patch.object(prepare_mkdocs, "MATERIALS", materials), patch.object(
                prepare_mkdocs, "DESTINATION", destination
            ):
                prepare_mkdocs.write_program_catalog()

            catalog = (destination / "programs" / "index.md").read_text(encoding="utf-8")
            self.assertIn("Directory Title", catalog)
            self.assertIn('data-program-difficulty="easy"', catalog)

    def test_catalog_uses_per_file_title_difficulty_and_tags(self):
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            materials = root / "materials"
            destination = root / "destination"
            directory = materials / "Loose" / "chapter"
            directory.mkdir(parents=True)
            (directory / "search.cpp").write_text("int main() {}\n", encoding="utf-8")
            (directory / "search.py").write_text("print('done')\n", encoding="utf-8")
            (directory / "_problems.yml").write_text(
                """search:
  title: Curated Search
  difficulty: hard
  topics: graphs
  patterns: breadth-first-search
  techniques: queue
""",
                encoding="utf-8",
            )

            with patch.object(prepare_mkdocs, "MATERIALS", materials), patch.object(
                prepare_mkdocs, "DESTINATION", destination
            ):
                prepare_mkdocs.write_program_catalog()

            catalog = (destination / "programs" / "index.md").read_text(encoding="utf-8")
            self.assertEqual(catalog.count("<strong>Curated Search</strong>"), 1)
            self.assertIn('data-program-difficulty="hard"', catalog)
            self.assertIn('data-program-tags="graphs|breadth-first-search|queue"', catalog)
            self.assertIn("C++ / Python", catalog)

    def test_catalog_keeps_different_stems_with_the_same_curated_title_separate(self):
        with tempfile.TemporaryDirectory() as temporary_directory:
            root = Path(temporary_directory)
            materials = root / "materials"
            destination = root / "destination"
            directory = materials / "Loose" / "chapter"
            directory.mkdir(parents=True)
            (directory / "first.py").write_text("print('first')\n", encoding="utf-8")
            (directory / "second.py").write_text("print('second')\n", encoding="utf-8")
            (directory / "_problems.yml").write_text(
                """first:
  title: Shared Display Title
  difficulty: easy
  topics: loops
  patterns: simulation
second:
  title: Shared Display Title
  difficulty: hard
  topics: arrays
  patterns: counting
""",
                encoding="utf-8",
            )

            with patch.object(prepare_mkdocs, "MATERIALS", materials), patch.object(
                prepare_mkdocs, "DESTINATION", destination
            ):
                prepare_mkdocs.write_program_catalog()

            catalog = (destination / "programs" / "index.md").read_text(encoding="utf-8")
            self.assertEqual(catalog.count("<strong>Shared Display Title</strong>"), 2)
            self.assertIn("#source-first-py", catalog)
            self.assertIn("#source-second-py", catalog)


class SourcePageMetadataTests(unittest.TestCase):
    def make_page(self, root, files, manifest=None, note=None):
        materials = root / "materials"
        destination = root / "destination"
        directory = materials / "TQC" / "chapter"
        directory.mkdir(parents=True)
        for name, contents in files.items():
            (directory / name).write_text(contents, encoding="utf-8")
            copied = destination / "TQC" / "chapter" / name
            copied.parent.mkdir(parents=True, exist_ok=True)
            copied.write_text(contents, encoding="utf-8")
        if manifest is not None:
            (directory / "_problems.yml").write_text(manifest, encoding="utf-8")
        if note is not None:
            (directory / "problem.md").write_text(note, encoding="utf-8")

        with patch.object(prepare_mkdocs, "MATERIALS", materials), patch.object(
            prepare_mkdocs, "DESTINATION", destination
        ):
            prepare_mkdocs.write_source_index("TQC")
        return (destination / "TQC" / "chapter" / "index.md").read_text(encoding="utf-8")

    def test_tqc_files_use_their_own_titles_and_tags(self):
        with tempfile.TemporaryDirectory() as temporary_directory:
            page = self.make_page(
                Path(temporary_directory),
                {"101.py": "print(1)\n", "102.py": "print(2)\n"},
                manifest="""101:
  title: First Exercise
  difficulty: easy
  topics: [arithmetic]
  patterns: [simulation]
102:
  title: Second Exercise
  difficulty: medium
  topics: [strings]
  patterns: [formatting]
""",
            )

        first, second = page.split('<a id="source-102-py"></a>')
        self.assertIn('<a id="source-101-py"></a>', first)
        self.assertIn("## `101.py` — First Exercise", first)
        self.assertIn("First Exercise 的一份可執行解法", first)
        self.assertIn(">arithmetic</span>", first)
        self.assertIn(">simulation</span>", first)
        self.assertNotIn(">strings</span>", first)
        self.assertIn("[開啟原始檔](101.py){ .source-download }", first)
        self.assertIn("## `102.py` — Second Exercise", second)
        self.assertIn("Second Exercise 的一份可執行解法", second)
        self.assertIn(">strings</span>", second)
        self.assertIn(">formatting</span>", second)
        self.assertNotIn(">arithmetic</span>", second)
        self.assertIn("[開啟原始檔](102.py){ .source-download }", second)

    def test_directory_note_takes_precedence_over_manifest_on_source_page(self):
        with tempfile.TemporaryDirectory() as temporary_directory:
            page = self.make_page(
                Path(temporary_directory),
                {"101.py": "print(1)\n"},
                manifest="- invalid manifest that must be ignored\n",
                note="""---
title: Directory Exercise
difficulty: easy
topics: [directory-topic]
patterns: [directory-pattern]
---
Directory notes.
""",
            )

        self.assertIn("# Directory Exercise", page)
        self.assertIn("Directory notes.", page)
        self.assertIn("## `101.py`\n\n", page)
        self.assertIn("Directory Exercise 的一份可執行解法", page)
        self.assertIn(">directory-topic</span>", page)
        self.assertIn(">directory-pattern</span>", page)
        self.assertIn('<a id="source-101-py"></a>', page)
        self.assertIn("[開啟原始檔](101.py){ .source-download }", page)

    def test_directory_without_manifest_keeps_existing_source_page_output(self):
        with tempfile.TemporaryDirectory() as temporary_directory:
            page = self.make_page(
                Path(temporary_directory), {"101.py": "print(1)\n"}
            )
            self.assertEqual(
                page,
                "# chapter\n\n"
                "[← 回到程式索引](../index.md)\n\n"
                '<a id="source-101-py"></a>\n\n'
                "## `101.py`\n\n"
                + prepare_mkdocs.source_explanation(
                    Path(temporary_directory) / "materials" / "TQC" / "chapter" / "101.py",
                    "chapter",
                )
                + "[開啟原始檔](101.py){ .source-download }\n\n"
                "````python\nprint(1)\n````\n\n",
            )


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
