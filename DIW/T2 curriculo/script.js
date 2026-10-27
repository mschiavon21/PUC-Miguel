const prefersReduced = window.matchMedia('(prefers-reduced-motion: reduce)').matches;

document.querySelectorAll('nav a').forEach(link => {
    link.addEventListener('click', function (e) {
        e.preventDefault();

        const destino = document.querySelector(this.getAttribute('href'));
        if (!destino) return;

        if (prefersReduced) {
            destino.scrollIntoView();
            return;
        }

        const maxScroll = document.documentElement.scrollHeight - window.innerHeight;
        const posicao = Math.min(
            destino.getBoundingClientRect().top + window.scrollY - 20,
            maxScroll
        );

        window.scrollTo({ top: posicao, behavior: 'smooth' });
    });
});

window.addEventListener('scroll', () => {
    const maxScroll = document.documentElement.scrollHeight - window.innerHeight;
    if (window.scrollY > maxScroll) {
        window.scrollTo({ top: maxScroll });
    }
});
