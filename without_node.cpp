#include <iostream>
#include "bayes_net.h"

using namespace std;

int main() {
	string passed_courses = "'start-', '8', '4', '5', '7', '0', '3', '-end'";
	string passed_courses1 = "'start-', '8', '5', '7', '0', '3', '-end'";
	string passed_courses2 = "'start-', '8', '4', '7', '0', '3', '1', '-end'";
	char* bayesian_result = bayesian_test((char *)passed_courses.c_str());
	cout<<bayesian_result;
	bayesian_result = bayesian_test((char *)passed_courses1.c_str());
	cout<<bayesian_result;
	bayesian_result = bayesian_test((char *)passed_courses2.c_str());
	cout<<bayesian_result;
	return 0;
}
