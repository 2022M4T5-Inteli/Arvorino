var i = 3

function showSensors(){
// PEGAR DADOS SOBRE AS ESTUFAS
    var url1 = "http://127.0.0.1:1234/estufas";
    var sensores;
    var xhttp1 = new XMLHttpRequest();
    xhttp1.open("GET", url1, false);
    xhttp1.send();
    sensores = JSON.parse(xhttp1.responseText);

//PEGAR DADOS SOBRE A TEMPERATURA E A UMIDADE
    var url2 = "http://127.0.0.1:1234/registros";
    var registros;
    var xhttp2 = new XMLHttpRequest();
    xhttp2.open("GET", url2, false);
    xhttp2.send();
    registros = JSON.parse(xhttp2.responseText)

    for(var i=0; i < sensores.length; i++){
        var divSensor = document.createElement("div");
        divSensor.setAttribute("class", "s sensor" + i);
        divSensor.setAttribute("id", "sensor"+i);
        document.getElementById("allSensors").appendChild(divSensor);


        var sensor = document.createElement("img");
        sensor.setAttribute("src", "resources/imagens/monitoramento 4.png");
        sensor.setAttribute("alt", "sensor");
        var title = document.createElement("h1");
        title.setAttribute("class", "stove");
        title.textContent = sensores[i].nome_estufa;
        var status = document.createElement("button");

        document.getElementById("sensor"+i).appendChild(sensor);
        document.getElementById("sensor"+i).appendChild(title);
    }


}

function addSensor(){
    var url1 = "http://127.0.0.1:3080/resposta/users";
    var resposta1;
    var xhttp1 = new XMLHttpRequest();
    xhttp1.open("GET", url1, false);
    xhttp1.send();
    resposta1 = JSON.parse(xhttp1.responseText);

    console.log("aqui");
    var divSensor = document.createElement("div");
    divSensor.setAttribute("class", "s sensor" + i);
    divSensor.setAttribute("id", "sensor"+i);
    document.getElementById("allSensors").appendChild(divSensor);


    var sensor = document.createElement("img");
    sensor.setAttribute("src", "resources/imagens/monitoramento 4.png");
    sensor.setAttribute("alt", "sensor");
    document.getElementById("sensor"+i).appendChild(sensor);


    i += 1;
}