#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <fstream>
#include <string.h>
#include <vector>
class Action;


using namespace std;

//--------------------------------------------------------------------------
// Account class:
//   -- holds the primary information of the account
//   -- calls for transactions
//   -- displays account's transaction history
//
// Implementation and assumptions:
//   -- Maximum account of client has is 10 accounts
//   -- listLOSE index present for each section bellow
//      0: Money Market         5: Capital Value Fund
//      1: Prime Money Market   6: Growth Equity Fund
//      2: Long-Term Bond       7: Growth Index Fund
//      3: Short-Term Bond      8: Value Fund
//      4: 500 Index Fund       9: Value Stock Index
//
//   -- Account ID is limited, cannot exceed 9999
//
//--------------------------------------------------------------------------

const int MAXID = 9999;
const int MAXACCOUNT = 10;

class Account {
    // display client information
    friend ostream& operator<<(ostream &, const Account&);
public:
    public:
    // initialize account information
    Account();
    ~Account();
    Account(int);
    Account& operator=(const Account&);

    int getAccountNumber();  // get account ID number
    
    //Action methods*************
    //deposit:
    void deposit(int, int, Action*);
    //withdraw
    void withdraw(int, int, Action*);
    //move
    void move(int, int, int, Account*, Action*);
    //display
    void displayHistory(Action*);
    //setData to take in file. is called in buildTree and will fill up the
    //accounts
    bool setAccountData(ifstream&);
    
    // comparison operators
    bool operator<(const Account&) const;
    bool operator>(const Account&) const;
    bool operator==(const Account&) const;
    bool operator!=(const Account&) const;

private:
    string firstName;
    string lastName;
    int iD;
    int accounts[MAXACCOUNT];
    int finalBalances[MAXACCOUNT];
    vector <Action*> HistoryList;
};

#endif /* ACCOUNT_H */
