var bayesian = require("./build/default/bayesian"), start = Date.now();

console.log("js "+(Date.now() - start), "before hello");

//er is error, res is result, n is name
bayesian.doSomething(2, 4, "hello", function (er, res, n) {
  console.log("js "+(Date.now() - start), er, res, n);
  console.log("Raiden");
});

/*console.log("js "+(Date.now() - start), "before goodbye");

bayesian.doSomething(3, 4, "goodbye", function (er, res, n) {
  console.log("js "+(Date.now() - start), er, res, n)
});*/
