// CÓDIGO DO SERVIDOR - CRUD

// importa bibliotecas necessárias
const express = require('express');
const sqlite3 = require('sqlite3').verbose();

// cria servidor no endereço local e determina que a pasta frontend deve ser usada como source
const app = express();
const hostname = '10.128.0.24';
const port = 1234;
const bodyParser = require('body-parser');
const urlencodedParser = bodyParser.urlencoded({ extended: false });

app.use(express.static("../frontend/temp_e_umidade"));

app.use(express.json());

// caminho do banco de dados
const DBPATH = 'arvorino2.db'


/* ================================================ DEFINIÇÃO DOS ENDPOINTS ==============================================*/

/*T A B E L A   R E G I S T R O S*/
// Read - Tabela registros
app.get('/registros', (req, res) => {
	res.statusCode = 200; 
	res.setHeader('Access-Control-Allow-Origin', '*'); 
	var db = new sqlite3.Database(DBPATH); 
	var sql = 'SELECT * FROM registros ORDER BY id DESC'; 
	db.all(sql, [], (err, rows) => {
		if (err) { throw err; }
		res.json(rows);
	}); db.close();
});

// Insert - Tabela registros
app.post('/registro/insert', urlencodedParser, (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');
	// insere valores de nome e tipo segundo a request enviada pelo cliente
	sql = "INSERT INTO registros (Temperatura, Umidade, Horario, Estufa) VALUES ('" + req.body.Temperatura + "', '" + req.body.Umidade + "', '" + req.body.Horario + "', '" + req.body.Estufa + "')";
	var db = new sqlite3.Database(DBPATH);
	db.run(sql, [], err => {
		if (err) {
			throw err;
		}
	});
	db.close();
	res.end();
});

//Delete - Tabela registros
app.post("/registro/delete", urlencodedParser, (req, res) => {
	res.statusCode = 200;
	res.setHeader("Access-Control-Allow-Origin", "*"); // Isso é importante para evitar o erro de CORS
	const sql = "DELETE FROM registro WHERE Horario =?";
	var db = new sqlite3.Database(DBPATH); // Abre o banco
	var params = req.body.Horario;
	db.run(sql, params, function (err) {
		if (err) return console.error(err.message);
	});

	db.close();
	res.end();
});


/* T A B E L A   J A N E L A S*/

// Read - Tabela Janela
app.get('/janelas', (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');

	var db = new sqlite3.Database(DBPATH);
	var sql = 'SELECT * FROM Janela ORDER BY id COLLATE NOCASE'; // ordena por id
	db.all(sql, [], (err, rows) => {
		if (err) {
			throw err;
		}
		res.json(rows);
	});
	db.close();
});

// Insert - Tabela Janela
app.post('/janela/insert', urlencodedParser, (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');
	// insere valores de nome e tipo segundo a request enviada pelo cliente
	sql = "INSERT INTO Janela (id_estufa) VALUES ('" + req.body.id_estufa + "')";
	var db = new sqlite3.Database(DBPATH);
	db.run(sql, [], err => {
		if (err) {
			throw err;
		}
	});
	db.close();
	res.end();
});

//Delete - Tabela Janela
app.post("/janela/delete", urlencodedParser, (req, res) => {
	res.statusCode = 200;
	res.setHeader("Access-Control-Allow-Origin", "*"); // Isso é importante para evitar o erro de CORS
	const sql = "DELETE FROM Janela WHERE id_janela =?";
	var db = new sqlite3.Database(DBPATH); // Abre o banco
	var params = req.body.id_janela;
	db.run(sql, params, function (err) {
		if (err) return console.error(err.message);
	});

	db.close();
	res.end();
});


/*T A B E L A  E S T U F A*/

//Read - Tabela Estufas
app.get('/estufas', (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');

	var db = new sqlite3.Database(DBPATH);
	var sql = 'SELECT * FROM Estufa ORDER BY id COLLATE NOCASE'; // ordena por id
	db.all(sql, [], (err, rows) => {
		if (err) {
			throw err;
		}
		res.json(rows);
	});
	db.close();
});

// Insert - Tebela Estufas
app.post('/estufa/insert', urlencodedParser, (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');
	// insere valores de nome e tipo segundo a request enviada pelo cliente
	sql = "INSERT INTO Estufa (sensor) VALUES ('" + req.body.sensor + "')";
	var db = new sqlite3.Database(DBPATH);
	db.run(sql, [], err => {
		if (err) {
			throw err;
		}
	});
	db.close();
	res.end();
});

// Delete - Tabela Estufas
app.post("/estufas/delete", urlencodedParser, (req, res) => {
	res.statusCode = 200;
	res.setHeader("Access-Control-Allow-Origin", "*"); // Isso é importante para evitar o erro de CORS
	const sql = "DELETE FROM Estufa WHERE sensor =?";
	var db = new sqlite3.Database(DBPATH); // Abre o banco
	var params = req.body.sensor;
	db.run(sql, params, function (err) {
		if (err) return console.error(err.message);
	});

	db.close();
	res.end();
});

//Update - Tabela Estufas
app.post('/estufa/update', urlencodedParser, (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');
	// permite alterar o nome e o tipo dado certo id (chave primária)
	sql = "UPDATE Estufa SET sensor = '" + req.body.sensor, "' WHERE id = " + req.body.id;
	var db = new sqlite3.Database(DBPATH);
	db.run(sql, [], err => {
		if (err) {
			throw err;
		}
		res.end();
	});
	db.close();
});

/*T A B E L A   S T A T U S_J A N E L A*/

//Read - Tabela Status_Janela
app.get('/statusjanelas', (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');

	var db = new sqlite3.Database(DBPATH);
	var sql = 'SELECT * FROM Status_Janela ORDER BY id COLLATE NOCASE'; // ordena por id
	db.all(sql, [], (err, rows) => {
		if (err) {
			throw err;
		}
		res.json(rows);
	});
	db.close();
});

// Insert - Tabela Status_Janela
app.post('/statusjanela/insert', urlencodedParser, (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');
	// insere valores de nome e tipo segundo a request enviada pelo cliente
	sql = "INSERT INTO Status_Janela (porcentagem, status, id_janela, hora) VALUES ('" + req.body.procentagem + "', '" + req.body.status + "', '" + req.body.id_janela + "', '" + req.body.hora + "')";
	var db = new sqlite3.Database(DBPATH);
	db.run(sql, [], err => {
		if (err) {
			throw err;
		}
	});
	db.close();
	res.end();
});

//Delete - Tabela Status_Janela
app.post("/statusjanela/delete", urlencodedParser, (req, res) => {
	res.statusCode = 200;
	res.setHeader("Access-Control-Allow-Origin", "*"); // Isso é importante para evitar o erro de CORS
	const sql = "DELETE FROM Status_Janela WHERE id =?";
	var db = new sqlite3.Database(DBPATH); // Abre o banco
	var params = req.body.id;
	db.run(sql, params, function (err) {
		if (err) return console.error(err.message);
	});

	db.close();
	res.end();
});

/* ============Inicia o servidor ==============*/
app.listen(port, hostname, () => {
	console.log(`Server running at http://${hostname}:${port}/`);
});