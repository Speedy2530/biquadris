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
		case "left", "l":
			//
			break;
		case "right", "r:
			//
			break;
		case "down", "dn":
			//
			break;
		case "clockwise", "c":
			//
			break;
		case "counterclockwise", "cc":
			//
			break;
		case "drop", "dp:
			//
			break;
		case "levelup", "lu":
			//
			break;
		case "leveldown", "ld:
			//
			break;
		case "norandom", "nr":
			//
			break;
		case "random", "rm":
			//
			break;
		case "sequence", "s":
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
		case "restart":
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
