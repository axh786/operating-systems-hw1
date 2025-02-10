#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    // Read first line and make it the size of a dynamic 2d array Eg: 26 7 would be 7 rows and 26 col
    //2nd line tells us where each character can go in a given range both numbers inclusive? U 0 10 means U can go in slots 0-10
    //3rd line and 4th line work togther, 3rd line tells us what range of char so 0 4 8 12... means 0-4 do the first 4 index in 4th line
    //Input is a multiline input string
    std::ifstream file("input1.txt");
    
    file.close();
}