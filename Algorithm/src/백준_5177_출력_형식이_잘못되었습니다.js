const readline = require('readline');

let K;
function normalize(str) {
    return str.trim()
        .replace(/[({[]/gi, '(')
        .replace(/[)}\]]/gi, ')')
        .replace(/[,;]/gi, ',')
        .replace(/ +/gi, ' ')    
        .replace(/\( +/gi, '(')
        .replace(/\) +/gi, ')')
        .replace(/, +/gi, ',')
        .replace(/\. +/gi, '.')
        .replace(/: +/gi, ':')
        .replace(/ +\(/gi, '(')
        .replace(/ +\)/gi, ')')
        .replace(/ +,/gi, ',')
        .replace(/ +\./gi, '.')
        .replace(/ +:/gi, ':')
        .toLowerCase();
}

function solve(str1, str2) {
    return normalize(str1) === normalize(str2);
}

const read = readline.createInterface(process.stdin, process.stdout);

let inputCount = 0;
let i = 0;
let str1, str2;
read.on('line', function (line) {
    inputCount++;
    line = line.trim();
    
    if (inputCount === 1) {
        K = Number(line);
    } else if (i < K * 2) {
        i++;
        if (i % 2 === 1) {
            str1 = line;
        } else {
            str2 = line;

            const success = solve(str1, str2);
            const message = `Data Set ${Math.floor(i / 2)}: ${success ? 'equal' : 'not equal'}`
            console.log(message);
            if (i !== K* 2) console.log();
        }

        if (i === K * 2) read.close();
    }
}).on('close', function () {
    process.exit();
});