//
//  BoundedQueue.cpp
//  BoundedQueueKPCB
//
//  Created by Sam Bodanis on 16/10/2013.
//  Copyright (c) 2013 Sam Bodanis. All rights reserved.
//

#include "BoundedQueue.h"

BoundedQueue::BoundedQueue(int size) {
    if (size <= 0) {
        throw "Cannot enter negative or zero queue size";
    }
    numElements = 0;
    allowedSize = size;
    head = NULL;
    tail = NULL;
}

BoundedQueue::~BoundedQueue() {
    clear();
}

bool BoundedQueue::fillWithArray(int *dataArray, int dataSize) {
    if (numElements + dataSize > allowedSize) {
        return false;
    }
    for (int i = 0; i < dataSize; i++) {
        bool successfulEnq = enqueue(dataArray[i]);
        if (!successfulEnq) return false;
    }
    return true;
}

bool BoundedQueue::enqueue(int data) {
    if (size() == allowedSize) {
        return false;
    }
    numElements++;
    if (head == NULL) {
        head = newNode(data, NULL, NULL);
        tail = head;
    } else {
        node *nodeToEnqueue = newNode(data, head, NULL);
        head->previous = nodeToEnqueue;
        head = nodeToEnqueue;
    }
    return true;
}

int BoundedQueue::dequeue() {
    if (size() == 0) {
        throw "Error: cannot dequeue empty queue";
    }
    int returnValue = tail->data;

    if (size() == 1) {
        delete tail;
        tail = NULL; // Check if necessary
        head = NULL; // Check if necessary
    } else {
        tail = tail->previous;
        delete tail->next;
        tail->next = NULL; // Check if necessary
    }
    numElements--;
    return returnValue;
}

int *BoundedQueue::toArray(int & size) {
    if (isEmpty()) {
        size = 0;
        return NULL;
    }
    node *traverser = head;
    int *outputArray = new int[numElements];
    size = numElements;
    int idx = 0;
    while (traverser != NULL) {
        outputArray[idx++] = traverser->data;
        traverser = traverser->next;
    }
    return outputArray;
}

void BoundedQueue::clear() {
    while (head != NULL) {
        node *temp = head;
        head = head->next;
        delete temp;
    }
    numElements = 0;
}

int BoundedQueue::boundedSize() {
    return allowedSize;
}

int BoundedQueue::size() {
    return numElements;
}

bool BoundedQueue::isEmpty() {
    return numElements == 0;
}

node *BoundedQueue::newNode(int data, node *next, node *previous) {
    node *n = new node;
    n->data = data;
    n->next = next;
    n->previous = previous;
    return n;
}




