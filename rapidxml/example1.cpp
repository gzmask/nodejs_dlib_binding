#include <string>
#include <fstream>
#include <iostream>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;


int main() {


	string block_str = "\
<?xml version=\"1.0\"?> \n\
<ANALYSISNOTEBOOK NAME=\"Notebook.bndefault\" ROOT=\"bndefault\"> \n\
<BNMODEL NAME=\"bndefault\"> \n\
	<STATICPROPERTIES><FORMAT>MSR DTAS XML</FORMAT> \n\
		<VERSION>1.0</VERSION> \n\
		<CREATOR>Microsoft Research DTAS</CREATOR> \n\
	</STATICPROPERTIES> \n\
	<DYNAMICPROPERTIES> \n\
		<PROPERTYTYPE NAME=\"DTASDG_Notes\" TYPE=\"stringarray\"> \n\
			<COMMENT>Notes on the diagram</COMMENT> \n\
		</PROPERTYTYPE> \n\
		<PROPERTYTYPE NAME=\"MS_Addins\" TYPE=\"stringarray\"/> \n\
	</DYNAMICPROPERTIES> \n\
	<VARIABLES> \n\
		<VAR NAME=\"Burglary\" TYPE=\"discrete\" XPOS=\"0\" YPOS=\"2500\"> \n\
			<FULLNAME>Burglary</FULLNAME> \n\
			<STATENAME>Yes</STATENAME> \n\
			<STATENAME>No</STATENAME> \n\
		</VAR> \n\
		<VAR NAME=\"Alarm\" TYPE=\"discrete\" XPOS=\"3250\" YPOS=\"7500\"> \n\
			<FULLNAME>Alarm</FULLNAME> \n\
			<STATENAME>Yes</STATENAME> \n\
			<STATENAME>No</STATENAME> \n\
		</VAR> \n\
		<VAR NAME=\"JohnCalls\" TYPE=\"discrete\" XPOS=\"0\" YPOS=\"12500\"> \n\
			<FULLNAME>JohnCalls</FULLNAME> \n\
			<STATENAME>Yes</STATENAME> \n\
			<STATENAME>No</STATENAME> \n\
		</VAR> \n\
		<VAR NAME=\"MaryCalls\" TYPE=\"discrete\" XPOS=\"6500\" YPOS=\"12500\"> \n\
			<FULLNAME>MaryCalls</FULLNAME> \n\
			<STATENAME>Yes</STATENAME> \n\
			<STATENAME>No</STATENAME> \n\
		</VAR> \n\
		<VAR NAME=\"Earthquake\" TYPE=\"discrete\" XPOS=\"6500\" YPOS=\"2500\"> \n\
			<FULLNAME>Earthquake</FULLNAME> \n\
			<STATENAME>Yes</STATENAME> \n\
			<STATENAME>No</STATENAME> \n\
		</VAR> \n\
	</VARIABLES> \n\
	<STRUCTURE> \n\
		<ARC PARENT=\"Burglary\" CHILD=\"Alarm\"/> \n\
		<ARC PARENT=\"Earthquake\" CHILD=\"Alarm\"/> \n\
		<ARC PARENT=\"Alarm\" CHILD=\"JohnCalls\"/> \n\
		<ARC PARENT=\"Alarm\" CHILD=\"MaryCalls\"/> \n\
	</STRUCTURE> \n\
	<DISTRIBUTIONS> \n\
		<DIST TYPE=\"discrete\"> \n\
			<PRIVATE NAME=\"Alarm\"/> \n\
			<CONDSET> \n\
				<CONDELEM NAME=\"Burglary\"/>     \n\
				<CONDELEM NAME=\"Earthquake\"/>   \n\
			</CONDSET> \n\
			<DPIS> \n\
				<DPI INDEXES=\"0 0 \">0.95 0.05 </DPI> \n\
				<DPI INDEXES=\"0 1 \">0.94 0.06 </DPI> \n\
				<DPI INDEXES=\"1 0 \">0.29 0.71 </DPI> \n\
				<DPI INDEXES=\"1 1 \">0.001 0.999 </DPI> \n\
			</DPIS> \n\
		</DIST> \n\
		<DIST TYPE=\"discrete\"> \n\
			<PRIVATE NAME=\"JohnCalls\"/> \n\
			<CONDSET> \n\
				<CONDELEM NAME=\"Alarm\"/>   \n\
			</CONDSET> \n\
			<DPIS> \n\
				<DPI INDEXES=\"0 \">0.9 0.1 </DPI> \n\
				<DPI INDEXES=\"1 \">0.05 0.95 </DPI> \n\
			</DPIS> \n\
		</DIST> \n\
		<DIST TYPE=\"discrete\"> \n\
			<PRIVATE NAME=\"MaryCalls\"/> \n\
			<CONDSET> \n\
				<CONDELEM NAME=\"Alarm\"/>   \n\
			</CONDSET> \n\
			<DPIS> \n\
				<DPI INDEXES=\"0 \">0.7 0.3 </DPI> \n\
				<DPI INDEXES=\"1 \">0.01 0.99 </DPI> \n\
			</DPIS> \n\
		</DIST> \n\
		<DIST TYPE=\"discrete\"> \n\
			<PRIVATE NAME=\"Burglary\"/> \n\
			<DPIS> \n\
				<DPI>0.001 0.999 </DPI> \n\
			</DPIS> \n\
		</DIST> \n\
		<DIST TYPE=\"discrete\"> \n\
			<PRIVATE NAME=\"Earthquake\"/> \n\
			<DPIS> \n\
				<DPI>0.002 0.998 </DPI> \n\
			</DPIS> \n\
		</DIST> \n\
	</DISTRIBUTIONS> \n\
</BNMODEL> \n\
</ANALYSISNOTEBOOK> \n";


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
