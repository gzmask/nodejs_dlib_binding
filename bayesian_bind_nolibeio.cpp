#include <v8.h>
#include <node.h>
#include <fstream>
#include "bayes_net.h"
 
using namespace node;
using namespace v8;

struct simple_request {
  char* bayesian_result;
  Persistent<Function> cb;
  char* passed_courses;
};
 
static Handle<Value> foo(const Arguments& args)
{
	//this is the code block that reads the ???.xbn file
	char* line_str = (char*)malloc(sizeof(char)*256);
	char* block_str = new char[4096];
	const char xbn_filename[] = "input.xbn";
	std::ifstream xbn_file (xbn_filename);
	if (xbn_file.is_open()) {
		xbn_file.getline(line_str, 256);
		strcpy(block_str, line_str);
		while (!xbn_file.eof()) {
			xbn_file.getline(line_str, 256);
			strcat(line_str, "\n");
			//printf("%s", line_str);
			strcat(block_str, line_str);
		}
		xbn_file.close();
	}
	printf("the length of block_str is: %i \n",(int)strlen(block_str));
	printf("%s", block_str);
	free(line_str);
	delete [] block_str;

	//init the struct
	String::Utf8Value passed_courses_args(args[0]); 
	Local<Function> cb = Local<Function>::Cast(args[1]); //this is the callback(cb) in updateEvidence, which is passed by javascript
	simple_request *sr = new simple_request();
	sr->cb = Persistent<Function>::New(cb);
	sr->passed_courses = (char*)malloc(sizeof(char)*512);
	strncpy(sr->passed_courses, *passed_courses_args, passed_courses_args.length() + 1);

	//heavy lifting
	sr->bayesian_result = bayesian_test(sr->passed_courses);

	//return results to js
	Local<Value> argv[3];
	argv[0] = Local<Value>::New(Null()); //cb(er)
	argv[1] = String::New(sr->bayesian_result); //cb(res)
	argv[2] = String::New(sr->passed_courses); //cb(n)
	TryCatch try_catch;
	sr->cb->Call(Context::GetCurrent()->Global(), 3, argv);//execute the js callback
	if (try_catch.HasCaught()) {
		FatalException(try_catch);
	}

	//clean the mess
	sr->cb.Dispose();
	free(sr->passed_courses);
	free(sr->bayesian_result);
	free(sr);

	return String::New("Hello World");
}
 
extern "C" {
	static void init(Handle<Object> target)
	{
		NODE_SET_METHOD(target, "updateEvidence", foo);
	}

	NODE_MODULE(bayesian, init);
}

