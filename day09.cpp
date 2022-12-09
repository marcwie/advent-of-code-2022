#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>

int sign (int x) {
    if (x > 0) return 1;
    else if (x < 0) return -1;
    else return 0;
}

class Rope {

private:
    int tailX, tailY, headX, headY;
    std::map<std::tuple<int, int>, bool> visited;

public:
    Rope () {
        tailX = 0;
        tailY = 0;
        headX = 0;
        headY = 0;
        visited[std::make_tuple(0, 0)] = true;
    }

    void updateTail () {

        if (tailY - headY == 2) {
            tailY--;
            tailX += sign(headX - tailX);
        }

        if (headY - tailY == 2) {
            tailY++;
            tailX += sign(headX - tailX);
        }

        if (tailX - headX == 2) {
            tailX--;
            tailY += sign(headY - tailY);
        }

        if (headX - tailX == 2) {
            tailX++;
            tailY += sign(headY - tailY);
        }
        
        visited[std::make_tuple(tailX, tailY)] = true;
    }

    void move (char direction) {
    
        if (direction == 'U') headY++;
        else if (direction == 'D') headY--;
        else if (direction == 'L') headX--;
        else if (direction == 'R') headX++;
        updateTail();
    }

    void setHead(int x, int y) {
        headX = x;
        headY = y;
        updateTail();
    }

    int totalVisited () {
        return visited.size();
    }

    int getTailX () {
        return tailX;
    }

    int getTailY () {
        return tailY;
    }
};

std::tuple<char, int> splitline(std::string line, char separator=' ') {
    std::istringstream stream(line);
    std::string entry;
    
    getline(stream, entry, separator);
    char direction = entry[0];

    getline(stream, entry, separator);
    int value = std::stoi(entry);

    return std::make_tuple (direction, value);
}

std::vector<std::tuple<char, int>> loadData(std::string inputFile) {

    std::vector<std::tuple<char, int>> data;
    std::string line;
    std::ifstream inputStream(inputFile);

    while (getline(inputStream, line)) data.push_back(splitline(line));

    return data;
}

int solve(std::string inputFile, int knots=1) {

    std::vector<std::tuple<char, int>> data = loadData(inputFile);

    char direction;
    int value;
    Rope ropes [knots];

    for (int i=0; i<data.size(); i++) {
        
        std::tie(direction, value) = data[i];
        
        for (int s=0; s<value; s++) {
        
            ropes[0].move(direction);
            for (int k=1; k<knots; k++) {
                ropes[k].setHead(ropes[k-1].getTailX(), ropes[k-1].getTailY());
            }
        }
    }
    
    return ropes[knots-1].totalVisited();
}

int main () {

    assert(solve("inputs/day09/test01.txt", 1) == 13);
    assert(solve("inputs/day09/test01.txt", 9) == 1);
    assert(solve("inputs/day09/test02.txt", 9) == 36);

    int solution;
    solution = solve("inputs/day09/input.txt", 1);
    std::cout << "Part 1 solution: " << solution << std::endl;
    assert(solution == 6376);

    solution = solve("inputs/day09/input.txt", 9);
    std::cout << "Part 2 solution: " << solution << std::endl;
    assert(solution == 2607);

    return 0;
}