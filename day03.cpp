#include <fstream>
#include <iostream>
#include <assert.h>

char findDuplicateItem(std::string backpack) {

    int n = backpack.length();
    char item;

    for (int i=0; i<n/2;i++) {
        for (int j=n/2; j<n; j++) {
            if (backpack[i] == backpack[j]) {
                item = backpack[i];
                goto end; // The only case where goto seems acceptable is to break out of a nested for loop
            }
        }
    }

    end:
    return item;
}

char findCommonAcrossBackbacks(std::string backpacks [3]) {

    char item;

    for (int i=0; i<backpacks[0].length(); i++) {
        for (int j=0; j<backpacks[1].length(); j++) {
            for (int k=0; k<backpacks[2].length(); k++) {
                if (backpacks[0][i] == backpacks[1][j] && backpacks[1][j] == backpacks[2][k]) {
                    item = backpacks[0][i];
                    goto end; // The only case where goto seems acceptable is to break out of a nested for loop
                }
            }
        }
    }

    end:
    return item;
}

int itemPriority(char item) {
    // Concert letter representing the item to a numerical priority
    // a - z -> 1 - 26
    // A - Z -> 27 - 52
    
    int priority = (int) item;
    priority -= 96;
    if (priority < 1) priority += 58;
    
    return priority;
}

int part1(std::string inputFile) {
    
    std::string line;
    std::ifstream Input(inputFile);
    char item;
    int score = 0;

    while (getline(Input, line)) {
        item = findDuplicateItem(line);
        score += itemPriority(item);
    }

    return score;
} 

int part2(std::string inputFile) {
    
    std::string line;
    std::ifstream Input(inputFile);
    char item;
    
    int score = 0;
    int counter = 0;
    std::string backpacks [3];

    while (getline(Input, line)) {
        backpacks[counter] = line;
        counter++;
        if (counter == 3) {
            counter = 0;
            item = findCommonAcrossBackbacks(backpacks);
            score += itemPriority(item);
        }
    }

    return score;
} 

int main () {
    
    assert(part1("inputs/day03/test.txt") == 157);
    assert(part2("inputs/day03/test.txt") == 70);

    int solution;
    
    solution = part1("inputs/day03/input.txt");
    std::cout << "Part 1 solution: " << solution << std::endl;
    assert(solution == 7428);

    solution = part2("inputs/day03/input.txt");
    std::cout << "Part 2 solution: " << solution << std::endl;
    assert(solution == 2650);

    return 0;
}