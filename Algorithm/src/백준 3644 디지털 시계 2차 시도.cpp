#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

const unsigned DIGIT_TO_BITS[10] = {126, 48, 109, 121, 51, 91, 95, 112, 127, 123};

unsigned stringToBits(const string &display_string) {
    unsigned b = 0;

    for (unsigned i = 0; i <= 4; ++i) {
        if (i != 2) {
            b <<= 7;
            b |= DIGIT_TO_BITS[display_string[i] - '0'];
        }
    }

    return b;
}

string timeToString(const unsigned &time) {
    const unsigned hh = time / 60;
    const unsigned mm = time % 60;

    ostringstream oss;

    oss << setfill('0') << setw(2) << hh << ':' <<  setw(2) << mm;

    return oss.str();
}

unsigned timeToBits(const unsigned & time) {
    const unsigned hh = time / 60;
    const unsigned mm = time % 60;

    return (DIGIT_TO_BITS[hh / 10] << 21) | (DIGIT_TO_BITS[hh % 10] << 14) |
           (DIGIT_TO_BITS[mm / 10] <<  7) | (DIGIT_TO_BITS[mm % 10]      ) ;
};

int main() {
    for (unsigned n; cin >> n;) {
        cout << n << " ";
        vector<unsigned> display_bits;

        for (string s; display_bits.size() < n;) {
            cin >> s;
            display_bits.push_back(stringToBits(s));
        }

        unsigned segment_is_active = 0;

        for (unsigned i = 0; i < n; ++i) {
            segment_is_active |= display_bits[i];
        }

        bool solved = false;

        for (unsigned starttime = 0; starttime < 1440; ++starttime) {
            unsigned segment_does_not_equal_nominal = 0;

            for (unsigned i = 0; i < n; ++i) {
                const unsigned predicted = timeToBits((starttime + i) % 1440);
                const unsigned observed  = display_bits[i];

                segment_does_not_equal_nominal |= (predicted ^ observed);
            }

            if ((segment_is_active & segment_does_not_equal_nominal) == 0) {
                if (solved)
                    cout << " ";
                cout << timeToString(starttime);
                solved = true;
            }

        }

        if (!solved)
            cout << "none";

        cout << endl;

    }

    return 0;
}
