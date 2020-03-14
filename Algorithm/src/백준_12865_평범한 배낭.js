const readline = require('readline');

function solve(totalWeight = 0, items = []) {
    items = items.sort((a, b) => a - b);

    const cache = new Map();
    function optimal(i, weight) {
        const key = JSON.stringify({ i, weight });

        if (weight <= 0) return 0;
        if (i < 0) return 0;
        if (cache.has(key)) return cache.get(key);

        if (items[i].weight > weight) cache.set(key, optimal(i - 1, weight));
        else cache.set(key, Math.max(items[i].value + optimal(i - 1, weight - items[i].weight), optimal(i - 1, weight)));

        return cache.get(key);
    }

    return optimal(items.length - 1, totalWeight);
}

const read = readline.createInterface(process.stdin, process.stdout);

let N, K;
let items = [];
let inputCount = 0;
let itemCount = 0;
read.on('line', function (line) {
    inputCount++;
    line = line.trim();
    
    if (inputCount === 1) {
        const token = line.split(' ').map((e) => Number(e));

        N = token[0];
        K = token[1];
    } else {
        itemCount++;

        const token = line.split(' ').map((e) => Number(e));
        items.push({ weight: token[0], value: token[1] })

        if (itemCount === N) read.close();
    }
}).on('close', function () {
    console.log(solve(K, items));
    process.exit();
});