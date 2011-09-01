#include "dlib/bayes_utils.h"
#include "dlib/graph_utils.h"
#include "dlib/graph.h"
#include "dlib/directed_graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "rapidxml/rapidxml.hpp"
#include "bayes_net.h"
using namespace rapidxml;
using namespace dlib;
using namespace std;

/*********************************************************************************
MS Bayesian Network XML Paring README, after the parsing is done, there are structures left as result:

	arrayVars[each variable as integer] = a string of the variable name
	arrayVarDoms[each variable as integer] = number of domains for this variable
	varCounter is the total number of variables

	arrayEdges[] is the array for all edges listed as [parent][child]...[parent][child]
	edgeCounter is the twice of the total number of edges, it actually represents nodes

	firstCPT is the head of the linked list for CPTs
	CPT.vars is the variables as int for each CPT, accessed by p(Vn|V1,V2...,Vn-1)
	CPT.indexArray[] is the array for all index variables for each CPT as int, accessed by [y*width+x]
	CPT.probArray[] is the array for all probability values for each CPT as float, accessed by [y*width+x]
	And these: CPT.indexArrayWidth CPT.indexArrayHeight CPT.probArrayWidth CPT.probArrayHeight
	Warning: total numbers of vars is indexArrayWidth+1 !
	cptCounter is the totoal number of CPTs

*********************************************************************************/

//recursively free CPT struct memory
bool freeCPT(struct CPT *aCPT) {
	if (aCPT->next == NULL) { 
		free(aCPT);
		return true; 
	} else if (freeCPT(aCPT->next)) {
		delete []aCPT->vars;
		delete []aCPT->indexArray;
		delete []aCPT->probArray;
		free(aCPT);
		return true;
	} else {
		return false;
	}
}

