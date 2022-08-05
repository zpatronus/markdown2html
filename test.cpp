#include <bits/stdc++.h>
using namespace std;
int main() {
    string s = "123456";
    cout << s.substr(3, 10);
    string& b = s;
    string& c = b;
    cout << c.substr(3, 10);
    cout << "\"";
    return 0;
}
