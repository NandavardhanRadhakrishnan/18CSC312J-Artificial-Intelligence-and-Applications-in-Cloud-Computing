#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Person {
public:
    string name;
    bool isMale;
    Person(string name, bool isMale) : name(name), isMale(isMale) {}
};

class Relationship {
public:
    Person* parent;
    Person* child;
    Relationship(Person* parent, Person* child) : parent(parent), child(child) {}
};

vector<Person*> findSiblings(Person* person, vector<Relationship>& relationships) {
    vector<Person*> siblings;
    for (const auto& rel : relationships) {
        if (rel.parent == person) {
            siblings.push_back(rel.child);
        }
        else if (rel.child == person) {
            siblings.push_back(rel.parent);
        }
    }
    return siblings;
}

int main() {
    Person John("John", true);
    Person Mary("Mary", false);
    Person Bob("Bob", true);
    Person Alice("Alice", false);
    vector<Relationship> relationships = {
        Relationship(&John, &Bob),
        Relationship(&Mary, &Bob),
        Relationship(&John, &Alice),
        Relationship(&Mary, &Alice)
    };
    cout << "Siblings of Bob:\n";
    vector<Person*> bobSiblings = findSiblings(&Bob, relationships);
    for (auto sibling : bobSiblings) {
        cout << sibling->name << endl;
    }
    return 0;
}