#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int count {};
    string input {};
    getline(cin, input);

    if (!input.empty()) {
        stringstream sio(input);
        
        string token;
        while (sio >> token)
            ++count;
    }

    cout << count;

    return 0;
}