// =========================== HOME SCREEN ===============================

// VARIÁVEIS GLOBAIS
var i = 0;



//FUNÇÃO PARA MOSTRAR AS ESTUFAS CADASTRADAS
function showSensors(){
// PEGAR DADOS SOBRE AS ESTUFAS
    var url1 = "http://127.0.0.1:3001/estufas";
    var sensores;
    var xhttp1 = new XMLHttpRequest();
    xhttp1.open("GET", url1, false);
    xhttp1.send();
    sensores = JSON.parse(xhttp1.responseText);

//PEGAR DADOS SOBRE A TEMPERATURA E A UMIDADE
    var url2 = "http://127.0.0.1:3001/registros";
    var registros;
    var xhttp2 = new XMLHttpRequest();
    xhttp2.open("GET", url2, false);
    xhttp2.send();
    registros = JSON.parse(xhttp2.responseText);
    registros[registros.length - 1].id_estufa = 1;

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
        status.setAttribute("class", "status");
        status.setAttribute("id", "stt"+i);
        status.textContent = "Regular"
        var info = document.createElement("button");
        info.textContent = "Informações";
        info.setAttribute("class", "status");
        var linkTo = document.createElement("a");
        linkTo.setAttribute("href", "info.html");
        linkTo.setAttribute("id", "linkTo"+i);
        if(sensores[i].id_estufa == registros[registros.length - 1].id_estufa && parseInt(registros[registros.length - 1].temperatura)/100 > 27){
            status.setAttribute("class", "statusH");
            status.textContent = "Alerta";
        } 


        document.getElementById("sensor"+i).appendChild(sensor);
        document.getElementById("sensor"+i).appendChild(title);
        document.getElementById("sensor"+i).appendChild(status);
        document.getElementById("sensor"+i).appendChild(linkTo);
        document.getElementById("linkTo"+i).appendChild(info);
    }
}

//FUNÇÃO PARA ABRIR POPUP
function addSensor(){
  var add = document.getElementById("popupAddSensor");
  add.setAttribute("display", "block");
}

//FUNÇÃO PARA ADICIONAR NO BANCO
function saveSensor(){
  $.ajax({
    url: "http://127.0.0.1:3001/estufainsert",
    type: 'POST',
    async: false,
    data: {
      nome_estufa: $("#stoveName").html(),
      coordenador: $("#manager").html(),
      }
  });
  var btnsave = document.getElementById("save");
  btnsave.setAttribute("display", "hide");
}



// ========================== INFO SCREEN =============================
function collapse(){
    var coll = document.getElementsByClassName("collapsible");
    var i;
    
    for (i = 0; i < coll.length; i++) {
      coll[i].addEventListener("click", function() {
        this.classList.toggle("active");
        var content = this.nextElementSibling;
        if (content.style.display === "block") {
          content.style.display = "none";
          document.getElementById("collapse").style.borderRadius = "20px";
        } else {
          content.style.display = "block";
          document.getElementById("collapse").style.borderRadius = "20px 20px 0px 0px";
        }
      });
    }
}

function showRecord(){
  var url2 = "http://127.0.0.1:3001/registros";
  var registros;
  var xhttp2 = new XMLHttpRequest();
  xhttp2.open("GET", url2, false);
  xhttp2.send();
  registros = JSON.parse(xhttp2.responseText);
  var temperatura = document.getElementById("temp"); 
  temperatura.textContent = parseInt(registros[registros.length - 1].temperatura)/100 + "°C";
  var umidade = document.getElementById("umid");
  umidade.textContent = parseInt(registros[registros.length - 1].umidade)/100 + "%";
}


// ========== DOWNLOAD CSV ========================
//https://medium.com/@danny.pule/export-json-to-csv-file-using-javascript-a0b7bc5b00d2
// function exportCSVFile(headers, items, fileTitle) {
//   if (headers) {
//       items.unshift(headers);
//   }

//   // Convert Object to JSON
//   var jsonObject = JSON.stringify(items);

//   var csv = this.convertToCSV(jsonObject);

//   var exportedFilenmae = fileTitle + '.csv' || 'export.csv';

//   var blob = new Blob([csv], { type: 'text/csv;charset=utf-8;' });
//   if (navigator.msSaveBlob) { // IE 10+
//       navigator.msSaveBlob(blob, exportedFilenmae);
//   } else {
//       var link = document.createElement("a");
//       if (link.download !== undefined) { // feature detection
//           // Browsers that support HTML5 download attribute
//           var url = URL.createObjectURL(blob);
//           link.setAttribute("href", url);
//           link.setAttribute("download", exportedFilenmae);
//           link.style.visibility = 'hidden';
//           document.body.appendChild(link);
//           link.click();
//           document.body.removeChild(link);
//       }
//   }
// }

