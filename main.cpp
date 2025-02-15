/*
COSC 3360: Programming Assignment 1
14 Feb 2025
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
    char** outputMatrix;
};

void * asciiArt(void *void_ptr) {
   arguments *ptr = (arguments *) void_ptr;

   std::vector<std::pair<char, std::vector<std::pair<int, int> > > >& ranges = ptr->ranges;
   std::vector<int>& dataPos = ptr->dataPos;
   int index = ptr->index;
   char** outputMatrix = ptr->outputMatrix;

   for (int i = ptr->headPos[0]; i < ptr->headPos[1]; i++) {
        int data = ptr->dataPos[i];
        for (int j = 0; j < ranges.size(); j++) {
            char character = ranges[j].first;
            const std::vector<std::pair<int, int> >& inner_ranges = ranges[j].second;
            for (int k = 0; k < inner_ranges.size(); k++) {
                int start = inner_ranges[k].first;
                int end = inner_ranges[k].second;
                if (data >= start && data <= end) {
                    outputMatrix[index][data] = character;
                    break;
                }
                
            }
        }
   }

    return NULL;
}

int main() {
    //Reading first line of input from the user
    int col, row;
    std::cin >> col >> row;
    std::cin.ignore();
    char** outputMatrix = new char*[row];
    
    for (int r = 0; r < row; ++r) { // initalize 2d array
        outputMatrix[r] = new char[col];
        std::fill(outputMatrix[r], outputMatrix[r] + col, ' '); // Initialize with spaces
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
    
    std::vector<arguments> arg;
    arg.reserve(row);
    for (int i = 0; i < row; i++) {
        arguments args = {ranges, std::vector<int>(), dataPos, i, outputMatrix};
        if (i == row - 1) {
            args.headPos.push_back(headPos[i]);
            args.headPos.push_back((int)dataPos.size());
        }
        else {
            args.headPos.push_back(headPos[i]);
            args.headPos.push_back(headPos[i+1]);
        }
        arg.push_back(args);
    }


    pthread_t *tid = new pthread_t[row];
    for (int i = 0; i < row; i++) {        
        if(pthread_create(&tid[i],nullptr,asciiArt,(void *) &arg.at(i))!= 0) {
			std::cerr << "Error creating thread" << std::endl;
			return 1;
		}
    }

    for (int j = 0; j < row; j++) {
        pthread_join(tid[j],nullptr);
    }

    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            std::cout << outputMatrix[r][c];
        }
        std::cout << std::endl;
    }

    //deallocate memory
    for (int r = 0; r < row; ++r) { 
        delete[] outputMatrix[r];
    }
    delete[] outputMatrix;
    delete[] tid;

    return 0;
}