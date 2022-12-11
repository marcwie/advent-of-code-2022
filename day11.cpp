#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

class Monkey {

private:
    std::vector<long> items_;
    std::string operation_;
    int operand_, test_, throwToIfTrue_, throwToIfFalse_;
    int inspected_ = 0;
    long reductionFactor_ = 3;
    std::string worryReduction_ = "division";

    void newWorryLevel (long &item) {
        
        if (operation_ == "add") item += operand_;
        else if (operation_ == "multiply") item *= operand_;
        else item *= item; 
    }

    void reduceWorryLevel(long &item) {

        if (worryReduction_ == "division") item /= reductionFactor_;
        else item %= reductionFactor_;
    }

public:

    Monkey (std::vector<long> items, std::string operation, int operand, int test, int throwIfTrue, int throwIfFalse) {
        items_ = items;
        operation_ = operation;
        operand_ = operand;
        test_ = test;
        throwToIfTrue_ = throwIfTrue;
        throwToIfFalse_ = throwIfFalse;
    }

    std::vector<long> treatItem () {
        
        inspected_++;

        long item = items_.front();
        items_.erase(items_.begin());
        
        newWorryLevel(item);
        reduceWorryLevel(item);

        int nextMonkey;
        if (item % test_ == 0) nextMonkey = throwToIfTrue_;
        else nextMonkey = throwToIfFalse_;
        
        return std::vector<long> {nextMonkey, item};
    }

    bool hasIitem () {return items_.size() > 0;}

    void getItem (long item) {items_.push_back(item);}

    int inspections () {return inspected_;}

    void setWorryReduction (std::string reductionType, long reductionFactor) {
        worryReduction_ = reductionType;
        reductionFactor_ = reductionFactor;
    }

    int testValue () { return test_; }
};

std::vector<std::string> loadData (std::string inputFile) {

    std::vector<std::string> data;
    std::string line;
    std::ifstream inputStream(inputFile);

    while (getline(inputStream, line)) data.push_back(line);

    return data;
}

std::vector<long> getItems(std::string line, char separator=',') {

    std::istringstream stream(line);
    std::string entry;
    std::vector<long> entries;

    while (getline(stream, entry, separator)) entries.push_back(std::stol(entry));
    
    return entries;
}

std::vector<Monkey> parseData (std::vector<std::string> data) {
    
    int nMonkeys = (data.size() - 6) / 7 + 1;
    
    std::vector<long> items;
    std::vector<Monkey> monkeys;
    int l, operand, test, throwIfTrue, throwIfFalse;
    std::string operation;

    for (int i=0; i<nMonkeys; i++) {
        l = 7 * i;
        
        items = getItems(data[++l].substr(18));
       
        if (data[++l][23] == '+') operation = "add";
        else if (data[l][23] == '*' && data[l][25] != 'o') operation = "multiply";
        else operation = "square";

        if (operation != "square") operand = std::stoi(data[l].substr(25));
        else operand = -1;
        
        test = std::stoi(data[++l].substr(21));
        throwIfTrue = std::stoi(data[++l].substr(29));
        throwIfFalse = std::stoi(data[++l].substr(30));

        monkeys.push_back(Monkey(items, operation, operand, test, throwIfTrue, throwIfFalse));
        }

    return monkeys;
}

long solve(std::string inputFile, int nRounds=20, int part = 1) {

    std::vector<std::string> data = loadData(inputFile);
    std::vector<Monkey> monkeys = parseData(data);

    if (part == 2) {
        long factor = 1;
        for (int m=0; m<monkeys.size(); m++) factor *= monkeys[m].testValue(); 
        for (int m=0; m<monkeys.size(); m++) monkeys[m].setWorryReduction("modulo", factor); 
    }

    std::vector<long> nextItem;
    for (int r=0; r<nRounds; r++) {
        for (int m=0; m<monkeys.size(); m++) {
            while (monkeys[m].hasIitem()) {
                nextItem = monkeys[m].treatItem();
                monkeys[nextItem[0]].getItem(nextItem[1]);
            }
        }
    }

    std::vector<long> inspections;
    for (int m=0; m<monkeys.size(); m++) {
        inspections.push_back(monkeys[m].inspections());
    }

    sort(inspections.begin(), inspections.end(), std::greater<int>());

    return inspections[0] * inspections[1];
}

int main () {

    assert(solve("inputs/day11/test.txt", 20, 1) == 10605);
    assert(solve("inputs/day11/test.txt", 10000, 2) == 2713310158);

    long solution;
    solution = solve("inputs/day11/input.txt", 20, 1);
    std::cout << "Part 1 solution: " << solution << std::endl;
    assert(solution == 54036);
    
    solution = solve("inputs/day11/input.txt", 10000, 2);
    std::cout << "Part 2 solution: " << solution << std::endl;
    assert(solution == 13237873355);
    
    return 0;
}