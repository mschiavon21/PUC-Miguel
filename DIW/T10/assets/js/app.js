/* ===== Dados (estrutura JSON) ===== */
const dados = {
  "parques": [
    {
      "id": 1,
      "nome": "Chapada Diamantina",
      "descricao": "Cachoeiras, grutas e vales no coração da Bahia.",
      "conteudo": "A Chapada Diamantina reúne cânions, rios de águas cor de chá e trilhas lendárias como a do Vale do Pati. É destino certo para quem gosta de caminhadas longas e banhos de cachoeira, como a Fumaça, uma das mais altas do Brasil.",
      "estado": "Bahia",
      "bioma": "Cerrado e Caatinga",
      "area": "152.000 ha",
      "criacao": "1985-09-17",
      "melhorEpoca": "Maio a setembro",
      "ingresso": "Gratuito (guia obrigatório em algumas trilhas)",
      "destaque": true,
      "imagemPrincipal": "assets/img/chapada_diamantina_0.jpg"
    },
    {
      "id": 2,
      "nome": "Lençóis Maranhenses",
      "descricao": "Dunas brancas e lagoas de água doce que surgem após as chuvas.",
      "conteudo": "Entre janeiro e agosto, a chuva enche os vales entre as dunas e forma milhares de lagoas azuis e verdes. O passeio de 4x4 e o pôr do sol na Lagoa Bonita são clássicos da região.",
      "estado": "Maranhão",
      "bioma": "Dunas e restingas",
      "area": "155.000 ha",
      "criacao": "1981-06-02",
      "melhorEpoca": "Julho a setembro",
      "ingresso": "Gratuito (passeios pagos à parte)",
      "destaque": true,
      "imagemPrincipal": "assets/img/lencois_maranhenses_0.jpg"
    },
    {
      "id": 3,
      "nome": "Foz do Iguaçu",
      "descricao": "Um dos maiores conjuntos de cataratas do planeta.",
      "conteudo": "São quase 270 quedas em meio à Mata Atlântica. A passarela até a Garganta do Diabo coloca o visitante a poucos metros da queda principal, e a fauna local inclui quatis e tucanos.",
      "estado": "Paraná",
      "bioma": "Mata Atlântica",
      "area": "185.000 ha",
      "criacao": "1939-01-10",
      "melhorEpoca": "Março a maio",
      "ingresso": "Pago (desconto para moradores)",
      "destaque": true,
      "imagemPrincipal": "assets/img/iguacu_0.jpg"
    },
    {
      "id": 4,
      "nome": "Jalapão",
      "descricao": "Fervedouros, dunas douradas e rios cristalinos no Tocantins.",
      "conteudo": "No Jalapão, o visitante flutua nos fervedouros, onde a água brota do chão com tanta pressão que impede o corpo de afundar. A região também tem cachoeiras, dunas e o famoso capim dourado.",
      "estado": "Tocantins",
      "bioma": "Cerrado",
      "area": "158.000 ha",
      "criacao": "2001-04-12",
      "melhorEpoca": "Maio a outubro",
      "ingresso": "Gratuito (acesso por 4x4)",
      "destaque": false,
      "imagemPrincipal": "assets/img/jalapao_0.jpg"
    },
    {
      "id": 5,
      "nome": "Itatiaia",
      "descricao": "O parque nacional mais antigo do Brasil, entre o RJ e Minas.",
      "conteudo": "Criado em 1937, Itatiaia protege picos como as Agulhas Negras e cachoeiras fáceis de alcançar. É ótimo para observação de aves e para quem quer montanha sem ir longe do Sudeste.",
      "estado": "Rio de Janeiro / Minas Gerais",
      "bioma": "Mata Atlântica e campos de altitude",
      "area": "28.000 ha",
      "criacao": "1937-06-14",
      "melhorEpoca": "Abril a setembro",
      "ingresso": "Pago",
      "destaque": false,
      "imagemPrincipal": "assets/img/itatiaia_0.jpg"
    },
    {
      "id": 6,
      "nome": "Fernando de Noronha",
      "descricao": "Arquipélago com praias premiadas e mergulho de classe mundial.",
      "conteudo": "Golfinhos-rotadores, tartarugas e águas de até 40 metros de visibilidade fazem de Noronha um dos melhores destinos de mergulho do país. A visitação é controlada para preservar o ecossistema.",
      "estado": "Pernambuco",
      "bioma": "Marinho-costeiro",
      "area": "11.270 ha",
      "criacao": "1988-09-14",
      "melhorEpoca": "Agosto a janeiro",
      "ingresso": "Taxa de preservação ambiental",
      "destaque": true,
      "imagemPrincipal": "assets/img/fernando_noronha_0.jpg"
    }
  ],
  "fotos": [
    { "parqueId": 1, "titulo": "Cachoeira da Fumaça", "imagem": "assets/img/chapada_diamantina_1.jpg" },
    { "parqueId": 1, "titulo": "Vale do Pati", "imagem": "assets/img/chapada_diamantina_2.jpg" },
    { "parqueId": 1, "titulo": "Poço Azul", "imagem": "assets/img/chapada_diamantina_3.jpg" },
    { "parqueId": 1, "titulo": "Morro do Pai Inácio", "imagem": "assets/img/chapada_diamantina_4.jpg" },
    { "parqueId": 1, "titulo": "Gruta da Lapa Doce", "imagem": "assets/img/chapada_diamantina_5.jpg" },
    { "parqueId": 1, "titulo": "Cachoeira do Buracão", "imagem": "assets/img/chapada_diamantina_6.jpg" },

    { "parqueId": 2, "titulo": "Lagoa Bonita", "imagem": "assets/img/lencois_maranhenses_1.jpg" },
    { "parqueId": 2, "titulo": "Lagoa Azul", "imagem": "assets/img/lencois_maranhenses_2.jpg" },
    { "parqueId": 2, "titulo": "Dunas ao entardecer", "imagem": "assets/img/lencois_maranhenses_3.jpg" },
    { "parqueId": 2, "titulo": "Travessia a pé", "imagem": "assets/img/lencois_maranhenses_4.jpg" },
    { "parqueId": 2, "titulo": "Rio Preguiças", "imagem": "assets/img/lencois_maranhenses_5.jpg" },
    { "parqueId": 2, "titulo": "Vista aérea das lagoas", "imagem": "assets/img/lencois_maranhenses_6.jpg" },

    { "parqueId": 3, "titulo": "Garganta do Diabo", "imagem": "assets/img/iguacu_1.jpg" },
    { "parqueId": 3, "titulo": "Passarela das cataratas", "imagem": "assets/img/iguacu_2.jpg" },
    { "parqueId": 3, "titulo": "Trilha das Bromélias", "imagem": "assets/img/iguacu_3.jpg" },
    { "parqueId": 3, "titulo": "Quatis na trilha", "imagem": "assets/img/iguacu_4.jpg" },
    { "parqueId": 3, "titulo": "Arco-íris sobre as quedas", "imagem": "assets/img/iguacu_5.jpg" },
    { "parqueId": 3, "titulo": "Passeio de barco", "imagem": "assets/img/iguacu_6.jpg" },

    { "parqueId": 4, "titulo": "Fervedouro do Ceiça", "imagem": "assets/img/jalapao_1.jpg" },
    { "parqueId": 4, "titulo": "Dunas do Jalapão", "imagem": "assets/img/jalapao_2.jpg" },
    { "parqueId": 4, "titulo": "Cachoeira da Velha", "imagem": "assets/img/jalapao_3.jpg" },
    { "parqueId": 4, "titulo": "Pedra Furada", "imagem": "assets/img/jalapao_4.jpg" },
    { "parqueId": 4, "titulo": "Capim dourado", "imagem": "assets/img/jalapao_5.jpg" },
    { "parqueId": 4, "titulo": "Rio Novo", "imagem": "assets/img/jalapao_6.jpg" },

    { "parqueId": 5, "titulo": "Agulhas Negras", "imagem": "assets/img/itatiaia_1.jpg" },
    { "parqueId": 5, "titulo": "Cachoeira Véu da Noiva", "imagem": "assets/img/itatiaia_2.jpg" },
    { "parqueId": 5, "titulo": "Prateleiras", "imagem": "assets/img/itatiaia_3.jpg" },
    { "parqueId": 5, "titulo": "Lago Azul", "imagem": "assets/img/itatiaia_4.jpg" },
    { "parqueId": 5, "titulo": "Mirante do Último Adeus", "imagem": "assets/img/itatiaia_5.jpg" },
    { "parqueId": 5, "titulo": "Campos de altitude", "imagem": "assets/img/itatiaia_6.jpg" },

    { "parqueId": 6, "titulo": "Baía do Sancho", "imagem": "assets/img/fernando_noronha_1.jpg" },
    { "parqueId": 6, "titulo": "Baía dos Porcos", "imagem": "assets/img/fernando_noronha_2.jpg" },
    { "parqueId": 6, "titulo": "Morro Dois Irmãos", "imagem": "assets/img/fernando_noronha_3.jpg" },
    { "parqueId": 6, "titulo": "Golfinhos-rotadores", "imagem": "assets/img/fernando_noronha_4.jpg" },
    { "parqueId": 6, "titulo": "Praia do Leão", "imagem": "assets/img/fernando_noronha_5.jpg" },
    { "parqueId": 6, "titulo": "Mergulho no naufrágio", "imagem": "assets/img/fernando_noronha_6.jpg" }
  ],
  "autor": {
    "nome": "Miguel Schiavon",
    "curso": "Ciencia da Computação",
    "sobre": "O Trilha Verde é um site criado para apresentar os principais parques nacionais do Brasil de forma simples e organizada. Aqui você pode conhecer informações sobre cada parque, visualizar fotos e descobrir um pouco mais sobre a natureza e a biodiversidade brasileira. O objetivo é facilitar o acesso a informações e incentivar o conhecimento e a valorização dos parques nacionais.",
    "redes": [
      { "nome": "GitHub", "url": "https://github.com/", "icone": "bi-github" },
      { "nome": "LinkedIn", "url": "https://www.linkedin.com/", "icone": "bi-linkedin" },
      { "nome": "Instagram", "url": "https://www.instagram.com/", "icone": "bi-instagram" }
    ]
  }
};

