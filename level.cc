#include "level.h"

// using namespace std;

Level::Level(int levelNumber, const vector<double>& probs) : 
    levelNum{levelNumber}, probs{probs}, currIdx{0}, isRand{true}, seed{0} {}

void Level::readFile(const string& file) {
    ifstream infile(file);

    if (!infile.is_open()) {
        cerr << "Error: Cannot open sequence file " << file << endl;
    }

    char c;
    while (infile >> c) {
        c = toupper(c, std::locale());
        seq.push_back(c);
    }
    infile.close();

    if (seq.empty()) {
        cerr << "Warning: Sequence file " << file << " is empty." << endl;
    }
}

unique_ptr<Block> Level::blockFromShape(char shape) {
    unique_ptr<Block> block = nullptr;

    switch(shape) {
        case 'I':
            block = make_unique<IBlock>(levelNum);
            break;
        case 'J':
            block = make_unique<JBlock>(levelNum);
            break;
        case 'L':
            block = make_unique<LBlock>(levelNum);
            break;
        case 'O':
            block = make_unique<OBlock>(levelNum);
            break;
        case 'S':
            block = make_unique<SBlock>(levelNum);
            break;
        case 'T':
            block = make_unique<TBlock>(levelNum);
            break;
        case 'Z':
            block = make_unique<ZBlock>(levelNum);
            break;
        default:
            cerr << "Warning: Unknown block type '" << shape << "' in sequence." << endl;
            break;
    }
    return block;
}

unique_ptr<Block> Level::makeBlockFromFile() {
    if (seq.empty()) {
        return nullptr;
    }

    char blockType = seq[currIdx % seq.size()];
    currIdx++;
    return blockFromShape(blockType);
}


int Level::randomIndex() {
    vector<double> cumulative(probs.size(), 0.0);
    cumulative[0] = probs[0];
    for (size_t i = 1; i < probs.size(); ++i) {
        cumulative[i] = cumulative[i - 1] + probs[i];
    }

    mt19937 gen(seed);
    uniform_real_distribution<> dis(0.0, 1.0);
    double randomValue = dis(gen);

    auto it = lower_bound(cumulative.begin(), cumulative.end(), randomValue);
    return distance(cumulative.begin(), it);
}

unique_ptr<Block> Level::blockFromIndex(int idx) {
    unique_ptr<Block> block = nullptr;

    switch(idx) {
        case 0:
            block = make_unique<IBlock>(levelNum);
            break;
        case 1:
            block = make_unique<JBlock>(levelNum);
            break;
        case 2:
            block = make_unique<LBlock>(levelNum);
            break;
        case 3:
            block = make_unique<OBlock>(levelNum);
            break;
        case 4:
            block = make_unique<SBlock>(levelNum);
            break;
        case 5:
            block = make_unique<TBlock>(levelNum);
            break;
        case 6:
            block = make_unique<ZBlock>(levelNum);
            break;
        default:
            cerr << "Warning: Unknown block type '" << idx << "' in sequence." << endl;
            break;
    }
    return block;
}

unique_ptr<Block> Level::makeRandomBlock() {
    return blockFromIndex(randomIndex());
}

void Level::setSeed(int seed) {
    this->seed = seed;
}

void Level::setRand(bool isRand) {
    this->isRand = isRand;
}
