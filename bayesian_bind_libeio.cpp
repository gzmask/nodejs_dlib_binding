#include <v8.h>
#include <node.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "bayes_net.h"

using namespace node;
using namespace v8;

static Handle<Value> DoSomethingAsync (const Arguments&); //this deploys DoSomething/DoSomething_After into the thread pool using libeio(eio_custom).
static int DoSomething (eio_req *);
static int DoSomething_After (eio_req *);
extern "C" void init (Handle<Object>); //this gets called by node.js when javascript calls this binding. this calls DoSomethingAsync

struct simple_request {
  char* bayesian_result;
  char* passed_courses;
  Persistent<Function> cb;
};


static Handle<Value> DoSomethingAsync (const Arguments& args) {
	HandleScope scope;
	const char *usage = "usage: doSomething(passed_courses, cb)";
	if (args.Length() != 2) {
		return ThrowException(Exception::Error(String::New(usage)));
	}
	String::Utf8Value passed_courses_args(args[0]); 
	Local<Function> cb = Local<Function>::Cast(args[1]); //this is the callback(cb) in doSomething, which is passed by javascript

	simple_request *sr = new simple_request();
	sr->cb = Persistent<Function>::New(cb);
	sr->passed_courses = (char*)malloc(sizeof(char)*(passed_courses_args.length()+1));
	strncpy(sr->passed_courses, *passed_courses_args, passed_courses_args.length() + 1);

	//deploy the c++ DoSomething/DoSomething_After function, and struct to thread pool using libeio 
	eio_custom(DoSomething, EIO_PRI_DEFAULT, DoSomething_After, sr); //I believe sr got sent to DoSomething/DoSomething_After as eio_req *req->data in the following func def
	ev_ref(EV_DEFAULT_UC);
	return Undefined();
}

// this function happens on the thread pool
// doing v8 things in here will make bad happen.
static int DoSomething (eio_req *req) {
	struct simple_request * sr = (struct simple_request *)req->data;
	sr->bayesian_result = bayesian_test(sr->passed_courses);
	return 0;
}

/*Static member functions have a class scope and they do not have access to the 'this' pointer of the class. When a member is declared as static, a static member of class, it has only one data for the entire class even though there are many objects created for the class. The main usage of static function is when the programmer wants to have a function which is accessible even when the class is not instantiated.*/

//the callback function cb, passed by javascript, happens after everything
static int DoSomething_After (eio_req *req) {
	HandleScope scope;
	ev_unref(EV_DEFAULT_UC);
	struct simple_request * sr = (struct simple_request *)req->data;
	Local<Value> argv[3];
	argv[0] = Local<Value>::New(Null()); //cb(er)
	argv[1] = String::New(sr->bayesian_result); //cb(res)
	argv[2] = String::New(sr->passed_courses); //cb(n)
	TryCatch try_catch;
	sr->cb->Call(Context::GetCurrent()->Global(), 3, argv);
	if (try_catch.HasCaught()) {
		FatalException(try_catch);
	}
	//clean up
	sr->cb.Dispose();
	free(sr->passed_courses);
	free(sr->bayesian_result);
	free(sr);
	return 0;
}

extern "C" void init (Handle<Object> target) {
	HandleScope scope;
	//usage:
	//export.updateEvidence(passed_courses, function (error, result, passed_courses)
	NODE_SET_METHOD(target, "updateEvidence", DoSomethingAsync);
}

