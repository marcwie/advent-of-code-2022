#include <fstream>
#include <iostream>
#include <assert.h>

bool oneFullyCountainsOther(int x0, int x1, int y0, int y1) {

    bool result = false;
    if (x0 >= y0 && x1 <= y1) result = true;
    else if (y0 >= x0 && y1 <= x1) result = true;

    return result;
}

bool overlapsAtAll(int x0, int x1, int y0, int y1) {

    bool result = true;
    if (x1 < y0 || y1 < x0) result = false;

    return result;    
}

int solve(std::string inputFile, int part) {

    std::string inputLine, section;
    std::ifstream Input(inputFile);
    int data [4], i, counter = 0;
    
    while (getline(Input, inputLine)) {

        i = 0; // i is counting from 0 to 3
        section = ""; // holds the current sectionID as string

        for (int j=0; j<inputLine.length(); j++) {

            // If the current character is either of the two separators, we reset
            if (inputLine[j] == '-' || inputLine[j] == ',') {
                section = "";
                i++;
            }
            // Otherwise, we append the character to the string representing the section and push that as in integer to the data array
            else {
                section += inputLine[j];
                data[i] = std::stoi(section);
            }
        }

        if (part == 1) counter += oneFullyCountainsOther(data[0], data[1], data[2], data[3]);
        else counter += overlapsAtAll(data[0], data[1], data[2], data[3]);
    }   

    return counter;
}

int main () {

    assert(oneFullyCountainsOther(2, 8, 3, 7) == true);
    assert(oneFullyCountainsOther(2, 8, 3, 9) == false);
    assert(solve("inputs/day04/test.txt", 1) == 2);
    assert(solve("inputs/day04/test.txt", 2) == 4);

    int solution;
    solution = solve("inputs/day04/input.txt", 1);
    std::cout << "Part 1 solution: " << solution << std::endl;
    assert(solution == 595);

    solution = solve("inputs/day04/input.txt", 2);
    std::cout << "Part 2 solution: " << solution << std::endl;
    assert(solution == 952);

    return 0;
}