//main function
char* bayesian_test(char *passed_courses) {
	char* resstr = (char*)malloc(sizeof(char)*256);
	strcat(resstr, "testing");

	//this is the code block that reads the ???.xbn file
	char* line_str = (char*)malloc(sizeof(char)*256);//released at :50
	char* block_str = new char[20000];//released at :55
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
	free(line_str);
	//parsing xml using rapidxml
	xml_document<>* doc = new xml_document<>();//released at :206
	try {
		doc->parse<0>(block_str);
	} catch (rapidxml::parse_error &e) {
		cout<<e.what()<<endl;
		return NULL;
	}
	delete [] block_str;
	//printf("Name of first node is %s.\n", doc->first_node()->first_node()->first_node("VARIABLES")->first_node("VAR")->name());

	//read variables and their domains (number of outcomes)
	//pointer of an array of char* pointers
	char** arrayVars;
	int varCounter = 0;
	for (xml_node<> *node = doc->first_node()->first_node()->first_node("VARIABLES")->first_node("VAR"); node; node = node->next_sibling()) {//determine the size of the array
		varCounter++;
	}
	int arrayVarDoms[varCounter];//init array to store Domains
	arrayVars = new char*[varCounter];//released at :205
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
	for (int i=0; i<varCounter; i++) { if (arrayVars[i]!=NULL) {printf("debug: arrayVars %i with dom %i\n",i, arrayVarDoms[i]);}}
	//printf("\n\n");

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
			if (strcasecmp(attr->name(),"PARENT")==0) {
				for (int i = 0; i<varCounter; i++) {
					if (strcasecmp(arrayVars[i], attr->value())==0)/*matches names in arrayVars*/ {arrayEdges[edgeCounter]=i/*var number*/;edgeCounter++;break;}
				}
			} else if (strcasecmp(attr->name(),"CHILD")==0) {
				for (int i = 0; i<varCounter; i++) {
					if (strcasecmp(arrayVars[i], attr->value())==0)/*matches names in arrayVars*/ {arrayEdges[edgeCounter]=i/*var number*/;edgeCounter++;break;}
				}
			}
		}
	}

	int cptCounter = 0; //counter

	//count CPTs, init structs and (y*width+x) arrays
	cptCounter = 0;
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
					if (strcasecmp(node_a->first_attribute()->value(),arrayVars[i])==0){currCPT->vars[cptVarCounter]=i;break;}}
				//cout<<"parents "<<node_a->first_attribute()->value()<<arrayVars[currCPT->vars[cptVarCounter]]<<endl;
				cptVarCounter++;
			}
			cptVarCounter++;//add private var count
		} else {
			currCPT->vars = new int[cptVarCounter];}
		//store private variable
		for (int i=0; i<varCounter; i++){
			if (strcasecmp(arrayVars[i],node->first_node("PRIVATE")->first_attribute()->value())==0){currCPT->vars[cptVarCounter-1]=i;break;}}
		//cout<<"child "<<node->first_node("PRIVATE")->first_attribute()->value()<<arrayVars[currCPT->vars[cptVarCounter-1]]<<endl;
		//init indexArray
		currCPT->indexArray = NULL;
		currCPT->indexArrayWidth = cptVarCounter-1;
		currCPT->indexArrayHeight = 1;
		for (int j=0; j<(cptVarCounter-1); j++) {
			currCPT->indexArrayHeight = currCPT->indexArrayHeight * arrayVarDoms[currCPT->vars[j]]/*number of domains of cpt var*/;}
		if (node->first_node("CONDSET")) {
			currCPT->indexArray = new int[currCPT->indexArrayWidth * currCPT->indexArrayHeight];
		}
		//init probArray
		currCPT->probArrayWidth = arrayVarDoms[currCPT->vars[cptVarCounter-1]];
		currCPT->probArrayHeight = currCPT->indexArrayHeight;
		currCPT->probArray = new float[currCPT->probArrayWidth * currCPT->probArrayHeight];
		//store indexes into currCPT->indexArray[y*width+x]
		int yCounter = 0;
		for (xml_node<> *node_a = node->first_node("DPIS")->first_node("DPI"); node_a; node_a = node_a->next_sibling("DPI")) {
			if (node_a->first_attribute()) {
				char *pch;
				pch = strtok(node_a->first_attribute()->value()," ");
				int xCounter = 0;
				while (pch != NULL) {
					currCPT->indexArray[yCounter * currCPT->indexArrayWidth + xCounter]=atoi(pch);
					pch = strtok(NULL, " ");
					xCounter++;
				}
			}
			//store probArray
			char *ppch;
			ppch = strtok(node_a->value()," ");
			int xxCounter = 0;
			while (ppch != NULL) {
				currCPT->probArray[yCounter * currCPT->probArrayWidth + xxCounter]=atof(ppch);
				ppch = strtok(NULL, " ");
				xxCounter++;
			}
			yCounter++;
		}
		//for (int k=0; k<(currCPT->indexArrayWidth+1); k++) {printf("debug: currCPT->vars: %s\n",arrayVars[currCPT->vars[k]]);}
		//init next CPT struct
		currCPT->next = (struct CPT*)malloc(sizeof(struct CPT));
		currCPT = currCPT->next;
		currCPT->next = NULL;
		cptCounter++;
	}


	//the dlib bayesian inference
    using namespace bayes_node_utils;
    directed_graph<bayes_node>::kernel_1a_c bn;
    bn.set_number_of_nodes(varCounter);

	//add edges	
	for (int i=0; i<edgeCounter; i=i+2) {
		bn.add_edge(arrayEdges[i],arrayEdges[i+1]);
		cout<<"edge: ";
		cout<<arrayEdges[i]<<",";
		cout<<arrayEdges[i+1]<<endl;
	}

	//add domains	
	for (int i=0; i<varCounter; i++) {
		set_node_num_values(bn, i, arrayVarDoms[i]);
	}

	assignment parent_state;
	//add CPTs
	currCPT = &firstCPT;
	//foreach CPT
	while (currCPT->next != NULL) {
		//child node: currCPT->vars[currCPT->indexArrayWidth]
		cout<<"parent_state.clear();"<<endl;
		parent_state.clear();
		//foreach parent node of this child node
		for (int i=0; i<currCPT->indexArrayWidth; i++) {
			//parent node: currCPT->vars[i]
			cout<<"parent_state.add("<<arrayVars[currCPT->vars[i]]<<");"<<endl;
			parent_state.add(currCPT->vars[i]);
		}
		//foreach row of indexArray and probArray
		for (int i=0; i<currCPT->indexArrayHeight; i++) {
			//foreach configuration of index vars
			for (int j=0; j<currCPT->indexArrayWidth; j++) {
				cout<<"parent_state["<<arrayVars[currCPT->vars[j]]<<"] = "<<currCPT->indexArray[i*currCPT->indexArrayWidth+j]<<endl;;
				parent_state[currCPT->vars[j]] = currCPT->indexArray[i*currCPT->indexArrayWidth+j];
			}
			//foreach dom of probArray*
			for (int k=0; k<currCPT->probArrayWidth; k++) {
				cout<<"set_node_probability(bn, "<<arrayVars[currCPT->vars[currCPT->indexArrayWidth]]<<", "<<k<<", parent_state, "<<currCPT->probArray[i*currCPT->probArrayWidth+k]<<")"<<endl;
				set_node_probability(bn, currCPT->vars[currCPT->indexArrayWidth], k, parent_state, currCPT->probArray[i*currCPT->probArrayWidth+k]);
			}
			cout<<endl;
		}
		currCPT = currCPT->next;
	}

	//setup join tree
    typedef set<unsigned long>::compare_1b_c set_type;
    typedef graph<set_type, set_type>::kernel_1a_c join_tree_type;
    join_tree_type join_tree;
    create_moral_graph(bn, join_tree);
    create_join_tree(join_tree, join_tree);
    bayesian_network_join_tree solution(bn, join_tree);

	//print prior probs
	//foreach variables
	for (int i=0; i<varCounter; i++) {
		cout<<arrayVars[i]<<solution.probability(i)(0)<<endl;	
	}

	//set evidence
	set_node_value(bn, 2, 0);//john called
	set_node_as_evidence(bn, 2);
	set_node_value(bn, 3, 0);//mary called
	set_node_as_evidence(bn, 3);

	//JTP
    bayesian_network_join_tree solution_with_evidence(bn, join_tree);

	//print post probs
	//foreach variables
	for (int i=0; i<varCounter; i++) {
		cout<<arrayVars[i]<<solution_with_evidence.probability(i)(0)<<endl;	
	}

	//clean the mess
	delete []arrayVars;
	delete doc;
	//release the linked list CPT struct using recursive function freeCPT(), and you can't free an auto var!
	freeCPT(firstCPT.next);
	delete []firstCPT.vars;
	delete []firstCPT.indexArray;
	delete []firstCPT.probArray;
	
	return resstr;
}

