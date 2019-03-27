/*********************************************************************
* Assignment: Lab 13 - Indexing and Exception Handling               *
* Author: Michael Carr                                               *
* Date: Spring 2018                                                  *
* File: LList2.hpp                                                   *
*                                                                    *
* Description: This file contains the implementations for a Templated*
* Linked List.                                                       *
*********************************************************************/

#ifndef LLIST_HPP
#define LLIST_HPP

#include <iostream>
using namespace std;

enum dtype { FORWARD, BACKWARD };

template <class LT> class LList2;
template <class LT> ostream & operator << (ostream & outs, const LList2<LT> & L);
/*********************************************************************
* Class: LList                                                       *
*                                                                    *
* Description: This class is designed to have have a struct used as  *
* node to gather data. Also all the implementations to link list     *
* together.                                                          *
*********************************************************************/
template <class LT>
class LList2
{
   private:
      struct LNode
      {
	LNode ();
	LT data;
	LNode * next;
	LNode * prev;
      };
   public:
  class Iterator{
  public:
    Iterator();
    Iterator (LNode * NP);
    LT & operator * () const;
    Iterator operator ++ ();
    Iterator operator ++ (int);
    Iterator operator -- ();
    Iterator operator -- (int);
    bool operator == (const Iterator & other) const;
    bool operator != (const Iterator & other) const;

  private:
    LNode * current;

  };
  
  LList2 ();
      LList2 (const LList2 & other);
      ~LList2 ();
      LList2 & operator = (const LList2 & other);
      bool operator == (const LList2 & other);
      int Size () const;
  void SetDirection (dtype);
  dtype GetDirection () const;
  friend ostream & operator << <> (ostream & outs, const LList2 & L);
  bool InsertFirst (const LT & value);
      bool InsertLast (const LT & value);
      bool DeleteFirst ();
      bool DeleteLast ();
  void Forward (void function (const LT & param));
  void Backward (void function (const LT & param));
  void PrintList (ostream & outs, int whichLines);
  Iterator begin() const;
  Iterator rbegin() const;
  Iterator end() const;
  Iterator rend() const;
  bool InsertAt (int position, const LT & value);
  bool DeleteAt (int position);
  LT & operator [] (const int & index) const;
 
   private:
      LNode * first;
      LNode * last;
      int size;
  dtype direction;
};


/*********************************************************************
* Assignment: Lab 10 - Singly Linked List implementation             *
* Author: Michael Carr                                               *
* Date: Spring 2018                                                  *
* File: LList.cpp                                                    *
*                                                                    *
* Description: This file contains the all functions for the Linked   *
* List class.                                                        *
*********************************************************************/



/*******************************************************************************
* Function: Default constructor for the struct                                 *
*                                                                              *
* Parameters: none                                                             *
* Return value: none                                                           *
* Description: This function will this will initialize values for the struct   *
*******************************************************************************/

template <class LT>
LList2<LT>::LNode::LNode ()
{ 
  next = NULL;
  prev = NULL;
}

/*******************************************************************************
* Function: Print Node Function                                                *
*                                                                              *
* Parameters:output stream                                                     *
* Return value: none                                                           *
* Description: This function will print the data inside each node              *
*******************************************************************************/
/*
template <class LT>
void LList2<LT>::LNode::PrintNode (ostream & output, int whichLines){
  if (1 & whichLines)
    output << data << ' ';

  if (next != NULL)
    next->PrintNode (output, whichLines);

  if (2 & whichLines)
    output << data << ' ';
  
}
*/
/*******************************************************************************
* Function: Default constructor for LList class                                *
*                                                                              *
* Parameters: none                                                             *
* Return value: none                                                           *
* Description: This function will initialize values for the LList class        *
*******************************************************************************/
template <class LT>
LList2<LT>::LList2 ()
{
  size = 0;     //sets size to 0
  first = NULL; //sets first pointer to NULL
  last = NULL; //sets last pointer initially to NULL
  direction = FORWARD;
}

/*********************************************************************
* Function: Copy Constructor                                         *
*                                                                    *
* Parameters: const LList & other                                    *
* Return value:                                                      *
* Description: This function will set size to 0 and first to NULL.   *
* For each nodes data in the other list, Insert Last will be called  *
* to input more data                                                 *
*********************************************************************/
template <class LT>
LList2<LT>::LList2 (const LList2 & other)
{ 
  size = 0;      //sets size to 0
  first = NULL;  //sets first pointer to NULL
  for (LNode * i = other.first; i != NULL; i = i->next)
    InsertLast(i->data);  //for each nodes data in other list will use
                          //InsertLast to input data into the last part of
                          //the list
  direction = other.direction;
}

