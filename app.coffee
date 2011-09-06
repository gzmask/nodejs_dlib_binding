bayesian = require("./build/default/bayesian")
express = require("express")
app = express.createServer()
app.configure ->
  app.use express.bodyParser()
  app.use express.static(__dirname + "/public")
  app.set "views", __dirname + "/views"
  app.set "view engine", "ejs"

app.get "/", (req, res) ->
  res.render "index", locals: title: "index page"

app.get "/index", (req, res) ->
  res.render "index", locals: title: "index page"

app.get "/evidence/new", (req, res) ->
  res.render "evidence_new"

app.post "/evidence", (req, res) ->
  console.log req.body
  passed_courses = req.body.passed_course.join("-")
  bayesian.updateEvidence passed_courses, (error, result, passed_courses) ->
    res.render "evidence", locals: 
      names: [ "foo", "bar", "baz" ]
      result: result
      user_name: req.body.user.name
      user_email: req.body.user.email

app.listen 8080
console.log "Express server started on port %s", app.address().port

