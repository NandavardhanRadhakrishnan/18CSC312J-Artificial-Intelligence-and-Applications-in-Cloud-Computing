#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Block {
public:
    string name;
    Block* onTopOf;
    Block(const string& n) : name(n), onTopOf(nullptr) {}

    const string& getName() const {
        return name;
    }

    Block* getOnTopOf() const {
        return onTopOf;
    }

    void stackOn(Block* block) {
        onTopOf = block;
    }

    void unstack() {
        onTopOf = nullptr;
    }
};

class BlockWorld {
private:
    unordered_map<string, Block*> blocks;

public:
    Block* getBlock(const string& name) const {
        auto it = blocks.find(name);
        if (it != blocks.end())
            return it->second;
        return nullptr;
    }

    bool addBlock(const string& name) {
        if (blocks.find(name) == blocks.end()) {
            blocks[name] = new Block(name);
            return true;
        }
        return false; // Block with same name already exists
    }

    void placeOn(Block* block, Block* onTopOf) {
        block->stackOn(onTopOf);
    }

    void removeBlock(Block* block) {
        if (block) {
            // Remove block and its references from the world
            for (auto& entry : blocks) {
                if (entry.second->getOnTopOf() == block)
                    entry.second->unstack();
            }
            delete block;
        }
    }

    void printWorld() const {
        for (const auto& entry : blocks) {
            cout << "Block " << entry.first;
            if (entry.second->getOnTopOf() != nullptr) {
                cout << " is on top of " << entry.second->getOnTopOf()->getName();
            } else {
                cout << " is on the table";
            }
            cout << endl;
        }
    }

    ~BlockWorld() {
        for (auto& entry : blocks)
            delete entry.second;
        blocks.clear();
    }
};

int main() {
    BlockWorld world;

    world.addBlock("A");
    world.addBlock("B");
    world.addBlock("C");

    Block* blockA = world.getBlock("A");
    Block* blockB = world.getBlock("B");
    Block* blockC = world.getBlock("C");

    world.placeOn(blockB, blockA);
    world.placeOn(blockC, blockB);

    cout << "Initial State:" << endl;
    world.printWorld();
    cout << endl;

    world.removeBlock(blockB);

    cout << "State after removing Block B:" << endl;
    world.printWorld();

    return 0;
}