/* ===== Utilitários ===== */
const IMG_FALLBACK = "data:image/svg+xml;utf8," + encodeURIComponent(
  '<svg xmlns="http://www.w3.org/2000/svg" width="1200" height="800"><rect width="100%" height="100%" fill="#2f4a3a"/><text x="50%" y="50%" fill="#e9e1cf" font-size="42" text-anchor="middle" font-family="sans-serif">Imagem indisponível</text></svg>');

function esc(texto) {
  const d = document.createElement("div");
  d.textContent = texto;
  return d.innerHTML;
}
function formatarData(iso) {
  const [a, m, d] = iso.split("-");
  return `${d}/${m}/${a}`;
}
function linkDetalhe(id) { return `detalhes.html?id=${id}`; }
function imgTag(src, alt, cls = "", busca = []) {
  const dataBusca = busca.length ? ` data-busca='${JSON.stringify(busca).replace(/'/g, "&#39;")}'` : "";
  return `<img src="${esc(src)}" alt="${esc(alt)}" class="${cls}"${dataBusca} onerror="this.onerror=null;this.src='${IMG_FALLBACK}'">`;
}

/* ===== Fotos reais (Wikimedia Commons) =====
   O JSON guarda uma imagem local de reserva. Ao abrir a página, o JavaScript
   busca no Wikimedia Commons uma foto real para cada termo e troca o src. */
