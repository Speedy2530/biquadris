#include <string>
using namespace std;

class CommandInterpreter {
	vector<string> commands {
		"left", "right", "down", "clockwise", "counterclockwise",
		"drop", "levelup", "leveldown", "norandom", "random",
		"sequence", "I", "J", "L", "O", "S", "Z", "T", "restart",
		"l", "r", "dn", "c", "cc", "dp" "lu", "ld", "nr", "rm" "s"
	}

public:
	void callMethod(string command, string file = "");
	string fullCommandName(string command);
	int getMultipler(string command);
}
