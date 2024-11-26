#include "level0.h"
#include "block.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

Level0::Level0(const string& file)
    : Level(0), seqFile(file), currentIndex(0) {
    readFile(seqFile);
}

void Level0::readFile(const string& file) {
    ifstream infile(file);

    if (!infile.is_open()) {
        cerr << "Error: Cannot open sequence file " << file << endl;
    }

    char c;
    while (infile >> c) {
        c = toupper(c);
        seq.push_back(c);
    }
    infile.close();

    if (seq.empty()) {
        cerr << "Warning: Sequence file " << file << " is empty." << endl;
    }
}

unique_ptr<Block> Level0::makeNextBlock() {
    if (seq.empty()) {
        return nullptr;
    }

    char blockType = seq[currIdx];
    unique_ptr<Block> block = nullptr;

    switch(blockType) {
        case 'I':
            block = make_unique<IBlock>();
            break;
        case 'J':
            block = make_unique<JBlock>();
            break;
        case 'L':
            block = make_unique<LBlock>();
            break;
        case 'O':
            block = make_unique<OBlock>();
            break;
        case 'S':
            block = make_unique<SBlock>();
            break;
        case 'T':
            block = make_unique<TBlock>();
            break;
        case 'Z':
            block = make_unique<ZBlock>();
            break;
        default:
            cerr << "Warning: Unknown block type '" << blockType << "' in sequence." << endl;
            break;
    }

    // next block in seq
    currentIndex = (currentIndex + 1) % seq.size();

    return block;
}

int Level0::getLevel() const {
    return levelNumber;
}

void Level0::setLevel() { 
    // nothing
}

void Level0::onBlockPlaced(bool clearedRows) {
    // nothing
}

void Level0::afterMoveOrRotate(int playerID) {
    // nothing
}

Level0::~Level0() {
    // Smart pointers handle memory
}
