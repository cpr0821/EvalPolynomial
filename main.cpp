//cpr170030
//Camryn Rogers

#include <iostream>
#include "node.h"
#include "linkedlist.h"
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

// Function prototypes
double total (linkedlist& LL, double xvalue);
string fillnode (node& newnode, string secondHalf, linkedlist& LL, string sign);


int main()
{
string wholeExpression;          // The whole expression
string firstHalf;                // The first half that has the x value
string secondHalf;               // The second half with the terms
ifstream input("poly3.txt");      // The input file
ofstream output("answers.txt");  // The output file
double index;                    // The index for cutting the expression up
double xbeg, xend;               // The indexes for getting the x value
string afterx;                   // The character after x
string sign = "x";               // The signs of the terms (x by default, means it doesn't have a sign)
string xvaluestring;                   // The x value
double xvalue;
double totalnum;                 // The evaluated expression

// If the input is readable
if(input.good())
{

   // While the file hasn't ended
   while (!input.eof())
   {
      // Create first node (head) and the linked list object
      node headnode;
      linkedlist LL(headnode);

      // Get the expression
      getline (input, wholeExpression);

      int counter = 0;

      // Splits the expression into two halves and outputs the first half
      index = wholeExpression.find('=');
      firstHalf = wholeExpression.substr(0,index);
      output << firstHalf << "= ";

      //Gets the x value
      xbeg = firstHalf.find('(');
      xend = firstHalf.find(')');
      xvaluestring = firstHalf.substr(xbeg + 1,xend);
      xvalue = stod(xvaluestring);


      // Gets the list of terms
      secondHalf = wholeExpression.substr(index+2); // skips equal sign and space so spin is correct later
      //good till here
//moved
      headnode.setsign("x");
      secondHalf = fillnode (headnode, secondHalf, LL, sign);

      //While there are terms left, put them in to nodes and into linked list
         while (secondHalf.length() > 0)
         {
               node newnode;
               newnode.setsign("x");
               secondHalf = fillnode (newnode, secondHalf, LL, "g");
               LL.insertnode(newnode);
         }

      // Output linked list and totals
      totalnum = total(LL, xvalue);
      output << LL << " = " << fixed <<setprecision(3) << totalnum << endl;
      }
   }
   return 0;
} // End main()



//Fill the nodes with right values
string fillnode (node &newnode, string secondHalf, linkedlist& LL, string sign)
{

string coeffstring, exstring, afterx;  //strings to hold ex, coeff, and karrot
double coeffindex, spaceindex;         // Indexes for co and space
double coeff, exp;                     // coeff and ex values

// IF there's a sign, its the first character in the string
         if (sign != "x")
         {
            sign = secondHalf[0];
            newnode.setsign(sign);
            secondHalf = secondHalf.substr(2);
         }

         coeffindex = secondHalf.find('x');

         // no x value, coeff is the number and the exponent is 0
         if (coeffindex == string::npos)
         {

            coeffstring = secondHalf.substr(0);
            coeff = stod(coeffstring);
            newnode.setcoeff(coeff);
            newnode.setexpon(0);
         }

         // is x value, find coeff
         else
         {

            if (coeffindex == 0)
            {
               newnode.setcoeff(1);
            }

            coeffstring = secondHalf.substr(0,coeffindex);

            if (coeffstring == "" || coeffstring == " ")
            {
               newnode.setcoeff(1);
            }
            else
            {
            coeff = stod(coeffstring);
            newnode.setcoeff(coeff);
            }

            // If there's a karrot, there's an expon
            afterx = secondHalf.substr(coeffstring.length() + 1);

            if (afterx[0] == '^')
            {
               spaceindex = afterx.find(' ');

               if (spaceindex == string::npos)
               {
                  exstring = afterx.substr(1);
               }
               else
               {
                  exstring = afterx.substr(1,spaceindex - 1);
               }

               exp = stod(exstring);
               newnode.setexpon(exp);
            }
            // otherwise exponent is 1
            else
            {
               newnode.setexpon(1);
            }
         }

         //reset second half to be where sign is first character

         spaceindex = secondHalf.find(' ');

         secondHalf = secondHalf.substr(spaceindex + 1);

         spaceindex = secondHalf.find(' ');
         cout << "Final space index: " << spaceindex << endl;

         //if it's the last term, length is zero, end loop

         if (spaceindex == string::npos)
         {
            secondHalf = "";
         }
   // return second half of string
   return secondHalf;

}

// Calc total
double total (linkedlist& LL, double xvalue)
// solve for total
{
      double exponent;     //Exponent of term
      double coefficient;  //Coefficient of term
      double total = 0;    // Total
      string sign = "x";   //Sign of term (whether to add or subtract)
      node*head;           //Pointer to the head

      //Sets head to beginning of list
      head = LL.gethead();

      //While it hadn't ended, set values to correct ones
      while (head != nullptr)
      {
      exponent = head->getexpon();// cout <<"exponent: " << exponent << endl;
      coefficient = head->getcoeff();// cout << "coefficient" << coefficient << endl;
      sign = head->getsign(); //cout << "sign: " << sign << endl;

      // If sign is positive or non existant, add to total
      if (sign == "+" || sign == "x")
         {
            total += (pow(xvalue, exponent) * coefficient);
         }
      // If minus, subtract
      if (sign == "-")
         {
            total -= (pow(xvalue, exponent) * coefficient);
         }
      // Move to next node
      head = head->next;
      }
      //return total value
      return total;

}






