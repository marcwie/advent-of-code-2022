#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::string> loadData(std::string inputFile) {

    std::vector<std::string> data;
    std::string line;
    std::ifstream inputStream(inputFile);

    while (getline(inputStream, line)) data.push_back(line);

    return data;
}

std::vector<std::string> splitline(std::string line, char separator=' ') {
    
    std::istringstream stream(line);
    std::string entry;
    std::vector<std::string> entries;

    while (getline(stream, entry, separator)) entries.push_back(entry);
    
    return entries;
}

class Computer {

private:
    int X_, cycle_, signalStrength_;
    std::string crt_;

    void reset() {
        X_ = 1;
        cycle_ = 0;
        signalStrength_ = 0;
        crt_ = "";
    }

public:

    Computer () {
        reset();
    }

    void execute (std::string command) {

        cycle_++;
        updateCRT();
        if ((cycle_ - 20) % 40 == 0) signalStrength_ += cycle_ * X_; 
        if (command != "noop" && command != "addx") X_ += std::stoi(command);

    }

    void updateCRT () {
        int currentPixel = (cycle_ - 1) % 40;
        if ( currentPixel >= X_ - 1 && currentPixel <= X_ + 1 ) crt_ += "#";
        else crt_ += " ";
    }

    void printScreen () {

        for (int i=0; i<crt_.length(); i++) {
            if (i % 40 == 0 && i != 0) std::cout << std::endl;
            std::cout << crt_[i];
        }
        std::cout << std::endl;
    }

    int signalStrength () { return signalStrength_; } 

    void run (std::vector<std::string> commands) {
        
        std::vector<std::string> command;

        for (int i=0; i<commands.size(); i++) {
            command = splitline(commands[i]);  
            for (int j=0; j<command.size(); j++) {
                execute(command[j]);
            }
        }
    }
};

int solve(std::string inputFile, bool print = false) {
    
    std::vector<std::string> data = loadData(inputFile);
    Computer computer;
    computer.run(data);
    if (print) computer.printScreen();
    return computer.signalStrength();

}

int main () {

    assert(solve("inputs/day10/test.txt") == 13140);

    int solution = solve("inputs/day10/input.txt");
    std::cout << "Part 1 solution: " << solution << std::endl;
    assert(solution == 13860);

    std::cout << "Part 2 solution:" << std::endl;
    solve("inputs/day10/input.txt", true);

    return 0;
}