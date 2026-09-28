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
      const matches = matchesQuery && matchesLetter && matchesDifficulty && matchesTopic;
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
  resetButton?.addEventListener("click", () => {
    search.value = "";
    if (difficultySelect) difficultySelect.value = "all";
    if (topicSelect) topicSelect.value = "all";
    if (sortSelect) sortSelect.value = "route";
    update();
  });
  update();
});
