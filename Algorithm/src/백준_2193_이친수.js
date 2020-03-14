const readline = require('readline');

// Can't solve only js
function solve(n) {
    const result = [0, 1];

    for (let i = 2; i <= n; i++) {
        result.push(result[i - 1] + result[i - 2]);
    }

    return result[n];
}

const read = readline.createInterface(process.stdin, process.stdout);

let N;
read.on('line', (line = '') => {
    line = line.trim();

    N = Number(line);
    read.close();
}).on('close', () => {    
    console.log(solve(N));
    
    process.exit();
});
