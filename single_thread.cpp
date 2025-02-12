#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int main(int argc, char* argv[]) {
    // Read first line and make it the size of a dynamic 2d array Eg: 26 7 would be 7 rows and 26 col
    //2nd line tells us where each character can go in a given range both numbers inclusive? U 0 10 means U can go in slots 0-10
    //3rd line and 4th line work togther, 3rd line tells us what range of char so 0 4 8 12... means 0-4 do the first 4 index in 4th line
    //Input is a multiline input string
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
    
    std::cout << "Columns: " << col << std::endl;
    std::cout << "Rows: " << row << std::endl; // Test row and col input
    
    int* outputArray = new int[row * col];

    std::string range;
    std::getline(file, range);
    std::vector<std::pair<char, std::pair<int, int> > > ranges;
    std::istringstream ss(range);
    std::string token;
    while (std::getline(ss, token, ',')) {
        char prefix;
        int x, y;
        std::istringstream tokenStream(token);
        tokenStream >> prefix >> x >> y;
        ranges.emplace_back(prefix, std::make_pair(x, y));
    }

    for (int i = 0; i < ranges.size(); i++) { // test second line ranges input
        std::cout << "Ranges and chars: " << ranges[i].first << ", " << ranges[i].second.first << " " << ranges[i].second.second << std::endl;
    }

    file.close();
    return 0;
}