//
//  main.cpp
//  Assignment5
//
//  Created by Harvy Barsoom on 5/24/20.
//  Copyright © 2020 Harvy Barsoom. All rights reserved.
//

#include <iostream>
#include "Account.h"
#include "Action.h"
#include "BSTree.h"
#include "Manager.h"
#include <iomanip>


int main(int argc, const char * argv[]) {
    
    
//manager object used to build tree
    Manager m;

    ifstream accountInfo("lab5data.txt"), actionInfo("lab5command.txt");

    m.buildTree(accountInfo);
    m.buildQueue(actionInfo);

    m.runQueue();
    m.printEndOfDayReport();
    
    return 0;
}
