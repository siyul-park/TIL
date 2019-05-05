#include <iostream>
#include <cstdio>

int getNumberOfFloors(int height, int weight, int numberOfGuests) {
    int numberOfFloors = numberOfGuests % height;

    if (numberOfFloors == 0)
        return height;
    return numberOfFloors;
}


int getRoomNumber(int height, int weight, int numberOfGuests) {
    return (numberOfGuests - 1) / height + 1;
}

int main() {
    int numberOfTestCase;
    std::cin >> numberOfTestCase;
    
    for (int i = 0; i < numberOfTestCase; ++i) {
        int H, W, N;
        std::cin >> H >> W >> N;

        int numberOfFloors = getNumberOfFloors(H, W, N);
        int roomNumber = getRoomNumber(H, W, N);

        std::printf("%d%02d\n", numberOfFloors, roomNumber);
    }
    
    return 0;
}