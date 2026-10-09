let grid = [];
let score = 0;
let oldGrid = null; // 用于比较旧值

window.onload = () => {
    console.log('页面加载完成');
    newGame();
};

// 开始新游戏
function newGame() {
    console.clear();
    grid = Array.from({ length: 4 }, () => Array(4).fill(0));
    score = 0;
    document.getElementById('score').textContent = score.toString();
    addNewNumber();
    addNewNumber();
    updateDisplay();
    oldGrid = JSON.parse(JSON.stringify(grid)); // 初始化 oldGrid
    console.log('新游戏开始');
}

// 添加新的数字(2或4)
function addNewNumber() {
    const emptyCells = [];
    for (let i = 0; i < 4; i++) {
        for (let j = 0; j < 4; j++) {
            if (grid[i][j] === 0) {
                emptyCells.push({ x: i, y: j });
            }
        }
    }
    if (emptyCells.length) {
        const randomCell = emptyCells[Math.floor(Math.random() * emptyCells.length)];
        grid[randomCell.x][randomCell.y] = Math.random() < 0.9 ? 2 : 4;
    }
}

// 在updateDisplay函数中对比旧值并添加动画效果
function updateDisplay() {
    const cells = document.querySelectorAll('.cell');
    const flatGrid = grid.flat();
    const flatOldGrid = oldGrid ? oldGrid.flat() : Array(16).fill(0);

    cells.forEach((cell, idx) => {
        const value = flatGrid[idx];
        const oldValue = flatOldGrid[idx];
        
        // 清除之前的动画类
        cell.classList.remove('slide-left', 'slide-right', 'slide-up', 'slide-down', 'merge', 'changed');
        
        // 设置新值
        cell.textContent = value || '';
        cell.setAttribute('data-value', value);

        // 添加移动动画
        if (value && value !== oldValue) {
            // 根据移动方向添加对应的动画类
            if (lastMove) {
                cell.classList.add(`slide-${lastMove}`);
            }
            // 如果是合并，添加合并动画
            if (oldValue && value === oldValue * 2) {
                cell.classList.add('merge');
            }
        }
    });

    document.getElementById('score').textContent = score;
    oldGrid = JSON.parse(JSON.stringify(grid));
}

let lastMove = '';

// 检查游戏结束
function checkGameOver() {
    for (let i = 0; i < 4; i++) {
        for (let j = 0; j < 4; j++) {
            if (grid[i][j] === 0) return; 
            if (j < 3 && grid[i][j] === grid[i][j + 1]) return;
            if (i < 3 && grid[i][j] === grid[i + 1][j]) return;
        }
    }
    alert(`游戏结束！您的分数为：${score}`);
}

// 移动逻辑
function move(direction) {
    const oldGridStr = JSON.stringify(grid);
    lastMove = direction; // 记录移动方向
    
    if (direction === 'left' || direction === 'right') {
        for (let i = 0; i < 4; i++) {
            let row = grid[i].filter(val => val !== 0);
            if (direction === 'right') row.reverse();
            for (let k = 0; k < row.length - 1; k++) {
                if (row[k] === row[k + 1]) {
                    row[k] *= 2;
                    score += row[k];
                    row.splice(k + 1, 1);
                }
            }
            while (row.length < 4) row.push(0);
            if (direction === 'right') row.reverse();
            grid[i] = row;
        }
    } else {
        for (let j = 0; j < 4; j++) {
            let col = [];
            for (let i = 0; i < 4; i++) {
                if (grid[i][j] !== 0) {
                    col.push(grid[i][j]);
                }
            }
            if (direction === 'down') col.reverse();
            for (let k = 0; k < col.length - 1; k++) {
                if (col[k] === col[k + 1]) {
                    col[k] *= 2;
                    score += col[k];
                    col.splice(k + 1, 1);
                }
            }
            while (col.length < 4) {
                col.push(0);
            }
            if (direction === 'down') col.reverse();
            for (let i = 0; i < 4; i++) {
                grid[i][j] = col[i];
            }
        }
    }
    // 如果有变化，就生成新数字并检查结束
    if (JSON.stringify(grid) !== oldGridStr) {
        // 等待动画完成后再添加新数字
        setTimeout(() => {
            addNewNumber();
            updateDisplay();
            checkGameOver();
        }, 200); // 与动画持续时间相匹配
    }
}

// 监听键盘
document.addEventListener('keydown', (e) => {
    switch (e.key) {
        case 'ArrowLeft':
            move('left');
            break;
        case 'ArrowRight':
            move('right');
            break;
        case 'ArrowUp':
            move('up');
            break;
        case 'ArrowDown':
            move('down');
            break;
        default:
            break;
    }
});
