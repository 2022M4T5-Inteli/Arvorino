// CÓDIGO DO SERVIDOR

// importa bibliotecas necessárias
const express = require('express'); 
const sqlite3 = require('sqlite3').verbose();

// cria servidor no endereço local e determina que a pasta frontend deve ser usada como source
const app = express();
const hostname = '127.0.0.1';
const port = 1234;
const bodyParser = require('body-parser');
const urlencodedParser = bodyParser.urlencoded({ extended: false });

app.use(express.static("../frontend/"));

app.use(express.json());

// caminho do banco de dados
const DBPATH = 'arvorino2.db'


/* DEFINIÇÃO DOS ENDPOINTS */

// NETWORKS - checar Registros cadastros na tabela NETWORK
app.get('/registros', (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');

	var db = new sqlite3.Database(DBPATH); 
  var sql = 'SELECT * FROM Registros ORDER BY id COLLATE NOCASE'; // ordena por id
	db.all(sql, [],  (err, rows ) => {
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
	sql = "INSERT INTO Registros (temperatura, umidade, hora, minuto, dia, mes, ano, id_estufa) VALUES ('" + req.body.temperatura + "', '" + req.body.umidade + "', '" + req.body.hora + "', '" + req.body.minuto + "', '" + req.body.dia + "', '" + req.body.mes + "', '" + req.body.ano + "', '" + req.body.id_estufa + "')";
	var db = new sqlite3.Database(DBPATH);
	db.run(sql, [],  err => {
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
  var sql = 'SELECT * FROM Janela ORDER BY id COLLATE NOCASE'; // ordena por id
	db.all(sql, [],  (err, rows ) => {
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
	db.run(sql, [],  err => {
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
  var sql = 'SELECT * FROM Estufa ORDER BY id COLLATE NOCASE'; // ordena por id
	db.all(sql, [],  (err, rows ) => {
		if (err) {
		    throw err;
		}
		res.json(rows);
	});
	db.close(); 
});

// NETWORKINSERT - inserir novos Registros na tabela NETWORK
app.post('/estufainsert', urlencodedParser, (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');
	// insere valores de nome e tipo segundo a request enviada pelo cliente
	sql = "INSERT INTO Estufa (nome_estufa, coordenador) VALUES ('" + req.body.nome_estufa + "', '" + req.body.coordenador + "')";
	var db = new sqlite3.Database(DBPATH);
	db.run(sql, [],  err => {
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
  var sql = 'SELECT * FROM Status_Janela ORDER BY id COLLATE NOCASE'; // ordena por id
	db.all(sql, [],  (err, rows ) => {
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
	sql = "INSERT INTO Status_Janela (porcentagem, status, id_janela, hora, minuto, dia, mes, ano) VALUES ('" + req.body.porcentagem + "', '" + req.body.status + "', '" + req.body.hora + "', '" + req.body.minuto + "', '" + req.body.dia + "', '" + req.body.mes + "', '" + req.body.ano + "', '" + req.body.id_janela + "')";
	var db = new sqlite3.Database(DBPATH);
	db.run(sql, [],  err => {
		if (err) {
		    throw err;
		}
	});
	db.close();
	res.end();
});

/* Inicia o servidor */
app.listen(port, hostname, () => {
    console.log(`Server running at http://${hostname}:${port}/`);
  });