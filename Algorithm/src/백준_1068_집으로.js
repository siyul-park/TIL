const readline = require('readline');

function solve(x, y, d, t) {
    const distance = Math.sqrt(x * x + y * y);
    const jump = Math.floor(distance / d);
    const distanceAfterJump = distance - d * jump;

    let result = Math.min(distance, distanceAfterJump + jump * t);
    if (jump > 0) result = Math.min(result, (jump + 1) * t);
    else result = Math.min(result, d - distance + t, t *2);
    
    return result;
}

const read = readline.createInterface(process.stdin, process.stdout);

let X, Y, D, T;
read.on('line', (line = '') => {
    const numbers = line.trim().split(' ').map((token) => Number(token));

    X = numbers[0];
    Y = numbers[1];
    D = numbers[2];
    T = numbers[3];

    read.close();
}).on('close', () => {
    console.log(solve(X, Y, D, T));
    
    process.exit();
})