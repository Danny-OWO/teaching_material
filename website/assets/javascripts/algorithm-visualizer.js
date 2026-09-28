document.addEventListener("DOMContentLoaded", () => {
  document.querySelectorAll("[data-binary-search]").forEach((root) => {
    const values = (root.dataset.values ?? "")
      .split(",")
      .map((value) => Number(value.trim()))
      .filter((value) => Number.isFinite(value));
    const target = Number(root.dataset.target);
    const cells = root.querySelector("[data-visualizer-cells]");
    const message = root.querySelector("[data-visualizer-message]");
    const stepLabel = root.querySelector("[data-visualizer-step]");
    const nextButton = root.querySelector("[data-visualizer-next]");
    const playButton = root.querySelector("[data-visualizer-play]");
    const resetButton = root.querySelector("[data-visualizer-reset]");
    let left = 0;
    let right = values.length - 1;
    let step = 0;
    let done = false;
    let timer = null;

    if (!cells || !message || values.length === 0 || !Number.isFinite(target)) return;

    const stop = () => {
      if (timer) window.clearInterval(timer);
      timer = null;
      if (playButton) playButton.textContent = "自動播放";
    };

    const render = (explanation = `目標是 ${target}。先觀察 left、mid、right。`) => {
      const middle = left <= right ? left + Math.floor((right - left) / 2) : -1;
      cells.replaceChildren(
        ...values.map((value, index) => {
          const cell = document.createElement("div");
          cell.className = "visualizer-cell";
          if (!done && (index < left || index > right)) cell.classList.add("is-discarded");
          if (index === left && !done) cell.classList.add("is-left");
          if (index === middle && !done) cell.classList.add("is-middle");
          if (index === right && !done) cell.classList.add("is-right");
          if (done && value === target) cell.classList.add("is-found");
          cell.innerHTML = `<span>${value}</span><small>${index}</small>`;
          return cell;
        })
      );
      message.textContent = explanation;
      if (stepLabel) stepLabel.textContent = `Step ${step}`;
      if (nextButton) nextButton.disabled = done;
    };

    const advance = () => {
      if (done) return;
      if (left > right) {
        done = true;
        stop();
        render(`搜尋區間已經為空，${target} 不在陣列裡。`);
        return;
      }

      const middle = left + Math.floor((right - left) / 2);
      step += 1;
      if (values[middle] === target) {
        done = true;
        stop();
        render(`a[${middle}] = ${target}，找到目標。`);
      } else if (values[middle] < target) {
        const oldMiddle = middle;
        left = middle + 1;
        render(`a[${oldMiddle}] = ${values[oldMiddle]} < ${target}，排除 mid 以及左半邊。`);
      } else {
        const oldMiddle = middle;
        right = middle - 1;
        render(`a[${oldMiddle}] = ${values[oldMiddle]} > ${target}，排除 mid 以及右半邊。`);
      }
    };

    const reset = () => {
      stop();
      left = 0;
      right = values.length - 1;
      step = 0;
      done = false;
      render();
    };

    nextButton?.addEventListener("click", advance);
    resetButton?.addEventListener("click", reset);
    playButton?.addEventListener("click", () => {
      if (timer) {
        stop();
        return;
      }
      if (done) reset();
      playButton.textContent = "暫停";
      advance();
      if (!done) timer = window.setInterval(advance, 1100);
    });
    reset();
  });
});
