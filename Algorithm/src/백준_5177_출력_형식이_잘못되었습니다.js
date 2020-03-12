const readline = require('readline');

let K;
function replaceString(str) {
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
    const result1 = replaceString(str1);
    const result2 = replaceString(str2);

    console.log(result1);
    console.log(result2);

    return result1 === result2;
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