/*********************************************************************
* Function: Destructor for LList                                     *
*                                                                    *
* Parameters: none                                                   *
* Return value: none                                                 *
* Description: This function will call DeleteFirst until first equals*
* NULL                                                               *
*********************************************************************/
template <class LT>
LList2<LT>::~LList2 ()
{
  if(first != NULL)
    DeleteFirst();
}

/*********************************************************************
* Function: Assignment operator                                      *
*                                                                    *
* Parameters: other                                                  *
* Return value: object pointed to this                               *
* Description: This function will check the assignment, while first  *
* doesn't equal NULL DeleteFirst is called. For each node's data in  *
* the other list, InsertLast function is called to insert data into  *
* the end of the list. Return the object pointed to by this.         *
*********************************************************************/
template <class LT>
LList2<LT> & LList2<LT>::operator = (const LList2 & other)
{ 
  if (this == &other)      //if this doesn't compare to the memory address of
                           //other return the object pointed to by this.
    return *this;
  while (first != NULL)    //while first doesn't equal NULL call DeleteFirst
    DeleteFirst();
  LNode * nnp = other.first;
  while (nnp != NULL){
    InsertLast (nnp->data);  //For each node's data in the other list, InsertLast
    nnp = nnp -> next;
  }                        //function is called to insert data into the end of
                           //the list.
  direction = other.direction;                        
  return * this;
}                          //return the object pointed to by this

/*********************************************************************
* Function: Equality Function                                        *
*                                                                    *
* Parameters: LList and other LList                                  *
* Return value: bool                                                 *
* Description: This function will determine if two LList are equal   *
*********************************************************************/
template <class LT>
bool LList2<LT>::operator == (const LList2 & other)
{ 
  if (size != other.size)
    return false;
  LNode * a = first;
  LNode * b = other.first;
  while (a != NULL){
    if (a->data != b->data)
      return false;
    a = a->next;
    b = b->next;
  }
  return true;
}

/*********************************************************************
* Function: Size Function                                            *
*                                                                    *
* Parameters: none                                                   *
* Return value: value of size                                        *
* Description: This function will return the value of size           *
*********************************************************************/
template <class LT>
int LList2<LT>::Size () const
{ 
	return size;
}

/*********************************************************************
* Function: Set Direction Function                                   *
*                                                                    *
* Parameters: enum dir                                               *
* Return value: none                                                 *
* Description: This function will set dir to direction to be used    *
* later when transversing forward or backwards                       *
*********************************************************************/

template <class LT>
void LList2<LT>::SetDirection (dtype dir){

  direction = dir;
}

/*********************************************************************
* Function: Get Direction Function                                   *
*                                                                    *
* Parameters: none                                                   *
* Return value: direction                                            *
* Description: This function will return direction                   *
*********************************************************************/

template <class LT>
dtype LList2<LT>::GetDirection () const{

  return direction;

}


/*********************************************************************
* Function: Output Operator                                          *
*                                                                    *
* Parameters: output stream & L                                      *
* Return value: outs                                                 *
* Description: This function will output a node                      *
*********************************************************************/
template <class LT>
ostream & operator << (ostream & outs, const LList2<LT> & L)
{ 
  if (L.first == NULL)
    return outs;
  if (L.direction == FORWARD){ //Prints forward
    outs << L.first->data;   //Prints first data
    typename LList2<LT>::LNode * n;  //creates new LNode pointer n
    for (n = L.first->next; n != NULL; n = n->next)  //transverses LList
      outs << ' ' << n->data;    //printing a space followed by the data
    }
  else   //printing backwards
    {
      outs << L.last->data;
      typename LList2<LT>::LNode * n;
      for (n = L.last->prev; n != NULL; n = n->prev)
	outs << ' ' << n->data;      
    }

    return outs;
}

/*********************************************************************
* Function: Insert First Function                                    *
*                                                                    *
* Parameters: value                                                  *
* Return value: bool                                                 *
* Description: This function will create space for new node, if new  *
* node space cant be allocated return false. If space can be, set    *
* new node data to value and new node next to first. If needed set  *
* the last of the list to contain the address of the new node. Set  *
* the first of the list to contain the address of the new node.     *
* Increase size and then return false.                              *
*********************************************************************/

