#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>

int main(int argc, char* argv[]) {
    // Read first line and make it the size of a dynamic 2d array Eg: 26 7 would be 7 rows and 26 col
    //2nd line tells us where each character can go in a given range both numbers inclusive? U 0 10 means U can go in slots 0-10
    //3rd line and 4th line work togther, 3rd line tells us what range of char so 0 4 8 12... means 0-4 do the first 4 index in 4th line
    //Input is a multiline input string
    //TODO get characters to work with integers and letter, current implmentation only works with chars
    //TODO get ranges working, will not always be a two number range will be things like 0 2 12 14 then another could be 4 6 etc 
    //example input: 
    /*
    26 7
    U 0 10,H 15 25 
    0 4 8 12 25 29 33
    0 10 15 25 0 10 15 25 0 10 15 25 0 10 15 16 17 18 19 20 21 22 23 24 25 0 10 15 25 1 9 15 25 2 3 4 5 6 7 8 15 25
    */

    std::ifstream file("input1.txt");
    int row, col;
    file >> col >> row;
    file.ignore();

    
    char outputArray[row][col];
    for (int d = 0; d < row; d++) {
        for (int e = 0; e < col; e++) {
            outputArray[d][e] = ' ';  // Print each element
        }
    }

    std::string line;
    std::getline(file, line);
    std::vector<std::pair<char, std::pair<int, int> > > ranges;
    std::istringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ',')) {
        char prefix;
        int x, y;
        std::istringstream tokenStream(token);
        tokenStream >> prefix >> x >> y;
        ranges.emplace_back(prefix, std::make_pair(x, y));
    }


    std::vector<int> loc;
    std::getline(file, line);
    std::istringstream ss1(line);
    int num;
    while (ss1 >> num) {
        loc.push_back(num);
    }

    std::queue<int> where;
    std::getline(file, line);
    std::istringstream ss2(line);
    while (ss2 >> num) {
        where.push(num);
    }

    int rows = 0;
    for (int a = 0; a < loc.size(); a++) {
        if (a+1 < loc.size()) {
            int rangeDiff = loc[a+1] - loc[a];
            while (rangeDiff > 0) {
                int val = where.front();
                for (int b = 0; b < ranges.size(); b++) { // trying to find what range is working check first char then next char etc
                    if (val >= ranges[b].second.first && val <=  ranges[b].second.second) {
                        outputArray[rows][where.front()]= ranges[b].first;
                    }
                }
                where.pop();
                rangeDiff -= 1;
            }
            
        }
        else {
            while (!where.empty()) {
                int val = where.front();
                for (int b = 0; b < ranges.size(); b++) { // trying to find what range is working check first char then next char etc
                    if (val >= ranges[b].second.first && val <=  ranges[b].second.second) {
                        outputArray[rows][where.front()]= ranges[b].first;
                    }
                }
                where.pop(); 
            }
        }
        rows += 1;
    }
    
    

    std::ofstream outputFile("output.txt");
    for (int d = 0; d < row; d++) {
        for (int e = 0; e < col; e++) {
            outputFile << outputArray[d][e];  // Print each element
        }
        if (d < row - 1) outputFile << std::endl;  // Move to the next line after each row
    }

    outputFile.close();
    file.close();
    return 0;
}