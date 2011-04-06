var bayesian = require("./build/default/bayesian"), start = Date.now();

//er is error, res is result, n is name
/*bayesian.doSomething(2, 4, "hello", function (er, res, n) {
  console.log("js "+(Date.now() - start), er, res, n);
  console.log("Raiden");
});*/

/*console.log("js "+(Date.now() - start), "before goodbye");
bayesian.doSomething(3, 4, "goodbye", function (er, res, n) {
  console.log("js "+(Date.now() - start), er, res, n)
});*/


//start the server 
var express = require('express');
var app = express.createServer();

app.configure(function(){
	app.use(express.bodyParser());
	app.use(express.static(__dirname + '/public'));
	app.set('views', __dirname + '/views');
	app.set('view engine', 'ejs');
});

app.get('/', function(req, res){
	bayesian.doSomething(2, 4, "hello", function (error, result, name) {
		console.log("js "+(Date.now() - start), error, result, name);
		res.send("js " + (Date.now() - start) + error + result + name);
	});
});

app.get('/names', function(req, res){
	res.render('names', {locals:{ names:['foo','bar','baz']}});
});

app.post('/evidence', function(req, res){
	//console.log(req.body.user); //{ name: 'ray', email: 'ray.lei@uregina.ca' }
	console.log(req.body); //user: { name: 'ray', email: 'gzmask@gmail.com' } }
	res.redirect('/names');
});

app.listen(8080);
console.log('Express server started on port %s', app.address().port);

