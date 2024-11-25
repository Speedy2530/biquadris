#include <iostream>
#include <string>

using namespace std;

void CommandInterpreter::callMethod(string command, string file = "") {
	string command_call;

	// check if command is correct (in commands)
	for (string correct_command : commands) {
		if (command == correct_command) {
			command_call = command;
		}
	}

	switch (command) {
		case "left", "l", "lef":
			//
			break;
		case "right", "r", "ri":
			//
			break;
		case "down", "dn", "do":
			//
			break;
		case "clockwise", "c", "cl":
			//
			break;
		case "counterclockwise", "cc", "co":
			//
			break;
		case "drop", "dp", "dr":
			//
			break;
		case "levelup", "lu":
			//
			break;
		case "leveldown", "ld:
			//
			break;
		case "norandom", "nr", "no":
			//
			break;
		case "random", "rm", "ra":
			//
			break;
		case "sequence", "s", "se":
			//
			break;
		case "I":
			//
			break;
		case "J":
			//
			break;
		case "L":
			//
			break;
		case "O":
			//
			break;
		case "S":
			//
			break;
		case "Z":
			//
			break;
		case "T":
			//
			break;
		case "restart", "re":
			//
			break;
		default:
			cout << "Incorrect Command. Refer to the documentation." << endl;

	}
}

string CommandInterpreter::fullCommandName(string command) {

}

int CommandInterpreter::getMultipler(string command) {

}
