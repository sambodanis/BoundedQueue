//
//  main.cpp
//  BoundedQueueKPCB
//
//  Created by Sam Bodanis on 16/10/2013.
//  Copyright (c) 2013 Sam Bodanis. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>

#include "BoundedQueue.h"

bool performTests();
void interactive();
int *intsFromString(std::string str, int & size);
std::string *tokeniseInput(std::string input);

const std::string instructions = "BoundedQueue commands are: \ne 'value' 'value' ... 'value' - to enqueue one or more values \nd - to dequeue a value\ns - for the size \nb - for bounded size \ncb 'value' - to change the bounded size \nall - to dispaly all elements \nc - to remove all values \nend - to end the program";

int main(int argc, const char * argv[]) {
    if (argc > 1 && strncmp(argv[1], "-test", strlen("-test")) == 0 && performTests()) {
        std::cout << "All tests passed!" << std::endl;
    } else {
        std::cout << instructions << std::endl;
        interactive();
    }
    

    return 0;
}

// Reallocates an array with a greater length and transfers old data over
std::string *grow(std::string *arr, int & size) {
    std::string *newArr = new std::string[size * 2];
    for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }
    size *= 2;
    return newArr;
}

// seperates input string, eg "apple banana orange" => ["apple", "banana", "orange"]
std::string *tokeniseInput(std::string input, int & tokens) {
    int i = 0;
    int initialSize = 5;
    std::string *arr = new std::string[initialSize];
    std::stringstream ssin(input);
    while (ssin.good()) {
        if (i == initialSize) {
            arr = grow(arr, initialSize);
        }
        ssin >> arr[i++];
    }
    tokens = i;
    return arr;
}

void interactive() {
    std::cout << "\nEnter the number of bounded value: ";
    std::string input = "";
    BoundedQueue *queue = NULL;
    bool first = true;
    while (true) {
        if (!first) std::cout << ">> ";
        getline(std::cin, input);
        int numTokens = 0;
        std::string *tokens = tokeniseInput(input, numTokens);
        if (first) {
            queue = new BoundedQueue(atoi(tokens[0].c_str()));
            first = false;
        } else {
            if (tokens[0] == "e") {
                
                if (numTokens > 2) {
                    int *intArray = new int[numTokens - 1];
                    for (int i = 0; i < numTokens - 1; i++) {
                        intArray[i] = atoi(tokens[i + 1].c_str());
                    }
                    if (!queue->fillWithArray(intArray, numTokens - 1)) {
                        std::cout << "Queue is full " << std::endl;
                    }
                    delete[] intArray;
                } else {
                    if (!queue->enqueue(atoi(tokens[1].c_str()))) {
                        std::cout << "Queue is full" << std::endl;
                    }
                }
            } else if (tokens[0] == "d") {
                if (queue->isEmpty()) {
                    std::cout << "Cannot dequeue from empty queue" << std::endl;
                } else {
                    std::cout << "Dequeued: " << queue->dequeue() << std::endl;
                }
            } else if (tokens[0] == "s") {
                std::cout << "Size: " << queue->size() << std::endl;
            } else if (tokens[0] == "b") {
                std::cout << "Bounded size: " << queue->boundedSize() << std::endl;
            } else if (tokens[0] == "cb") {
                delete queue;
                queue = new BoundedQueue(atoi(tokens[1].c_str()));
                std::cout << "Queue rebounded with new length of " << tokens[1] << std::endl;
            } else if (tokens[0] == "all") {
                int queueSize = 0;
                int *queueContents = queue->toArray(queueSize);
                for (int i = 0; i < queueSize; i++) {
                    std::cout << queueContents[i] << " ";
                }
                std::cout << std::endl;
                delete [] queueContents;
            } else if (tokens[0] == "c") {
                queue->clear();
                std::cout << "Queue cleared" << std::endl;
            } else if (tokens[0] == "end") {
                return;
            } else {
                std::cout << "Please enter a valid command\n\n" << instructions << std::endl;
            }
        }
    }
}

