//-----------------------------------------------------------------------------

//This file includes the implementation of the Account.h file. It includes
//th data of the client as in the Id, name and accounts owned by them.
//this is where the actual transactions are performed which are called
//from the action class. Has one getter for the account number which
//differs from the account number in Action.

//-----------------------------------------------------------------------------
#include "Account.h"
#include "Action.h"
#include <iomanip>

ostream& operator<<(ostream& os, const Account& acc)
{
    //printing the account information.
    os << endl;
    os <<endl<<acc.iD << " " << acc.firstName << " " << acc.lastName << endl;
    
    os << "Initial Balances: ";
    for(int i = 0; i < MAXACCOUNT; i++) //printing the initial and final balances
    {
        os<< setw(6) << acc.accounts[i];
    }
    os<<endl;
    os << "Final Balances:   ";
    for(int i = 0; i < MAXACCOUNT; i++)
    {
        os<< setw(6) << acc.finalBalances[i];
    }
    
    return os;
}
//------------------------------------------------------------------------------
//constructs new account object
Account::Account()
{    
    firstName = "NO FNAME";
    lastName = "NO LNAME";
    iD = 0;
    
    for(int i = 0; i < MAXACCOUNT; i++)
        accounts[i] = -1;
    
    for(int i = 0; i < MAXACCOUNT; i++)
    finalBalances[i] = -1;
    
}
//------------------------------------------------------------------------------
Account::~Account()
{
    for(int i = 0 ; i < HistoryList.size(); i++)
    {
        delete HistoryList[i]; //deleting the object and freeing it.
        HistoryList[i] = nullptr;
    }
}
//------------------------------------------------------------------------------
Account::Account(int val)
{
    iD = val; //for when we want to perform, we create an account
              //with only an Id
}
//------------------------------------------------------------------------------
//operator= for assiging accounts.
Account& Account::operator=(const Account& Account)
{
   if (this != &Account)
   {
      this->iD = Account.iD;
      this->firstName = Account.firstName;
      this->lastName = Account.lastName;
      this->HistoryList = Account.HistoryList;

      for(int i = 0; i < MAXACCOUNT; i++)
         this->accounts[i] = Account.accounts[i];
       
      for(int i = 0; i < MAXACCOUNT; i++)
         this->finalBalances[i] = Account.finalBalances[i];
   }
   return *this;
}
//------------------------------------------------------------------------------
int Account::getAccountNumber()
{
    return iD % 10; //returns the last digit telling us which account to
                    //perform transaction on.
}
//------------------------------------------------------------------------------
//deposits amount into account
void Account::deposit(int amount, int accNum, Action* ac)
{
    finalBalances[accNum] += amount; //adding the amount to the
                                     //the account number
    HistoryList.push_back(ac);       //adding the actions to HistoryList
}
//------------------------------------------------------------------------------
//withdraws amount from account
void Account::withdraw(int amount, int accNum, Action* ac)
{
    //cases for money markets and bond markets
    //When it's a money market and the amount in the other money
    //market is greater than the amount needed to withdraw so it
    //isn't negative, we take from that money market and
    //add it to the other money market.
    
    
    if(amount > finalBalances[accNum] &&
       ac->getAccountName() == "Prime Money Market" &&
       finalBalances[accNum-1] >= amount - finalBalances[accNum])
    {
        finalBalances[accNum-1] -= amount - finalBalances[accNum];
        finalBalances[accNum] += amount - finalBalances[accNum];

        finalBalances[accNum] -= amount;
        HistoryList.push_back(ac);
    }
    else  if(amount > finalBalances[accNum] &&
          ac->getAccountName() == "Money Market" &&
          finalBalances[accNum+1] >= amount - finalBalances[accNum])
       {
           finalBalances[accNum+1] -= amount - finalBalances[accNum];
           finalBalances[accNum] += amount - finalBalances[accNum];

           finalBalances[accNum] -= amount;
           HistoryList.push_back(ac);
       }
    else  if(amount > finalBalances[accNum] &&
          ac->getAccountName() == "Short-Term Bond" &&
          finalBalances[accNum-1] >= amount - finalBalances[accNum])
       {
           finalBalances[accNum-1] -= amount - finalBalances[accNum];
           finalBalances[accNum] += amount - finalBalances[accNum];

           finalBalances[accNum] -= amount;
           HistoryList.push_back(ac);
       }
    else  if(amount > finalBalances[accNum] &&
          ac->getAccountName() == "Long-Term Bond" &&
          finalBalances[accNum+1] >= amount - finalBalances[accNum])
       {
           finalBalances[accNum+1] -= amount - finalBalances[accNum];
           finalBalances[accNum] += amount - finalBalances[accNum];

           finalBalances[accNum] -= amount;
           HistoryList.push_back(ac);
       }
    
    else if(finalBalances[accNum] >= amount)  //checking if the amount
    {
        finalBalances[accNum] -= amount; //is less than the money
        HistoryList.push_back(ac);       //and subtracting if so
    }
                                         
    else
    {
        cout<<"Unable to withdraw from " << ac->getAccountName()
        << " of " << firstName << " " << lastName
        << " due to insufficent funds. " << endl;
        delete ac; //this is an object that won't be added to the
        ac = nullptr; //historyList so it should be deleted here.
    }
}
//------------------------------------------------------------------------------
//moves amount from one account to another account
void Account::move(int amount, int accFrom, int to, Account* account, Action* ac)
{
    //check for account names and withdraw limit.
    if(finalBalances[accFrom] >= amount)
    {
        finalBalances[accFrom] -= amount;
        account->finalBalances[to] += amount;
        HistoryList.push_back(ac);
    }
    else
    {
        cout<<"Unable to move money from " << ac->getAccountName()
        << " of " << firstName << " " << lastName
        << " due to insufficent funds. " << endl;
        delete ac; //this is an object that won't be added to the
        ac = nullptr; //historyList so it should be deleted here.
    }
}
//------------------------------------------------------------------------------
//displayling history of client using vector.
void Account::displayHistory(Action* ac)
{
    HistoryList.push_back(ac);  //adding the display action to HL so it is
    cout<<endl;                 //printed during the loop.
    cout<<endl;
    cout<< "History of transactions for client " << firstName << " " <<
    lastName << ", Client ID = " <<iD << endl;
    cout<< "Type " <<  setw(12) << "Amount " << setw(9) << "Detail" << endl;
    cout<< "---------" << " " << "---------" << " " << "-----------------"
    <<endl;
    for(int i = 0; i < HistoryList.size(); i++)
    {
        cout<<*HistoryList[i]; //printing the action object
    }
}
//------------------------------------------------------------------------------
//setting the client's info from the file.
bool Account::setAccountData(ifstream& account)
{
    account >> lastName >> firstName >> iD;
    bool valid = true;
    
    for(int i = 0; i < MAXACCOUNT; i++)
    {
        account >> accounts[i]; //looping through the array of accounts.
        valid = accounts[i] >= 0;
        finalBalances[i] = accounts[i];  //setting both the accounts and
    }                                    //finalBalances so the actions are
                                         //on finalBalances.
    
    return iD >= 0 && valid;
}
//------------------------------------------------------------------------------
bool Account::operator<(const Account& acc) const
{
    return iD < acc.iD; //when less than
}
//------------------------------------------------------------------------------
bool Account::operator>(const Account& acc) const
{
    return iD > acc.iD; //when greater than
}
//------------------------------------------------------------------------------
bool Account::operator==(const Account& acc) const
{
    return this->iD == acc.iD; //when equal
}
//------------------------------------------------------------------------------
bool Account::operator!=(const Account& acc) const
{
    return this->iD != acc.iD; //when not equal
}







