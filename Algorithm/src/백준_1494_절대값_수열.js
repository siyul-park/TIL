const readline = require('readline');

let number;
const cache = [];
function solve(index) {
    if (index < 0) return 0;

    if (cache[index] === undefined) cache[index] = Math.floor(Math.abs(solve(index - 2) - solve(index - 1)));
    return cache[index]
}

const read = readline.createInterface(process.stdin, process.stdout);

let inputCount = 0;
read.on('line', function (line) {
    inputCount++;
    line = line.trim();
    
    if (inputCount === 1) {
        const token = line.split(' ');

        cache[0] = parseInt(token[0]);
        cache[1] = parseInt(token[1]);
        number = parseInt(token[2]);
    } else if (inputCount <= number + 1) {
        console.log(solve(parseInt(line)));
    }
    
    if (inputCount >= number + 1) read.close();
}).on('close', function () {
    process.exit();
});