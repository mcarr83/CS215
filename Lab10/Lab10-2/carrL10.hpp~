/*********************************************************************
* Assignment: Lab 10 - Singly Linked List implementation             *
* Author: Michael Carr                                               *
* Date: Spring 2018                                                  *
* File: LList.hpp                                                      *
*                                                                    *
* Description: This file contains the implementations for a Templated*
* Linked List.                                                       *
*********************************************************************/

#ifndef LLIST_HPP
#define LLIST_HPP

#include <iostream>
using namespace std;

enum dtype { FORWARD, BACKWARDS };

template <class LT> class LList;
template <class LT> ostream & operator << (ostream & outs, const LList<LT> & L);
/*********************************************************************
* Class: LList                                                       *
*                                                                    *
* Description: This class is designed to have have a struct used as  *
* node to gather data. Also all the implementations to link list     *
* together.                                                          *
*********************************************************************/
template <class LT>
class LList
{
   private:
      struct LNode
      {
         LNode ();
         LT data;
	void PrintNode (ostream & output);
         LNode * next;
      };
   public:
      LList ();
      LList (const LList & other);
      ~LList ();
      LList & operator = (const LList & other);
      bool operator == (const LList & other);
      int Size () const;
  void SetDirection (dtype);
  dtype GetDirection () const;
  friend ostream & operator << <> (ostream & outs, const LList & L);
  bool InsertFirst (const LT & value);
      bool InsertLast (const LT & value);
      bool DeleteFirst ();
      bool DeleteLast ();
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
LList<LT>::LNode::LNode ()
{ 
  next = NULL;
}

/*******************************************************************************
* Function: Print Node Function                                                *
*                                                                              *
* Parameters:output stream                                                     *
* Return value: none                                                           *
* Description: This function will print the data inside each node              *
*******************************************************************************/

template <class LT>
void LList<LT>::LNode::PrintNode (ostream & output){
  if (next != NULL)
    next->PrintNode (output);

  if (next != NULL)
    output << ' ';

  output << data;
  
}

/*******************************************************************************
* Function: Default constructor for LList class                                *
*                                                                              *
* Parameters: none                                                             *
* Return value: none                                                           *
* Description: This function will initialize values for the LList class        *
*******************************************************************************/
template <class LT>
LList<LT>::LList ()
{
  size = 0;     //sets size to 0
  first = NULL; //sets first pointer to NULL
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
LList<LT>::LList (const LList & other)
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
LList<LT>::~LList ()
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
LList<LT> & LList<LT>::operator = (const LList & other)
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
bool LList<LT>::operator == (const LList & other)
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
int LList<LT>::Size () const
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
void LList<LT>::SetDirection (dtype dir){

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
dtype LList<LT>::GetDirection () const{

  return direction;

}


/*********************************************************************
* Function: Output Operator                                          *
*                                                                    *
* Parameters: output stream & L                                      *
* Return value: outs                                                 *
* Description: This function will create a new node, set itself to   *
* LList first, until the new node hits NULL print, return outs       *
*********************************************************************/
template <class LT>
ostream & operator << (ostream & outs, const LList<LT> & L)
{ 
  if (L.first == NULL)
    return outs;
  if (L.direction == FORWARD){ //Prints forward
    outs << L.first->data;   //Prints first data
    typename LList<LT>::LNode * n;  //creates new LNode pointer n
    for (n = L.first->next; n != NULL; n = n->next)  //transverses LList
      outs << ' ' << n->data;    //printing a space followed by the data
    }
  else   //printing backwards
    {
      L.first->PrintNode(outs);
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
bool LList<LT>::InsertFirst (const LT & value)
{ 
  LNode * nnp = new LNode; //allocate space for new node
  if (nnp == NULL)     //if space can not be allocated return false
    return false;      
  nnp -> data = value; // set the data of the new node to the input value
  nnp -> next = first; //set the next of the new node to the current first
  if (first == NULL)   //if needed set the last of the list to contain the address of the new node
    last = nnp;        
  first = nnp;         //set the first of the list to contain the address of the new node
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
bool LList<LT>::InsertLast (const LT & value)
{ 
  if (size == 0)       // If the list is empty call insert first to start building from the beginning
    return InsertFirst(value);

  LNode * nnp = new LNode; //Allocate space for new node
  if (nnp == NULL)     //if space can not be allocated return false
    return false;
  nnp->data = value;   //set data of new node to value
  last-> next = nnp;   //set next of the current last node to the new node
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
bool LList<LT>::DeleteFirst ()
{ 
  
  if (first == NULL || size == 0)  //If first is NULL or size is 0, return false.
    return false;
  LNode * nnp = first;  //make new variable point and point to the current first.
  first = first -> next;    //make current first nodes next equal the next node (2nd one) as first 
  if (size == 1)            //if size equals 1 last equals NULL
    last = NULL;;
  delete nnp;               //delete the nnp
  size--;                   //decrease size by one
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
bool LList<LT>::DeleteLast ()
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

#endif
