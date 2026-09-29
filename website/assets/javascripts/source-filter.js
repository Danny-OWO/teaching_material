const initializeSourceFilter = () => {
  const programCatalog = document.querySelector("[data-program-catalog]");
  const root = programCatalog ?? document;
  const search = root.querySelector(".source-search input");
  const cards = [...root.querySelectorAll(".source-card")];
  const count = root.querySelector(".source-count");
  const empty = root.querySelector(".source-empty");
  const letterButtons = [...root.querySelectorAll("[data-source-letter]")].filter(
    (element) => element.tagName === "BUTTON"
  );
  const groups = [...root.querySelectorAll("[data-source-group]")];
  const problemIndex = root.querySelector("[data-problem-index]");
  const difficultySelect = root.querySelector("[data-problem-difficulty]");
  const topicSelect = root.querySelector("[data-problem-topic]");
  const sortSelect = root.querySelector("[data-problem-sort]");
  const resetButton = root.querySelector("[data-problem-reset]");
  const programSource = root.querySelector("select[data-program-source]");
  const programLanguage = root.querySelector("select[data-program-language]");
  const programReset = root.querySelector("button[data-program-reset]");
  const programSelection = root.querySelector("[data-program-selection]");
  const programTagButtons = [...root.querySelectorAll("[data-program-tag]")];
  const selectedProgramTags = new Set();
  let selectedLetter = "all";

  if (!search || cards.length === 0 || search.dataset.filterReady === "true") return;
  search.dataset.filterReady = "true";

  const normalize = (value) => value.normalize("NFKC").trim().toLocaleLowerCase("zh-Hant");

  const update = () => {
    const queryTerms = normalize(search.value).split(/\s+/).filter(Boolean);
    let visible = 0;

    cards.forEach((card) => {
      const haystack = normalize(card.dataset.sourceSearch ?? "");
      const matchesQuery = queryTerms.every((term) => haystack.includes(term));
      const matchesLetter =
        selectedLetter === "all" || card.dataset.sourceLetter === selectedLetter;
      const selectedDifficulty = difficultySelect?.value ?? "all";
      const selectedTopic = topicSelect?.value ?? "all";
      const cardTopics = (card.dataset.problemTopic ?? "").split(" ");
      const matchesDifficulty =
        selectedDifficulty === "all" || card.dataset.problemDifficulty === selectedDifficulty;
      const matchesTopic = selectedTopic === "all" || cardTopics.includes(selectedTopic);
      const selectedSource = programSource?.value ?? "all";
      const selectedLanguage = programLanguage?.value ?? "all";
      const programTags = (card.dataset.programTags ?? "").split("|").filter(Boolean);
      const matchesSource = selectedSource === "all" || card.dataset.programSource === selectedSource;
      const matchesLanguage =
        selectedLanguage === "all" || card.dataset.programLanguage === selectedLanguage;
      const matchesProgramTags = [...selectedProgramTags].every((tag) => programTags.includes(tag));
      const matches =
        matchesQuery && matchesLetter && matchesDifficulty && matchesTopic &&
        matchesSource && matchesLanguage && matchesProgramTags;
      card.hidden = !matches;
      if (matches) visible += 1;
    });

    if (problemIndex && sortSelect) {
      const sortKey = sortSelect.value;
      const sortedCards = [...cards].sort((left, right) => {
        if (sortKey === "title") {
          return left.dataset.problemTitle.localeCompare(right.dataset.problemTitle, "zh-Hant");
        }
        const field = sortKey === "difficulty" ? "problemDifficultyOrder" : "problemRouteOrder";
        const difference = Number(left.dataset[field]) - Number(right.dataset[field]);
        return difference || Number(left.dataset.problemRouteOrder) - Number(right.dataset.problemRouteOrder);
      });
      sortedCards.forEach((card) => problemIndex.append(card));
    }

    groups.forEach((group) => {
      group.hidden = ![...group.querySelectorAll(".source-card")].some(
        (card) => !card.hidden
      );
    });

    if (count) {
      const noun = programCatalog ? "個程式" : "個項目";
      count.textContent = `${visible} / ${cards.length} ${noun}`;
    }
    if (empty) empty.hidden = visible !== 0;
    if (programSelection) {
      programSelection.textContent = selectedProgramTags.size
        ? `已選 ${selectedProgramTags.size} 個：${[...selectedProgramTags].join("、")}`
        : "尚未選取標籤";
    }
  };

  letterButtons.forEach((button) => {
    button.addEventListener("click", () => {
      selectedLetter = button.dataset.sourceLetter;
      letterButtons.forEach((candidate) => {
        const active = candidate === button;
        candidate.classList.toggle("is-active", active);
        candidate.setAttribute("aria-pressed", String(active));
      });
      update();
    });
  });

  search.addEventListener("input", update);
  difficultySelect?.addEventListener("change", update);
  topicSelect?.addEventListener("change", update);
  sortSelect?.addEventListener("change", update);
  programSource?.addEventListener("change", update);
  programLanguage?.addEventListener("change", update);
  programTagButtons.forEach((button) => {
    button.addEventListener("click", () => {
      const tag = button.dataset.programTag;
      if (selectedProgramTags.has(tag)) {
        selectedProgramTags.delete(tag);
      } else {
        selectedProgramTags.add(tag);
      }
      programTagButtons.forEach((candidate) => {
        if (candidate.dataset.programTag !== tag) return;
        const active = selectedProgramTags.has(tag);
        candidate.classList.toggle("is-active", active);
        candidate.setAttribute("aria-pressed", String(active));
      });
      update();
    });
  });
  resetButton?.addEventListener("click", () => {
    search.value = "";
    if (difficultySelect) difficultySelect.value = "all";
    if (topicSelect) topicSelect.value = "all";
    if (sortSelect) sortSelect.value = "route";
    update();
  });
  programReset?.addEventListener("click", () => {
    search.value = "";
    if (programSource) programSource.value = "all";
    if (programLanguage) programLanguage.value = "all";
    selectedProgramTags.clear();
    programTagButtons.forEach((button) => {
      button.classList.remove("is-active");
      button.setAttribute("aria-pressed", "false");
    });
    update();
  });
  update();
};

if (typeof document$ !== "undefined") {
  document$.subscribe(initializeSourceFilter);
} else if (document.readyState === "loading") {
  document.addEventListener("DOMContentLoaded", initializeSourceFilter);
} else {
  initializeSourceFilter();
}
