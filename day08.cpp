#include <vector>
#include <fstream>
#include <iostream>
#include <string>

std::vector<std::string> loadData(std::string inputFile) {

    std::vector<std::string> data;
    std::string line;
    std::ifstream inputStream(inputFile);

    while (getline(inputStream, line)) data.push_back(line);

    return data;
}

std::vector<int> solve(std::string inputFile) {

    // Load data
    std::vector<std::string> data = loadData(inputFile);

    // Create an array representing the forest
    int nRows = data.size();
    int nCols = data[0].length();

    int forest [nRows][nCols];

    for (int i=0; i<nRows; i++) {
        for (int j=0; j<nCols; j++) {
            forest[i][j] = (int) data[i][j] - 48;
        }
    }

    // Solve part 1 and 2
    int maxScenicScore = 0;
    int scenicScore, k;
    int visible = 2 * (nRows + nCols - 2);
    bool isVisible;

    for (int i=1; i<nRows-1; i++) {
        for (int j=1; j<nCols-1; j++) {
            
            scenicScore = 1;
            isVisible = false;

            for (k=i-1; k>=0; k--) {
                if (forest[k][j] >= forest[i][j]) break;
                else if (k == 0) {isVisible = true;}
            }
            if (k == -1) k++;
            scenicScore *= (i - k);

            for (k=i+1; k<nRows; k++) {
                if (forest[k][j] >= forest[i][j])  break;
                else if (k == nRows - 1) isVisible = true;
            }
            if (k == nRows) k--;
            scenicScore *= (k - i);

            for (k=j-1; k>=0; k--) {
                if (forest[i][k] >= forest[i][j]) break;
                else if (k == 0) isVisible = true;
            }
            if (k == -1) k++;
            scenicScore *= (j - k); 

            for (k=j+1; k<nCols; k++) {
                if (forest[i][k] >= forest[i][j]) break;
                else if (k == nCols - 1) isVisible = true;
            }
            if (k == nRows) k--;
            scenicScore *= (k - j);

            visible += isVisible;
            if (scenicScore > maxScenicScore) maxScenicScore = scenicScore;
        }
    }

    std::vector<int> results = {visible, maxScenicScore};
    return results;

}

int main () {

    assert(solve("inputs/day08/test.txt")[0] == 21);
    assert(solve("inputs/day08/test.txt")[1] == 8);

    std::vector solution = solve("inputs/day08/input.txt");
    std::cout << "Part 1 solution: " << solution[0] << std::endl;
    assert(solution[0] == 1840);

    std::cout << "Part 2 solution: " << solution[1] << std::endl;
    assert(solution[1] == 405769);

    return 0;
}