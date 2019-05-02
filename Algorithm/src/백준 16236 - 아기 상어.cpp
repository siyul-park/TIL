#include <iostream>
#include <vector>
#include <queue>

template <typename T>
using vector2x = std::vector<std::vector<T>>;

struct Position {
    int x, y;
};

struct Item {
    Position position;
    int time;
};

struct BabyShark {
    BabyShark() : size{2}, eatNum{0}, go{{-1, 0}, {0, -1}, {1, 0}, {0, 1}} {}

    bool canEat(int fish) {
        return fish < size && fish != 0;
    }

    void eat(int &fish) {
        fish = 0, eatNum++;

        if (eatNum == size) {
            size++;
            eatNum = 0;
        }
    }

    bool canMove(int fish) {
        return fish <= size;
    }

    int size;
    int eatNum;

    Position go[4];
};


struct Map {
    Map(int n) : map(n, std::vector<int>(n, 0)), time{0}, n{n} {}

    int TimeToCallMother() {
        BabyShark babyShark{};
        std::queue<Item> willGo;
        willGo.push(Item{getBabySharkPosition(), 0});

        while (true) {
            std::vector<Item> fish{};

            vector2x<bool> isVisted(n, std::vector<bool>(n, false)); 
            while (!willGo.empty()) {
                auto item = willGo.front();
                isVisted[item.position.x][item.position.y] = true;

                willGo.pop();

                for (int i = 0; i < 4; ++i) {
                    int dX = item.position.x + babyShark.go[i].x;
                    int dY = item.position.y + babyShark.go[i].y;
                    
                    if (dX < n && dY < n && dX >=0 && dY >= 0 && babyShark.canMove(map[dX][dY]) && !isVisted[dX][dY]) {
                        isVisted[dX][dY] = true;
                        willGo.push(Item{Position{dX, dY}, item.time + 1});
                        if (babyShark.canEat(map[dX][dY]))
                            fish.push_back(Item{Position{dX, dY}, item.time + 1});
                    }
                }
            }
            isVisted.clear();
            
            if (fish.size() > 0) {
                auto best = findBestFish(fish);
                willGo.push(best);

                babyShark.eat(map[best.position.x][best.position.y]);
                time = best.time;
            } else
                break;
        }

        return time;
    }

    Position getBabySharkPosition() {
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                if (map[i][j] == 9) {
                    map[i][j] = 0;
                    return Position{i, j};
                }
            }
        }
        return Position{-1, -1};
    }

    Item findBestFish(std::vector<Item> &fish) {
        Item best = fish[0];
        for (int i = 1; i < fish.size(); i++) {
            if (best.time > fish[i].time)
                best = fish[i];
            else if (best.time == fish[i].time) {
                if (best.position.x > fish[i].position.x)
                    best = fish[i];
                else if (best.position.x == fish[i].position.x)
                    if (best.position.y > fish[i].position.y)
                        best = fish[i];
            }
        }
        
        return best;
    }

    vector2x<int> map;
    int time;
    int n;
};

int main() {
    int n;
    std::cin >> n;

    Map map{n};
    for (int i = 0; i < map.map.size(); i++) {
        for (int j = 0; j < map.map[i].size(); j++) {
            std::cin >> map.map[i][j];
        }
    }

    std::cout << map.TimeToCallMother();

    return 0;
}