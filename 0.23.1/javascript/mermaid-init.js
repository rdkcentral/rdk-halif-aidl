document$.subscribe(function() {
    mermaid.initialize({
        startOnLoad: true,
        theme: "default",  // Or "dark" if using dark mode
        securityLevel: "loose"
    });
});
