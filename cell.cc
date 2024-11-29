#include "cell.h"

#include <string>
#include <iostream>

using namespace std;

Cell::Cell(int r, int c, char s, int id)
    : row{r}, col{c}, shape{s}, locked{false}, blind{false}, blockID{id} {}

int Cell::getRow() const {
	return row;
}

int Cell::getCol() const {
	return col;
}

char Cell::getShape() const {
	if (blind) {
		return '?';
	}
	return shape;
}

int Cell::getBlockID() const {
	return blockID;
}

bool Cell::isFilled() const {
	return shape != ' ';
}

bool Cell::isBlind() const {
	return blind;
}

void Cell::fill(char s, int id) {
	shape = s;
	blockID = id;
}

void Cell::setBlind(bool b) {
	blind = b;
}

void Cell::clear() {
	shape = ' ';

}

void Cell::display() const {
	if (!blind) {
		cout << shape;
	} else {
		cout << '?';
	}
}

