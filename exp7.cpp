// unification and resolution (idts it is working)

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Type representing a variable or constant in logic
using Term = string;

// Type representing a predicate with its arguments
struct Predicate {
    string name;
    vector<Term> arguments;

    // Define equality operator for Predicate
    bool operator==(const Predicate& other) const {
        return name == other.name && equal(arguments.begin(), arguments.end(), other.arguments.begin());
    }
};

// Type representing a clause in first-order logic
struct Clause {
    vector<Predicate> predicates;
};

// Type representing a substitution map
using Substitution = unordered_map<Term, Term>;

// Function to unify two terms
bool unify(Term t1, Term t2, Substitution& substitution) {
    if (t1 == t2) {
        return true; // Same term, unification successful
    }
    if (substitution.count(t1)) {
        return unify(substitution[t1], t2, substitution); // Substitute and unify
    }
    if (substitution.count(t2)) {
        return unify(t1, substitution[t2], substitution); // Substitute and unify
    }
    substitution[t1] = t2; // Assign substitution
    return true;
}

// Function to apply substitution to a term
Term applySubstitution(Term term, const Substitution& substitution) {
    if (substitution.count(term)) {
        return applySubstitution(substitution.at(term), substitution);
    }
    return term;
}

// Function to apply substitution to a predicate
Predicate applySubstitution(const Predicate& predicate, const Substitution& substitution) {
    Predicate result = predicate;
    for (auto& arg : result.arguments) {
        arg = applySubstitution(arg, substitution);	
    }
    return result;
}

// Function to resolve two clauses
vector<Clause> resolve(const Clause& clause1, const Clause& clause2) {
    vector<Clause> resolvents;
    for (const auto& pred1 : clause1.predicates) {
        for (const auto& pred2 : clause2.predicates) {
            if (pred1.name == pred2.name && pred1.arguments.size() == pred2.arguments.size()) {
                Substitution substitution;
                bool unifiable = true;
                for (size_t i = 0; i < pred1.arguments.size(); ++i) {
                    if (!unify(pred1.arguments[i], pred2.arguments[i], substitution)) {
                        unifiable = false;
                        break;
                    }
                }
                if (unifiable) {
                    Clause resolvent;
                    for (const auto& pred : clause1.predicates) {
                        if (pred == pred1) {
                            continue;
                        }
                        resolvent.predicates.push_back(applySubstitution(pred, substitution));
                    }
                    for (const auto& pred : clause2.predicates) {
                        if (pred == pred2) {
                            continue;
                        }
                        resolvent.predicates.push_back(applySubstitution(pred, substitution));
                    }
                    resolvents.push_back(resolvent);
                }
            }
        }
    }
    return resolvents;
}

// Function to print a clause
void printClause(const Clause& clause) {
    for (const auto& pred : clause.predicates) {
        cout << pred.name << "(";
        for (size_t i = 0; i < pred.arguments.size(); ++i) {
            cout << pred.arguments[i];
            if (i < pred.arguments.size() - 1) {
                cout << ", ";
            }
        }
        cout << ")";
        if (&pred != &clause.predicates.back()) {
            cout << " || ";
        }
    }
    cout << endl;
}

int main() {
    // Example input clauses
    Clause clause1 = { { {"is_mortal", {"X"}} } };
    Clause clause2 = { { {"is_human", {"Socrates"}} } };

    // Resolve the clauses
    auto resolvents = resolve(clause1, clause2);

    // Print the input clauses
    cout << "Input Clauses:" << endl;
    cout << "Clause 1: ";
    printClause(clause1);
    cout << "Clause 2: ";
    printClause(clause2);
    cout << endl;

    // Print the resolvents
    cout << "Resolvents:" << endl;
    for (const auto& resolvent : resolvents) {
        printClause(resolvent);
    }

    return 0;
}