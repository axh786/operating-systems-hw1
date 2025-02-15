/*
Ali Husain
Dr. Rincon
COSC 3360: Programming Assignment 1
14 Feb 2025
*/

/*
each thread should have ranges, poiner to matrix initialized in main, and the head datapos

ok so for the 0th iteration (goes up to 6 i< 7) my struct will always contain the ranges, i can load in the full dataPos and then load in
the pair of ranges in headpos being those only 2 ranges then store that information i decode into a vector? of col size so 26 for the UH
example
*/

#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>

#include <utility>
#include <sstream>

struct arguments {
    std::vector<std::pair<char, std::vector<std::pair<int, int> > > >& ranges;
    std::vector<int> headPos;
    std::vector<int>& dataPos;
    int index;
    char** matrix;
};

void * threadFunction(void *ptr) {
    
    return NULL;
}

int main() {
    //Reading first line of input from the user
    int col, row;
    std::cin >> col >> row;
    std::cin.ignore();
    char** matrix = new char*[row];
    
    for (int r = 0; r < row; ++r) { // initalize 2d array
        matrix[r] = new char[col];
        std::fill(matrix[r], matrix[r] + col, ' '); // Initialize with spaces
    }
    
    //Reading second line of input from the user
    std::vector<std::pair<char, std::vector<std::pair<int, int> > > > ranges;
    std::string line;
    std::getline(std::cin, line); // Read the second line
    std::istringstream iss(line);
    std::string token;
    while (std::getline(iss, token, ',')) {
        char id = token[0];
        std::vector<std::pair<int, int> > pairs;

        std::istringstream subIss(token.substr(2)); // Skip "X " where X is the identifier and space
        int a, b;
        while (subIss >> a >> b) {
            pairs.emplace_back(a, b);
        }

        ranges.emplace_back(id, pairs);
    }

    //Reading third line of input from the user
    std::vector<int> headPos;
    std::getline(std::cin, line);
    std::istringstream headStream(line);
    int value;
    while (headStream >> value) {
        headPos.push_back(value);
    }

    //Reading fourth line of input from the user
    std::vector<int> dataPos;
    std::getline(std::cin, line);
    std::istringstream dataStream(line);
    while (dataStream >> value) {
        dataPos.push_back(value);
    }

    std::vector<int> arg;
    arg.reserve(row);
    for (int i = 0; i < row; i++) {
        arguments args = {ranges, std::vector<int>(), dataPos, i, matrix};
        if (i == row - 1) {
            args.headPos.push_back(headPos[i]);
            args.headPos.push_back((int)dataPos.size() -1);
        }
        else {
            args.headPos.push_back(headPos[i]);
            args.headPos.push_back(headPos[i+1]);
        }
    }

    pthread_t *tid = new pthread_t[row];
    for (int i = 0; i < row; i++) {        
        if(pthread_create(&tid[i],nullptr,threadFunction,(void *) &arg.at(i))!= 0) {
			std::cerr << "Error creating thread" << std::endl;
			return 1;
		}
    }

    for (int j = 0; j < row; j++) {
        pthread_join(tid[j],nullptr);
    }

    //Clean up memory
    for (int r = 0; r < row; ++r) { 
        delete[] matrix[r];
    }
    delete[] matrix;
    delete[] tid;

    return 0;
}