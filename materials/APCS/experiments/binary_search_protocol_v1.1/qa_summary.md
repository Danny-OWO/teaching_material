# Binary Search Protocol v1.1 — QA Summary

QA date: 2026-11-13 (Asia/Taipei)

## Result

All hard gates passed. The revised lesson is publishable as an experiment alongside the original `binary_search.md`.

## Factual Correctness

- Verified the closed-interval implementation against empty, single-element, endpoint, absent-target and out-of-range cases.
- Exhaustively checked Python exact search for targets from -25 through 25 against a sorted range from -20 through 20.
- Compiled the C++ implementation with `g++ -std=c++17 -Wall -Wextra -pedantic` and executed assertions.
- Verified `lower_bound([1,3,3,3,5,7], 3) == 1` and `upper_bound(...) == 4` in both C++ and Python.
- Verified that searching for 100 returns C++ `end()` and Python `len(a)` rather than a safe-to-dereference element.
- Cross-checked semantics with the Python `bisect` documentation and the C++ working draft.

## Coverage & Alignment

| Learning objective | Lesson evidence | Assessment evidence |
|---|---|---|
| LO1 applicability | Sections 1–2, 12 | 13A, 13E |
| LO2 interval tracing | Sections 3–5 | Section 5 check, 13B |
| LO3 implementation | Sections 6–7 | Edge-case table, 13C |
| LO4 complexity | Section 8 | 13A, 13E |
| LO5 boundary search | Section 9 | 13D |
| LO6 standard tools | Sections 10–11 | 13A, 13D |
| LO7 strategy choice | Sections 8, 13E | 13E |

No required objective is left without teaching content or an assessment opportunity.

## Pedagogical and Communication Review

- The phone-book story is followed by an explicit concept mapping and failure boundary.
- Worked examples precede implementation.
- The closed-interval convention is used consistently throughout the hand-written algorithm.
- Common failure modes are tied to counterexamples rather than merely listed.
- One-shot timing claims from the source lesson were replaced by a derivation and a measurement caveat.
- Exact search, lower bound and upper bound are separated as different questions.

## Site Verification

- `python tools/prepare_mkdocs.py`: passed.
- `mkdocs build --strict -f .mkdocs.generated.yml`: passed.
- Generated page exists at `site/APCS/binary_search_protocol_v1.1/index.html`.
- Generated navigation contains the new lesson.
- Referenced image exists at `site/APCS/resources/tomolin.jpg`.
- Native `<details>` answer blocks were confirmed in generated HTML.

## Corrected Source-Lesson Defects

- Removed the mismatch where an `upper_bound` explanation used a `lower_bound` iterator.
- Added mandatory range checks before dereferencing a returned boundary position.
- Distinguished insertion positions from successful exact matches.
- Removed binary-search-tree exercises from the binary-search learning path.
- Replaced a single noisy benchmark result with complexity reasoning.

## Verification Not Performed

- No real student trial or teacher classroom observation was performed.
- External exercise links were not used as evidence for technical correctness.
- Responsive layout was not manually tested across multiple physical devices.

These are not hard-gate failures for the current experimental publication, but student confusion observed during teaching should feed back into a later revision.
