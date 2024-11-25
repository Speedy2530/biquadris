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
		case "left": case "l": case "lef":
			//
			break;
		case "right": case "r": case "ri":
			//
			break;
		case "down": case "dn": case "do":
			//
			break;
		case "clockwise": case "c": case "cl":
			//
			break;
		case "counterclockwise": case "cc": case "co":
			//
			break;
		case "drop": case "dp": case "dr":
			//
			break;
		case "levelup": case "lu":
			//
			break;
		case "leveldown": case "ld":
			//
			break;
		case "norandom": case "nr": case "no":
			//
			break;
		case "random": case "rm": case "ra":
			//
			break;
		case "sequence": case "s": case "se":
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
		case "restart": case "re":
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
