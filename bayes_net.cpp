#include "dlib/bayes_utils.h"
#include "dlib/graph_utils.h"
#include "dlib/graph.h"
#include "dlib/directed_graph.h"
#include <iostream>


using namespace dlib;
using namespace std;
#include "bayes_net.h"

// ----------------------------------------------------------------------------------------
int bayesian_test(int x, int y)
{
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
    enum nodes
    {
        cs110 = 0,
        cs201 = 1,
        cs207 = 2,
        cs115 = 3
    };

    // The next few blocks of code setup our bayesian network.

    // The first thing we do is tell the bn object how many nodes it has
    // and also add the three edges.  Again, we are using the network
    // shown in ASCII art at the top of this file.
    bn.set_number_of_nodes(4);
    bn.add_edge(cs110, cs201);
    bn.add_edge(cs110, cs207);
    bn.add_edge(cs110, cs115);


    // Now we inform all the nodes in the network that they are binary
    // nodes.  That is, they only have two possible values.  
    set_node_num_values(bn, cs110, 2);
    set_node_num_values(bn, cs201, 2);
    set_node_num_values(bn, cs207, 2);
    set_node_num_values(bn, cs115, 2);

    assignment parent_state;
    // Now we will enter all the conditional probability information for each node.
    // Each node's conditional probability is dependent on the state of its parents.  
    // To specify this state we need to use the assignment object.  This assignment 
    // object allows us to specify the state of each nodes parents. 


    // Here we specify that p(cs110=1) = 0.5
    // parent_state is empty in this case since cs110 is a root node. 
    set_node_probability(bn, cs110, 1, parent_state, 0.5);
    set_node_probability(bn, cs110, 0, parent_state, 1-0.5);

    // This is our first node that has parents. So we set the parent_state
    // object to reflect that cs201 has cs110 as parents.
    parent_state.add(cs110, 1);
    // Here we specify that p(cs201=1 | cs110=1) = 0.8 
    set_node_probability(bn, cs201, 1, parent_state, 0.8);
    set_node_probability(bn, cs201, 0, parent_state, 1-0.8);

    // Here we use the [] notation because cs110 has already
    // been added into parent state.  
    parent_state[cs110] = 0;
    // Here we specify that p(cs201=1 | cs110=0) = 0 
    set_node_probability(bn, cs201, 1, parent_state, 0);
    set_node_probability(bn, cs201, 0, parent_state, 1-0);

    // Here we set probabilities for node cs207.
    // First we clear out parent state so that it doesn't have any of
    // the assignments for the cs110 used above.
    parent_state.clear();
    parent_state.add(cs110,1);
    // Here we specify that p(cs207=1 | cs110=1) = 0.8 
    set_node_probability(bn, cs207, 1, parent_state, 0.8);
    set_node_probability(bn, cs207, 0, parent_state, 1-0.8);

    parent_state[cs110] = 0;
    // Here we specify that p(cs207=1 | cs110=0) = 0 
    set_node_probability(bn, cs207, 1, parent_state, 0);
    set_node_probability(bn, cs207, 0, parent_state, 1-0);

    // Here we set probabilities for node cs115.
    // First we clear out parent state so that it doesn't have any of
    // the assignments for the cs110 used above.
    parent_state.clear();
    parent_state.add(cs110,1);
    // Here we specify that p(cs115=1 | cs110=1) = 0.8 
    set_node_probability(bn, cs115, 1, parent_state, 0.8);
    set_node_probability(bn, cs115, 0, parent_state, 1-0.8);

    parent_state[cs110] = 0;
    // Here we specify that p(cs115=1 | cs110=0) = 0 
    set_node_probability(bn, cs115, 1, parent_state, 0);
    set_node_probability(bn, cs115, 0, parent_state, 1-0);


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
    cout << "p(cs110=0) = " << solution.probability(cs110)(0) << endl;
    cout << "p(cs201=1) = " << solution.probability(cs201)(1) << endl;
    cout << "p(cs201=0) = " << solution.probability(cs201)(0) << endl;
    cout << "p(cs207=1) = " << solution.probability(cs207)(1) << endl;
    cout << "p(cs207=0) = " << solution.probability(cs207)(0) << endl;
    cout << "p(cs115=1) = " << solution.probability(cs115)(1) << endl;
    cout << "p(cs115=0) = " << solution.probability(cs115)(0) << endl;
    cout << "\n\n\n";


    // Now to make things more interesting lets say that we have discovered that the cs110 
    // node really has a value of 1.  That is to say, we now have evidence that 
    // cs110 is 1.  We can represent this in the network using the following two function
    // calls.
    set_node_value(bn, cs110, 1);
    set_node_as_evidence(bn, cs110);

    // Now we want to compute the probabilities of all the nodes in the network again
    // given that we now know that cs110 is 1.  We can do this as follows:
    bayesian_network_join_tree solution_with_evidence(bn, join_tree);

    // now print out the probabilities for each node
    cout << "Using the join tree algorithm, post:\n";
    cout << "p(cs110=1|cs110=1) = " << solution_with_evidence.probability(cs110)(1) << endl;
    cout << "p(cs110=0|cs110=1) = " << solution_with_evidence.probability(cs110)(0) << endl;
    cout << "p(cs201=1|cs110=1) = " << solution_with_evidence.probability(cs201)(1) << endl;
    cout << "p(cs201=0|cs110=1) = " << solution_with_evidence.probability(cs201)(0) << endl;
    cout << "p(cs207=1|cs110=1) = " << solution_with_evidence.probability(cs207)(1) << endl;
    cout << "p(cs207=0|cs110=1) = " << solution_with_evidence.probability(cs207)(0) << endl;
    cout << "p(cs115=1|cs110=1) = " << solution_with_evidence.probability(cs115)(1) << endl;
    cout << "p(cs115=0|cs110=1) = " << solution_with_evidence.probability(cs115)(0) << endl;
    cout << "\n\n\n";

    // Note that when we made our solution_with_evidence object we reused our join_tree object.
    // This saves us the time it takes to calculate the join_tree object from scratch.  But
    // it is important to note that we can only reuse the join_tree object if we haven't changed
    // the structure of our bayesian network.  That is, if we have added or removed nodes or 
    // edges from our bayesian network then we must recompute our join_tree.  But in this example
    // all we did was change the value of a bayes_node object (we made node cs110 be evidence)
    // so we are ok.

    return x+y;
}


