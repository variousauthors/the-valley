console.log(
  "db",
  process.argv[2]
    .split("")
    .map((ch) => ch.charCodeAt(0))
    .map((ch) => ch - 62)
    .map((ch) => {
      switch (ch) {
        case -30: // space
          return 2;
        case -16: // period
          return 29;
        default:
          return ch;
      }
    })
    .join(", "),
  ", LINE_FEED"
);
