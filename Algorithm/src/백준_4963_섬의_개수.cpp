#include <iostream>
#include <vector>

using namespace std;

struct Index {
    int height{}, width{};
};

Index getSize(const vector<vector<int>> &map) {
    Index size{};
    size.height = map.size();
    if (size.height > 0)
        size.width = map[0].size();

    return size;
}

bool goLand(const vector<vector<int>> &map, vector<vector<bool>> &goen, const Index &size, const Index &index) {
    if (index.height < 0 || index.width < 0 || index.height >= size.height || index.width >= size.width)
        return false;
    
    if (goen[index.height][index.width])
        return false;

    goen[index.height][index.width] = true;

    if (map[index.height][index.width] == 0)
        return false;

    goLand(map, goen, size, Index{index.height - 1, index.width});
    goLand(map, goen, size, Index{index.height + 1, index.width});
    goLand(map, goen, size, Index{index.height, index.width - 1});
    goLand(map, goen, size, Index{index.height, index.width + 1});
    goLand(map, goen, size, Index{index.height - 1, index.width - 1});
    goLand(map, goen, size, Index{index.height + 1, index.width - 1});
    goLand(map, goen, size, Index{index.height - 1, index.width + 1});
    goLand(map, goen, size, Index{index.height + 1, index.width + 1});

    return true;
}


int getNumberOfLand(const vector<vector<int>> &map) {
    Index size{getSize(map)};
    
    vector<vector<bool>> goen(size.height, vector<bool>(size.width, false));

    int num_of_land{0};
    for (auto i = 0; i < size.height; ++i)
        for (auto j = 0; j < size.width; ++j)
            if (goLand(map, goen, size, Index{i, j}))
                num_of_land++;

    return num_of_land;
}

int main() {
    
    int w, h;
    while (true) {
        cin >> w >> h;

        vector<vector<int>> map(h, vector<int>(w, 0));
        for (auto i = 0; i < h; ++i)
            for (auto j = 0; j < w; ++j)
                cin >> map[i][j];
        
        if (w == 0 && h == 0)
            break;

        cout << getNumberOfLand(map) << "\n";
    }

    return 0;
}