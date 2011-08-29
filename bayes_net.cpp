#include "dlib/bayes_utils.h"
#include "dlib/graph_utils.h"
#include "dlib/graph.h"
#include "dlib/directed_graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "rapidxml/rapidxml.hpp"
using namespace rapidxml;
using namespace dlib;
using namespace std;

#include "bayes_net.h"

// ----------------------------------------------------------------------------------------
char* bayesian_test(char * passed_courses) {
    // There are many useful convenience functions in this namespace.  They all
    // perform simple access or modify operations on the nodes of a bayesian network. 
    // You don't have to use them but they are convenient and they also will check for
    // various errors in your bayesian network when your application is built with
    // the DEBUG or ENABLE_ASSERTS preprocessor definitions defined.  So their use
    // is recommended.  In fact, most of the global functions used in this example 
    // program are from this namespace.
    //using namespace bayes_node_utils;

    // This statement declares a bayesian network called bn.  Note that a bayesian network
    // in the dlib world is just a directed_graph object that contains a special kind 
    // of node called a bayes_node.
    //directed_graph<bayes_node>::kernel_1a_c bn;


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
			strcat(block_str, line_str);
		}
		xbn_file.close();
	}
	printf("the length of block_str is: %i \n", (int)strlen(block_str));
	printf("%s", block_str);
	free(line_str);

	//parsing xml using rapidxml
	xml_document<>* doc = new xml_document<>();
	doc->parse<0>(block_str);
	delete [] block_str;
	printf("Name of first node is %s.\n", doc->first_node()->first_node()->first_node("VARIABLES")->first_node("VAR")->name());

	//read variables and their domains (number of outcomes)
	//pointer of an array of char* pointers
	char** arrayVars;
	int varCounter = 0;
	for (xml_node<> *node = doc->first_node()->first_node()->first_node("VARIABLES")->first_node("VAR"); node; node = node->next_sibling()) {//determine the size of the array
		varCounter++;
	}
	int arrayVarDoms[varCounter];//init array to store Domains
	arrayVars = new char*[varCounter];
	for (int i=0; i<varCounter; i++) { arrayVars[i] = NULL; } //init pointers

	//var traversal
	varCounter = 0;
	for (xml_node<> *node = doc->first_node()->first_node()->first_node("VARIABLES")->first_node("VAR"); node; node = node->next_sibling()) {
		for (xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute("NAME")) {
			//printf("Node var has attribute %s ", attr->name()); printf("with value %s\n", attr->value());
		}
		arrayVars[varCounter] = node->first_node("FULLNAME")->value(); //store var names into arrayVars
		//get numbers of var domains
		arrayVarDoms[varCounter] = 0;
		for (xml_node<> *node_a = node->first_node("STATENAME"); node_a; node_a = node_a->next_sibling("STATENAME")) {
			arrayVarDoms[varCounter]++;
		}
		varCounter++;
	}
	for (int i=0; i<varCounter; i++) { if (arrayVars[i]!=NULL) {printf("debug: arrayVars %s with dom %i\n",arrayVars[i], arrayVarDoms[i]);}}
	printf("\n\n");

	//count edges
	int edgeCounter = 0;
	for (xml_node<> *node = doc->first_node()->first_node()->first_node("STRUCTURE")->first_node("ARC"); node; node = node->next_sibling()) {
		edgeCounter++;
	}

	//init array of edges as pairs of integers
	int arrayEdges [edgeCounter*2];//[parent][child]...[parent][child]
	edgeCounter = 0;

	//store each end of the edges into arrayEdges 
	for (xml_node<> *node = doc->first_node()->first_node()->first_node("STRUCTURE")->first_node("ARC"); node; node = node->next_sibling()) {
		for (xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
			if (strcmp(attr->name(),"PARENT")==0) {
				for (int i = 0; i<varCounter; i++) {
					if (strcmp(arrayVars[i], attr->value())==0)/*matches names in arrayVars*/ {arrayEdges[edgeCounter]=i/*var number*/;edgeCounter++;break;}
				}
			} else if (strcmp(attr->name(),"CHILD")==0) {
				for (int i = 0; i<varCounter; i++) {
					if (strcmp(arrayVars[i], attr->value())==0)/*matches names in arrayVars*/ {arrayEdges[edgeCounter]=i/*var number*/;edgeCounter++;break;}
				}
			}
		}
	}
	for (int i=0; i<edgeCounter; i++) { printf("debug: arrayEdges %s\n", arrayVars[arrayEdges[i]]); }
	printf("\n\n");

	//CPT struct linked-list
	struct CPT {
		int* vars;//p(vn|v1,v2,...)
		int* indexArray;//indexes (y*width+x) array
		int indexArrayWidth;
		int indexArrayHeight;
		float* probArray;//p values (y*width+x) array
		int probArrayWidth;
		int probArrayHeight;
		CPT* next;
	};
	int cptCounter = 0; //counter

	//count CPTs, init structs and (y*width+x) arrays
	cptCounter = 0;
	//firstCPT.indexArray = new int[2*4];
	//delete firstCPT.indexArray;
	struct CPT firstCPT;
	struct CPT *currCPT = &firstCPT;  	
	for (xml_node<> *node = doc->first_node()->first_node()->first_node("DISTRIBUTIONS")->first_node("DIST"); node; node = node->next_sibling("DIST")) 
	{
		//counting variables in CPT
		int cptVarCounter=1;//there is one private var already
		//count condition variables, notice that some CPT don't have one
		if (node->first_node("CONDSET")) {
			for (xml_node<> *node_a = node->first_node("CONDSET")->first_node("CONDELEM"); node_a; node_a = node_a->next_sibling("CONDELEM")) {
				cptVarCounter++;
			}
			//init vars array
			currCPT->vars = new int[cptVarCounter];
			//store condition variables
			cptVarCounter=0;
			for (xml_node<> *node_a = node->first_node("CONDSET")->first_node("CONDELEM"); node_a; node_a = node_a->next_sibling("CONDELEM")) {
				for (int i=0; i<varCounter; i++) {
					if (strcmp(node_a->first_attribute()->value(),arrayVars[i])==0){currCPT->vars[cptVarCounter]=i;break;}}
				cptVarCounter++;
			}
			cptVarCounter++;//add private var count
		} else {
			currCPT->vars = new int[cptVarCounter];}
		//store private variable
		for (int i=0; i<varCounter; i++){
			if (strcmp(arrayVars[i],node->first_node("PRIVATE")->first_attribute()->value())==0){currCPT->vars[cptVarCounter]=i;break;}}
		//init indexArray if there is condition var
		if (node->first_node("CONDSET")) {
			currCPT->indexArrayWidth = cptVarCounter-1;
			currCPT->indexArrayHeight = 1;
			for (int j=0; j<(cptVarCounter-1); j++) {
				currCPT->indexArrayHeight = currCPT->indexArrayHeight * arrayVarDoms[currCPT->vars[j]]/*number of domains of cpt var*/;}
			currCPT->indexArray = new int[currCPT->indexArrayWidth * currCPT->indexArrayHeight];
			//store indexes into currCPT->indexArray[y*width+x]
			int yCounter = 0;
			for (xml_node<> *node_a = node->first_node("DPIS")->first_node("DPI"); node_a; node_a = node_a->next_sibling("DPI")) {
				if (node_a->first_attribute()) {
					char *pch;
					pch = strtok(node_a->first_attribute()->value()," ");
					int xCounter = 0;
					while (pch != NULL) {
						printf("%s\n",pch);
						currCPT->indexArray[yCounter * currCPT->indexArrayWidth + xCounter]=atoi(pch);
						pch = strtok(NULL, " ");
						xCounter++;
					}
				}
			printf("Node %s has value ", node_a->name());
			printf(" %s \n", node_a->value());
			yCounter++;
			}
			printf("debug:currCPT->indexArraysize: %i\n",currCPT->indexArrayWidth * currCPT->indexArrayHeight);
		}
		//init probArray

		//init next CPT struct
		currCPT->next = (struct CPT*)malloc(sizeof(struct CPT));
		currCPT = currCPT->next;
		cptCounter++;
	}

	/*/CPT traversal 
	for (xml_node<> *node = doc->first_node()->first_node()->first_node("DISTRIBUTIONS")->first_node("DIST"); node; node = node->next_sibling("DIST")) 
	{
		for (xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
			printf("Node DIST has attribute %s ", attr->name());
			printf("with value %s\n", attr->value());
		}
		//read private variable
		printf("Node PRIVATE has attribute %s ", node->first_node("PRIVATE")->first_attribute()->name());
		printf("with value %s\n", node->first_node("PRIVATE")->first_attribute()->value());
		for (int i=0; i<varCounter; i++) {
			if (strcmp(node->first_node("PRIVATE")->first_attribute()->value(), arrayVars[i])==0) {*//*give struct private var as i here*//*;break;}
		}
		//read condition variables, notice that some CPT don't have one
		if (node->first_node("CONDSET")) {
			for (xml_node<> *node_a = node->first_node("CONDSET")->first_node("CONDELEM"); node_a; node_a = node_a->next_sibling("CONDELEM")) {
				printf("Node CONDELEM has attribute %s ", node_a->first_attribute()->name());
				printf("with value %s\n", node_a->first_attribute()->value());
			}
		}
		//read DPI values
		for (xml_node<> *node_a = node->first_node("DPIS")->first_node("DPI"); node_a; node_a = node_a->next_sibling("DPI")) {
			if (node_a->first_attribute()) {
				printf("Node DPI has attribute %s ", node_a->first_attribute()->name());
				printf("with value %s\n", node_a->first_attribute()->value());
			}
			printf("Node %s has value ", node_a->name());
			printf(" %s \n", node_a->value());
		}
	}*/

	printf("\n\n");
	//clean the mess
	delete []arrayVars;
	delete doc;

	char* aCString = (char *)malloc(strlen(aCString)+1);
	strcpy(aCString, "fuckyouc");
	return aCString;
}
