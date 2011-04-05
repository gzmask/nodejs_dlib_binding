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


//this is the server part
var express = require('express'),
        app = express.createServer();

app.configure(function(){
	app.set('view engine', 'ejs');
});

app.get('/', function(req, res){
	bayesian.doSomething(2, 4, "hello", function (error, result, name) {
	  console.log("js "+(Date.now() - start), error, result, name);
          res.send("js " + (Date.now() - start) + error + result + name);
	});
        //res.send('Hello World');
});

app.get('/index', function(req, res){
	res.render('index', { title: 'Bayesian network' });
});

app.listen(8080);
console.log('Express server started on port %s', app.address().port);

