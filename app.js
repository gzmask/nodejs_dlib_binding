var bayesian = require("./build/default/bayesian");

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
	res.render('index', {locals:{ title: 'index page'}});
});

app.get('/index', function(req, res){
	res.render('index', {locals:{ title: 'index page'}});
});

//outputs the query form
app.get('/evidence/new', function(req, res){
	res.render('evidence_new');
});

//get the student's feedback, sent to bayesian network, render output
app.post('/evidence', function(req, res){
	//console.log(req.body.user); //{ name: 'ray', email: 'ray.lei@uregina.ca' }
	console.log(req.body); //user: { name: 'ray', email: 'gzmask@gmail.com' } }
	var passed_courses = req.body.passed_course.join("-");
	bayesian.updateEvidence(passed_courses, function (error, result, passed_courses) {
		res.render('evidence', 
			{locals:
				{ names:['foo','bar','baz'], 
				'result':result, 
				'user_name':req.body.user.name,
				'user_email':req.body.user.email
				}});
	});
	//res.redirect('/names');
});

app.listen(8080);
console.log('Express server started on port %s', app.address().port);

