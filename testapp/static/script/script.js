const time = document.getElementById('time');
const startButton = document.getElementById('start');
const stopButton = document.getElementById('stop');
const resetButton = document.getElementById('reset');
const value=time.getAttribute('value')

// 開始時間
let startTime;
// 停止時間
let stopTime = 0;
// タイムアウトID
let timeoutID;

// 時間を表示する関数
function displayTime(time1) {
    const currentTime = new Date(time1-(Date.now() - startTime + stopTime));
    const m = String(currentTime.getMinutes()).padStart(2, '0');
    const s = String(currentTime.getSeconds()).padStart(2, '0');

    time.textContent = `残り${m}分${s}秒だよ`;
    timeoutID = setTimeout(displayTime, 10,time1);
}

// スタートボタンがクリックされたら時間を進める
startButton.addEventListener('click', () => {
    startButton.disabled = true;
    stopButton.disabled = false;
    resetButton.disabled = true;
    startTime = Date.now();
    displayTime(Number(value)*60*1000);
});

// ストップボタンがクリックされたら時間を止める
stopButton.addEventListener('click', function() {
    startButton.disabled = false;
    stopButton.disabled = true;
    resetButton.disabled = false;
    clearTimeout(timeoutID);
    stopTime += (Date.now() - startTime);
});

// リセットボタンがクリックされたら時間を0に戻す
resetButton.addEventListener('click', function() {
    startButton.disabled = false;
    stopButton.disabled = true;
    resetButton.disabled = true;
    time.textContent =  "時間を測るためにstartを押してね";
    stopTime = 0;
});

