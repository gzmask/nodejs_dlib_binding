var bayesian = require("./build/default/bayesian"), start = Date.now();

console.log("js "+(Date.now() - start), "before hello");

//er is error, res is result, n is name
bayesian.doSomething(1, 2, "hello", function (er, res, n) {
  console.log("js "+(Date.now() - start), er, res, n);
  console.log("Raiden");
});

/*console.log("js "+(Date.now() - start), "before goodbye");

bayesian.doSomething(3, 4, "goodbye", function (er, res, n) {
  console.log("js "+(Date.now() - start), er, res, n)
});*/


//this is the server part
var express = require('./node_modules/express'),
        app = express.createServer();


app.get('/', function(req, res){
        res.send('Hello World');
});


app.listen(8080);
console.log('Express server started on port %s', app.address().port);

