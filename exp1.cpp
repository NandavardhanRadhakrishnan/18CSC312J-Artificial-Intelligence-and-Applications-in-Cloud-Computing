// hanoi

#include <iostream>
using namespace std;

void toh(int n, char s, char a, char d){

    if(n==1){
        cout << "move disk from " << s << " to " << d << endl;
        return;
    }

    toh(n-1,s,d,a);
    cout << "move disk from " << s << " to " << d << endl;
    toh(n-1,a,s,d);
}

int main(){
    int n = 3;

    toh(n,'a','b','c');
}