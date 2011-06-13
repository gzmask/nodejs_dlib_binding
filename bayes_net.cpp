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
char* bayesian_test(char * passed_courses)
{
	string xbn_filename;
	string line_str;
	string block_str;

	//this is the code block that reads the ???.xbn file
	xbn_filename = "input.xbn";
	ifstream xbn_file (xbn_filename.c_str());
	if (xbn_file.is_open()) {
		while (!xbn_file.eof()) {
			getline(xbn_file, line_str);
			//line_str need to be examine throughoutly 
			//cout<<"line_str size:"<<line_str.size()<<endl;
			//for (int i=0; i< line_str.size(); i++) {
				//cout<<line_str[i];
				//printf("%c\n", line_str[i]);
			//}
			block_str.append(line_str);
			block_str.append("\n");
		}
		//cout<<block_str<<endl;
		xbn_file.close();
	}
	
	cout<<block_str<<endl;
/*
	cout<<block_str.size()<<endl;
	for (int i = 0; i< block_str.size(); i++) {
		if (i % 2 == 0)
			cout<<"char "<<i<<':'<<block_str[i]<<endl;
	}
*/

/*
	//cast the string to char*
	char *xml_text = (char *)block_str.c_str();
	//parse the string
	xml_document<> doc;    // character type defaults to char
	cout<<xml_text<<endl;
	doc.parse<0>(xml_text);    // 0 means default parse flags

	cout << "Name of my first node is: " << doc.first_node()->name() << "\n";

	//nest node traversal
	for (xml_node<> *node = doc.first_node()->first_node()->first_node("VARIABLES"); node; node = node->next_sibling()) {
		cout << "Node variable has value " << node->first_node("FULLNAME")->value() << "\n\n";
	}
*/




    // There are many useful convenience functions in this namespace.  They all
    // perform simple access or modify operations on the nodes of a bayesian network. 
    // You don't have to use them but they are convenient and they also will check for
    // various errors in your bayesian network when your application is built with
    // the DEBUG or ENABLE_ASSERTS preprocessor definitions defined.  So their use
    // is recommended.  In fact, most of the global functions used in this example 
    // program are from this namespace.
    using namespace bayes_node_utils;

    // This statement declares a bayesian network called bn.  Note that a bayesian network
    // in the dlib world is just a directed_graph object that contains a special kind 
    // of node called a bayes_node.
    directed_graph<bayes_node>::kernel_1a_c bn;

    // Use an enum to make some more readable names for our nodes.
	enum nodes { cs110, cs201, cs207, cs115, math105, math110, cs270, cs100, engl100, math122, math111, cs261, cs280, cs301, cs203, cs271 };

	//enum for the array of difficulty levels
	enum difficulties { easy, middle, hard };

	//set the pass rate for each difficulty
	float difficulties[3];
	difficulties[easy] = 0.8;
	difficulties[middle] = 0.7;
	difficulties[hard] = 0.6;

    // The next few blocks of code setup our bayesian network.

    // The first thing we do is tell the bn object how many nodes it has
    // and also add the three edges.  Again, we are using the network
    // shown in ASCII art at the top of this file.
    bn.set_number_of_nodes(16);
    bn.add_edge(cs110, cs201);
    bn.add_edge(cs110, cs207);
    bn.add_edge(cs110, cs115);
    bn.add_edge(math110, cs115);
    bn.add_edge(math105, cs115);
    bn.add_edge(cs110, cs270);
    bn.add_edge(cs100, cs270);
    bn.add_edge(engl100, cs270);
	bn.add_edge(math122, cs261);
	bn.add_edge(math111, cs261);
	bn.add_edge(cs110, cs261);
	bn.add_edge(cs115, cs261);
	bn.add_edge(engl100, cs280);
	bn.add_edge(cs110, cs280);
	bn.add_edge(cs201, cs301);
	bn.add_edge(cs115, cs203);
	bn.add_edge(cs110, cs271);
	bn.add_edge(cs270, cs271);



    // Now we inform all the nodes in the network that they are binary
    // nodes.  That is, they only have two possible values.  
    set_node_num_values(bn, cs110, 2);
    set_node_num_values(bn, cs201, 2);
    set_node_num_values(bn, cs207, 2);
    set_node_num_values(bn, cs115, 2);
    set_node_num_values(bn, math105, 2);
    set_node_num_values(bn, math110, 2);
    set_node_num_values(bn, cs270, 2);
    set_node_num_values(bn, cs100, 2);
    set_node_num_values(bn, engl100, 2);
    set_node_num_values(bn, math122, 2);
    set_node_num_values(bn, math111, 2);
    set_node_num_values(bn, cs261, 2);
    set_node_num_values(bn, cs280, 2);
    set_node_num_values(bn, cs301, 2);
    set_node_num_values(bn, cs203, 2);
    set_node_num_values(bn, cs271, 2);

    assignment parent_state;
    // Now we will enter all the conditional probability information for each node.
    // Each node's conditional probability is dependent on the state of its parents.  
    // To specify this state we need to use the assignment object.  This assignment 
    // object allows us to specify the state of each nodes parents. 


    //==============================p(cs110=1) = 0.5==============================
    // parent_state is empty in this case since cs110 is a root node. 
    set_node_probability(bn, cs110, 1, parent_state, 0.5);
    set_node_probability(bn, cs110, 0, parent_state, 1-0.5);

    //==============================p(cs100=1) = 0.5==============================
    set_node_probability(bn, cs100, 1, parent_state, 0.5);
    set_node_probability(bn, cs100, 0, parent_state, 1-0.5);

    //==============================p(engl100=1) = 0.5==============================
    set_node_probability(bn, engl100, 1, parent_state, 0.5);
    set_node_probability(bn, engl100, 0, parent_state, 1-0.5);

    //==============================p(math105=1) = 0.5==============================
    set_node_probability(bn, math105, 1, parent_state, 0.5);
    set_node_probability(bn, math105, 0, parent_state, 1-0.5);

    //==============================p(math110=1) = 0.5==============================
    set_node_probability(bn, math110, 1, parent_state, 0.5);
    set_node_probability(bn, math110, 0, parent_state, 1-0.5);

    //==============================p(math111=1) = 0.5==============================
    set_node_probability(bn, math111, 1, parent_state, 0.5);
    set_node_probability(bn, math111, 0, parent_state, 1-0.5);

    //==============================p(math122=1) = 0.5==============================
    set_node_probability(bn, math122, 1, parent_state, 0.5);
    set_node_probability(bn, math122, 0, parent_state, 1-0.5);

    // This is our first node that has parents. So we set the parent_state
    // object to reflect that cs201 has cs110 as parents.
    parent_state.add(cs110, 1);
    //==============================p(cs201=1 | cs110=1) = 0.8============================== 
    set_node_probability(bn, cs201, 1, parent_state, difficulties[easy]);
    set_node_probability(bn, cs201, 0, parent_state, 1-difficulties[easy]);
    parent_state[cs110] = 0;
    //==============================p(cs201=1 | cs110=0) = 0==============================
    set_node_probability(bn, cs201, 1, parent_state, 0);
    set_node_probability(bn, cs201, 0, parent_state, 1-0);


    //==============================p(cs207 | cs110) CPT============================== 
    parent_state.clear();
    parent_state.add(cs110,1);
    set_node_probability(bn, cs207, 1, parent_state, difficulties[easy]);
    set_node_probability(bn, cs207, 0, parent_state, 1-difficulties[easy]);
    parent_state[cs110] = 0;
    set_node_probability(bn, cs207, 1, parent_state, 0);
    set_node_probability(bn, cs207, 0, parent_state, 1-0);

    //==================p(cs115 | cs110, math105, math110) CPT===================== 
    parent_state.clear();
    parent_state.add(cs110,1);
    parent_state.add(math105, 1);
    parent_state.add(math110, 1);
    set_node_probability(bn, cs115, 1, parent_state, difficulties[easy]);
    set_node_probability(bn, cs115, 0, parent_state, 1-difficulties[easy]);
    parent_state[cs110] = 1;
    parent_state[math105] = 1;
    parent_state[math110] = 0;
    set_node_probability(bn, cs115, 1, parent_state, difficulties[easy]);
    set_node_probability(bn, cs115, 0, parent_state, 1-difficulties[easy]);
    parent_state[cs110] = 1;
    parent_state[math105] = 0;
    parent_state[math110] = 1;
    set_node_probability(bn, cs115, 1, parent_state, difficulties[easy]);
    set_node_probability(bn, cs115, 0, parent_state, 1-difficulties[easy]);
    parent_state[cs110] = 1;
    parent_state[math105] = 0;
    parent_state[math110] = 0;
    set_node_probability(bn, cs115, 1, parent_state, 0);
    set_node_probability(bn, cs115, 0, parent_state, 1-0);
    parent_state[cs110] = 0;
    parent_state[math105] = 1;
    parent_state[math110] = 1;
    set_node_probability(bn, cs115, 1, parent_state, 0);
    set_node_probability(bn, cs115, 0, parent_state, 1-0);
    parent_state[cs110] = 0;
    parent_state[math105] = 1;
    parent_state[math110] = 0;
    set_node_probability(bn, cs115, 1, parent_state, 0);
    set_node_probability(bn, cs115, 0, parent_state, 1-0);
    parent_state[cs110] = 0;
    parent_state[math105] = 0;
    parent_state[math110] = 1;
    set_node_probability(bn, cs115, 1, parent_state, 0);
    set_node_probability(bn, cs115, 0, parent_state, 1-0);
    parent_state[cs110] = 0;
    parent_state[math105] = 0;
    parent_state[math110] = 0;
    set_node_probability(bn, cs115, 1, parent_state, 0);
    set_node_probability(bn, cs115, 0, parent_state, 1-0);


    //==================p(cs270 | cs110, cs100, engl100) CPT===================== 
    parent_state.clear();
    parent_state.add(cs110,1);
    parent_state.add(cs100, 1);
    parent_state.add(engl100, 1);
    set_node_probability(bn, cs270, 1, parent_state, difficulties[easy]);
    set_node_probability(bn, cs270, 0, parent_state, 1-difficulties[easy]);
    parent_state[cs110] = 1;
    parent_state[cs100] = 1;
    parent_state[engl100] = 0;
    set_node_probability(bn, cs270, 1, parent_state, 0);
    set_node_probability(bn, cs270, 0, parent_state, 1-0);
    parent_state[cs110] = 1;
    parent_state[cs100] = 0;
    parent_state[engl100] = 1;
    set_node_probability(bn, cs270, 1, parent_state, difficulties[easy]);
    set_node_probability(bn, cs270, 0, parent_state, 1-difficulties[easy]);
    parent_state[cs110] = 1;
    parent_state[cs100] = 0;
    parent_state[engl100] = 0;
    set_node_probability(bn, cs270, 1, parent_state, difficulties[easy]);
    set_node_probability(bn, cs270, 0, parent_state, 1-difficulties[easy]);
    parent_state[cs110] = 0;
    parent_state[cs100] = 1;
    parent_state[engl100] = 1;
    set_node_probability(bn, cs270, 1, parent_state, difficulties[easy]);
    set_node_probability(bn, cs270, 0, parent_state, 1-difficulties[easy]);
    parent_state[cs110] = 0;
    parent_state[cs100] = 1;
    parent_state[engl100] = 0;
    set_node_probability(bn, cs270, 1, parent_state, 0);
    set_node_probability(bn, cs270, 0, parent_state, 1-0);
    parent_state[cs110] = 0;
    parent_state[cs100] = 0;
    parent_state[engl100] = 1;
    set_node_probability(bn, cs270, 1, parent_state, 0);
    set_node_probability(bn, cs270, 0, parent_state, 1-0);
    parent_state[cs110] = 0;
    parent_state[cs100] = 0;
    parent_state[engl100] = 0;
    set_node_probability(bn, cs270, 1, parent_state, 0);
    set_node_probability(bn, cs270, 0, parent_state, 1-0);

    //==================p(cs261 | math111, math122, cs110, cs115) CPT===================== 
    parent_state.clear();
    parent_state.add(math111,1);
    parent_state.add(math122,1);
    parent_state.add(cs110,1);
    parent_state.add(cs115,1);
    set_node_probability(bn, cs261, 1, parent_state, difficulties[easy]);
    set_node_probability(bn, cs261, 0, parent_state, 1-difficulties[easy]);
    parent_state[math111] = 1;
    parent_state[math122] = 1;
    parent_state[cs110] = 1;
    parent_state[cs115] = 0;
    set_node_probability(bn, cs261, 1, parent_state, difficulties[easy]);
    set_node_probability(bn, cs261, 0, parent_state, 1-difficulties[easy]);
    parent_state[math111] = 1;
    parent_state[math122] = 1;
    parent_state[cs110] = 0;
    parent_state[cs115] = 1;
    set_node_probability(bn, cs261, 1, parent_state, difficulties[easy]);
    set_node_probability(bn, cs261, 0, parent_state, 1-difficulties[easy]);
    parent_state[math111] = 1;
    parent_state[math122] = 1;
    parent_state[cs110] = 0;
    parent_state[cs115] = 0;
    set_node_probability(bn, cs261, 1, parent_state, 0);
    set_node_probability(bn, cs261, 0, parent_state, 1-0);
    parent_state[math111] = 1;
    parent_state[math122] = 0;
    parent_state[cs110] = 1;
    parent_state[cs115] = 1;
    set_node_probability(bn, cs261, 1, parent_state, 0);
    set_node_probability(bn, cs261, 0, parent_state, 1-0);
    parent_state[math111] = 1;
    parent_state[math122] = 0;
    parent_state[cs110] = 1;
    parent_state[cs115] = 0;
    set_node_probability(bn, cs261, 1, parent_state, 0);
    set_node_probability(bn, cs261, 0, parent_state, 1-0);
    parent_state[math111] = 1;
    parent_state[math122] = 0;
    parent_state[cs110] = 0;
    parent_state[cs115] = 1;
    set_node_probability(bn, cs261, 1, parent_state, 0);
    set_node_probability(bn, cs261, 0, parent_state, 1-0);
    parent_state[math111] = 1;
    parent_state[math122] = 0;
    parent_state[cs110] = 0;
    parent_state[cs115] = 0;
    set_node_probability(bn, cs261, 1, parent_state, 0);
    set_node_probability(bn, cs261, 0, parent_state, 1-0);
    parent_state[math111] = 0;
    parent_state[math122] = 1;
    parent_state[cs110] = 1;
    parent_state[cs115] = 1;
    set_node_probability(bn, cs261, 1, parent_state, 0);
    set_node_probability(bn, cs261, 0, parent_state, 1-0);
    parent_state[math111] = 0;
    parent_state[math122] = 1;
    parent_state[cs110] = 1;
    parent_state[cs115] = 0;
    set_node_probability(bn, cs261, 1, parent_state, 0);
    set_node_probability(bn, cs261, 0, parent_state, 1-0);
    parent_state[math111] = 0;
    parent_state[math122] = 1;
    parent_state[cs110] = 0;
    parent_state[cs115] = 1;
    set_node_probability(bn, cs261, 1, parent_state, 0);
    set_node_probability(bn, cs261, 0, parent_state, 1-0);
    parent_state[math111] = 0;
    parent_state[math122] = 1;
    parent_state[cs110] = 0;
    parent_state[cs115] = 0;
    set_node_probability(bn, cs261, 1, parent_state, 0);
    set_node_probability(bn, cs261, 0, parent_state, 1-0);
    parent_state[math111] = 0;
    parent_state[math122] = 0;
    parent_state[cs110] = 1;
    parent_state[cs115] = 1;
    set_node_probability(bn, cs261, 1, parent_state, 0);
    set_node_probability(bn, cs261, 0, parent_state, 1-0);
    parent_state[math111] = 0;
    parent_state[math122] = 0;
    parent_state[cs110] = 1;
    parent_state[cs115] = 0;
    set_node_probability(bn, cs261, 1, parent_state, 0);
    set_node_probability(bn, cs261, 0, parent_state, 1-0);
    parent_state[math111] = 0;
    parent_state[math122] = 0;
    parent_state[cs110] = 0;
    parent_state[cs115] = 1;
    set_node_probability(bn, cs261, 1, parent_state, 0);
    set_node_probability(bn, cs261, 0, parent_state, 1-0);
    parent_state[math111] = 0;
    parent_state[math122] = 0;
    parent_state[cs110] = 0;
    parent_state[cs115] = 0;
    set_node_probability(bn, cs261, 1, parent_state, 0);
    set_node_probability(bn, cs261, 0, parent_state, 1-0);

    //===========================p(cs280 | cs110, engl100) CPT========================== 
    parent_state.clear();
    parent_state.add(cs110,1);
    parent_state.add(engl100,1);
    set_node_probability(bn, cs280, 1, parent_state, difficulties[easy]);
    set_node_probability(bn, cs280, 0, parent_state, 1-difficulties[easy]);
    parent_state[cs110] = 1;
    parent_state[engl100] = 0;
    set_node_probability(bn, cs280, 1, parent_state, 0);
    set_node_probability(bn, cs280, 0, parent_state, 1-0);
    parent_state[cs110] = 0;
    parent_state[engl100] = 1;
    set_node_probability(bn, cs280, 1, parent_state, 0);
    set_node_probability(bn, cs280, 0, parent_state, 1-0);
    parent_state[cs110] = 0;
    parent_state[engl100] = 0;
    set_node_probability(bn, cs280, 1, parent_state, 0);
    set_node_probability(bn, cs280, 0, parent_state, 1-0);

    //===========================p(cs301 | cs201) CPT========================== 
    parent_state.clear();
    parent_state.add(cs201,1);
    set_node_probability(bn, cs301, 1, parent_state, difficulties[easy]);
    set_node_probability(bn, cs301, 0, parent_state, 1-difficulties[easy]);
    parent_state[cs201] = 0;
    set_node_probability(bn, cs301, 1, parent_state, 0);
    set_node_probability(bn, cs301, 0, parent_state, 1-0);

    //===========================p(cs203 | cs115) CPT========================== 
    parent_state.clear();
    parent_state.add(cs115,1);
    set_node_probability(bn, cs203, 1, parent_state, difficulties[easy]);
    set_node_probability(bn, cs203, 0, parent_state, 1-difficulties[easy]);
    parent_state[cs115] = 0;
    set_node_probability(bn, cs203, 1, parent_state, 0);
    set_node_probability(bn, cs203, 0, parent_state, 1-0);

    //===========================p(cs271 | cs110, cs270) CPT========================== 
    parent_state.clear();
    parent_state.add(cs110,1);
    parent_state.add(cs270,1);
    set_node_probability(bn, cs271, 1, parent_state, difficulties[easy]);
    set_node_probability(bn, cs271, 0, parent_state, 1-difficulties[easy]);
    parent_state[cs110] = 1;
    parent_state[cs270] = 0;
    set_node_probability(bn, cs271, 1, parent_state, 0);
    set_node_probability(bn, cs271, 0, parent_state, 1-0);
    parent_state[cs110] = 0;
    parent_state[cs270] = 1;
    set_node_probability(bn, cs271, 1, parent_state, 0);
    set_node_probability(bn, cs271, 0, parent_state, 1-0);
    parent_state[cs110] = 0;
    parent_state[cs270] = 0;
    set_node_probability(bn, cs271, 1, parent_state, 0);
    set_node_probability(bn, cs271, 0, parent_state, 1-0);

    // We have now finished setting up our bayesian network.  So lets compute some 
    // probability values.  The first thing we will do is compute the prior probability
    // of each node in the network.  To do this we will use the join tree algorithm which
    // is an algorithm for performing exact inference in a bayesian network.   

    // First we need to create an undirected graph which contains set objects at each node and
    // edge.  This long declaration does the trick.
    typedef set<unsigned long>::compare_1b_c set_type;
    typedef graph<set_type, set_type>::kernel_1a_c join_tree_type;
    join_tree_type join_tree;

    // Now we need to populate the join_tree with data from our bayesian network.  The next  
    // function calls do this.  Explaining exactly what they do is outside the scope of this
    // example.  Just think of them as filling join_tree with information that is useful 
    // later on for dealing with our bayesian network.  
    create_moral_graph(bn, join_tree);
    create_join_tree(join_tree, join_tree);


    // Now that we have a proper join_tree we can use it to obtain a solution to our
    // bayesian network.  Doing this is as simple as declaring an instance of
    // the bayesian_network_join_tree object as follows:
    bayesian_network_join_tree solution(bn, join_tree);


    // now print out the probabilities for each node
    cout << "Using the join tree algorithm, prior:\n";
    cout << "p(cs110=1) = " << solution.probability(cs110)(1) << endl;
    cout << "p(math105=1) = " << solution.probability(math105)(1) << endl;
    cout << "p(math110=1) = " << solution.probability(math110)(1) << endl;
    cout << "p(cs201=1) = " << solution.probability(cs201)(1) << endl;
    cout << "p(cs207=1) = " << solution.probability(cs207)(1) << endl;
    cout << "p(cs115=1) = " << solution.probability(cs115)(1) << endl;
    cout << "p(engl100=1) = " << solution.probability(engl100)(1) << endl;
    cout << "p(cs100=1) = " << solution.probability(cs100)(1) << endl;
    cout << "p(cs270=1) = " << solution.probability(cs270)(1) << endl;
    cout << "p(math111=1) = " << solution.probability(math111)(1) << endl;
    cout << "p(math122=1) = " << solution.probability(math122)(1) << endl;
    cout << "p(cs261=1) = " << solution.probability(cs261)(1) << endl;
    cout << "p(cs280=1) = " << solution.probability(cs280)(1) << endl;
    cout << "p(cs301=1) = " << solution.probability(cs301)(1) << endl;
    cout << "p(cs203=1) = " << solution.probability(cs203)(1) << endl;
    cout << "p(cs271=1) = " << solution.probability(cs271)(1) << endl;
    cout << "\n\n\n";


    // Now to make things more interesting lets say that we have discovered that the cs110 
    // node really has a value of 1.  That is to say, we now have evidence that 
    // cs110 is 1.  We can represent this in the network using the following two function
    // calls.
	/*  cs110 = 0,
        cs201 = 1,
        cs207 = 2,
        cs115 = 3,
		math105 = 4,
		math110 = 5,
		cs270 = 6,
		cs100 = 7,
		engl100 = 8,
		math122 = 9,
		math111 = 10,
		cs261 = 11,
		cs280 = 12,
		cs301 = 13,
		cs203 = 14,
		cs271 = 15 */

	//set leaf nodes to be 0:
	set_node_value(bn, cs110, 0);
	set_node_as_evidence(bn, cs110);
	set_node_value(bn, cs100, 0);
	set_node_as_evidence(bn, cs100);
	set_node_value(bn, engl100, 0);
	set_node_as_evidence(bn, engl100);
	set_node_value(bn, math105, 0);
	set_node_as_evidence(bn, math105);
	set_node_value(bn, math110, 0);
	set_node_as_evidence(bn, math110);
	set_node_value(bn, math111, 0);
	set_node_as_evidence(bn, math111);
	set_node_value(bn, math122, 0);
	set_node_as_evidence(bn, math122);

	//update evidence according to user input
	if (strstr(passed_courses, "-0-") != NULL) {
		set_node_value(bn, cs110, 1);
		set_node_as_evidence(bn, cs110);
	}
	if (strstr(passed_courses, "-1-") != NULL) {
		set_node_value(bn, cs201, 1);
		set_node_as_evidence(bn, cs201);
	}
	if (strstr(passed_courses, "-2-") != NULL) {
		set_node_value(bn, cs207, 1);
		set_node_as_evidence(bn, cs207);
	}
	if (strstr(passed_courses, "-3-") != NULL) {
		set_node_value(bn, cs115, 1);
		set_node_as_evidence(bn, cs115);
	}
	if (strstr(passed_courses, "-4-") != NULL) {
		set_node_value(bn, math105, 1);
		set_node_as_evidence(bn, math105);
	}
	if (strstr(passed_courses, "-5-") != NULL) {
		set_node_value(bn, math110, 1);
		set_node_as_evidence(bn, math110);
	}
	if (strstr(passed_courses, "-6-") != NULL) {
		set_node_value(bn, cs270, 1);
		set_node_as_evidence(bn, cs270);
	}
	if (strstr(passed_courses, "-7-") != NULL) {
		set_node_value(bn, cs100, 1);
		set_node_as_evidence(bn, cs100);
	}
	if (strstr(passed_courses, "-8-") != NULL) {
		set_node_value(bn, engl100, 1);
		set_node_as_evidence(bn, engl100);
	}
	if (strstr(passed_courses, "-9-") != NULL) {
		set_node_value(bn, math122, 1);
		set_node_as_evidence(bn, math122);
	}
	if (strstr(passed_courses, "-10-") != NULL) {
		set_node_value(bn, math111, 1);
		set_node_as_evidence(bn, math111);
	}
	if (strstr(passed_courses, "-11-") != NULL) {
		set_node_value(bn, cs261, 1);
		set_node_as_evidence(bn, cs261);
	}
	if (strstr(passed_courses, "-12-") != NULL) {
		set_node_value(bn, cs280, 1);
		set_node_as_evidence(bn, cs280);
	}
	if (strstr(passed_courses, "-13-") != NULL) {
		set_node_value(bn, cs301, 1);
		set_node_as_evidence(bn, cs301);
	}
	if (strstr(passed_courses, "-14-") != NULL) {
		set_node_value(bn, cs203, 1);
		set_node_as_evidence(bn, cs203);
	}
	if (strstr(passed_courses, "-15-") != NULL) {
		set_node_value(bn, cs271, 1);
		set_node_as_evidence(bn, cs271);
	}

    // Now we want to compute the probabilities of all the nodes in the network again
    // given that we now know that cs110 is 1.  We can do this as follows:
    bayesian_network_join_tree solution_with_evidence(bn, join_tree);

    // now print out the probabilities for each node
    cout << "Using the join tree algorithm, post:\n";
    cout << "p(cs110=1) = " << solution_with_evidence.probability(cs110)(1) << endl;
    cout << "p(math105=1) = " << solution_with_evidence.probability(math105)(1) << endl;
    cout << "p(math110=1) = " << solution_with_evidence.probability(math110)(1) << endl;
    cout << "p(cs201=1) = " << solution_with_evidence.probability(cs201)(1) << endl;
    cout << "p(cs207=1) = " << solution_with_evidence.probability(cs207)(1) << endl;
    cout << "p(cs115=1) = " << solution_with_evidence.probability(cs115)(1) << endl;
    cout << "p(engl100=1) = " << solution_with_evidence.probability(engl100)(1) << endl;
    cout << "p(cs100=1) = " << solution_with_evidence.probability(cs100)(1) << endl;
    cout << "p(cs270=1) = " << solution_with_evidence.probability(cs270)(1) << endl;
    cout << "p(math111=1) = " << solution_with_evidence.probability(math111)(1) << endl;
    cout << "p(math122=1) = " << solution_with_evidence.probability(math122)(1) << endl;
    cout << "p(cs261=1) = " << solution_with_evidence.probability(cs261)(1) << endl;
    cout << "p(cs280=1) = " << solution_with_evidence.probability(cs280)(1) << endl;
    cout << "p(cs301=1) = " << solution_with_evidence.probability(cs301)(1) << endl;
    cout << "p(cs203=1) = " << solution_with_evidence.probability(cs203)(1) << endl;
    cout << "p(cs271=1) = " << solution_with_evidence.probability(cs271)(1) << endl;
    cout << "\n\n\n";

    // Note that when we made our solution_with_evidence object we reused our join_tree object.
    // This saves us the time it takes to calculate the join_tree object from scratch.  But
    // it is important to note that we can only reuse the join_tree object if we haven't changed
    // the structure of our bayesian network.  That is, if we have added or removed nodes or 
    // edges from our bayesian network then we must recompute our join_tree.  But in this example
    // all we did was change the value of a bayes_node object (we made node cs110 be evidence)
    // so we are ok.

	//cout<<passed_courses<<endl;
	ostringstream result_str;
	result_str << "{ cs110:" 
		<< solution_with_evidence.probability(cs110)(1) << ", "
		<< "math105:" << solution_with_evidence.probability(math105)(1)<< ", "
		<< "math110:" << solution_with_evidence.probability(math110)(1)<< ", "
		<< "cs201:" << solution_with_evidence.probability(cs201)(1)<< ", "
		<< "cs207:" << solution_with_evidence.probability(cs207)(1)<< ", "
		<< "cs115:" << solution_with_evidence.probability(cs115)(1)<< ", "
		<< "engl100:" << solution_with_evidence.probability(engl100)(1)<< ", "
		<< "cs100:" << solution_with_evidence.probability(cs100)(1)<< ", "
		<< "cs270:" << solution_with_evidence.probability(cs270)(1)<< ", "
		<< "math111:" << solution_with_evidence.probability(math111)(1)<< ", "
		<< "math122:" << solution_with_evidence.probability(math122)(1)<< ", "
		<< "cs261:" << solution_with_evidence.probability(cs261)(1)<< ", "
		<< "cs280:" << solution_with_evidence.probability(cs280)(1)<< ", "
		<< "cs301:" << solution_with_evidence.probability(cs301)(1)<< ", "
		<< "cs203:" << solution_with_evidence.probability(cs203)(1)<< ", "
		<< "cs271:" << solution_with_evidence.probability(cs271)(1)
		<< "}";
	cout<<"bayes_net.cpp:"<<endl;
	cout<< result_str.str().c_str()<<endl;
	//ostringstream s;
	//s << 123791842.5;
	//cout<<s.str()<<endl;
/*
	char aCString[result_str.str().size()]; 
	strcpy(aCString, result_str.str().c_str());	
    return aCString;
*/

	char* aCString = (char *) malloc(result_str.str().length()+1);
	strncpy(aCString, result_str.str().c_str(), result_str.str().length() + 1);
	return aCString;
}


