const section = document.querySelector("section"),
overlay = document.querySelector(".overlay"),
showBtn = document.querySelector(".show-modal"),
closeBtn = document.querySelector(".close-btn");

showBtn.addEventListener("click", () => section.classList.add("active"));

overlay.addEventListener("click", () =>
section.classList.remove("active")
);

closeBtn.addEventListener("click", () =>
section.classList.remove("active")
);

temp = document.getElementById("#temperatura");
console.log(get_registros());

function get_registros() {
    let array = [];
    $.ajax({
        url: "http://10.128.0.24:1234/registros",
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
document.getElementById("temperatura").innerHTML = dados[dados.length - 1].temperatura;
document.getElementById("umidade").innerHTML = dados[dados.length - 1].umidade;
document.getElementById("estufa").innerHTML = dados[dados.length - 1].estufa;
document.getElementById("horario").innerHTML = dados[dados.length - 1].horario;