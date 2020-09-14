#ifndef Action_h
#define Action_h
#include <iostream>
#include "Account.h"
class BSTree;

using namespace std;

//--------------------------------------------------------------------------
//Description: interacts directly with the money. Using accessors and mutators on the money, and user’s information we manipulate what the info is and use it in the action class to make transactions. Has the user’s name, ID, and accounts which are store in an array.
//
//-------------------------------------------------------------------------

class Action {
    // display transaction information
    friend ostream& operator<<(ostream&, const Action&);
public:
    Action();
    
    //perform method for calls********************** (call retrieve method here or in deposit)
    void perform(const BSTree&);
    string getActionName() const;
    bool setActionData(ifstream&);
    int getAccountNumber() const;
    int getAccountNumber2() const;
    string getAccountName() const;

    
private:
    char action;
    int Id;
    int amount;
    int Id2;
    string accountNames[MAXACCOUNT];

};

#endif /* Action_h */
