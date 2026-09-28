document.addEventListener("DOMContentLoaded", () => {
  document.querySelectorAll("[data-chalk-cycle]").forEach((root) => {
    const values = (root.dataset.values ?? "").split(",").map(Number);
    const initialChalk = Number(root.dataset.chalk);
    const total = values.reduce((sum, value) => sum + value, 0);
    const cells = root.querySelector("[data-chalk-cells]");
    const message = root.querySelector("[data-chalk-message]");
    const stepLabel = root.querySelector("[data-chalk-step]");
    const nextButton = root.querySelector("[data-chalk-next]");
    const resetButton = root.querySelector("[data-chalk-reset]");
    let phase = "modulo";
    let student = 0;
    let remaining = initialChalk;

    if (!cells || !message || values.some((value) => !Number.isFinite(value))) return;

    const render = (explanation) => {
      cells.replaceChildren(
        ...values.map((need, index) => {
          const cell = document.createElement("div");
          cell.className = "visualizer-cell";
          if (phase !== "modulo" && index === student) cell.classList.add("is-middle");
          if (phase === "done" && index === student) cell.classList.add("is-found");
          cell.innerHTML = `<span>學生 ${index}</span><small>需要 ${need} 枝</small>`;
          return cell;
        })
      );
      message.textContent = explanation;
      stepLabel.textContent = phase === "modulo" ? "尚未取模" : `剩餘 ${remaining} 枝`;
      nextButton.disabled = phase === "done";
    };

    const advance = () => {
      if (phase === "modulo") {
        remaining %= total;
        phase = "scan";
        render(`${initialChalk} % ${total} = ${remaining}，完整週期已全部跳過。`);
        return;
      }
      if (remaining < values[student]) {
        phase = "done";
        render(`剩下 ${remaining} 枝，小於學生 ${student} 需要的 ${values[student]} 枝；答案是 ${student}。`);
        return;
      }
      const used = values[student];
      remaining -= used;
      student = (student + 1) % values.length;
      render(`上一位使用 ${used} 枝，接著檢查學生 ${student}。`);
    };

    const reset = () => {
      phase = "modulo";
      student = 0;
      remaining = initialChalk;
      render(`一輪共需要 ${total} 枝。先對 ${initialChalk} 取模，不必真的跑完整週期。`);
    };

    nextButton.addEventListener("click", advance);
    resetButton?.addEventListener("click", reset);
    reset();
  });

  document.querySelectorAll("[data-prefix-query]").forEach((root) => {
    const values = (root.dataset.values ?? "").split(",").map(Number).sort((a, b) => a - b);
    const queries = (root.dataset.queries ?? "").split(",").map(Number);
    const prefix = [];
    values.reduce((sum, value) => {
      const next = sum + value;
      prefix.push(next);
      return next;
    }, 0);
    const cells = root.querySelector("[data-prefix-cells]");
    const message = root.querySelector("[data-prefix-message]");
    const status = root.querySelector("[data-prefix-status]");
    const controls = root.querySelector("[data-prefix-controls]");

    if (!cells || !message || !controls || values.some((value) => !Number.isFinite(value))) return;

    const showQuery = (query) => {
      const count = prefix.filter((sum) => sum <= query).length;
      cells.replaceChildren(
        ...values.map((value, index) => {
          const cell = document.createElement("div");
          cell.className = "prefix-cell";
          if (index < count) cell.classList.add("is-selected");
          if (index === count && count < values.length) cell.classList.add("is-boundary");
          cell.innerHTML = `<span>值 ${value}</span><small>prefix = ${prefix[index]}</small>`;
          return cell;
        })
      );
      status.textContent = `query = ${query}`;
      message.textContent = `第一個大於 ${query} 的前綴位置是 ${count}，所以最多可選 ${count} 個元素。`;
    };

    controls.replaceChildren(
      ...queries.map((query) => {
        const button = document.createElement("button");
        button.type = "button";
        button.textContent = `query = ${query}`;
        button.addEventListener("click", () => showQuery(query));
        return button;
      })
    );
    showQuery(queries[0]);
  });
});
