const [a, b, ...texts] = process.argv;

console.log(a, b, texts)

const MAX_LINE_LENGTH = 18

console.log("|..................|");

texts.forEach((text) => {
  if (text.length > MAX_LINE_LENGTH) {
    console.log(`|${text.slice(0, MAX_LINE_LENGTH)}|${text.slice(MAX_LINE_LENGTH)}`);

    return;
  } else {
    console.log(`|${text.padEnd(MAX_LINE_LENGTH, ".")}|`);
  }
})

console.log(`; node ./src/scripts/text-encode.js`, texts.map((text) => `"${text}"`).join(' '))

texts.forEach((text, i) => {
  console.log(
    "db",
    text
      .toUpperCase()
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
      .concat(i === texts.length - 1 ? "NULL" : "LINE_FEED")
      .join(", "),
  );
});
