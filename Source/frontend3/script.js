var i = 3

function showSensors(){
    var url1 = "http://127.0.0.1:3080/resposta/users";
    var resposta1;
    var xhttp1 = new XMLHttpRequest();
    xhttp1.open("GET", url1, false);
    xhttp1.send();
    resposta1 = JSON.parse(xhttp1.responseText);
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