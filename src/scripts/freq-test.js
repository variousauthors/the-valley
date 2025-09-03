// const [a, b, ...corpus] = process.argv;

const corpus = [
  "the world aches\n",
  "no kings remain\n",
  "and the dead stir\n",
  "a deep wrongness\n",
  "goes unanswered\n",
  "I know you see it\n",
  "heed our words\n",
  "seek the sages\n",
  "heal this world\n",
];

/** in practice we would want to analyze the entire db of text and
 * determine freqs for the corpus, but this generic English one is OK
 */
const ALPHABET = ` ETAOINSHRDLC\nUMEWFGYPBVKJXQZ.`.split("");

const FREQS = ALPHABET.map((group) => group.split(""));

const F = 15;
const E = 14;

/*
const freqs = corpus.join('').split('').reduce((hist, ch) => {
  if (!hist[ch]) {
    hist[ch] = 1
    return hist
  }

  hist[ch] += 1

  return hist
}, {})

console.log(freqs)
*/

const result = corpus.reduce((bytes, text) => {
  const freq = toFreqEncoding(text);

  return bytes + freq.length / 2;
}, 0);

const control = corpus.reduce((bytes, text) => {
  const nibbles = toBytes(text);

  return bytes + nibbles.length / 2;
}, 0);

console.log(`from ${control} bytes to ${result} bytes`);

function makeCode(len) {
  if (len < F) {
    return len.toString(16).toUpperCase();
  }

  let result = "";

  while (len >= F) {
    result = result + "F";

    len -= E;
  }

  return result + len.toString(16).toUpperCase();
}

function toFreqEncoding(str) {
  return str
    .toUpperCase()
    .split("")
    .reduce((acc, ch) => {
      const i = ALPHABET.findIndex((CH) => CH === ch);

      return acc + makeCode(i);
    }, "");
}

function toBytes(str) {
  return str
    .toUpperCase()
    .split("")
    .reduce((acc, ch) => {
      const i = ALPHABET.findIndex((CH) => CH === ch);

      return acc + i.toString(16).toUpperCase().padStart(2, "0");
    }, "");
}
