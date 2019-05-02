#include <iostream>

struct Radio {
    int num, den;

    void print() {
        std::cout << num << "/" << den;
    }
};

class InfinitelyLargeArray {
public:
    Radio operator[](std::size_t index) {
        Radio radio {1, 1};
    
        bool is_corner = true;
        for (int i = 0; i < index; ++i)
            is_corner = getNext(radio, is_corner);

        return radio;
    }
private:
    bool getNext(Radio& radio, bool is_corner) {
        if (is_corner) {
            if (radio.num == 1)
                radio.den++;
            else if (radio.den == 1)
                radio.num++;
            return false;
        } else if ((radio.num + radio.den) % 2 != 0) {
            radio.num++;
            radio.den--;
        } else if ((radio.num + radio.den) % 2 == 0) {
            radio.num--;
            radio.den++;
        }
        if (radio.num == 1 || radio.den == 1)
            return true;
        return false;
    }
};


int main() {
    int x;
    std::cin >> x;

    InfinitelyLargeArray array {};

    array[x-1].print();
    std::cout << std::endl;

    return 0;
}
