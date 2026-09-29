document.addEventListener("DOMContentLoaded", () => {
  const search = document.querySelector(".source-search input");
  const cards = [...document.querySelectorAll(".source-card")];
  const count = document.querySelector(".source-count");
  const empty = document.querySelector(".source-empty");
  const letterButtons = [...document.querySelectorAll("[data-source-letter]")].filter(
    (element) => element.tagName === "BUTTON"
  );
  const groups = [...document.querySelectorAll("[data-source-group]")];
  const problemIndex = document.querySelector("[data-problem-index]");
  const difficultySelect = document.querySelector("[data-problem-difficulty]");
  const topicSelect = document.querySelector("[data-problem-topic]");
  const sortSelect = document.querySelector("[data-problem-sort]");
  const resetButton = document.querySelector("[data-problem-reset]");
  const programSource = document.querySelector("[data-program-source]");
  const programLanguage = document.querySelector("[data-program-language]");
  const programReset = document.querySelector("[data-program-reset]");
  const programTagButtons = [...document.querySelectorAll("[data-program-tag]")];
  const selectedProgramTags = new Set();
  let selectedLetter = "all";

  if (!search || cards.length === 0) return;

  const update = () => {
    const query = search.value.trim().toLowerCase();
    let visible = 0;

    cards.forEach((card) => {
      const matchesQuery = card.dataset.sourceSearch.includes(query);
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

    count.textContent = `顯示 ${visible} / ${cards.length} 個項目`;
    empty.hidden = visible !== 0;
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
      const active = selectedProgramTags.has(tag);
      button.classList.toggle("is-active", active);
      button.setAttribute("aria-pressed", String(active));
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
});
