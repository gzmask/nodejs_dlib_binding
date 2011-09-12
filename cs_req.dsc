network "bndefault"
{
	version is 1;
	creator is "Microsoft Research DTAS";
	format is "MSR DTAS XML";
}

properties
{
	type DTASDG_Notes = array of string,
		"Notes on the diagram";
	type MS_Addins = array of string;
}

node Cs100
{
	name = "cs100";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (14845, -4527);
}

node Cs110
{
	name = "cs110";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (8713, -4521);
}

node Cs115
{
	name = "cs115";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (17214, 4489);
}

node Cs201
{
	name = "cs201";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (2854, 4541);
}

node Cs203
{
	name = "cs203";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (13738, 7140);
}

node Cs207
{
	name = "cs207";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (8929, 4553);
}

node Cs210
{
	name = "cs210";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (19414, 12314);
}

node Cs215
{
	name = "cs215";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (1779, 19517);
}

node Cs261
{
	name = "cs261";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (33143, 4594);
}

node Cs270
{
	name = "cs270";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (25929, 4577);
}

node Cs271
{
	name = "cs271";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (24059, 8346);
}

node Cs280
{
	name = "cs280";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (41033, 4768);
}

node Cs301
{
	name = "cs301";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (2779, 8259);
}

node Cs310
{
	name = "cs310";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (8257, 19459);
}

node Cs315
{
	name = "cs315";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (14615, 19435);
}

node Cs320
{
	name = "cs320";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (21294, 19400);
}

node Cs327
{
	name = "cs327";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (10859, 12314);
}

node Cs330
{
	name = "cs330";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (27414, 19398);
}

node Cs335
{
	name = "cs335";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (33911, 19398);
}

node Cs340
{
	name = "cs340";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (40214, 19242);
}

node Cs350
{
	name = "cs350";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (46673, 19164);
}

node Cs360
{
	name = "cs360";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (33259, 8493);
}

node Cs401
{
	name = "cs401";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (2392, 12400);
}

node Cs461
{
	name = "cs461";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (33379, 12344);
}

node Engl100
{
	name = "engl100";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (21029, -4501);
}

node Has60credit
{
	name = "has60credit";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (2569, -4531);
}

node Math105
{
	name = "math105";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (27317, -4501);
}

node Math110
{
	name = "math110";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (33673, -4414);
}

node Math111
{
	name = "math111";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (39755, -4472);
}

node Math122
{
	name = "math122";
	type = discrete[2]
	{
		"Yes",
		"No"
	};

	position = (46107, -4473);
}

probability(Cs100)
{
	0.773, 0.227;
}

probability(Cs110)
{
	0.807, 0.193;
}

probability(Cs115|Cs110,Math105,Math110)
{
	(0, 0, 0) = 0.5, 0.5;
	(0, 0, 1) = 0.5, 0.5;
	(0, 1, 0) = 0.5, 0.5;
	(0, 1, 1) = 0.5, 0.5;
	(1, 0, 0) = 0.5, 0.5;
	(1, 0, 1) = 0.5, 0.5;
	(1, 1, 0) = 0.504, 0.496;
	(1, 1, 1) = 0, 1;
}

probability(Cs201|Cs110)
{
	(0) = 0.706, 0.294;
	(1) = 0, 1;
}

probability(Cs203|Cs115)
{
	(0) = 0.5, 0.5;
	(1) = 0.5, 0.5;
}

probability(Cs207|Cs110)
{
	(0) = 0.79, 0.21;
	(1) = 0, 1;
}

probability(Cs210|Cs115)
{
	(0) = 0.5, 0.5;
	(1) = 0.5, 0.5;
}

probability(Cs215|Cs210)
{
	(0) = 0.5, 0.5;
	(1) = 0.5, 0.5;
}

probability(Cs261|Cs110,Math111,Math122)
{
	(0, 0, 0) = 0.5, 0.5;
	(0, 0, 1) = 0.5, 0.5;
	(0, 1, 0) = 0.5, 0.5;
	(0, 1, 1) = 0.5, 0.5;
	(1, 0, 0) = 0.5, 0.5;
	(1, 0, 1) = 0.5, 0.5;
	(1, 1, 0) = 0.5, 0.5;
	(1, 1, 1) = 0.5, 0.5;
}

probability(Cs270|Cs110,Cs115,Cs100,Engl100)
{
	(0, 0, 0, 0) = 0.5, 0.5;
	(0, 0, 0, 1) = 0.5, 0.5;
	(0, 0, 1, 0) = 0.5, 0.5;
	(0, 0, 1, 1) = 0.5, 0.5;
	(0, 1, 0, 0) = 0.5, 0.5;
	(0, 1, 0, 1) = 0.5, 0.5;
	(0, 1, 1, 0) = 0.5, 0.5;
	(0, 1, 1, 1) = 0.5, 0.5;
	(1, 0, 0, 0) = 0.5, 0.5;
	(1, 0, 0, 1) = 0.5, 0.5;
	(1, 0, 1, 0) = 0.5, 0.5;
	(1, 0, 1, 1) = 0.5, 0.5;
	(1, 1, 0, 0) = 0.5, 0.5;
	(1, 1, 0, 1) = 0.5, 0.5;
	(1, 1, 1, 0) = 0.5, 0.5;
	(1, 1, 1, 1) = 0.5, 0.5;
}

probability(Cs271|Cs270,Cs110)
{
	(0, 0) = 0.5, 0.5;
	(0, 1) = 0.5, 0.5;
	(1, 0) = 0.5, 0.5;
	(1, 1) = 0.5, 0.5;
}

probability(Cs280|Cs110)
{
	(0) = 0.5, 0.5;
	(1) = 0.5, 0.5;
}

probability(Cs301|Cs201)
{
	(0) = 0.84, 0.16;
	(1) = 0, 1;
}

probability(Cs310|Cs210)
{
	(0) = 0.5, 0.5;
	(1) = 0.5, 0.5;
}

probability(Cs315|Cs210)
{
	(0) = 0.5, 0.5;
	(1) = 0.5, 0.5;
}

probability(Cs320|Cs210)
{
	(0) = 0.5, 0.5;
	(1) = 0.5, 0.5;
}

probability(Cs327|Has60credit)
{
	(0) = 0.5, 0.5;
	(1) = 0.5, 0.5;
}

probability(Cs330|Cs210)
{
	(0) = 0.5, 0.5;
	(1) = 0.5, 0.5;
}

probability(Cs335|Cs210)
{
	(0) = 0.5, 0.5;
	(1) = 0.5, 0.5;
}

probability(Cs340|Cs210)
{
	(0) = 0.5, 0.5;
	(1) = 0.5, 0.5;
}

probability(Cs350|Cs210)
{
	(0) = 0.5, 0.5;
	(1) = 0.5, 0.5;
}

probability(Cs360|Cs261)
{
	(0) = 0.5, 0.5;
	(1) = 0.5, 0.5;
}

probability(Cs401|Cs301)
{
	(0) = 0.807, 0.193;
	(1) = 0, 1;
}

probability(Cs461|Cs360)
{
	(0) = 0.5, 0.5;
	(1) = 0.5, 0.5;
}

probability(Engl100)
{
	0.689, 0.311;
}

probability(Has60credit)
{
	0.782, 0.218;
}

probability(Math105)
{
	0.765, 0.235;
}

probability(Math110)
{
	0.756, 0.244;
}

probability(Math111)
{
	0.714, 0.286;
}

probability(Math122)
{
	0.807, 0.193;
}

