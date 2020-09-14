#include "BSTree.h"
//------------------------------------------------------------------------------
//This class implements the BST methods in the .h files. There is a constructor
//and a destructor as well as the insert retrieve methods with the empty
//and display methods and their helper functions.
//------------------------------------------------------------------------------


BSTree::BSTree()
{
    root = nullptr;
}
//------------------------------------------------------------------------------
BSTree::~BSTree()
{
    makeEmpty();
}
//------------------------------------------------------------------------------
bool BSTree::insert(Account*& info) {
   Node* ptr = new Node;
   if (ptr == NULL) return false;            // out of memory
   ptr->data = info;
   ptr->left = ptr->right = NULL;
   if (isEmpty()) {
      root = ptr;
   }
   else {
      Node* current = root;                           // walking pointer
      bool inserted = false;                          // whether inserted yet

      // if item is less than current item, insert in left subtree,
      // otherwise insert in right subtree
      while (!inserted) {
         if (*ptr->data < *current->data) {
            if (current->left == NULL) {              // insert left
               current->left = ptr;
               inserted = true;
            }
            else
               current = current->left;               // one step left
         }
         else {
            if (current->right == NULL) {             // insert right
               current->right = ptr;
               inserted = true;
            }
            else
               current = current->right;              // one step right
         }
      }
   }
   return true;
}
//------------------------------------------------------------------------------
bool BSTree::retrieve(const Account& target, Account*& hold) const
{
    return retrieveHelper(target, hold, root);
}
//------------------------------------------------------------------------------
bool BSTree::retrieveHelper(const Account& t, Account*& h, Node* cur) const
{
    if(cur == nullptr)
        return false;

   else if(t < *cur->data)
        return retrieveHelper(t, h, cur->left);

   else if(t > *cur->data)
        return retrieveHelper(t, h, cur->right);

    //when it is equal we set the holding pointer to the target
    h = cur->data;

    return true;

}
//------------------------------------------------------------------------------
void BSTree::makeEmpty()
{
    makeEmptyHelper(root);
}
//------------------------------------------------------------------------------
void BSTree::makeEmptyHelper(Node* cur)
{
    if(cur == nullptr)
    return;
    
    makeEmptyHelper(cur->left);  //recursing both sides then deleting
    makeEmptyHelper(cur->right); //data and the actual node and setting to
                                 //nullptr
    delete cur->data;
    cur->data = nullptr;
    
    delete cur;
    cur = nullptr;
    
    
    
}
//------------------------------------------------------------------------------
void BSTree::display() const
{
    displayHelper(root);
}
//------------------------------------------------------------------------------
void BSTree::displayHelper(Node* cur) const
{
    
    if(cur->left != nullptr) //traversing left to go to smallest account
        displayHelper(cur->left);
    
    cout << *cur->data << endl; //printing then recursing right
    
    if(cur->right != nullptr)
        displayHelper(cur->right);
}
//------------------------------------------------------------------------------
bool BSTree::isEmpty() const
{
    return root == nullptr;
}

