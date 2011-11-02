#include "smile/smile.h"
void CreateNetwork(void);

void CreateNetwork(void) {
	DSL_network theNet;

	// create node "Success"
	int success = theNet.AddNode(DSL_CPT,"Success");

	// setting number (and name) of outcomes
	DSL_idArray someNames;
	someNames.Add("Success");
	someNames.Add("Failure");
	theNet.GetNode(success)->Definition()->SetNumberOfOutcomes(someNames);  

	// create node "Forecast"
	int forecast = theNet.AddNode(DSL_CPT,"Forecast");

	// setting number (and name) of outcomes
	someNames.Flush();
	someNames.Add("Good");
	someNames.Add("Moderate");
	someNames.Add("Poor");
	theNet.GetNode(forecast)->Definition()->SetNumberOfOutcomes(someNames);  

	 // add arc from "Success" to "Forecast"
	 theNet.AddArc(success,forecast);

	// now fill in the conditional distribution for node "Success" using
	// direct method. The probabilities are:
	// P("Success" = Success) = 0.2
	// P("Success" = Failure) = 0.8 
	DSL_doubleArray theProbs;
	theProbs.SetSize(2); // it has to be an array
	theProbs[0] = 0.2;
	theProbs[1] = 0.8;
	theNet.GetNode(success)->Definition()->SetDefinition(theProbs);

	// now fill in the conditional distribution for node "Forecast" using a system of 
	// coordinates. The probabilities are:
	// P("Forecast" = Good | "Success" = Success) = 0.4
	// P("Forecast" = Moderate | "Success" = Success) = 0.4
	// P("Forecast" = Poor | "Success" = Success) = 0.2
	// P("Forecast" = Good | "Success" = Failure) = 0.1
	// P("Forecast" = Moderate | "Success" = Failure) = 0.3
	// P("Forecast" = Poor | "Success" = Failure) = 0.6
	DSL_sysCoordinates theCoordinates (*theNet.GetNode(forecast)->Definition());
	theCoordinates.UncheckedValue() = 0.4;
	theCoordinates.Next();
	theCoordinates.UncheckedValue() = 0.4;
	theCoordinates.Next();
	theCoordinates.UncheckedValue() = 0.2;
	theCoordinates.Next();
	theCoordinates.UncheckedValue() = 0.1;
	theCoordinates.Next();
	theCoordinates.UncheckedValue() = 0.3;
	theCoordinates.Next();
	theCoordinates.UncheckedValue() = 0.6; 
	theNet.WriteFile("tutorial.dsl");
}

char* bayesian_test(char *passed_courses) {  
	char* resstr = (char*)malloc(sizeof(char)*256);
	strcat(resstr, "testing");

	CreateNetwork();  
	//InfereceWithBayesNet();  
	//UpgradeToInfluenceDiagram();  
	//InferenceWithInfluenceDiagram();  
	//ComputeValueOfInformation();  
	return resstr;
};

