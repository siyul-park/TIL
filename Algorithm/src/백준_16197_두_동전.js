const readline = require('readline');

function findCoinPosition(board = []) {
    const coinPosition = [];
    for (let i = 0; i < board.length; i++) {
        for (let j = 0; j < board[i].length; j++) {
            if (board[i][j] === 'o') {
                coinPosition.push({ x: i, y: j });
            }
        }
    }

    return coinPosition;
}

function removeCoin(board = []) {
    for (let i = 0; i < board.length; i++) {
        for (let j = 0; j < board[i].length; j++) {
            if (board[i][j] === 'o') {
                board[i][j] = '.';
            }
        }
    }
}

function isCoinInBoard(board, coin) {
    return !(coin.x < 0 || coin.y < 0 || coin.x >= board.length || coin.y >= board[coin.x].length);
}

const move = [
    { x: -1, y: 0 },
    { x: +1, y: 0 },
    { x: 0, y: -1 },
    { x: 0, y: +1 },
];

const visit = new Set();
function solve(board = []) {
    const coins = findCoinPosition(board);
    removeCoin(board);

    const que = [];
    que.push({ coins: JSON.stringify(coins), deep: 0 });

    while (que.length > 0) {
        let { coins, deep } = que.shift();

        if (visit.has(coins)) continue;
        visit.add(coins);

        coins = JSON.parse(coins);

        if (deep > 10) return -1;
        if (!isCoinInBoard(board, coins[0]) || !isCoinInBoard(board, coins[1])) {
            return deep;
        }

        for (const moving of move) {
            let newCoins = coins.map((coin) => {
                const position = { x: coin.x + moving.x, y: coin.y + moving.y };
                if (board[position.x] && board[position.x][position.y] === '#') return coin;
                return position;
            });

            if (newCoins[0].x === newCoins[1].x && newCoins[0].y === newCoins[1].y) {
                continue;
            } else if (!isCoinInBoard(board, newCoins[0]) && !isCoinInBoard(board, newCoins[1])) {
                continue;
            } else {
                que.push({ coins: JSON.stringify(newCoins), deep: deep + 1 });
            }
        }
    }

    return -1;
}

const read = readline.createInterface(process.stdin, process.stdout);

let N, M;
let lineIndex = 0;
let boardIndex = 0;
const board = [];
read.on('line', (line = '') => {
    lineIndex++;
    line = line.trim();

    if (lineIndex === 1) {
        const token = line.split(' ');
        N = Number(token[0]);
        M = Number(token[0]);
    } else {
        boardIndex++;
        board.push(line.split(''));
        if (boardIndex === N) read.close();
    }
}).on('close', () => {    
    console.log(solve(board));
    
    process.exit();
})