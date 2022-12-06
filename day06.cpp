#include <iostream>
#include <assert.h>
#include <fstream>

int markerPosition (std::string datastream, int nDistinct) {

    char characters [nDistinct];
    int i;
    bool valid;

    for (int j=0; j<nDistinct; j++) {
        characters[j] = datastream[j];
    }

    for (i=4; i<datastream.size(); i++) {
        
        valid = true;
        for (int j=0; j<nDistinct; j++) {
            for (int k=j+1; k<nDistinct; k++) {
                if (characters[j] == characters[k]) valid = false;
            }
        }

        if (valid) break;
        else characters[i % nDistinct] = datastream[i];
        
    }

    return i;
}

int main () {

    assert(markerPosition("bvwbjplbgvbhsrlpgdmjqwftvncz", 4) == 5);
    assert(markerPosition("nppdvjthqldpwncqszvftbrmjlhg", 4) == 6);
    assert(markerPosition("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 4) == 10);
    assert(markerPosition("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 4) == 11);

    assert(markerPosition("bvwbjplbgvbhsrlpgdmjqwftvncz", 14) == 23);
    assert(markerPosition("nppdvjthqldpwncqszvftbrmjlhg", 14) == 23);
    assert(markerPosition("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 14) == 29);
    assert(markerPosition("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 14) == 26);

    int solution;
    std::string line;
    std::ifstream Input("inputs/day06/input.txt");
    getline(Input, line);
    Input.close();
    
    solution = markerPosition(line, 4);
    std::cout << "Part 1 solution: " << solution << std::endl;
    assert(solution == 1876);

    solution = markerPosition(line, 14);
    std::cout << "Part 2 solution: " << solution << std::endl;
    assert(solution == 2202);
} 