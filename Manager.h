#ifndef MANAGER_H
#define MANAGER_H
#include <iostream>
#include <fstream>
#include "BSTree.h"
#include <queue>



using namespace std;

//------------------------------------------------------------------------------
//This file provides prototypes of the manager class which collects data about accounts from
//a file and is able to run the transactions that are in the queue.
//------------------------------------------------------------------------------


class Manager {
public:
    Manager();                              // constructor
    ~Manager();                             // destructor
    void runQueue();                        // execute next transaction
    //calls perform
    void buildTree(ifstream &);             // collect data from file
    void buildQueue(ifstream &);            // collect data from file
    void printEndOfDayReport();             //prints all report
    
private:
    BSTree tree;
    queue<Action*> action;
    
    
    
};
#endif /* MANAGER_H */

