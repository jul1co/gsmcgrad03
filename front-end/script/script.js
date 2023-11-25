/* Definições de predefinições para variáveis de estilo, relacionadas à cor associada a um status do sensor */
var redTheme = {
    "--normal": "#ed1b2e",
    "--darker": "#c71625"
};

var greenTheme = {
    "--normal": "#4caf50",
    "--darker": "#3d8d40"
};

/* Varíavel que armazena o tema atual (temporário) */
var currentTheme = 'red'

function changeColor() {
    if(currentTheme === 'red') {
        applyGreenTheme();
        currentTheme = 'green';
    } else {
        applyRedTheme();
        currentTheme = 'red'
    }
}

/* Altera as variáveis do CSS para aplicar o tema */
function applyTheme(theme) {
    for(var property in theme) {
        document.documentElement.style.setProperty(property, theme[property]);
    }
}

function applyGreenTheme() {
    applyTheme(greenTheme);
    var figures = document.querySelectorAll('figure');
    figures.forEach(function(figure) {
        /* 
            Essa função forEach() irá selecionar todas as tags passadas no QSA e
            para cada uma, irá selecionar a imagem correspondente. Será executado
            outro QS que selecionará a fonte da imagem e o texto alternativo
            presente dentro da tag figure, trocando-os de modo a respeitar o tema
            selecionado.
        */
        var image = figure.querySelector('img');
        image.src = "./images/check-icon.png"
        image.alt = "Ícone verde representando que está tudo certo"
    });
}

function applyRedTheme() {
    applyTheme(redTheme);
    var figures = document.querySelectorAll('figure');
    figures.forEach(function(figure) {
        /* 
            Essa função forEach() irá selecionar todas as tags passadas no QSA e
            para cada uma, irá selecionar a imagem correspondente. Será executado
            outro QS que selecionará a fonte da imagem e o texto alternativo
            presente dentro da tag figure, trocando-os de modo a respeitar o tema
            selecionado.
        */
        var image = figure.querySelector('img');
        image.src = "./images/error-icon.png"
        image.alt = "Ícone vermelho representando um erro"
    });
}