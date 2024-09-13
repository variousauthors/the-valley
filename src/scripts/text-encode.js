const [a, b, ...texts] = process.argv;

console.log(a, b, texts)

texts.forEach((text) => {
  if (text.length > 17) {
    console.log("TEXT TOO LONG");
    console.log(".................|");
    console.log(`${text.slice(0, 17)}|${text.slice(17)}`);

    return;
  } else {
    console.log(".................|");
    console.log(`${text.padEnd(17, ".")}|`);
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
      .join(", "),
    ", LINE_FEED", i === texts.length - 1 ? ", NULL" : ""
  );
});
