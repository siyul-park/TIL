#include "iostream"
#include "vector"
#include "algorithm"

struct Building {
    int time;
    std::vector<int> preBuilded;
    bool isCal;
};

std::vector<Building> analyseInputData() {
    int buildingNum, buildedRuleNum;
    std::cin >> buildingNum >> buildedRuleNum;

    std::vector<Building> buildings(buildingNum, Building{0, std::vector<int>(), false});

    for (int i = 0; i < buildingNum; ++i) {
        std::cin >> buildings[i].time;
    }

    for (int i = 0; i < buildedRuleNum; ++i) {
        int building, preBuilded;
        std::cin >> preBuilded >> building;
        buildings[building - 1].preBuilded.push_back(preBuilded - 1);
    }

    return buildings;
}

int findMinTimeForBuild(std::vector<Building> &buildings, int willBuildBuilding) { 
    if (buildings[willBuildBuilding].isCal)
        return buildings[willBuildBuilding].time;
    
    buildings[willBuildBuilding].isCal = true;

    if (buildings[willBuildBuilding].preBuilded.empty())
        return buildings[willBuildBuilding].time;

    int max = 0;
    int preBuild;
    int size = buildings[willBuildBuilding].preBuilded.size();
    for (int i = 0; i < size; ++i) {
        preBuild = buildings[willBuildBuilding].preBuilded[i];
        max = std::max(max, findMinTimeForBuild(buildings, preBuild));
    }

    buildings[willBuildBuilding].time += max;
    return buildings[willBuildBuilding].time;
}

int main() {
    int caseNum;
    std::cin >> caseNum;

    for  (int i = 0; i < caseNum; ++i) {
        int willBuildBuilding;

        std::vector<Building> buildings{std::move(analyseInputData())};
        std::cin >> willBuildBuilding;

        int time = findMinTimeForBuild(buildings, willBuildBuilding - 1);

        std::cout << time << '\n';
    }

    return 0;
}