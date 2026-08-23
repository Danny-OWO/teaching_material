document.addEventListener("DOMContentLoaded", () => {
  const search = document.querySelector(".source-search input");
  const cards = [...document.querySelectorAll(".source-card")];
  const count = document.querySelector(".source-count");
  const empty = document.querySelector(".source-empty");
  const letterButtons = [...document.querySelectorAll("[data-source-letter]")].filter(
    (element) => element.tagName === "BUTTON"
  );
  const groups = [...document.querySelectorAll("[data-source-group]")];
  let selectedLetter = "all";

  if (!search || cards.length === 0) return;

  const update = () => {
    const query = search.value.trim().toLowerCase();
    let visible = 0;

    cards.forEach((card) => {
      const matchesQuery = card.dataset.sourceSearch.includes(query);
      const matchesLetter =
        selectedLetter === "all" || card.dataset.sourceLetter === selectedLetter;
      const matches = matchesQuery && matchesLetter;
      card.hidden = !matches;
      if (matches) visible += 1;
    });

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
  update();
});
