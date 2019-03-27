/*********************************************************************
* Assignment: Lab 10 - Singly Linked List implementation             *
* Author: Michael Carr                                               *
* Date: Spring 2018                                                  *
* File: LList.h                                                      *
*                                                                    *
* Description: This file contains the implementations for a Linked   *
* List.                                                              *
*********************************************************************/

#ifndef LLIST_H
#define LLIST_H
#include <iostream>

using namespace std;

/*********************************************************************
* Class: LList                                                       *
*                                                                    *
* Description: This class is designed to have have a struct used as  *
* node to gather data. Also all the implementations to link list     *
* together.                                                          *
*********************************************************************/

class LList
{
   private:
      struct LNode
      {
         LNode ();
         int data;
         LNode * next;
      };
   public:
      LList ();
      LList (const LList & other);
      ~LList ();
      LList & operator = (const LList & other);
      bool operator == (const LList & other);
      int Size () const;
      friend ostream & operator << (ostream & outs, const LList & L);
      bool InsertFirst (const int & value);
      bool InsertLast (const int & value);
      bool DeleteFirst ();
      bool DeleteLast ();
   private:
      LNode * first;
      LNode * last;
      int size;
};

#endif
