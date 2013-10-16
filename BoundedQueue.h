//
//  BoundedQueue.h
//  BoundedQueueKPCB
//
//  Created by Sam Bodanis on 16/10/2013.
//  Copyright (c) 2013 Sam Bodanis. All rights reserved.
//

#ifndef __BoundedQueueKPCB__BoundedQueue__
#define __BoundedQueueKPCB__BoundedQueue__

#include <iostream>

struct node {
    int data;
    node *next;
    node *previous;
};

class BoundedQueue {
    
public:

    BoundedQueue(int size);
    
    ~BoundedQueue();
    
    // Puts the elements of an array into the queue.
    // Returns false if doing so would go past the bounding
    // limit of the queue.
    bool fillWithArray(int dataArray[], int dataSize);
    
    // If queue is full, return false. If queue is empty, set new node to
    // head and tail. Else stick node onto the front.
    bool enqueue(int data);
    
    // Throw error if dequeueing from empty queue
    // Save data in tail node, delete tail node, return data
    int dequeue();
    
    // Returns an array containing all elements of the queue.
    // Takes a size parameter passed by reference that is updated
    // with the size of the array. 
    int *toArray(int & size);
    
    // Removes all data from the queue
    void clear();
    
    // Returns initially given bounding size of the number of
    // elements allowed in the queue.
    int boundedSize();
    
    // Returns the number of elements in the queue.
    int size();

    // Returns whether the queue is empty or not.
    bool isEmpty();
    
private:
    
    node *newNode(int data, node *next, node *previous);
    
    node *head;
    
    node *tail;
    
    int numElements;
    
    int allowedSize;
};

#endif /* defined(__BoundedQueueKPCB__BoundedQueue__) */
