document.addEventListener("DOMContentLoaded", () => {
  const search = document.querySelector(".source-search input");
  const cards = [...document.querySelectorAll(".source-card")];
  const count = document.querySelector(".source-count");
  const empty = document.querySelector(".source-empty");

  if (!search || cards.length === 0) return;

  const update = () => {
    const query = search.value.trim().toLowerCase();
    let visible = 0;

    cards.forEach((card) => {
      const matches = card.dataset.sourceSearch.includes(query);
      card.hidden = !matches;
      if (matches) visible += 1;
    });

    count.textContent = `顯示 ${visible} / ${cards.length} 個項目`;
    empty.hidden = visible !== 0;
  };

  search.addEventListener("input", update);
  update();
});
