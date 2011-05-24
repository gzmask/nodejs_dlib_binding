#include <string>
#include <fstream>
#include <iostream>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;


int main() {

	string ori_text = "\
<!-- Edited by XMLSpy® --> \n\
<breakfast_menu> \n\
	<food order=\"first\"> \n\
		<name>Belgian Waffles</name> \n\
		<price>$5.95</price> \n\
		<description> \n\
			two of our famous Belgian Waffles with plenty of real maple syrup \n\
		</description> \n\
		<calories>650</calories> \n\
	</food> \n\
	<food order=\"second\"> \n\
		<name>Strawberry Belgian Waffles</name> \n\
		<price>$7.95</price> \n\
		<description> \n\
			light Belgian waffles covered with strawberries and whipped cream \n\
		</description> \n\
		<calories>900</calories> \n\
	</food> \n\
	<food order=\"third\"> \n\
		<name>Berry-Berry Belgian Waffles</name> \n\
		<price>$8.95</price> \n\
		<description> \n\
			light Belgian waffles covered with an assortment of fresh berries and whipped cream \n\
		</description> \n\
		<calories>900</calories> \n\
	</food> \n\
	<food order=\"fourth\"> \n\
		<name>French Toast</name> \n\
		<price>$4.50</price> \n\
		<description> \n\
			thick slices made from our homemade sourdough bread \n\
		</description> \n\
		<calories>600</calories> \n\
	</food> \n\
	<food order=\"fifth\"> \n\
		<name>Homestyle Breakfast</name> \n\
		<price>$6.95</price> \n\
		<description> \n\
			two eggs, bacon or sausage, toast, and our ever-popular hash browns \n\
		</description> \n\
		<calories>950</calories> \n\
	</food> \n\
</breakfast_menu> \n";

	//cast the string to char*
	char *text = (char *)ori_text.c_str();

	//parse the string
	xml_document<> doc;    // character type defaults to char
	cout<<text<<endl;
	doc.parse<0>(text);    // 0 means default parse flags

	cout << "Name of my first node is: " << doc.first_node()->name() << "\n";

	//nest node traversal
	for (xml_node<> *node = doc.first_node()->first_node("food"); node; node = node->next_sibling()) {

		//attribute traversal
		for (xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
			cout << "Node food has attribute " << attr->name() << " ";
			cout << "with value " << attr->value() << "\n";
		}

		cout << "Node food has value " << node->first_node("name")->value() << "\n\n";
	}

	
	
	return 0;
}