const BUSCA_PARQUE = {
  1: "Chapada Diamantina", 2: "Lençóis Maranhenses", 3: "Cataratas do Iguaçu",
  4: "Jalapão", 5: "Parque Nacional do Itatiaia", 6: "Fernando de Noronha"
};
const termosParque = p => [BUSCA_PARQUE[p.id], p.nome];
const termosFoto = (f, p) => [`${f.titulo} ${p.nome}`, f.titulo, BUSCA_PARQUE[p.id]];

async function candidatasCommons(termo) {
  const chave = "tvimg:" + termo;
  try {
    const salvo = sessionStorage.getItem(chave);
    if (salvo) return JSON.parse(salvo);
  } catch (e) { /* sem cache */ }
  const params = new URLSearchParams({
    action: "query", format: "json", origin: "*", generator: "search",
    gsrnamespace: 6, gsrlimit: 20, gsrsearch: termo + " filetype:bitmap",
    prop: "imageinfo", iiprop: "url|mime|size", iiurlwidth: 1200
  });
  const resp = await fetch("https://commons.wikimedia.org/w/api.php?" + params);
  const dados = await resp.json();
  const lista = Object.values((dados.query && dados.query.pages) || {})
    .sort((a, b) => a.index - b.index)
    .map(pg => ({ titulo: pg.title, info: (pg.imageinfo || [])[0] }))
    .filter(x => x.info && x.info.mime === "image/jpeg" && x.info.width >= 1000 && x.info.width > x.info.height)
    .map(x => ({ titulo: x.titulo, url: x.info.thumburl || x.info.url }));
  try { sessionStorage.setItem(chave, JSON.stringify(lista)); } catch (e) { /* ignora */ }
  return lista;
}