template <class LT>
bool LList2<LT>::InsertFirst (const LT & value)
{ 
  LNode * nnp = new LNode; //allocate space for new node
  if (nnp == NULL)     //if space can not be allocated return false
    return false;      
  nnp -> data = value; // set the data of the new node to the input value
  nnp -> next = first; //set the next of the new node to the current first

  if (first == NULL)   //if needed set the last of the list to contain the address of the new node
    last = nnp;        
  else
    first->prev = nnp;         //set the first of the list to contain the address of the new node
  first = nnp;
  size++;              //increment size
  return true;         //return true
}

/*********************************************************************
* Function: Insert Last Function                                     *
*                                                                    *
* Parameters: value                                                  *
* Return value: bool                                                 *
* Description: This function will determine if list is empty or not, *
* if list is empty it will call InsertFirst function else continue   *
* on. Allocate space for new Node, if not return false. Set data of  *
* of new node to value, set next of the current last node to the new *
* node. Set the last of the list to contain the address of the new   * 
* node, increase size by 1. Return true.                             *
*********************************************************************/

template <class LT>
bool LList2<LT>::InsertLast (const LT & value)
{ 
  if (size == 0)       // If the list is empty call insert first to start building from the beginning
    return InsertFirst(value);

  LNode * nnp = new LNode; //Allocate space for new node
  if (nnp == NULL)     //if space can not be allocated return false
    return false;
  nnp->data = value;   //set data of new node to value
  last-> next = nnp;  //set next of the current last node to the new node
  nnp->prev = last;   // sets last to nnp prev
  last = nnp;          //set the last of the list to contain the address of the new node
  size++;              //increment the size of the list
  return true;
    
}

/*********************************************************************
* Function: Delete First Function                                    *
*                                                                    *
* Parameters: none                                                   *
* Return value: bool                                                 *
* Description: This function will determine if first is NULL or size *
* is zero. Make current first nodes next equal the next node         *
* (2nd one) as first. If size equals 1 last equals NULL. Delete the  *
* temp variable and decrease size by one. Return true.               *
*********************************************************************/

template <class LT>
bool LList2<LT>::DeleteFirst ()
{ 
  
  if (first == NULL || size == 0)  //If first is NULL or size is 0, return false.
    return false;
  LNode * nnp = first;  //make new variable point and point to the current first.
  first = nnp-> next;    //make current first nodes next equal the next node (2nd one) as first 
  if (first != NULL)
    first->prev = NULL;
  delete nnp;             //delete the nnp
  size--;                 //decrease size by one
  if (size == 0)          //if size equals 0 last equals NULL
    last = NULL;;
                 
                   
  return true;              //return true
  
  
}


/*********************************************************************
* Function: Delete Last Function                                     *
*                                                                    *
* Parameters: none                                                   *
* Return value: bool                                                 *
* Description: This function will delete the last node in the linked *
* list. First it will check if first is NULL or size is 0. If size   *
* is 1, return DeleteFirst function. Create new node pointer set to  *
* first than tranverse the linked list to find the second to last    * 
* node then save th epointer to the second to last node. Second to   *
* last next will be set to NULL. Delete last, set last to nnp,       *
* decrease size by one and return false.                             *
*********************************************************************/

template <class LT>
bool LList2<LT>::DeleteLast ()
{ 
  if (first == NULL || size == 0) //if first = NULL or size == 0 return false
    return false;
  if (size == 1)                  //if size == 1 call DeleteFirst function
    return DeleteFirst();
  LNode * nnp = first;        //make new nnp node and set it to first
  while (nnp->next != last)   //while nnp node next doesn't equal last value keep going to second to last
    nnp = nnp->next;      //save the pointer to the last node in npp 
  nnp->next = NULL;       //change the next of the 2nd to last to NULL
  delete last;            //delete the node that was last
  last = nnp;             //change last to the second to last
  size--;                 //decrease size by one
  return true;            //return true
}

/*********************************************************************
* Function: Print List Function                                      *
*                                                                    *
* Parameters: outstream and integer whichLines                       *
* Return value: none                                                 *
* Description:                                                       *
*********************************************************************/
template <class LT>
void LList2<LT>::PrintList (ostream & outs, int whichLines){

  if (first != NULL)
    first->PrintNode (outs, whichLines);

}


/*********************************************************************
* Function: Foward Function                                          *
*                                                                    *
* Parameters: void Function                                          *
* Return value: none                                                 *
* Description:                                                       *
*********************************************************************/
template <class LT>

