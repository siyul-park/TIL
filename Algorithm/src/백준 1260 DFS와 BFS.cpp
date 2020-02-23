#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using Grape = std::vector<std::vector<int>>;

std::vector<int> BFS(const Grape& grape, int start_point);
std::vector<int> DFS(const Grape& grape, int start_point);

bool isVisited(const std::vector<int>& visited, int new_place);
void printVector(const std::vector<int>& vec);

int main() {
    int N, M, V;
    std::cin >> N >> M >> V;

    Grape grape (N);
    int parent, child;
    for (auto i = 0; i < M; ++i) {
        std::cin >> parent >> child;
        --parent, --child;
        
        grape[parent].push_back(child);
        grape[child].push_back(parent);
    }

    for (auto i = 0; i < N; ++i)
        std::sort(grape[i].begin(), grape[i].end());

    printVector(DFS(grape, V-1));
    std::cout << std::endl;
    printVector(BFS(grape, V-1));

    return 0;
}

void BFS(const Grape& grape, int start_point, std::vector<int>& res) {
    std::queue<int> visit;
    visit.push(start_point);

    while (!visit.empty()) {
        start_point = visit.front();
        visit.pop();

        for (auto i = 0; i < grape[start_point].size(); ++i) {
            if (!isVisited(res, grape[start_point][i])) {
                res.push_back(grape[start_point][i]+1);
                visit.push(grape[start_point][i]);
            }
        }
    }
}
std::vector<int> BFS(const Grape& grape, int start_point) {
    std::vector<int> res {};
    
    res.push_back(start_point+1);
    BFS(grape, start_point, res);
    return res;
}
void DFS(const Grape& grape, int start_point, std::vector<int>& res) {
    res.push_back(start_point+1);

    for (auto i = 0; i < grape[start_point].size(); ++i)
        if (!isVisited(res, grape[start_point][i]))
            DFS(grape, grape[start_point][i], res);
}

std::vector<int> DFS(const Grape& grape, int start_point) {
    std::vector<int> res {};
    
    DFS(grape, start_point, res);
    return res;
}

bool isVisited(const std::vector<int>& visited, int new_place) {
    for (auto node : visited)
        if (node == new_place+1)
            return true;
    return false;
}
void printVector(const std::vector<int>& vec) {
    for (auto i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
}