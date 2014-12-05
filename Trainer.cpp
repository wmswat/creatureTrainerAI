//
//  Trainer.cpp
//  CreatureTrainer
//
//  You may NOT #include any .h files we provide you (Battle, Creature, CreatureType,
//  EECSRandom, Party, PrintHelper)
//  other than the ones name "ClassX.h" and "Trainer.h"
//  You may #include other <> libraries if you wish to
//
//  Created by Jeremy Gibson on 11/4/14.
//  Copyright (c) 2014 Jeremy Richard Gibson. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include "Trainer.h"
#include "Class1.h"
#include "Class2.h"
#include "Class3.h"
#include "Class4.h"
#include "Class5.h"

//#include "CreatureType.h"

using namespace std;

string Trainer::makeMove(stringstream& situation) {

	cout << situation.str();
	// pull the entire string out of stringStream& situation
	string situationString = situation.str();
	// situationString now includes ALL of the lines that will be sent to cout

	// Here's how to use the stringSplit function
	vector<string> lines = splitString(situationString, "\n");
	// This splits situationString into a vector of individual lines.
	// (it splits on the new line character "\n")
	// To access the 3rd line (as in 0, 1, 2, 3), you would use bracket access
	//   as in: lines[3]

	// This loop will iterate through all the lines
	int pipeLine = -1;
	// lines.size() tells us how many elements are in the vector<string> lines
	// In this case, it tells us how many lines we pulled in
	for (int i = 0; i < lines.size(); i++) {
		// Store each line in the string line
		string line = lines[i];
		// Store the first char of line in the char c
		char c = line[0];
		// If c is a pipe ('|'), then this is the line that tells us about our
		//    party and the health of each Creature we own.
		if (c == '|') {
			// Store which line number this is
			pipeLine = i;
		}
	}

	// Now that we know which line has the health, do something with it
	//cout << lines[pipeLine] << "\n"; // Output for testing only

	// Split the party health line by pipes "|"
	vector<string> creatureHealthBits = splitString(lines[pipeLine], "|");
	// This gives us something like the vector description below
	/* { "",
	" *Jackal     10/10",
	" Yaminon    17/17",
	" Megapode   13/13",
	" Jackal     10/10",
	"" } */
	// You can see that the first and last pipe caused empty strings

	// Now, go through this information and pull out info for each entry
	// We do 1 to <creatureHealthBits.size()-1 because we only need the middle
	//    four elements (and are skipping the empty ones.
	int health;
	int maxHealth;
	int creatureHealth[4];
	int creatureMaxHealth[4];
	int activeHealth;
	int activeMaxHealth;
	string name;
	int creatureNameMaxHealth[26] = { -20 }; //Random number -20
	int activeIndex = 0;

	for (int i = 1; i < creatureHealthBits.size() - 1; i++) {

		// cout just for testing
		//cout << creatureHealthBits[i] << "\n";

		// We are putting the string into a stringStream so we can use >>
		stringstream ss;
		ss << creatureHealthBits[i];

		// For example, we have a stringstream ss containing " *Jackal   10/10 "
		// pull the name as a string

		ss >> name; // name = "*Jackal"

		// pull the health

		ss >> health; // health = 10

		// Get rid of the slash char
		char slash;
		ss >> slash; // slash = '/'

		// get max health

		ss >> maxHealth; // maxHealth = 10

		creatureNameMaxHealth[int(name[0]) - 65] = maxHealth;

		// cout this info for testing purposes
		//cout << "Name: " << name << " health: " << health << "\n";

		creatureHealth[i - 1] = health;
		creatureMaxHealth[i - 1] = maxHealth;

		if (name[0] == '*'){
			activeHealth = health;
			activeMaxHealth = maxHealth;
			activeIndex = i - 1;
		}
	}


	string yourtype;
	int yourAttack = -1;
	string yourName;


	situationString = situation.str();
	lines = splitString(situationString, "\n");
	int pipeLineY = -1;

	// lines.size() tells us how many elements are in the vector<string> lines
	// In this case, it tells us how many lines we pulled in
	for (int i = 0; i < lines.size(); i++) {
		//cout << i << endl;
		// Store each line in the string line

		string line = lines[i];
		//cout << line;
		// Store the first char of line in the char c
		char c = line[0];
		// If c is a pipe ('|'), then this is the line that tells us about our
		//    party and the health of each Creature we own.
		//cout << c << endl;
		//cout << "*" << c << "*" << endl;
		if (c == 'Y') {
			// Store which line number this is
			//cout << i << endl;
			pipeLineY = i;
		}
	}

	if (pipeLineY == -1){
		return "a";
	}

	//cout << lines[pipeLineY] << endl;
	//cout << pipeLineY << endl;


	string yourMove;
	yourMove = lines[pipeLineY];
	// cout just for testing
	//cout << creatureHealthBits[i] << "\n";

	// We are putting the string into a stringStream so we can use >>
	stringstream ssYM;
	ssYM << yourMove;

	//gets ride of Your
	string temp1;
	ssYM >> temp1;

	//gets name of creature
	ssYM >> yourName;

	// Get rid of attacks
	string temp2;
	ssYM >> temp2;

	// get rid of Enemy
	string temp3;
	ssYM >> temp3;

	// get rid of Enemy name
	string temp4;
	ssYM >> temp4;

	// get rid of with
	string temp5;
	ssYM >> temp5;

	//get your type
	ssYM >> yourtype;

	// get rid of for
	string temp6;
	ssYM >> temp6;

	//get your attack
	ssYM >> yourAttack;

	string opptype;
	int oppAttack = -1;
	string oppName;

	situationString = situation.str();
	lines = splitString(situationString, "\n");

	int pipeLineE = -1;
	// lines.size() tells us how many elements are in the vector<string> lines
	// In this case, it tells us how many lines we pulled in
	for (int i = 0; i < lines.size(); i++) {
		// Store each line in the string line
		string line = lines[i];
		// Store the first char of line in the char c
		char c = line[0];
		// If c is a pipe ('|'), then this is the line that tells us about our
		//    party and the health of each Creature we own.
		//cout << "**" << c << "**" << endl;
		if (c == 'E') {
			// Store which line number this is
			pipeLineE = i;
		}
	}

	string oppMove;
	oppMove = lines[pipeLineE];

	// cout just for testing
	//cout << creatureHealthBits[i] << "\n";

	// We are putting the string into a stringStream so we can use >>
	stringstream ssOM;
	ssOM << oppMove;

	//gets ride of Your

	ssOM >> temp1;

	//gets name of creature
	ssOM >> oppName;

	// Get rid of attacks

	ssOM >> temp2;

	// get rid of Enemy

	ssOM >> temp3;

	// get rid of Enemy name

	ssOM >> temp4;

	// get rid of with

	ssOM >> temp5;

	//get your type
	ssOM >> opptype;

	// get rid of for

	ssOM >> temp6;

	//get your attack
	ssOM >> oppAttack;

	// This is something else you can do ONLY for testing.
	// In a previous post, I recommended #including CreatureType.h so that you
	//    can make a Trainer::decide() function that will make the right
	//    decision if you have perfect data about creature types.
	// While developing, you can use the static vector<CreatureType> TYPES to
	//    get that perfect information, though you will eventually need to write
	//    your own function to learn that information from the data that is sent
	//    in via stringstream& situation.

	/*
	// This makes ct a copy of the CreatureType for Creature 0 (the Axolotyl).
	// All CreatureType and Element names start with a different letter of the
	//    alphabet (CreatureType is A-Z, Element is A-H).
	CreatureType ct = CreatureType::TYPES[0];
	// You can then get the type of ct, which is 0 because it's the Axolotyl
	int type = ct.getType();
	// You can also directly get info from CreatureTypes::TYPES elements.
	int elementalWeakness3 = CreatureType::TYPES[3].getElementalWeakness();
	*/

	// Output for human player
	// Instead of doing this, you will need to replace the code of Trainer
	// to parse the input situation and create a proper response,
	// (like "a" for attack or "s3" to swap to the creature in slot 3).


	//cout << situation.str();


	/*
	* This line is basically what your AI chooses to do
	* When first playing, you may type in your move.
	* For both the core and reach portions, however, you need to
	* comment out "cin >> response" and instead have this function
	* generate a response string.
	*/
	string response;
	//cin >> response;


	//cout << endl << yourAttack << endl << oppAttack << endl;
	//cout << activeHealth << endl;
	if (yourAttack >= oppAttack && activeHealth > 7){
		response = "a";
	}
	else{
		response = "test";
		int i = 0;
		if (i == activeIndex){
			i++;
		}
		while (response == "test" && i < 4){
			if (creatureHealth[i] > 6){
				if (i == 0){
					response = "s1";
				}
				else if (i == 1){
					response = "s2";
				}
				else if (i == 2){
					response = "s3";
				}
				else{
					response = "s4";
				}
			}
			i++;
			if (i == activeIndex){
				i++;
			}
		}
	}
	

	if (response == "test"){
		response = "a";
	}
	//cout << activeHealth << endl << activeMaxHealth << endl;


	//cout << '*' << response << endl;;
	return response;
}


void Trainer::finalSituation(stringstream& situation) {
	cout << situation.str();

}



vector<string> Trainer::splitString(string inString, string splitOn) {
	vector<string> elements;
	string substring;

	size_t splitIndex = inString.find(splitOn),
		substrStart = 0;

	// keep searching until no spaces remain
	while (splitIndex != string::npos) {
		substring = inString.substr(substrStart, splitIndex - substrStart);
		elements.push_back(substring);
		substrStart = splitIndex + 1;
		// start at next character after finding substring
		splitIndex = inString.find(splitOn, substrStart);
	}
	// add last element to vector
	substring = inString.substr(substrStart, inString.length() - substrStart);
	elements.push_back(substring);

	return elements;
}
