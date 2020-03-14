const readline = require('readline');

function solve(arr = [], m = 0) {
    let max = 0;
    for (let i = 0; i < arr.length; i++) {
        for (let j = 0; j < arr.length; j++) {
            if (j === i) continue;

            for (let k = 0; k < arr.length; k++) {
                if (k === i || k === j) continue;

                if (arr[i] + arr[j] + arr[k] <= m)
                    max = Math.max(max, arr[i] + arr[j] + arr[k]);
            }
        }
    }

    return max;
}

const read = readline.createInterface(process.stdin, process.stdout);

let M, arr;
let lineIndex = 0;
read.on('line', (line = '') => {
    lineIndex++;
    line = line.trim();

    if (lineIndex === 1) {
        M = Number(line.split(' ')[1]);
    } else if (lineIndex === 2) {
        arr = line.split(' ').map((e) => Number(e));
        read.close();
    }
}).on('close', () => {    
    console.log(solve(arr, M));
    
    process.exit();
});
