(() => {
  const reduceMotion = window.matchMedia("(prefers-reduced-motion: reduce)");
  const smallScreen = window.matchMedia("(max-width: 44.984375em)");

  if (reduceMotion.matches || smallScreen.matches) return;

  const video = document.createElement("video");
  video.className = "site-background-video";
  video.autoplay = true;
  video.loop = true;
  video.muted = true;
  video.playsInline = true;
  video.preload = "metadata";
  video.setAttribute("aria-hidden", "true");

  const source = document.createElement("source");
  const scriptElement =
    document.currentScript ??
    [...document.scripts].find((script) =>
      script.src.endsWith("/assets/javascripts/background-video.js"),
    );
  source.src = new URL(
    "../media/lofi-cat-background.mp4",
    scriptElement?.src ?? window.location.href,
  ).href;
  source.type = "video/mp4";
  video.append(source);

  video.addEventListener(
    "canplay",
    () => {
      video.classList.add("is-ready");
      void video.play().catch(() => {});
    },
    { once: true },
  );

  document.body.prepend(video);
})();
