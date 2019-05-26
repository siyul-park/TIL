#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string getDeparture(int numOfA, int numOfB, int numOfC) {
    int n = numOfA + numOfB + numOfC;

    stringstream stringStream{};

    while (n > 0) {
        if (numOfA >= 1 && numOfB >= 2 && numOfC >= 1 && (n + 2) / 3 > numOfC) {
            stringStream << "BCBA";

            numOfA--;
            numOfB -= 2;
            numOfC--;
        } else if (numOfA >= 1 && numOfB >= 1 && numOfC >= 1) {
            stringStream << "CBA";

            numOfA--;
            numOfB--;
            numOfC--;
        } else if (numOfA >= 2 && numOfB == 0 && numOfC >= 1) {
            stringStream << "CAA";

            numOfA -= 2;
            numOfC--;
        } else if (numOfA >= 1 && numOfB >= 1 && numOfC == 0) {
            stringStream << "BA";

            numOfA--;
            numOfB--;
        } else if (numOfA >= 1 && numOfB == 0 && numOfC == 0) {
            stringStream << "AA";
            
            numOfA -= 2;
        } else if (n == 1) {
            if (numOfA == 1) {
                stringStream << "A";

                numOfA--;
            } else if (numOfB == 1) {
                stringStream << "B";

                numOfB--;
            } else if (numOfC == 1) { 
                stringStream << "C";

                numOfC--;
            } else {
                return string{"-1"};
            }
        } else if (n == 2) {
            if (numOfB == 1 && numOfC == 1) { 
                stringStream << "CB";

                numOfB--;
                numOfC--;
            } else if (numOfA == 1 && numOfC == 1) {
                stringStream << "CA";

                numOfA--;
                numOfC--;
            } else {
                return string{"-1"};
            }
        } else if (n == 3) {
            if (numOfB == 2 && numOfC == 1) {
                stringStream << "BCB";

                numOfB -= 2;
                numOfC--;
            } else {
                return string{"-1"};
            }
        } else {
            return string{"-1"};
        }

        n = numOfA + numOfB + numOfC;
    }

    return stringStream.str();
}

int main() {
    int numOfA{0}, numOfB{0}, numOfC{0};

    char ch;
    while ((ch = getchar()) != '\n') {
        if (ch == 'A')
            numOfA++;
        else if (ch == 'B')
            numOfB++;
        else if (ch == 'C')
            numOfC++;
    }

    cout << getDeparture(numOfA, numOfB, numOfC);

    return 0;
}