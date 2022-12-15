#include <vector>
#include <fstream>
#include <array>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>

bool overlap (int x0, int x1, int y0, int y1) {
    if (x1 + 1 < y0 || y1 + 1 < x0) return false;
    else return true;
}

std::array<int, 2> computeOverlap (int x0, int x1, int y0, int y1) {
    if (x0 <= y0 && y1 <= x1) return {x0, x1};
    else if (y0 <= x0 && x1 <= y1) return {y0, y1};
    else if (x0 <= y0 && x1 <= y1) return {x0, y1};
    else if (y0 <= x0 && y1 <= x1) return {y0, x1};
    else assert(false);
}

class Tunnels {

private: 
    std::vector<std::string> inputData_;
    std::string inputFile_;
    std::vector<std::array<int, 4>> beacons_;
    std::map<int, std::set<int>> beaconsPerRow_;

    void loadData () {
        std::string line;
        std::ifstream inputStream(inputFile_);
        while (getline(inputStream, line)) inputData_.push_back(line);
    }

    void loadBeaconData () {

        int pos;
        std::string line;
        int x0, y0, x1, y1;
        
        for (int i=0; i<inputData_.size(); i++) {
            
            line = inputData_[i];

            line.erase(0, line.find('=') + 1);
            x0 = std::stoi(line.substr(0, line.find(',')));
            line.erase(0, line.find('=') + 1);
            y0 = std::stoi(line.substr(0, line.find(',')));
            line.erase(0, line.find('=') + 1);
            x1 = std::stoi(line.substr(0, line.find(',')));
            line.erase(0, line.find('=') + 1);
            y1 = std::stoi(line);

            beacons_.push_back({x0, y0, x1, y1});
            beaconsPerRow_[y0].insert(x0);
            beaconsPerRow_[y1].insert(x1);
        }
    }

    void reduceRowMap(std::vector<std::array<int, 2>> &rowMap) {

        bool foundOverlap = true;
        int i, j;

        while (foundOverlap) {
            
            foundOverlap = false;

            for (i=0; i<rowMap.size(); i++) {
                for (j=i+1; j<rowMap.size(); j++) {
                    if (overlap(rowMap[i][0], rowMap[i][1], rowMap[j][0], rowMap[j][1])) {
                        foundOverlap = true;
                        goto end;
                    }
                }
            }

            end:

            if (foundOverlap) {
                rowMap.push_back(computeOverlap(rowMap[i][0], rowMap[i][1], rowMap[j][0], rowMap[j][1]));
                rowMap.erase(rowMap.begin() + i);
                rowMap.erase(rowMap.begin() + j-1);
            }
        }
    }

    std::vector<std::array<int, 2>> generateRowMap (int row) {
    
        int distance, remainder;
        std::vector<std::array<int, 2>> rowMap;
        
        for (int i=0; i<beacons_.size(); i++) {
            
            distance = abs(beacons_[i][0] - beacons_[i][2]) + abs(beacons_[i][1] - beacons_[i][3]);
            remainder = distance - abs(row - beacons_[i][1]);
            if (abs(beacons_[i][1] - row) <= distance) {
                rowMap.push_back({beacons_[i][0] - remainder, beacons_[i][0] +remainder});
            } 
        }    
        reduceRowMap(rowMap);
        return rowMap;
    }

public:
    
    Tunnels (std::string inputFile) {
        inputFile_ = inputFile;
        loadData();
        loadBeaconData();
    }

    int impossibleLocations (int row) {

        std::vector<std::array<int, 2>> rowMap = generateRowMap(row);
        return rowMap[0][1] - rowMap[0][0] + 1 - beaconsPerRow_[row].size();
    }

    long distressBeacon (int extent) {
    
        std::vector<std::array<int, 2>> rowMap;
        std::array <long, 4> bounds;

        for (long i=0; i<=extent; i++) {
            rowMap = generateRowMap(i);
            if (rowMap.size() > 1) {
                bounds = {rowMap[0][0], rowMap[0][1], rowMap[1][0], rowMap[1][1]};
                std::sort(std::begin(bounds), std::end(bounds));
                return (bounds[1] + 1) * 4000000 + i;
            }
        }
        return -1;
    }

};

int part1 (std::string inputFile, int row) {
    Tunnels tunnels (inputFile);
    return tunnels.impossibleLocations(row);
}

long part2 (std::string inputFile, int extent) {
    Tunnels tunnels (inputFile);
    return tunnels.distressBeacon(extent);
}

int main () {

    assert(part1("inputs/day15/test.txt", 10) == 26); 
    assert(part2("inputs/day15/test.txt", 20) == 56000011); 

    long solution;
    solution = part1("inputs/day15/input.txt", 2000000);
    std::cout << "Part 1 solution: " << solution << std::endl;
    assert(solution == 5461729);

    solution = part2("inputs/day15/input.txt", 4000000);
    std::cout << "Part 2 solution: " << solution << std::endl;
    assert(solution == 10621647166538);
    return 0;
}