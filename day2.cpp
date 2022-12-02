#include <fstream>
#include <iostream>
#include <assert.h>

char transformPlayerB(char playerB) {
    
    if (playerB == 'X') return 'A';
    else if (playerB == 'Y') return 'B';
    else return 'C';

}

char findStragetyPlayerB(char playerA, char outcome) {

    char playerB;
    if (outcome == 'X') {
        if (playerA == 'A') playerB = 'C';
        else if (playerA == 'B') playerB = 'A';
        else playerB = 'B';
    } 
    else if (outcome == 'Y') playerB = playerA;
    else {
        if (playerA == 'A') playerB = 'B';
        else if (playerA == 'B') playerB = 'C';
        else playerB = 'A';
    }

    return playerB;
}

int play(char playerA, char playerB) {

    int score = 0;
    
    if (playerB == 'A') score = 1;
    else if (playerB == 'B') score = 2;
    else score = 3;

    if (playerA == playerB) score += 3;
    else if (playerA == 'A' && playerB == 'B') score += 6;
    else if (playerA == 'B' && playerB == 'C') score += 6;
    else if (playerA == 'C' && playerB == 'A') score += 6;

    return score;

}

int solve(std::string inputFile, int part) {

    std::string line;
    std::ifstream Input(inputFile);
    char playerA;
    char playerB;
    int totalScore = 0;
    while (getline (Input, line)) {
        playerA = line[0];
        playerB = line[2];
        if (part == 1) playerB = transformPlayerB(playerB);
        else playerB = findStragetyPlayerB(playerA, playerB);
        totalScore += play(playerA, playerB);
    }

    Input.close();

    return totalScore;
}

int main () {

    assert(solve("inputs/day2/test.txt", 1) == 15);
    assert(solve("inputs/day2/test.txt", 2) == 12);

    int solution;
    solution = solve("inputs/day2/input.txt", 1);
    std::cout << "Part 1 solution: " << solution << std::endl;
    assert(solution == 14297);

    solution = solve("inputs/day2/input.txt", 2);
    std::cout << "Part 2 solution: " << solution << std::endl;
    assert(solution == 10498);

    return 0;
}