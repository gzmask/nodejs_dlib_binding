var nas = require("./build/default/nas"), start = Date.now();

console.log("js "+(Date.now() - start), "before hello");

//er is error, res is result, n is name
nas.doSomething(1, 2, "hello", function (er, res, n) {
  console.log("js "+(Date.now() - start), er, res, n);
  console.log("Raiden");
});

console.log("js "+(Date.now() - start), "before goodbye");

nas.doSomething(3, 4, "goodbye", function (er, res, n) {
  console.log("js "+(Date.now() - start), er, res, n)
});