async function resolverFoto(termos, usadas) {
  for (const termo of termos) {
    try {
      const achada = (await candidatasCommons(termo)).find(c => !usadas.has(c.titulo));
      if (achada) { usadas.add(achada.titulo); return achada.url; }
    } catch (e) { /* tenta o próximo termo */ }
  }
  return null;
}

async function carregarFotosReais() {
  const grupos = new Map();
  document.querySelectorAll("img[data-busca]").forEach(img => {
    const chave = img.dataset.busca;
    if (!grupos.has(chave)) grupos.set(chave, []);
    grupos.get(chave).push(img);
  });
  const usadas = new Set();
  for (const [chave, imgs] of grupos) {
    const url = await resolverFoto(JSON.parse(chave), usadas);
    if (!url) continue;
    imgs.forEach(img => {
      const teste = new Image();
      teste.onload = () => { img.src = url; };
      teste.src = url;
    });
  }
}

/* ===== Cabeçalho e rodapé (compartilhados) ===== */
function montarCabecalho() {
  const el = document.getElementById("cabecalho");
  if (!el) return;
  el.innerHTML = `
    <nav class="navbar navbar-expand-sm navbar-dark topo">
      <div class="container">
        <a class="navbar-brand logo" href="index.html"><i class="bi bi-tree-fill me-2"></i>Trilha Verde</a>
        <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#menu" aria-controls="menu" aria-expanded="false" aria-label="Abrir menu">
          <span class="navbar-toggler-icon"></span>
        </button>
        <div class="collapse navbar-collapse" id="menu">
          <ul class="navbar-nav ms-auto">
            <li class="nav-item"><a class="nav-link" href="index.html#destaques">Destaques</a></li>
            <li class="nav-item"><a class="nav-link" href="index.html#parques">Todos os parques</a></li>
            <li class="nav-item"><a class="nav-link" href="index.html#autoria">Autoria</a></li>
          </ul>
        </div>
      </div>
    </nav>`;
}

/* ===== Home ===== */
function montarCarrossel() {
  const destaques = dados.parques.filter(p => p.destaque);
  const itens = destaques.map((p, i) => `
    <div class="carousel-item ${i === 0 ? "active" : ""}">
      <a href="${linkDetalhe(p.id)}" class="slide-link" aria-label="Ver detalhes de ${esc(p.nome)}">
        ${imgTag(p.imagemPrincipal, p.nome, "d-block w-100 slide-img", termosParque(p))}
      </a>
      <div class="carousel-caption slide-legenda">
        <h3><a href="${linkDetalhe(p.id)}">${esc(p.nome)}</a></h3>
        <p>${esc(p.descricao)}</p>
      </div>
    </div>`).join("");
  const indicadores = destaques.map((p, i) => `
    <button type="button" data-bs-target="#carrosselDestaques" data-bs-slide-to="${i}" ${i === 0 ? 'class="active" aria-current="true"' : ""} aria-label="${esc(p.nome)}"></button>`).join("");

  document.getElementById("carrossel").innerHTML = `
    <div id="carrosselDestaques" class="carousel slide" data-bs-ride="carousel">
      <div class="carousel-indicators">${indicadores}</div>
      <div class="carousel-inner">${itens}</div>
      <button class="carousel-control-prev" type="button" data-bs-target="#carrosselDestaques" data-bs-slide="prev">
        <span class="carousel-control-prev-icon" aria-hidden="true"></span><span class="visually-hidden">Anterior</span>
      </button>
      <button class="carousel-control-next" type="button" data-bs-target="#carrosselDestaques" data-bs-slide="next">
        <span class="carousel-control-next-icon" aria-hidden="true"></span><span class="visually-hidden">Próximo</span>
      </button>
    </div>`;
}

function montarCards() {
  document.getElementById("cards").innerHTML = dados.parques.map(p => `
    <div class="col">
      <article class="card h-100 cartao">
        <a href="${linkDetalhe(p.id)}">${imgTag(p.imagemPrincipal, p.nome, "card-img-top", termosParque(p))}</a>
        <div class="card-body">
          <p class="cartao-estado mb-1"><i class="bi bi-geo-alt-fill"></i> ${esc(p.estado)}</p>
          <h3 class="card-title h5"><a href="${linkDetalhe(p.id)}">${esc(p.nome)}</a></h3>
          <p class="card-text">${esc(p.descricao)}</p>
        </div>
        <div class="card-footer">
          <a href="${linkDetalhe(p.id)}" class="btn btn-sm btn-trilha">Ver detalhes</a>
        </div>
      </article>
    </div>`).join("");
}

