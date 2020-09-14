//-----------------------------------------------------------------------------

//this file implements the methods from the action.h file. This file mainly
//has the perform method for the different transactions from the file.
//Also incudes getters for the different data that is needed in other
//methods in the account class.

//-----------------------------------------------------------------------------

#include "Action.h"
#include "BSTree.h"
#include <iomanip>

//prints the outcome after the the transactions
ostream& operator<<(ostream& os, const Action& action)
{
    switch (action.action)
    {
        case 'D': //action, amount, into account name using getAccountNumber m.
            os << action.getActionName() << setw(5)<< "$" <<setw(7)
            << action.amount
            <<" into "<<action.accountNames[action.getAccountNumber()]
            << endl;
            break;
            
        case 'W':
            os << action.getActionName() <<setw(4)<< "$" <<setw(7)
            << action.amount
            <<" from "<<action.accountNames[action.getAccountNumber()]
            << endl;
            break;
            
        case 'M':
            os << action.getActionName() <<setw(8)<< "$" <<setw(7)
            << action.amount
            <<" from "<<action.accountNames[action.getAccountNumber()]
            <<" to " << action.accountNames[action.getAccountNumber2()]
            <<" for client " << action.Id2
            << endl;
            break;
            
        case 'H':
            os<<"History" <<endl;
            break;
            
        default:
            cout<<"incorrect action" << endl;
    }
    return os;
}
//------------------------------------------------------------------------------
Action::Action()
{
    action = '#';
    Id = -1;
    amount = -1;
    Id2 = -1;
    
    accountNames[0] = "Money Market";
    accountNames[1] = "Prime Money Market";
    accountNames[2] = "Long-Term Bond";
    accountNames[3] = "Short-Term Bond";
    accountNames[4] = "500 Index Fund";
    accountNames[5] = "Capital Value Fund";
    accountNames[6] = "Growth Equity Fund";
    accountNames[7] = "Growth Index Fund";
    accountNames[8] = "Value Fund";
    accountNames[9] = "Value Stock Index";
}
//------------------------------------------------------------------------------
void Action::perform(const BSTree& data)
{
    //instantiating an account with the given Id to find it from
    //the tree. getting the actual Id.
    int realID = Id;
    if(action != 'H')
        realID = Id/10;
    
    Account target(realID), *hold;
    bool found = data.retrieve(target, hold);
        
    //based on the letter of the action, we go to that method to perform
    //the givn action.
    if(found)
    {
        //if the action was 'M' we create another object and have a special case.
        if(action == 'M')
        {      //creating another account to move to and retrieving it from
               //the tree.
            int realID2 = Id2/10;
            Account moving(realID2), *moveTo;
            bool found2 = data.retrieve(moving, moveTo);
            
            if(found2)
                //going to move in account to move amount from Id1 to Id2
                hold->move(amount, getAccountNumber(), getAccountNumber2(),
                moveTo, this);
            else
            {
                cout<<"Unkown client ID "<<realID2 <<" or "<<realID
                << " requested" << endl;
                delete this;
            }
            
            return;
        }
        
        switch (action)
        {
            case 'D':
                hold->deposit(amount, getAccountNumber(), this);
                break;
                
            case 'W':
                hold->withdraw(amount, getAccountNumber(), this);
                break;
                
            case 'H':
                hold->displayHistory(this);
                break;

            default:
                cout<<"ERROR: " << action << " Incorrect Input." << endl;
                delete this;
                break;
        }
    }
    else
    {
        cout << "Unkown client ID "<< realID << " requested." << endl;
        delete this;
    }
}
//------------------------------------------------------------------------------
//gets the name of the action (transaction) based on the letter
string Action::getActionName() const
{
    string str;
    
    switch(action) //for printing the history of the client.
    {
        case 'D':
            str = "Deposit";
            break;
            
        case 'W':
            str = "Withdraw";
            break;
        
        case 'M':
            str = "Move";
            break;
            
        case 'H':
            str = "History";
            break;
    }
    
    return str;
}
//------------------------------------------------------------------------------
bool Action::setActionData(ifstream& info)
{
    info >> action;
    
    if(action == 'H')
    {
        info>> Id;
        return Id >= 0 && Id < 10000; //Id for history won't have a fifth num.
    }
    else if(action == 'W' || action == 'D')
    {
        info>> Id >> amount;
        return Id >= 0 && Id < 100000 && amount >= 0;
    }
    
   
    //if the action is M, there is an extra amount.
    else if(action == 'M')
    {
        info>> Id >> amount >> Id2;
        return Id >= 0 && Id < 100000 && amount >= 0 &&
               Id2 >= 0 && Id2 < 100000;
    }
    
    else
    {//When the letter is none of the above, we use getline to get to the
     //line and then returning false.
        string s;
        getline(info, s, '\n');
        return false;
    }
}
//------------------------------------------------------------------------------
int Action::getAccountNumber() const
{
    return Id % 10;
}
//------------------------------------------------------------------------------
string Action::getAccountName() const
{
    return accountNames[getAccountNumber()]; //gets the name of the account
                                             //using accountNames
}
//------------------------------------------------------------------------------
int Action::getAccountNumber2() const
{
    return Id2 % 10; //for second Id number if the action is move.
                     //Could have used parameter for the first method
                     //but decided to make another method due to
                     //quicker judgement.
}


