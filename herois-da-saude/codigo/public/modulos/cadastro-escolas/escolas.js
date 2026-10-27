// TI2 - Heróis da Saúde
// Cadastro de escolas (inserir, alterar e excluir) usando o JSON Server
// Eduardo Augusto Freitas Nogueira

const API_ESCOLAS = '/escolas';

// escolas que vieram do db.json
let escolas = [];

// id da escola clicada na tabela (null = nenhuma)
let escolaSelecionadaId = null;

const form = document.getElementById('form-escola');
const tabela = document.getElementById('tabela-escolas');
const btnInserir = document.getElementById('btn-inserir');
const btnExcluir = document.getElementById('btn-excluir');
const btnAlterar = document.getElementById('btn-alterar');

// pega as escolas no servidor e mostra na tabela
function carregarEscolas() {
    fetch(API_ESCOLAS)
        .then(response => response.json())
        .then(data => {
            escolas = data;
            exibirEscolas();
        })
        .catch(error => {
            console.error('Erro ao ler escolas via API JSONServer:', error);
            alert('Erro ao carregar as escolas. O servidor está rodando (npm start)?');
        });
}

// monta a tabela
function exibirEscolas() {
    tabela.innerHTML = '';

    if (escolas.length == 0) {
        tabela.innerHTML = '<tr><td colspan="5" class="text-center text-muted">Nenhuma escola cadastrada.</td></tr>';
        return;
    }

    for (let escola of escolas) {
        let linha = document.createElement('tr');
        let colunas = [
            escola.nome,
            escola.cnpj,
            `${escola.endereco.cidade}/${escola.endereco.estado}`,
            escola.codigo_inep,
            escola.dependencia_administrativa,
        ];
        for (let valor of colunas) {
            let celula = document.createElement('td');
            celula.textContent = valor;
            linha.appendChild(celula);
        }

        if (escola.id == escolaSelecionadaId) {
            linha.classList.add('selecionada');
        }
        linha.addEventListener('click', () => selecionarEscola(escola.id));
        tabela.appendChild(linha);
    }
}

// quando clica numa linha joga os dados no form
// se clicar na mesma de novo, desmarca
function selecionarEscola(id) {
    if (escolaSelecionadaId == id) {
        limparFormulario();
        return;
    }

    let escola = escolas.find(e => e.id == id);
    escolaSelecionadaId = id;

    document.getElementById('nome').value = escola.nome;
    document.getElementById('cnpj').value = escola.cnpj;
    document.getElementById('rua').value = escola.endereco.rua;
    document.getElementById('numero').value = escola.endereco.numero;
    document.getElementById('cep').value = escola.endereco.cep;
    document.getElementById('bairro').value = escola.endereco.bairro;
    document.getElementById('cidade').value = escola.endereco.cidade;
    document.getElementById('estado').value = escola.endereco.estado;
    document.getElementById('codigo_inep').value = escola.codigo_inep;
    document.getElementById('dependencia').value = escola.dependencia_administrativa;

    atualizarBotoes();
    exibirEscolas();
}

// pega o que ta no form e monta o objeto igual ao do db.json
function lerFormulario() {
    return {
        nome: document.getElementById('nome').value.trim(),
        cnpj: document.getElementById('cnpj').value.trim(),
        endereco: {
            rua: document.getElementById('rua').value.trim(),
            numero: document.getElementById('numero').value.trim(),
            cep: document.getElementById('cep').value.trim(),
            bairro: document.getElementById('bairro').value.trim(),
            cidade: document.getElementById('cidade').value.trim(),
            estado: document.getElementById('estado').value.trim().toUpperCase(),
        },
        codigo_inep: document.getElementById('codigo_inep').value.trim(),
        dependencia_administrativa: document.getElementById('dependencia').value,
    };
}

// confere se nao tem campo vazio
function formularioValido() {
    // tira os espaços pra nao aceitar campo so com espaço
    for (let campo of form.querySelectorAll('input')) {
        campo.value = campo.value.trim();
    }

    form.classList.add('was-validated');
    if (!form.checkValidity()) {
        alert('Preencha todos os campos antes de continuar.');
        return false;
    }
    return true;
}

// limpa tudo e tira a seleção
function limparFormulario() {
    form.reset();
    form.classList.remove('was-validated');
    escolaSelecionadaId = null;
    atualizarBotoes();
    exibirEscolas();
}

// sem escola selecionada so da pra inserir
// com escola selecionada so da pra excluir ou alterar
function atualizarBotoes() {
    let temSelecao = escolaSelecionadaId != null;
    btnInserir.disabled = temSelecao;
    btnExcluir.disabled = !temSelecao;
    btnAlterar.disabled = !temSelecao;
}

// botao inserir (POST)
function inserirEscola() {
    if (!formularioValido()) return;

    fetch(API_ESCOLAS, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(lerFormulario()),
    })
        .then(response => response.json())
        .then(() => {
            alert('Escola inserida com sucesso.');
            limparFormulario();
            carregarEscolas();
        })
        .catch(error => {
            console.error('Erro ao inserir escola via API JSONServer:', error);
            alert('Erro ao inserir a escola.');
        });
}

// botao excluir (DELETE)
function excluirEscola() {
    let escola = escolas.find(e => e.id == escolaSelecionadaId);
    if (!confirm(`Tem certeza que deseja excluir a escola "${escola.nome}"?`)) return;

    fetch(`${API_ESCOLAS}/${escolaSelecionadaId}`, { method: 'DELETE' })
        .then(() => {
            alert('Escola excluída com sucesso.');
            limparFormulario();
            carregarEscolas();
        })
        .catch(error => {
            console.error('Erro ao excluir escola via API JSONServer:', error);
            alert('Erro ao excluir a escola.');
        });
}

// botao alterar (PUT)
function alterarEscola() {
    if (!formularioValido()) return;

    fetch(`${API_ESCOLAS}/${escolaSelecionadaId}`, {
        method: 'PUT',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(lerFormulario()),
    })
        .then(response => response.json())
        .then(() => {
            alert('Escola alterada com sucesso.');
            limparFormulario();
            carregarEscolas();
        })
        .catch(error => {
            console.error('Erro ao alterar escola via API JSONServer:', error);
            alert('Erro ao alterar a escola.');
        });
}

btnInserir.addEventListener('click', inserirEscola);
btnExcluir.addEventListener('click', excluirEscola);
btnAlterar.addEventListener('click', alterarEscola);

carregarEscolas();
