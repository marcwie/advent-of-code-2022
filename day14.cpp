#include <map>
#include <tuple>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <array>

class Cave {

private:

    std::vector<std::string> data_;
    std::string inputFile_;
    std::map<std::array<int, 2>, bool> caveMap_;
    std::vector<std::array<int, 2>> polygon_;
    std::string delimiter_ = " -> ";
    int abyss_ = 0;
    int nSands_ = 0;
    int caveHeight_ = 2;
    int sandEntry_ = 500;
    
    void caveMap() {

        caveMap_.clear();
        std::vector<std::array<int, 2>> corners; 
        int x0, x1, y0, y1;

        for (int i=0; i<data_.size(); i++) {
            setCurrentPolygon(data_[i]);
            
            for (int j=1; j<polygon_.size(); j++) {
                x0 = polygon_[j-1][0]; 
                x1 = polygon_[j][0];
                y0 = polygon_[j-1][1]; 
                y1 = polygon_[j][1];
                
                if (y0 > abyss_) abyss_ = y0;
                if (y1 > abyss_) abyss_ = y1;

                if (x0 == x1) { 
                    if (y0 > y1) std::swap(y0, y1);
                    for (int l=y0; l<=y1; l++) caveMap_[{x0, l}] = true;
                }
                else {
                    if (x0 > x1) std::swap(x0, x1);
                    for (int l=x0; l<=x1; l++) caveMap_[{l, y0}] = true;
                }
            }
        }
    }

    void loadData() {
        std::string line;
        std::ifstream inputStream(inputFile_);
        while (getline(inputStream, line)) data_.push_back(line);
    }

    void setCurrentPolygon(std::string data) {
        
        polygon_.clear();
        std::string entry;

        while (data.find(delimiter_) <= data.length()) {
            entry = data.substr(0, data.find(delimiter_));
            data.erase(0, data.find(delimiter_) + delimiter_.length());
            polygon_.push_back(getCoordinate(entry));
        }
        polygon_.push_back(getCoordinate(data));
    }

    std::array<int, 2> getCoordinate(std::string input) {
        
        int x = std::stoi(input.substr(0, input.find(',')));
        input.erase(0, input.find(',') + 1);
        int y = std::stoi(input);

        return std::array<int, 2> {x, y};    
    }

public:

    Cave (std::string inputFile) {
        inputFile_ = inputFile;
        loadData();
        caveMap();
    }

    void printAbyss() {
        std::cout << abyss_ << std::endl;
    }

    void addFloor () {
        for (int i=-3*abyss_; i<3*abyss_; i++) caveMap_[{sandEntry_+i, abyss_ + caveHeight_}] = true;
    }

    void run () {
        
        int x, y;
        bool running = true;
        bool isDripping;

        while(running) {
            x = 500;
            y = 0;
        
            while (!caveMap_[{x, y}] && running) {

                if (!caveMap_[{x, y+1}]) {
                    y++;
                }
                else if(!caveMap_[{x-1, y+1}]) {
                    x--;
                    y++;
                }
                else if(!caveMap_[{x+1, y+1}]) {
                    x++;
                    y++;
                }
                else {
                    caveMap_[{x, y}] = true;
                    nSands_++;
                }

                if(y > abyss_ + 2 || y == 0) {
                    running = false;
                }
            }
        }
    }

    int numberOfSandUnits () { return nSands_; }

};

int solve (std::string inputFile, bool addFloor = false) {
    Cave cave(inputFile);
    if (addFloor) cave.addFloor();
    cave.run();
    return cave.numberOfSandUnits();
}

int main () {

    assert(solve("inputs/day14/test.txt") == 24);
    assert(solve("inputs/day14/test.txt", true) == 93);
    
    int solution;
    solution = solve("inputs/day14/input.txt");
    std::cout << "Part 1 solution: " << solution << std::endl;
    assert(solution == 715);

    solution = solve("inputs/day14/input.txt", true);
    std::cout << "Part 2 solution: " << solution << std::endl;
    assert(solution == 25248);

    return 0;
}    