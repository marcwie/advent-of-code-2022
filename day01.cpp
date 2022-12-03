#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <assert.h>
#include <algorithm>

std::map<int, int> computeTotalCalories(std::string inputFile) {
    
    std::string line;
    std::ifstream Input(inputFile);

    int elfCounter = 0;
    int calories = 0;
    std::map<int, int> elves;

    while (getline (Input, line)) {
        if (line == "") {
            elves[elfCounter] = calories;
            calories = 0;
            elfCounter++;
            continue;
        }
        calories += std::stoi(line);
    }

    // Add info for the last elf, since that info is not followed by an empty line
    elves[elfCounter] = calories;

    return elves;

}

int findElfWithMostCalories(std::map<int, int> elves){

    int maxCalories = 0;
    int topElf = 0;
    
    for (int i=0; i<elves.size(); i++){
        if (elves[i] > maxCalories) {
            maxCalories = elves[i];
            topElf = i;
        }
    }

    return topElf + 1;

}

int findTotalCaloriesOfTopThreeElves(std::map<int, int> elves) {

    int topCalories [3] = {0, 0, 0};
    int totalCalories = 0;

    for (int i=0; i<elves.size(); i++) {
        std::sort(std::begin(topCalories), std::end(topCalories));
        if (elves[i] > topCalories[0]) topCalories[0] = elves[i];
    }

    for (int i=0; i<3; i++){
        totalCalories += topCalories[i];
    }

    return totalCalories;

}

int main () {

    std::map<int, int> elves;
    int solution;

    elves = computeTotalCalories("inputs/day01/test.txt");
    assert(findElfWithMostCalories(elves) == 4);
    assert(findTotalCaloriesOfTopThreeElves(elves) == 45000);

    elves = computeTotalCalories("inputs/day01/input.txt");
    solution = findElfWithMostCalories(elves);
    std::cout << "Part 1 solution: " << elves[solution - 1] << std::endl;
    assert(elves[solution - 1] == 72240);

    solution = findTotalCaloriesOfTopThreeElves(elves);
    std::cout << "Part 2 solution: " << solution << std::endl;
    assert(solution == 210957);

    return 0;
};