void LList2<LT>::Forward (void function (const LT & param))
{
  for (LNode * n = first; n; n = n->next)
    function (n->data);
}
/*********************************************************************
* Function: Backward Function                                        *
*                                                                    *
* Parameters: void Function                                          *
* Return value: none                                                 *
* Description:                                                       *
*********************************************************************/
template <class LT>
void LList2<LT>::Backward (void function (const LT & param))
{
  for (LNode * n = last; n; n = n->prev)
    function (n->data);
}

/*********************************************************************
* Function: Iterator Default Constructor                             *
*                                                                    *
* Parameters: none                                                   *
* Return value: none                                                 *
* Description: Initializes current to NULL                           *
*********************************************************************/

template <class LT>
LList2<LT>::Iterator::Iterator(){

  current = NULL;

}


/*********************************************************************
* Function: Iterator Copy Constructor                                *
*                                                                    *
* Parameters: pointer NP                                             *
* Return value: none                                                 *
* Description: Sets NP to current                                    *
*********************************************************************/

template <class LT>
LList2<LT>::Iterator::Iterator(LNode * NP){

  current = NP;
  
}

/*********************************************************************
* Function: Dereference Operator Function                            *
*                                                                    *
* Parameters: none                                                   *
* Return value: currents data value                                  *
* Description:                                                       *
*********************************************************************/

template <class LT>
LT & LList2<LT>::Iterator::operator * () const{

  try{
    if (current == NULL)
      throw ("Cannot dereference a NULL pointer");
  return current->data;
  }
  catch (const char * message){
    cerr << message << endl;
    exit(1);
  }
  
  
}

/*********************************************************************
* Function: Iterator ++ Function                                     *
*                                                                    *
* Parameters: none                                                   *
* Return value: pointer of this                                      *
* Description:                                                       *
*********************************************************************/

template <class LT>
typename LList2<LT>::Iterator LList2<LT>::Iterator::operator ++ (){

  try {
    if (current == NULL)
      throw ("Cannot post-increment a NULL pointer");
  current = current->next;
  return *this;
  }
  catch (const char * message){
    cerr << message << endl;
    exit(2);
  }

  
}

/*********************************************************************
* Function: Iterator ++ Function (int)                               *
*                                                                    *
* Parameters: integer                                                *
* Return value: temp                                                 *
* Description:                                                       *
*********************************************************************/

template <class LT>
typename LList2<LT>::Iterator LList2<LT>::Iterator::operator ++ (int){

  Iterator temp = *this;
  try {
    if (current == NULL)
      throw ("Cannot post-increment a NULL pointer");
  current = current->next;
  return temp;
  }
  catch (const char * message){
    cerr << message << endl;
    exit(3);
  }
  

}

/*********************************************************************
* Function: Iterator -- Function                                     *
*                                                                    *
* Parameters: none                                                   *
* Return value: point to this                                        *
* Description:                                                       *
*********************************************************************/

template <class LT>
typename LList2<LT>::Iterator LList2<LT>::Iterator::operator -- (){

try {
    if (current == NULL)
      throw ("Cannot pre-increment a NULL pointer");
  current = current->prev;
  return *this;
 }
 catch (const char * message){
    cerr << message << endl;
    exit(4);
  }
}

/*********************************************************************
* Function: Iterator -- Function (int)                               *
*                                                                    *
* Parameters: int                                                    *
* Return value: temp                                                 *
* Description:                                                       *
*********************************************************************/

template <class LT>
typename LList2<LT>::Iterator LList2<LT>::Iterator::operator -- (int){
  Iterator temp = *this;
try {
    if (current == NULL)
      throw ("Cannot pre-increment a NULL pointer");
  current = current->prev;
  return temp;
 }
 catch (const char * message){
    cerr << message << endl;
    exit(5);
  }
 
}

/*********************************************************************
* Function: Iterator == Function                                     *
*                                                                    *
* Parameters: other                                                  *
* Return value: bool                                                 *
* Description:                                                       *
*********************************************************************/

template <class LT>
bool LList2<LT>::Iterator::operator == (const Iterator & other) const {

  return current == other.current;

}

/*********************************************************************
* Function: Iterator != Function                                     *
*                                                                    *
* Parameters: other                                                  *
* Return value: bool                                                 *
* Description:                                                       *
*********************************************************************/

template <class LT>
bool LList2<LT>::Iterator::operator != (const Iterator & other) const {

  return current != other.current;

}

/*********************************************************************
* Function: Iterator Begin Function (Forward)                        *
*                                                                    *
* Parameters: none                                                   *
* Return value: temp                                                 *
* Description:                                                       *
*********************************************************************/

