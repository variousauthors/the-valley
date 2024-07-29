const text = process.argv[2]

if (text.length > 17) {
  console.log('TEST TOO LONG')
  console.log('.................|')
  console.log(`${text.slice(0, 17)}|${text.slice(17)}`)

  return
}

console.log(
  "db",
  text
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
