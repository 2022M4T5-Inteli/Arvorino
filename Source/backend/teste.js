// CÓDIGO DO SERVIDOR

// importa bibliotecas necessárias
const sqlite3 = require('sqlite3').verbose();
const fetch = require('node-fetch');

// importa bibliotecas necessárias

const express = require("express");
const hostname = '127.0.0.1';
const app = express();
const port = process.env.PORT || 3001;
var html = express.static("../frontend3/index.html")

app.use(express.static("../frontend3/"));
app.use(express.json());

app.listen(port, () => console.log(`App listening on port ${port}!`));




const bodyParser = require('body-parser');
const urlencodedParser = bodyParser.urlencoded({ extended: false });

// app.use(express.static("../frontend3/"));
app.use(express.json());

// caminho do banco de dados
const DBPATH = 'arvorino2.db'


/* DEFINIÇÃO DOS ENDPOINTS */


/* FETCH TEST POSTMAN API THINGSPEAK */
setInterval(test, 60000)
test();
async function test() {
	let response = await fetch("https://api.thingspeak.com/channels/1953984/feeds.json?minutes=1&results=1&timezone=America/Sao_Paulo") 
	let data = await response.json()
	for (let i = 0; i < data.feeds.length; i++) {
		const element = data.feeds[i];
		let sql = "INSERT INTO Teste (campo) VALUES ('" + element.field1 + "')";
		var db = new sqlite3.Database(DBPATH);
		db.run(sql, [], err => {
			if (err) {
				throw err;
			}
		});
		db.close();
	}
}

/* FETCH ESP32 DATA API THINGSPEAK */
setInterval(test, 60000)
test();
async function test() {
	let response = await fetch("https://api.thingspeak.com/channels/1963863/feeds.json?minutes=1&results=1&timezone=America/Sao_Paulo") 
	let data = await response.json()
	for (let i = 0; i < data.feeds.length; i++) {
		const element = data.feeds[i];
		let sql = "INSERT INTO Registros (temperatura, umidade, hora, minuto, dia, mes, id_estufa) VALUES ('" + element.field1 + "', '" + element.field2 + "', '" + element.field3 + "', '" + element.field4 + "', '" + element.field5 + "', '" + element.field6 + "', '" + element.field7 + "')";
		var db = new sqlite3.Database(DBPATH);
		db.run(sql, [], err => {
			if (err) {
				throw err;
			}
		});
		db.close();
	}
}

// NETWORKS - checar Registros cadastros na tabela NETWORK
app.get('/registros', (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');

	var db = new sqlite3.Database(DBPATH);
	var sql = 'SELECT * FROM Registros ORDER BY id COLLATE NOCASE'; // ordena por id
	db.all(sql, [], (err, rows) => {
		if (err) {
			throw err;
		}
		res.json(rows);
	});
	db.close();
});


// NETWORKINSERT - inserir novos Registros na tabela NETWORK
app.post('/registroinsert', urlencodedParser, (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');
	// insere valores de nome e tipo segundo a request enviada pelo cliente
	sql = "INSERT INTO Registros (temperatura, umidade, hora, minuto, dia, mes, id_estufa) VALUES ('" + req.body.temperatura + "', '" + req.body.umidade + "', '" + req.body.hora + "', '" + req.body.minuto + "', '" + req.body.dia + "', '" + req.body.mes + "', '" + req.body.id_estufa + "')";
	var db = new sqlite3.Database(DBPATH);
	db.run(sql, [], err => {
		if (err) {
			throw err;
		}
	});
	db.close();
	res.end();
});

app.get('/janelas', (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');

	var db = new sqlite3.Database(DBPATH);
	var sql = 'SELECT * FROM Janela ORDER BY id_janela COLLATE NOCASE'; // ordena por id
	db.all(sql, [], (err, rows) => {
		if (err) {
			throw err;
		}
		res.json(rows);
	});
	db.close();
});

// NETWORKINSERT - inserir novos Registros na tabela NETWORK
app.post('/janelainsert', urlencodedParser, (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');
	// insere valores de nome e tipo segundo a request enviada pelo cliente
	sql = "INSERT INTO Janela (id_estufa, numero_janela, classe) VALUES ('" + req.body.id_estufa + "', '" + req.body.numero_janela + "', '" + req.body.classe + "')))";
	var db = new sqlite3.Database(DBPATH);
	db.run(sql, [], err => {
		if (err) {
			throw err;
		}
	});
	db.close();
	res.end();
});

app.get('/estufas', (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');

	var db = new sqlite3.Database(DBPATH);
	var sql = 'SELECT * FROM Estufa ORDER BY id_estufa COLLATE NOCASE'; // ordena por id
	db.all(sql, [], (err, rows) => {
		if (err) {
			throw err;
		}
		res.json(rows);
	});
	db.close();
});

//Get estufa específica
app.post("/resultadoEixo/userupdate", urlencodedParser, (req, res) => {
	res.statusCode = 200;
	res.setHeader("Access-Control-Allow-Origin", "*"); // Isso é importante para evitar o erro de CORS
  
	sql =
	  "'SELECT * FROM Estufa WHERE id_estufa = ? ORDER BY id_estufa COLLATE NOCASE";
	var db = new sqlite3.Database(DBPATH); // Abre o banco
	var params = [];
	params.push(req.body.id_estufa);
  
	db.run(sql, params, (err) => {
	  if (err) {
		throw err;
	  }
	});
	db.close(); // Fecha o banco
	res.end();
  });

// NETWORKINSERT - inserir novos Registros na tabela NETWORK
app.post('/estufainsert', urlencodedParser, (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');
	// insere valores de nome e tipo segundo a request enviada pelo cliente
	sql = "INSERT INTO Estufa (nome_estufa, coordenador) VALUES ('" + req.body.nome_estufa + "', '" + req.body.coordenador + "')";
	var db = new sqlite3.Database(DBPATH);
	db.run(sql, [], err => {
		if (err) {
			throw err;
		}
	});
	db.close();
	res.end();
});

app.get('/statusjanelas', (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');

	var db = new sqlite3.Database(DBPATH);
	var sql = 'SELECT * FROM Status_Janela ORDER BY id_status COLLATE NOCASE'; // ordena por id
	db.all(sql, [], (err, rows) => {
		if (err) {
			throw err;
		}
		res.json(rows);
	});
	db.close();
});

// NETWORKINSERT - inserir novos Registros na tabela NETWORK
app.post('/statusjanelainsert', urlencodedParser, (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');
	// insere valores de nome e tipo segundo a request enviada pelo cliente
	sql = "INSERT INTO Status_Janela (porcentagem, status, id_janela, hora, minuto, dia, mes, ano) VALUES ('" + req.body.porcentagem + "', '" + req.body.status + "', '" + req.body.id_janela + "', '" + req.body.hora + "', '" + req.body.minuto + "', '" + req.body.dia + "', '" + req.body.mes + "', '" + req.body.ano + "')";
	var db = new sqlite3.Database(DBPATH);
	db.run(sql, [], err => {
		if (err) {
			throw err;
		}
	});
	db.close();
	res.end();
});

app.listen(port, hostname, () => {
	console.log(`BD server running at http://${hostname}:${port}/`);
  });