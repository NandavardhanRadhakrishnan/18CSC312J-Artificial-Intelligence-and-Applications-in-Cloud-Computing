#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class BlockWorld {
private:
    vector<string> blocks; // Vector to store block names
    vector<int> onTopOf;   // Vector to store index of block on top of another (-1 for table)

public:
    BlockWorld() {}

    int getBlockIndex(const string& name) const {
        auto it = find(blocks.begin(), blocks.end(), name);
        if (it != blocks.end())
            return distance(blocks.begin(), it);
        return -1;
    }

    bool addBlock(const string& name) {
        if (getBlockIndex(name) == -1) {
            blocks.push_back(name);
            onTopOf.push_back(-1); // Initialize block as being on the table
            return true;
        }
        return false; // Block with same name already exists
    }

    void placeOn(const string& block, const string& onTopOf) {
        int idxBlock = getBlockIndex(block);
        int idxOnTopOf = (onTopOf == "table") ? -1 : getBlockIndex(onTopOf);
        if (idxBlock != -1 && idxOnTopOf != -1) {
            this->onTopOf[idxBlock] = idxOnTopOf;
        }
    }

    void removeBlock(const string& block) {
        int idxBlock = getBlockIndex(block);
        if (idxBlock != -1) {
            onTopOf.erase(onTopOf.begin() + idxBlock); // Remove block's position from onTopOf vector
            blocks.erase(blocks.begin() + idxBlock); // Remove the block from the blocks vector
        }
    }

    void printWorld() const {
        for (int i = 0; i < blocks.size(); ++i) {
            cout << "Block " << blocks[i];
            if (onTopOf[i] != -1) {
                cout << " is on top of " << blocks[onTopOf[i]];
            } else {
                cout << " is on the table";
            }
            cout << endl;
        }
    }
};

int main() {
    BlockWorld world;

    world.addBlock("A");
    world.addBlock("B");
    world.addBlock("C");

    world.placeOn("B", "A");
    world.placeOn("C", "B");

    cout << "Initial State:" << endl;
    world.printWorld();
    cout << endl;

    world.removeBlock("B");

    cout << "State after removing Block B:" << endl;
    world.printWorld();

    return 0;
}
