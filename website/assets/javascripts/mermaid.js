const initializeMermaid = () => {
  if (!window.mermaid) return;

  window.mermaid.initialize({
    startOnLoad: false,
    theme: "dark",
    securityLevel: "strict",
  });

  const diagrams = document.querySelectorAll(".mermaid:not([data-processed='true'])");
  if (diagrams.length > 0) {
    window.mermaid.run({ nodes: diagrams });
  }
};

if (typeof document$ !== "undefined") {
  document$.subscribe(initializeMermaid);
} else if (document.readyState === "loading") {
  document.addEventListener("DOMContentLoaded", initializeMermaid);
} else {
  initializeMermaid();
}
