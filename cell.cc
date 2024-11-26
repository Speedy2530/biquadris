#include "cell.h"

#include <string>
#include <iostream>

using namespace std;

Cell::Cell(int r = 0, int c = 0, char s = ' ') : row{r}, col{c}, shape{s}, locked{false}, blind{false} {}

int Cell::getRow() const {
	return row;
}

int Cell::getCol() const {
	return col;
}

char Cell::getShape() const {
	return shape;
}

bool Cell::isFilled() const {
	return shape != ' ';
}

bool Cell::isLocked() const {
	return locked;
}

bool Cell::isBlind() const {
	return blind;
}

void Cell::fill(char s) {
	shape = s;
}

void Cell::setLocked(bool lock) {
	locked = lock;
}

void Cell::setBlind(bool b) {
	blind = b;
}

void Cell::display() const {
	if (!blind) {
		cout << shape;
	} else {
		cout << '?';
	}
}

