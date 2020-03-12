const readline = require('readline');

let N, M;
let state = [];
function breakWall(x, y) {
    state[x - 1]++;
    state[y - 1]--;
}

function solve() {
    let sum = 0, answer = N;
    for (let i = 0; i < N - 1; i++) {
        sum += state[i];
        if (sum) answer--;
    }

    return answer;
}

const read = readline.createInterface(process.stdin, process.stdout);

let inputCount = 0;
let i = 0;
read.on('line', function (line) {
    inputCount++;
    line = line.trim();
    
    if (inputCount === 1) {
        N = Number(line);
        for (let i = 0; i < N - 1; i++) {
            state[i] = 0;
        }
    } else if (inputCount === 2) {
        M = Number(line);
        if (M === 0) read.close();
    } else if (i < M) {
        i++;
        const [x, y] = line.split(' ');
        breakWall(Number(x), Number(y));

        if (i === M) read.close();
    }
}).on('close', function () {
    console.log(solve());

    process.exit();
});