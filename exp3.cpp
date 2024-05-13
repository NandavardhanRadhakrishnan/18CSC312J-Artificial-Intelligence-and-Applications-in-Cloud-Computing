// send more money

#include <iostream>
#include <vector>
#include <tuple>
#include <set>
using namespace std;

vector<tuple<int, int, int>> solutions() {
    vector<tuple<int, int, int>> all_solutions;
    for (int s = 9; s >= 0; --s) {
        for (int e = 9; e >= 0; --e) {
            for (int n = 9; n >= 0; --n) {
                for (int d = 9; d >= 0; --d) {
                    for (int m = 9; m > 0; --m) {
                        for (int o = 9; o >= 0; --o) {
                            for (int r = 9; r >= 0; --r) {
                                for (int y = 9; y >= 0; --y) {
                                    set<int> digits {s, e, n, d, m, o, r, y};
                                    if (digits.size() == 8) {
                                        int send = 1000 * s + 100 * e + 10 * n + d;
                                        int more = 1000 * m + 100 * o + 10 * r + e;
                                        int money = 10000 * m + 1000 * o + 100 * n + 10 * e + y;

                                        if (send + more == money) {
                                            all_solutions.push_back(make_tuple(send, more, money));
                                            return all_solutions;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return all_solutions;
}

int main() {
    auto result = solutions();
    for (auto &tuple : result) {
        cout << "SEND: " << get<0>(tuple) << ", MORE: " << get<1>(tuple) << ", MONEY: " << get<2>(tuple) << endl;
    }
    return 0;
}
