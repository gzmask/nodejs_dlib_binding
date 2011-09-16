net Unnamed
{
 HEADER = 
  {
   ID = Unnamed;
   NAME = "Unnamed";
  };
 CREATION = 
  {
  };
 NUMSAMPLES = 1000;
 SCREEN = 
  {
   POSITION = 
    {
     CENTER_X = 0;
     CENTER_Y = 0;
     WIDTH = 76;
     HEIGHT = 36;
    };
   COLOR = 16250597;
   SELCOLOR = 12303291;
   FONT = 1;
   FONTCOLOR = 0;
   BORDERTHICKNESS = 3;
   BORDERCOLOR = 12255232;
  };
 WINDOWPOSITION = 
  {
   CENTER_X = 0;
   CENTER_Y = 0;
   WIDTH = 0;
   HEIGHT = 0;
  };
 BKCOLOR = 16777215;
 USER_PROPERTIES = 
  {
  };
 DOCUMENTATION = 
  {
  };
 SHOWAS = 3;

 node Success
  {
   TYPE = CPT;
   HEADER = 
    {
     ID = Success;
     NAME = "Success";
    };
   SCREEN = 
    {
     POSITION = 
      {
       CENTER_X = 0;
       CENTER_Y = 0;
       WIDTH = 76;
       HEIGHT = 36;
      };
     COLOR = 16250597;
     SELCOLOR = 12303291;
     FONT = 1;
     FONTCOLOR = 0;
     BORDERTHICKNESS = 1;
     BORDERCOLOR = 12255232;
    };
   USER_PROPERTIES = 
    {
    };
   DOCUMENTATION = 
    {
    };
   PARENTS = ();
   DEFINITION = 
    {
     NAMESTATES = (Success, Failure);
     PROBABILITIES = (0.20000000, 0.80000000);
    };
   EXTRA_DEFINITION = 
    {
     DIAGNOSIS_TYPE = AUXILIARY;
     RANKED = FALSE;
     MANDATORY = FALSE;
     SETASDEFAULT = FALSE;
     SHOWAS = 4;
     FAULT_STATES = (0, 0);
     FAULT_NAMES = ("", "");
     FAULT_LABELS = ("", "");
     DEFAULT_STATE = 0;
     DOCUMENTATION = 
      {
      };
     DOCUMENTATION = 
      {
      };
     STATECOMMENTS = ("", "");
     STATEREPAIRINFO = ("", "");
     QUESTION = "";
    };
  };

 node Forecast
  {
   TYPE = CPT;
   HEADER = 
    {
     ID = Forecast;
     NAME = "Forecast";
    };
   SCREEN = 
    {
     POSITION = 
      {
       CENTER_X = 0;
       CENTER_Y = 0;
       WIDTH = 76;
       HEIGHT = 36;
      };
     COLOR = 16250597;
     SELCOLOR = 12303291;
     FONT = 1;
     FONTCOLOR = 0;
     BORDERTHICKNESS = 1;
     BORDERCOLOR = 12255232;
    };
   USER_PROPERTIES = 
    {
    };
   DOCUMENTATION = 
    {
    };
   PARENTS = (Success);
   DEFINITION = 
    {
     NAMESTATES = (Good, Moderate, Poor);
     PROBABILITIES = (0.40000000, 0.40000000, 0.20000000, 0.10000000, 
     0.30000000, 0.60000000);
    };
   EXTRA_DEFINITION = 
    {
     DIAGNOSIS_TYPE = AUXILIARY;
     RANKED = FALSE;
     MANDATORY = FALSE;
     SETASDEFAULT = FALSE;
     SHOWAS = 4;
     FAULT_STATES = (0, 0, 0);
     FAULT_NAMES = ("", "", "");
     FAULT_LABELS = ("", "", "");
     DEFAULT_STATE = 0;
     DOCUMENTATION = 
      {
      };
     DOCUMENTATION = 
      {
      };
     DOCUMENTATION = 
      {
      };
     STATECOMMENTS = ("", "", "");
     STATEREPAIRINFO = ("", "", "");
     QUESTION = "";
    };
  };
 OBSERVATION_COST = 
  {

   node Success
    {
     PARENTS = ();
     COSTS = (0.00000000);
    };

   node Forecast
    {
     PARENTS = ();
     COSTS = (0.00000000);
    };
  };
};
