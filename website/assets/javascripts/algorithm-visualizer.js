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

  document.querySelectorAll("[data-ratio-split]").forEach((root) => {
    const values = (root.dataset.values ?? "").split(",").map(Number);
    const l = Number(root.dataset.l);
    const r = Number(root.dataset.r);
    const a = Number(root.dataset.a);
    const b = Number(root.dataset.b);
    const prefix = [0];
    values.forEach((value) => prefix.push(prefix.at(-1) + value));

    const cells = root.querySelector("[data-ratio-cells]");
    const message = root.querySelector("[data-ratio-message]");
    const status = root.querySelector("[data-ratio-status]");
    const nextButton = root.querySelector("[data-ratio-next]");
    const playButton = root.querySelector("[data-ratio-play]");
    const resetButton = root.querySelector("[data-ratio-reset]");

    const isValid =
      cells && message && status && nextButton && playButton && resetButton &&
      values.length > 0 && values.every(Number.isFinite) &&
      Number.isInteger(l) && Number.isInteger(r) && l >= 1 && r <= values.length && l <= r &&
      Number.isFinite(a) && Number.isFinite(b) && a > 0 && b > 0;
    if (!isValid) return;

    const total = prefix[r] - prefix[l - 1];
    const steps = [];
    let left = l;
    let right = r;
    while (left < right) {
      const mid = Math.floor((left + right) / 2);
      const partial = prefix[mid] - prefix[l - 1];
      const feasible = partial * (a + b) >= a * total;
      steps.push({ left, right, mid, partial, feasible });
      if (feasible) right = mid;
      else left = mid + 1;
    }
    const answer = left;
    const frames = [
      { kind: "prefix" },
      { kind: "target" },
      ...steps.map((step) => ({ kind: "search", ...step })),
      { kind: "done", answer },
    ];

    let frameIndex = 0;
    let timer = null;

    const stopPlaying = () => {
      if (timer !== null) window.clearInterval(timer);
      timer = null;
      playButton.textContent = "播放動畫";
    };

    const renderCells = (frame) => {
      cells.replaceChildren(
        ...values.map((value, index) => {
          const position = index + 1;
          const cell = document.createElement("div");
          cell.className = "visualizer-cell";
          if (position < l || position > r) cell.classList.add("is-discarded");
          if (frame.kind === "search") {
            if (position < frame.left || position > frame.right) cell.classList.add("is-discarded");
            if (position === frame.left) cell.classList.add("is-left");
            if (position === frame.right) cell.classList.add("is-right");
            if (position === frame.mid) cell.classList.add("is-middle");
          }
          if (frame.kind === "done" && position === frame.answer) cell.classList.add("is-found");
          cell.innerHTML = `<span>w[${position}] = ${value}</span><small>prefix[${position}] = ${prefix[position]}</small>`;
          return cell;
        })
      );
    };

    const render = () => {
      const frame = frames[frameIndex];
      renderCells(frame);

      if (frame.kind === "prefix") {
        status.textContent = `prefix = [${prefix.join(", ")}]`;
        message.textContent = `先累積一次。之後 S(${l},${r}) = prefix[${r}] - prefix[${l - 1}] = ${prefix[r]} - ${prefix[l - 1]} = ${total}。`;
      } else if (frame.kind === "target") {
        status.textContent = `目標比例 ${a}/${a + b}`;
        message.textContent = `避免小數：找第一個 k，使 S(${l},k) × ${a + b} ≥ ${a} × ${total} = ${a * total}。`;
      } else if (frame.kind === "search") {
        const comparison = `${frame.partial * (a + b)} ${frame.feasible ? "≥" : "<"} ${a * total}`;
        status.textContent = `left=${frame.left}, mid=${frame.mid}, right=${frame.right}`;
        message.textContent = `S(${l},${frame.mid}) = ${frame.partial}，所以 ${comparison}：mid ${frame.feasible ? "已達標，保留 mid 並收右界" : "未達標，答案只能在右側"}。`;
      } else {
        status.textContent = `答案 k = ${frame.answer}`;
        message.textContent = `搜尋範圍只剩 ${frame.answer}；它是第一個讓累積比例達標的位置。`;
      }

      nextButton.disabled = frameIndex === frames.length - 1;
      if (nextButton.disabled) stopPlaying();
    };

    const advance = () => {
      if (frameIndex < frames.length - 1) frameIndex += 1;
      render();
    };

    nextButton.addEventListener("click", () => {
      stopPlaying();
      advance();
    });
    playButton.addEventListener("click", () => {
      if (timer !== null) {
        stopPlaying();
        return;
      }
      if (frameIndex === frames.length - 1) frameIndex = 0;
      playButton.textContent = "暫停";
      render();
      timer = window.setInterval(advance, 1300);
    });
    resetButton.addEventListener("click", () => {
      stopPlaying();
      frameIndex = 0;
      render();
    });

    render();
  });
});
