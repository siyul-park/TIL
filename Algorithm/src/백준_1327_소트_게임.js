const readline = require('readline');

function reverse(arr = [], start = 0, size = 0) {
    if (size === 0) return;

    for (let i = 0; i < size / 2; i++) {
        const j = start + i;
        const k = start + size - 1 - i;

        const tmp = arr[j];
        arr[j] = arr[k];
        arr[k] = tmp;
    }
}

function solve(arr = [], size) {
    const target = JSON.stringify([...arr.sort()]);
    const set = new Set();

    const que = [];
    que.push({ arr: JSON.stringify(arr), deep: 0 });

    
    while (que.length > 0) {        
        let { arr, deep } = que.shift();

        if (arr === target) return deep;

        arr = JSON.parse(arr);

        for (let i = 0; i <= arr.length - size; i++) {
            reverse(arr, i, size);
            const str = JSON.stringify(arr);
            if (!set.has(str)) {
                set.add(str);
                que.push({ arr: str, deep: deep + 1 });
            }
            reverse(arr, i, size);
        }
    }

    return -1;
}

const read = readline.createInterface(process.stdin, process.stdout);

let N, K;
let inputCount = 0;
read.on('line', function (line) {
    inputCount++;
    line = line.trim();
    
    if (inputCount === 1) {
        const token = line.split(' ');
        
        N = Number(token[0]);
        K = Number(token[1]);
    } else if (inputCount === 2) {
        const token = line.split(' ');
        const arr = token.map((num) => Number(num));
        
        console.log(solve(arr, K));
        read.close();
    }
}).on('close', function () {
    process.exit();
});