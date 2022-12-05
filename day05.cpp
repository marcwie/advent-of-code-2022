#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <assert.h>

class Crane {

private:
    int nStacks_;
    std::vector<std::string> stacks_; 
    std::vector<std::array<int, 3>> moves_;    
    std::string inputLine_;
    std::string inputFile_;

    void setNumberStacks() {
        std::ifstream Input(inputFile_);
        getline(Input, inputLine_);
        nStacks_ = (inputLine_.size() + 1) / 4;
        Input.close();
    }

    void initalizePositions () {
        
        std::ifstream Input(inputFile_);

        stacks_.clear();
        for (int i=0; i<nStacks_; i++) {stacks_.push_back("");}

        while (getline(Input, inputLine_)) {
            if (inputLine_[1] == '1') break;
            for (int i=0; i<nStacks_; i++) {
                if (inputLine_[1 + 4 * i] != ' ')
                stacks_[i] += inputLine_[1 + 4 * i];
            }
        };

        for (int i=0; i<nStacks_; i++) {
            std::reverse(stacks_[i].begin(), stacks_[i].end());
        }

        Input.close();        
    }

    void loadMoves () {
        
        int offsets [3] = {5, 6, 4};
        std::ifstream Input(inputFile_);
        std::array<int, 3> oneMove;
        std::string move;
        int pos;

        moves_.clear();
        
        while (getline(Input, inputLine_)) {
            if (inputLine_[0] != 'm') continue;
            
            pos = 0;
            for (int i=0; i<3; i++) {
                pos += offsets[i];
                move = "";
                while (inputLine_[pos] != ' ') {
                    move += inputLine_[pos];
                    pos++;
                }
                oneMove[i] = std::stoi(move);
                if (i > 0) oneMove[i]--;
            }
            moves_.push_back(oneMove);
        };    
        Input.close();
    }

public:
    Crane(std::string inputFile) {
        resetInput(inputFile);
    }

    void reset() {
        setNumberStacks();
        initalizePositions();
        loadMoves();
    }

    void resetInput(std::string inputFile) {
        inputFile_ = inputFile;
        reset();
    }

    void move(bool moveMultiple = false) {
    
        std::string crates = "";
        
        for (int i=0; i<moves_.size(); i++) {
        
            for (int j=0; j<moves_[i][0]; j++) {
                crates += stacks_[moves_[i][1]].back();
                stacks_[moves_[i][1]].pop_back();
            }

            if (moveMultiple) std::reverse(crates.begin(), crates.end());
            stacks_[moves_[i][2]] += crates;
            crates = "";
        }
    }

    std::string result() {

        std::string res;
        for (int i=0; i<stacks_.size(); i++) res += stacks_[i].back();
        return res;
    }
};

int main () {

    Crane crane("inputs/day05/test.txt");
    crane.move();
    assert(crane.result() == "CMZ");

    crane.reset();
    crane.move(true);
    assert(crane.result() == "MCD");

    crane.resetInput("inputs/day05/input.txt");
    crane.move();
    std::cout << "Part 1 solution: " << crane.result() << std::endl; 
    assert(crane.result() == "RLFNRTNFB");

    crane.reset();
    crane.move(true);
    std::cout << "Part 2 solution: " << crane.result() << std::endl; 
    assert(crane.result() == "MHQTLJRLB");

    return 0;
}