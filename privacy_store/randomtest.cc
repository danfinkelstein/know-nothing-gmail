#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

int main() {
    srandom(1);                 // for reproducibility
    cout << random() << endl;
    cout << random() << endl;
    srandom(1);                 // for reproducibility
    cout << random() << endl;
    cout << random() << endl;
    string s = string("test");
    cout << sizeof(s) * 8 << endl;
    return 0;
}
