// 根据 main 里的 section/h2 生成侧边目录，滚动时高亮当前章节
(() => {
  const nav = document.getElementById('nav');
  if (!nav) return;
  const secs = [...document.querySelectorAll('main section[id]')];
  const links = secs.map((sec, i) => {
    const h = sec.querySelector('h2');
    const title = h.lastChild.textContent.trim();
    if (!h.querySelector('.num')) h.insertAdjacentHTML('afterbegin', `<span class="num">${i + 1}</span>`);
    const a = document.createElement('a');
    a.href = '#' + sec.id;
    a.innerHTML = `<span class="n">${i + 1}</span>${title}`;
    nav.appendChild(a);
    return { a, sec };
  });
  const spy = () => {
    let cur = links[0];
    for (const l of links) if (l.sec.getBoundingClientRect().top < 160) cur = l;
    links.forEach(l => l.a.classList.toggle('on', l === cur));
  };
  addEventListener('scroll', spy, { passive: true });
  spy();
})();