bool performTests() {
    int testSize = 5;
    BoundedQueue *testQ = new BoundedQueue(testSize);
    
    //-----------------------------$$
    if (testQ->boundedSize() != testSize) {
        std::cerr << "Test size of " << testSize << " not equal to actual size of " << testQ->boundedSize() << std::endl;
        return false;
    }
    if (testQ->size() != 0) {
        std::cerr << "Empty queue should contain zero elements but contains: " << testQ->size() << " elements." << std::endl;
        return false;
    }
    std::cout << "Passed size checks" << std::endl;
    
    //-----------------------------$$
    int valueToEnqueue = 6;
    if (!testQ->enqueue(valueToEnqueue)) {
        std::cerr << "Supposedly empty queue is full, contains " << testQ->size() << " elements." << std::endl;
        return false;
    }
    if (testQ->size() != 1) {
        std::cerr << "Queue should contain 1 element but contains " << testQ->size() << " elements." << std::endl;
        return false;
    }
    std::cout << "Passed enqueue checks" << std::endl;
    
    int dequeuedValue = testQ->dequeue();
    if (dequeuedValue != valueToEnqueue) {
        std::cerr << valueToEnqueue << " was enqueued, " << dequeuedValue << " was dequeued" << std::endl;
        return false;
    }
    if (!testQ->isEmpty()) {
        std::cerr << "Queue should be empty but contains " << testQ->size() << " elements" << std::endl;
        return false;
    }
    std::cout << "Passed dequeue checks" << std::endl;
    
    //-----------------------------$$
    for (int i = 0; i < testSize; i++) {
        testQ->enqueue(i);
    }
    if (testQ->enqueue(valueToEnqueue)) {
        std::cerr << "Queue should be full but enqueued value, contains " << testQ->size() << " elements" << std::endl;
        return false;
    }
    if (testQ->size() != testSize) {
        std::cerr << "Queue size should be " << testSize << " but is " << testQ->size() << std::endl;
        return false;
    }
    std::cout << "Passed enqueue to full checks" << std::endl;
    
    //-----------------------------$$
    int arraySize;
    int *arrayRepresentation = testQ->toArray(arraySize);
    if (arraySize != testSize) {
        std::cerr << "Array should contain " << testSize << " elements but contains " << arraySize << " elements" << std::endl;
        return false;
    }
    for (int i = 0; i < arraySize; i++) {
        if (arrayRepresentation[i] != arraySize - i - 1) {
            std::cerr << "Array element is " << arrayRepresentation[i] << " but should be " << (arraySize - i - 1) << std::endl;
            return false;
        }
    }
    std::cout << "Passed toArray checks" << std::endl;
    
    if (testQ->fillWithArray(arrayRepresentation, arraySize)) {
        std::cerr << "Queue should be full and return false to fillWithArray but contains " << testQ->size() << " elements" << std::endl;
        return false;
    }
    
    //-----------------------------$$
    for (int i = 0; i < testSize; i++) {
        dequeuedValue = testQ->dequeue();
        if (dequeuedValue != i) {
            std::cerr << dequeuedValue << " was dequeued, should have been " << i << std::endl;
            return false;
        }
    }
    if (!testQ->isEmpty()) {
        std::cerr << "Queue should be empty but contains " << testQ->size() << " elements" << std::endl;
        return false;
    }
    std::cout << "Passed dequeue to empty checks" << std::endl;
    
    //-----------------------------$$
    if (!testQ->fillWithArray(arrayRepresentation, arraySize)) {
        std::cerr << "Queue should've been empty but contains " << testQ->size() << " elements" << std::endl;
        return false;
    }
    if (testQ->size() != arraySize) {
        std::cerr << "Queue should've enqueued " << arraySize << " elements but contains " << testQ->size() << " elements" << std::endl;
        return false;
    }
    std::cerr << "Passed fillWithArray checks" << std::endl;

    return true;
}

