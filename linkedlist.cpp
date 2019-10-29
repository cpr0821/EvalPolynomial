//cpr170030
//Camryn Rogers
#include "linkedlist.h"
#include "node.h"
#include <string>
#include <iomanip>
#include <iostream>

using namespace std;

linkedlist::linkedlist()
{
   //constructor
}

linkedlist::~linkedlist()
{
   //destructor
}

void linkedlist::insertnode(node& newNode)
{

   //If node being inserted is a lower degree than the current one, it goes at the end of the list

      if (newNode.getexpon() < head->getexpon() || newNode.getexpon() == 0)
      {
      node* last = head;

         while (last->next != nullptr)
         {
            last = last->next;
         }
      last->next = &newNode;

      newNode.next = nullptr;
      }
      // Else it goes to the beginning
      else
      {
         head->setsign ("+"); //fix
         newNode.next = head;
         head = &newNode;
      }

}


// Overloading operator to print out LL
ostream& operator<<(ostream& os, const linkedlist& LL)
{
//Start at head of list
 node* nodeofint = LL.head;
 //Go through list
   while (nodeofint != nullptr)
   {
   double exponent = nodeofint->getexpon();
   double coefficient = nodeofint->getcoeff();
   string sign = nodeofint->getsign();

   // If the term has a sign print it out
   if (sign != "x")
      os << " " << sign << " ";
   // If the term has a coefficient that's not 1 print it
   if (coefficient > 0 && coefficient != 1)
      os << coefficient;
   // If the term has an exponent greater than 1, print it
   if (exponent > 0)
      os << "x^" << exponent;
   // Go to next node
   nodeofint = nodeofint->next;
   }
    return os;
}



