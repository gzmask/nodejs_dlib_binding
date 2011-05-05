#include <v8.h>
#include <node.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
using namespace node;
using namespace v8;
#include "bayes_net.h"

static Handle<Value> DoSomethingAsync (const Arguments&); //this deploys DoSomething/DoSomething_After into the thread pool using libeio(eio_custom).
static int DoSomething (eio_req *);
static int DoSomething_After (eio_req *);
extern "C" void init (Handle<Object>); //this gets called by node.js when javascript calls this binding. this calls DoSomethingAsync

struct simple_request {
  char* bayesian_result;
  Persistent<Function> cb;
  // maybe it matters to put the char[] last?  not sure.
  // it's because you want to extent the sizeof passed_courses dynamically later on due to security measure.
  // however, order does not matter
  char passed_courses[1];
};


static Handle<Value> DoSomethingAsync (const Arguments& args) {
  HandleScope scope;
  const char *usage = "usage: doSomething(passed_courses, cb)";
  if (args.Length() != 2) {
    return ThrowException(Exception::Error(String::New(usage)));
  }
  String::Utf8Value passed_courses(args[0]); //this is the name in doSomething
  Local<Function> cb = Local<Function>::Cast(args[1]); //this is the callback(cb) in doSomething, which is passed by javascript

  simple_request *sr = (simple_request *)
    malloc(sizeof(struct simple_request) + passed_courses.length() + 1); //get memory in heap

  //assign four parameters of doSomething to struct
  sr->cb = Persistent<Function>::New(cb);
  strncpy(sr->passed_courses, *passed_courses, passed_courses.length() + 1);

  //deploy the c++ DoSomething/DoSomething_After function, and struct to thread pool using libeio 
  eio_custom(DoSomething, EIO_PRI_DEFAULT, DoSomething_After, sr); //I believe sr got sent to DoSomething/DoSomething_After as eio_req *req->data in the following func def
  ev_ref(EV_DEFAULT_UC);
  return Undefined();
}

// this function happens on the thread pool
// doing v8 things in here will make bad happen.
static int DoSomething (eio_req *req) {
  struct simple_request * sr = (struct simple_request *)req->data;
  //sleep(2); // just to make it less pointless to be async.
  //req->result = sr->x + sr->y;
  sr->bayesian_result = bayesian_test(sr->passed_courses);
  //bayesian_result = bayesian_test(sr->x, sr->y, sr->passed_courses);
  return 0;
}


//the callback function cb, passed by javascript, happens after everything
//in this case, callback(er = null, res = x + y, n = name), which are argv[0], argv[1] and argv[2] 
static int DoSomething_After (eio_req *req) {
  HandleScope scope;
  ev_unref(EV_DEFAULT_UC);
  struct simple_request * sr = (struct simple_request *)req->data;
  Local<Value> argv[3];
  argv[0] = Local<Value>::New(Null()); //cb(er)
  argv[1] = String::New(sr->bayesian_result); //cb(res)
  //argv[1] = String::New(bayesian_result); //cb(res)
  argv[2] = String::New(sr->passed_courses); //cb(n)
  TryCatch try_catch;
  sr->cb->Call(Context::GetCurrent()->Global(), 3, argv);
  if (try_catch.HasCaught()) {
    FatalException(try_catch);
  }
  sr->cb.Dispose();
  free(sr);
  return 0;
}

extern "C" void init (Handle<Object> target) {
  HandleScope scope;
  //usage:
  //export.updateEvidence(passed_courses, function (error, result, passed_courses)
  NODE_SET_METHOD(target, "updateEvidence", DoSomethingAsync);
}
