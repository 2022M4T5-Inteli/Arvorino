temp = document.getElementById("#temperatura");
console.log(get_registros());

function get_registros() {
    let array = [];
    $.ajax({
        url: "http://127.0.0.1:1234/registros",
        type: 'GET',
        async: false,
        success: data => {
            data.forEach(element => {
                array.push(element);
            });
        }
    });
    return array;
}
var dados = get_registros();

//alert(dados[dados.length - 1].umidade);

document.getElementById("temperatura").innerHTML = dados[dados.length - 1].temperatura;
document.getElementById("umidade").innerHTML = dados[dados.length - 1].umidade;
document.getElementById("estufa").innerHTML = dados[dados.length - 1].id_estufa;
document.getElementById("horario").innerHTML = dados[dados.length - 1].hora;