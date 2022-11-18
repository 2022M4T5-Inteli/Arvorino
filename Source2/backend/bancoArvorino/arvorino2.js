// CÓDIGO DO SERVIDOR - CRUD

// importa bibliotecas necessárias
const express = require('express'); 
const sqlite3 = require('sqlite3').verbose();

// cria servidor no endereço local e determina que a pasta frontend deve ser usada como source
const app = express();
const hostname = '127.0.0.1';
const port = 1234;
const bodyParser = require('body-parser');
const urlencodedParser = bodyParser.urlencoded({ extended: false });

app.use(express.static("../frontend/temp_e_umidade/"));

app.use(express.json());

// caminho do banco de dados
const DBPATH = 'arvorino2.db'

app.get('/', function(request, response){
    response.sendFile('C:\Users\Inteli\Documents\git-aula\Projeto1\Source\frontend\temp_e_umidade\index.html', { root: '.' });
});
/* ================================================ DEFINIÇÃO DOS ENDPOINTS ==============================================*/

/*T A B E L A   R E G I S T R O S*/
// Read - Tabela registros
app.get('/registros', (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');

	var db = new sqlite3.Database(DBPATH); 
  var sql = 'SELECT * FROM registros ORDER BY id COLLATE NOCASE'; // ordena por id
	db.all(sql, [],  (err, rows ) => {
		if (err) {
		    throw err;
		}
		res.json(rows);
	});
	db.close(); 
});


// Insert - Tabela registros
app.post('/registro/insert', urlencodedParser, (req, res) => {
	res.statusCode = 200;
	res.setHeader('Access-Control-Allow-Origin', '*');
	// insere valores de nome e tipo segundo a request enviada pelo cliente
	sql = "INSERT INTO registros (Temperatura, Umidade, Horario) VALUES ('" + req.body.Temperatura + "', '" + req.body.Umidade + "', '" + req.body.Horario + "')";
	var db = new sqlite3.Database(DBPATH);
	db.run(sql, [],  err => {
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


/* ============Inicia o servidor ==============*/
app.listen(port, hostname, () => {
    console.log(`Server running at http://${hostname}:${port}/`);
  });