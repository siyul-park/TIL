const readline = require('readline');

const read = readline.createInterface(process.stdin, process.stdout);

read.on('line', (line = '') => {
    console.log(parseInt(line.trim(), 16));

    read.close();
}).on('close', () => {    
    process.exit();
})