function montarAutoria() {
  const a = dados.autor;
  document.getElementById("autoria").innerHTML = `
    <div class="row g-4">
      <div class="col-md-7">
        <h3 class="h6 subtitulo">Sobre</h3>
        <p>${esc(a.sobre)}</p>
      </div>
      <div class="col-md-5">
        <h3 class="h6 subtitulo">Autoria</h3>
        <div class="d-flex align-items-start gap-3">
          <i class="bi bi-person-circle avatar"></i>
          <ul class="list-unstyled mb-0">
            <li><strong>Aluno:</strong> ${esc(a.nome)}</li>
            <li><strong>Curso:</strong> ${esc(a.curso)}</li>
          </ul>
        </div>
        <p class="mt-3 mb-0"><strong>Redes sociais:</strong>
          ${a.redes.map(r => `<a class="rede" href="${esc(r.url)}" target="_blank" rel="noopener" aria-label="${esc(r.nome)}"><i class="bi ${r.icone}"></i></a>`).join("")}
        </p>
      </div>
    </div>`;
}

/* ===== Detalhes ===== */
function montarDetalhes() {
  const alvo = document.getElementById("detalhes");
  const id = Number(new URLSearchParams(window.location.search).get("id"));
  const parque = dados.parques.find(p => p.id === id);

  if (!parque) {
    alvo.innerHTML = `
      <div class="alert alert-warning">
        Parque não encontrado. <a href="index.html" class="alert-link">Volte para a página inicial</a> e escolha um da lista.
      </div>`;
    document.getElementById("secao-fotos").classList.add("d-none");
    return;
  }

  document.title = `${parque.nome} | Trilha Verde`;
  const fatos = [
    ["bi-geo-alt-fill", "Localização", parque.estado],
    ["bi-tree-fill", "Bioma", parque.bioma],
    ["bi-arrows-fullscreen", "Área protegida", parque.area],
    ["bi-calendar-event", "Criação do parque", formatarData(parque.criacao)],
    ["bi-sun-fill", "Melhor época para visitar", parque.melhorEpoca],
    ["bi-ticket-perforated-fill", "Ingresso", parque.ingresso]
  ];

  alvo.innerHTML = `
    <div class="row g-4 align-items-start">
      <div class="col-lg-5">
        ${imgTag(parque.imagemPrincipal, parque.nome, "img-fluid detalhe-img", termosParque(parque))}
      </div>
      <div class="col-lg-7">
        <h1 class="detalhe-titulo">${esc(parque.nome)}</h1>
        <p class="lead">${esc(parque.descricao)}</p>
        <p>${esc(parque.conteudo)}</p>
        <dl class="row fatos">
          ${fatos.map(([icone, rotulo, valor]) => `
            <dt class="col-sm-5"><i class="bi ${icone} me-2"></i>${rotulo}</dt>
            <dd class="col-sm-7">${esc(valor)}</dd>`).join("")}
        </dl>
      </div>
    </div>`;

  const fotos = dados.fotos.filter(f => f.parqueId === parque.id);
  document.getElementById("galeria").innerHTML = fotos.map(f => `
    <figure class="foto">
      ${imgTag(f.imagem, f.titulo, "", termosFoto(f, parque))}
      <figcaption>${esc(f.titulo)}</figcaption>
    </figure>`).join("");

  const galeria = document.getElementById("galeria");
  const passo = () => galeria.clientWidth * 0.8;
  document.getElementById("galeria-anterior").onclick = () => galeria.scrollBy({ left: -passo(), behavior: "smooth" });
  document.getElementById("galeria-proximo").onclick = () => galeria.scrollBy({ left: passo(), behavior: "smooth" });
}

/* ===== Inicialização ===== */
document.addEventListener("DOMContentLoaded", () => {
  montarCabecalho();
  const pagina = document.body.dataset.pagina;
  if (pagina === "home") {
    montarCarrossel();
    montarCards();
    montarAutoria();
    carregarFotosReais();
  } else if (pagina === "detalhes") {
    montarDetalhes();
    carregarFotosReais();
  }
});
