/** a js implementation of twiddle
 * to prove its behaviour
 */

function twiddle(a) {
  let stack = []
  console.log('twiddle', a)
  if (a === 0) {
    return a;
  }

  let b = a;
  b = b >> 1; // divide by 2
  stack.push(b)
  a = 0;

  console.log(b)
  do {
    a = a | b;
    b = b >> 1;
  } while (b);

  let r = RAND()
  console.log(a, r.toString(2))
  a = a & r;
  console.log(a)

  b = stack.pop()
  console.log(b)

  if (a <= b) {
    return a
  }

  a = a - b

  return a;
}

function RAND() {
  return (Math.random() * 256) | 0;
}

const randHist = {};

for (let i = 0; i < 10000; i++) {
  const r = RAND();

  if (randHist[r]) {
    randHist[r] += 1;
  } else {
    randHist[r] = 1;
  }
}

const twiddleHists = [];

for (let i = 0; i < 10; i++) {
  twiddleHists[i] = {};
  for (let j = 0; j < 100; j++) {
    const t = twiddle(i);

    if (twiddleHists[i][t]) {
      twiddleHists[i][t] += 1;
    } else {
      twiddleHists[i][t] = 1;
    }
  }
}

console.log(twiddleHists);
console.log(twiddle(3));
console.log(twiddle(3));
console.log(twiddle(3));
console.log(twiddle(3));
console.log(twiddle(3));