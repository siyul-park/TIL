#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Score {

    int& value(bool can_move_one) {
        if (can_move_one)
            return can_move_one_value;
        else
            return cant_move_one_value;
    }
 
    int can_move_one_value, cant_move_one_value;
};

int findMaxScore(const vector<int> &score, int position, bool can_move_one) {
    static vector<Score> cache(position + 1, Score{-1, -1});
    
    if (position < 0)
        return 0;
    
    if (cache[position].value(can_move_one) >= 0)
        return cache[position].value(can_move_one);
    
    if (position == 0)
        cache[position].value(can_move_one) = score[position];
    else {
        if (can_move_one)
            cache[position].value(can_move_one) = score[position] + max(findMaxScore(score, position - 1, false), findMaxScore(score, position - 2, true));
        else
            cache[position].value(can_move_one) = score[position] + findMaxScore(score, position - 2, true);
    }
      
    return cache[position].value(can_move_one);
}

int main() {
    int size_of_stairs;
    cin >> size_of_stairs;

    vector<int> score(size_of_stairs);
    for (auto i = 0; i < size_of_stairs; ++i)
        cin >> score[i];
    
    cout << findMaxScore(score, size_of_stairs - 1, true);

    return 0;
}