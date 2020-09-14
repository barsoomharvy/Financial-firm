//------------------------------------------------------------------------------
//this file implements the methods in the manager.h files which are the ones
//that peform
//the transactions on the accounts in the files. we read from using a tree for
//the accounts
//and using a queue for the actions to perform.
//------------------------------------------------------------------------------
#include "Manager.h"
#include "Action.h"
#include "BSTree.h"
#include "Account.h"
//construts new manager object
Manager::Manager()
{
    //Objects are initialized using their class
}
//------------------------------------------------------------------------------
//clears data in a manager object.
Manager::~Manager()
{
    //manager object including the tree and queue goes out of scope after
    //compile
}
//------------------------------------------------------------------------------
//runs the process of performing transactions.
void Manager::runQueue()
{
    //calls perform using a loop to dequeue
    while(!action.empty())
    {
        action.front()->perform(tree);
        action.pop();
    }
}
//------------------------------------------------------------------------------
//retrieves the data of the accounts using a BST
void Manager::buildTree(ifstream& accounts)
{
    Account* info; //creating an object for the information
    bool successfulRead = false;
    bool success = false;                           // successfully insert
    for (;;) {
       info = new Account;
       successfulRead = info->setAccountData(accounts); // setting the data of
       if (accounts.eof()) {                           //accounts
          delete info;
          info = nullptr;
          break;
       }

       // insert good data into the list, otherwise ignore it
       if (successfulRead) {
           success = tree.insert(info);  //inserting into the tree if the read
       }                                 //was successful
       else {
          delete info;
       }
       if (!success) break;
    }
}
//------------------------------------------------------------------------------
//retrieves the data of the actions to perform using a Queue
void Manager::buildQueue(ifstream& actions)
{
    Action* info;
    bool successfulRead = false;                    // read good data
    bool success = false;                           // successfully insert
    for (;;) {
       info = new Action;
       successfulRead = info->setActionData(actions); // setting the data of
       if (actions.eof()) {                           //accounts
          delete info;
          info = nullptr;
          break;
       }

       // insert good data into the list, otherwise ignore it
       if (successfulRead) {
           action.push(info);            //inserting into the queue if the read
           
           if(action.back() == info)
               success = true;              //was successful
       }
       else {
           delete info;
       }
    }
}
//------------------------------------------------------------------------------
//prints the information at the end of the day.
void Manager::printEndOfDayReport()
{
    tree.display();
}




