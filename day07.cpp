#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>     

using namespace std;

vector<string> splitline(string line, char separator=' ')
{
    vector<string> entries;
    string entry;
    istringstream stream(line);
    while (getline(stream, entry, separator)) entries.push_back(entry);

    return entries;
}

class Filesystem {

private:
    vector<string> data_;
    vector<string> dirs_;
    map<string, int> totalSizes;


public: 
    Filesystem(string inputFile) {
        load(inputFile);
    }

    void load(string inputFile) {
        string inputLine;
        ifstream Input(inputFile);

        while (getline(Input, inputLine)) data_.push_back(inputLine);
    }

    void fixDuplicateFolderNames() {
        
        vector<string> line;
        for (int i=0; i<data_.size(); i++) {
            line = splitline(data_[i]);
            if (line[1] == "cd" && line[2] != ".." && line[2] != "/") data_[i] += to_string(i);
        }
    }

    void findDirectories () {

        vector<string> line;

        for (int i=0; i<data_.size(); i++) {
            line = splitline(data_[i]);   
            if (line[1] == "cd" && line[2] != "..") {
                dirs_.push_back(line[2]);
             }
        }
    }

    int filesize(string inputLine) {
        vector<string> line = splitline(inputLine);
        return stoi(line[0]);
    }

    string filename(string inputLine) {
        vector<string> line = splitline(inputLine);
        return line[1];
    }

    void computeSizes () {

        int depth;
        vector<string> line;

        for (int i=0; i<dirs_.size(); i++) {
            
            depth = 0;
            totalSizes[dirs_[i]] = 0;

            for (int j=0; j<data_.size(); j++) {
                
                line = splitline(data_[j]);
                if (line[1] == "cd" && line[2] == dirs_[i]) depth++;
                else if (line[2] == ".." && depth > 0) depth--;
                else if (line[1] == "cd" && depth > 0) depth++;
                else if (line[0] != "$" && line[0] != "dir" && depth > 0) totalSizes[dirs_[i]] += filesize(data_[j]);
            }
        }
    }

    int totalSum(int maxSize = 100000) {
        int result = 0;
        for (int i=0; i<dirs_.size(); i++) {
            if (totalSizes[dirs_[i]] <= maxSize) result += totalSizes[dirs_[i]];
        }
        return result;
    }

    int efficientDelete() {
        
        int totalSpace = 70000000;
        int requiredSpace = 30000000;
        int totalSize = totalSizes["/"];
        int toFree = requiredSpace - (totalSpace - totalSize);

        int smallestSize = totalSize;
        for (int i=0; i<dirs_.size(); i++) {
            if (totalSizes[dirs_[i]] > toFree && totalSizes[dirs_[i]] < smallestSize) {
                smallestSize = totalSizes[dirs_[i]];
            }
        }

        return smallestSize;

    }
};

int solve(string inputFile, int part) {
    
    Filesystem filesystem(inputFile);
    filesystem.fixDuplicateFolderNames();
    filesystem.findDirectories();
    filesystem.computeSizes();

    if (part == 1) return filesystem.totalSum();
    else return filesystem.efficientDelete();    
}

int main () {

    assert(solve("inputs/day07/test.txt", 1) == 95437);
    assert(solve("inputs/day07/test.txt", 2) == 24933642);

    int solution;
    solution = solve("inputs/day07/input.txt", 1);
    cout << "Part 1 solution: " << solution << endl;
    assert(solution == 1447046);

    solution = solve("inputs/day07/input.txt", 2);
    cout << "Part 2 solution: " << solution << endl;
    assert(solution == 578710);
    
    return 0;

};