template <class LT>
typename LList2<LT>::Iterator LList2<LT>::begin() const {

  Iterator temp(first);
  return temp;

}


/*********************************************************************
* Function: Iterator Begin Function (Backwards)                      *
*                                                                    *
* Parameters: none                                                   *
* Return value: temp                                                 *
* Description:                                                       *
*********************************************************************/

template <class LT>
typename LList2<LT>::Iterator LList2<LT>::rbegin() const {

  Iterator temp(last);
  return temp;

}


/*********************************************************************
* Function: Iterator End Function (Forward)                        *
*                                                                    *
* Parameters: none                                                   *
* Return value: temp                                                 *
* Description:                                                       *
*********************************************************************/

template <class LT>
typename LList2<LT>::Iterator LList2<LT>::end() const {

  Iterator temp;
  return temp;

}

/*********************************************************************
* Function: Iterator End Function (Backwards)                        *
*                                                                    *
* Parameters: none                                                   *
* Return value: temp                                                 *
* Description:                                                       *
*********************************************************************/

template <class LT>
typename LList2<LT>::Iterator LList2<LT>::rend() const {

  Iterator temp;
  return temp;

}

/*********************************************************************
* Function: InsertAt                                                 *
*                                                                    *
* Parameters: position, value                                        *
* Return value: bool                                                 *
* Description: Based on position number, value inserted at that      *
* place.                                                             *
*********************************************************************/
template <class LT>
bool LList2<LT>::InsertAt (int position, const LT & value){
  if (position < 1)
    return false;
  if (position > size+1)
    return false;
  if (position == 1)
    return InsertFirst(value);
  if (position == size+1)
    return InsertLast(value);
  
 

  LNode * np = new LNode;
  np->data = value;
  np->next = first;

  for (int i = 1; i < position; i++){
    np->next = np->next->next;
  }
  np->next->prev->next = np;
  np->prev = np->next->prev;
  np->next->prev = np;
  size++;
  return true;

  
  
}

/*********************************************************************
* Function: DeleteAt                                                 *
*                                                                    *
* Parameters: position                                               *
* Return value: bool                                                 *
* Description: Based on position number, value deleted at that       *
* place.                                                             *
*********************************************************************/

template <class LT>
bool LList2<LT>::DeleteAt (int position){
  if (position < 1)
    return false;
  if (position > size)
    return false;
  if (position == 1)
    return DeleteFirst();
  if (position == size)
    return DeleteLast();

 
  LNode * np = new LNode;
  np->next = first;

  for (int i = 1; i < position; i++){
    np->next = np->next->next;
  }
  np->next->next->prev = np->next->prev;
  np->next->prev->next = np->next->next;
  delete np;
  size--;
  return true;
  
}
/*********************************************************************
* Function: Function Operator []                                     *
*                                                                    *
* Parameters: index                                                  *
* Return value: reference type                                       *
* Description: Allows for subscripted expressions to be used         *
*********************************************************************/

template <class LT>
LT & LList2<LT>::operator [] (const int & index) const{
  LList2<LT>::LNode* n = first;

  try{
    if (index == size)
      throw ("Subscript out of bounds : index is too large");
    
    for (int i = 0; i < index; i++){
      n = n->next;
    }
    return n->data;
    }
    catch (const char * message){
    cerr << message << endl;
    exit(10);
    }

    
  
  try{
    if (first == NULL)
      throw ("Cannot subscript a NULL pointer");
    
    for (int i = 0; i < index; i++){
      n = n->next;
    }
    return n->data;

  }
  catch (const char * message){
    cerr << message << endl;
    exit(6);
  }
  
    try{
    if (n->next == NULL)
      throw ("Cannot subscript a NULL pointer");
    
    for (int i = 0; i < index; i++){
      n = n->next;
    }
    return n->data;

  }
  catch (const char * message){
    cerr << message << endl;
    exit(7);
  }

   try{
    if (n == NULL)
      throw ("Cannot subscript a NULL pointer");
    
    for (int i = 0; i < index; i++){
      n = n->next;
    }
    return n->data;

  }
  catch (const char * message){
    cerr << message << endl;
    exit(8);
  }

     try{
    if (size == 0)
      throw ("Cannot subscript a NULL pointer");
    
    for (int i = 0; i < index; i++){
      n = n->next;
    }
    return n->data;

  }
  catch (const char * message){
    cerr << message << endl;
    exit(9);
  }
}
#endif
