"use strict";

const player = document.getElementById("player");
const tracks = [...document.querySelectorAll(".track")];
const title = document.getElementById("now-playing");
const status = document.getElementById("player-status");
const previous = document.getElementById("previous-track");
const next = document.getElementById("next-track");
let currentIndex = -1;
let playRequest = 0;

function renderPlayback() {
  tracks.forEach((track, index) => {
    const selected = index === currentIndex;
    const playing = selected && !player.paused && !player.ended;
    track.classList.toggle("is-current", selected);
    track.setAttribute("aria-pressed", String(playing));
    track.setAttribute("aria-label", `${playing ? "暂停" : "播放"} ${track.dataset.title}`);
    track.querySelector(".track-indicator").textContent = playing ? "❚❚" : "▶";
  });
}

function playTrack(index) {
  const request = ++playRequest;
  const track = tracks[index];
  if (currentIndex !== index) {
    currentIndex = index;
    player.src = new URL(track.dataset.src, document.baseURI).href;
    title.textContent = `${track.dataset.title} · ${track.dataset.artist}`;
    previous.disabled = false;
    next.disabled = false;
  }
  status.textContent = "正在加载歌曲…";
  renderPlayback();
  player.play().catch((error) => {
    // Selecting another song or pausing can cancel an in-flight play request.
    if (request !== playRequest || error.name === "AbortError") return;
    status.textContent = "播放失败，请检查网络或浏览器对该音频格式的支持。";
    renderPlayback();
  });
}

tracks.forEach((track, index) => {
  track.addEventListener("click", () => {
    if (index === currentIndex && !player.paused) {
      ++playRequest;
      player.pause();
    } else {
      playTrack(index);
    }
  });
});

document.getElementById("play-all").addEventListener("click", () => {
  player.currentTime = 0;
  playTrack(0);
});
previous.addEventListener("click", () => playTrack((currentIndex - 1 + tracks.length) % tracks.length));
next.addEventListener("click", () => playTrack((currentIndex + 1) % tracks.length));
player.addEventListener("ended", () => playTrack((currentIndex + 1) % tracks.length));
player.addEventListener("playing", () => { status.textContent = "正在播放"; renderPlayback(); });
player.addEventListener("pause", () => { status.textContent = "已暂停"; renderPlayback(); });
player.addEventListener("waiting", () => { status.textContent = "正在缓冲…"; });
player.addEventListener("error", () => {
  status.textContent = "音频加载失败，请检查网络或浏览器对该音频格式的支持。";
  renderPlayback();
});
