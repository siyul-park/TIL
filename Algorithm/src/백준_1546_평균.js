const readline = require('readline');

function solve(scores = []) {
    const max = Math.max(...scores);
    return scores.map((score) => score * 100 / max).reduce((a, b) => a + b, 0) / scores.length || 0;
}

const read = readline.createInterface(process.stdin, process.stdout);

let N;
let scores;
let lineIndex = 0;
read.on('line', (line = '') => {
    lineIndex++;
    line = line.trim();

    if (lineIndex === 1) {
        N = Number(line);
    } else {
        scores = line.split(' ').map((e) => Number(e));
        read.close();
    }
}).on('close', () => {    
    console.log(solve(scores));
    
    process.exit();
})