#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;

    int count = 0;
    char pre, ch;
    cin >> pre;
    for (int i = 1; i < N; ++i) {
        cin >> ch;
        if (pre == 'E' && ch == 'W')
            count++;
        pre = ch;
    }

    cout << count;
    
    return 0;
}