#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>


class Monkey {

private:
    std::vector<int> items_;
    std::string operation_;
    int operand_;
    int test_;
    int throwToIfTrue_;
    int throwToIfFalse_;
    int inspected_ = 0;

    void newWorryLevel (int &item) {
        
        if (operation_ == "add") item += operand_;
        else if (operation_ == "multiply") item *= operand_;
        else item *= item; 

        item /= 3;

    }
public:

    Monkey (std::vector<int> items, std::string operation, int operand, int test, int throwIfTrue, int throwIfFalse) {
        items_ = items;
        operation_ = operation;
        operand_ = operand;
        test_ = test;
        throwToIfTrue_ = throwIfTrue;
        throwToIfFalse_ = throwIfFalse;
    }

    std::vector<int> treatItem () {
        
        inspected_++;

        // Get first item
        int item = items_.front();
        items_.erase(items_.begin());
        
        // Compute worry level
        newWorryLevel(item);
        
        // Decide which monkey gets the item next
        int nextMonkey;
        if (item % test_ == 0) nextMonkey = throwToIfTrue_;
        else nextMonkey = throwToIfFalse_;
        
        return std::vector<int> {nextMonkey, item};
    }

    bool hasIitem () {return items_.size() > 0;}

    void getItem (int item) {items_.push_back(item);}

    int inspections () {return inspected_;}

};

std::vector<std::string> loadData (std::string inputFile) {

    std::vector<std::string> data;
    std::string line;
    std::ifstream inputStream(inputFile);

    while (getline(inputStream, line)) data.push_back(line);

    return data;
}

std::vector<int> getItems(std::string line, char separator=',') {

    std::istringstream stream(line);
    std::string entry;
    std::vector<int> entries;

    while (getline(stream, entry, separator)) entries.push_back(std::stoi(entry));
    
    return entries;
}

std::vector<Monkey> parseData (std::vector<std::string> data) {
    
    int nMonkeys = (data.size() - 6) / 7 + 1;
    
    std::vector<int> items;
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

int part1(std::string inputFile, int nRounds=20) {

    std::vector<std::string> data = loadData(inputFile);
    std::vector<Monkey> monkeys = parseData(data);

    std::vector<int> nextItem;
    for (int r=0; r<nRounds; r++) {
        for (int m=0; m<monkeys.size(); m++) {
            while (monkeys[m].hasIitem()) {
                nextItem = monkeys[m].treatItem();
                monkeys[nextItem[0]].getItem(nextItem[1]);
            }
        }
    }

    std::vector<int> inspections;
    for (int m=0; m<monkeys.size(); m++) {
        inspections.push_back(monkeys[m].inspections());
    }

    sort(inspections.begin(), inspections.end(), std::greater<int>());

    return inspections[0] * inspections[1];
}

int main () {

    assert(part1("inputs/day11/test.txt") == 10605);

    int solution;
    solution = part1("inputs/day11/input.txt");
    std::cout << "Part 1 solution: " << solution << std::endl;
    assert(solution == 54036);
    
    return 0;
}