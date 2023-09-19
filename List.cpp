//-----------------------------------------------------------------------------
// List.cpp
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"


// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}


// Class Constructors & Destructors -------------------------------------------

// Creates a new List in the empty state.
List::List(){
   frontDummy = new Node(0);
   backDummy = new Node(0);
   frontDummy->prev = nullptr;
   backDummy->next = nullptr;
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   this->num_elements = 0;
   this->pos_cursor = 0;
}

// Copy Constructor.
List::List(const List& Q){
   frontDummy = new Node(0);
   backDummy = new Node(0);
   frontDummy->prev = nullptr;
   backDummy->next = nullptr;
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   this->num_elements = 0;
   this->pos_cursor = 0;
   // load elements of Q into this List
   Node* N = Q.frontDummy->next;
   int n = 0;
   while( n != Q.num_elements){
      int num = N->data;
      List::insertBefore(num);
      N = N->next;
      ++n;
   }
   pos_cursor = 0;
}

// Destructor
List::~List(){
   if( num_elements > 0 ) {
      int n = 0;
      for (Node* N = frontDummy; n != this->num_elements;) {
         Node* old_n = N;
         N = old_n->next; 
      	delete old_n;
         ++n;
	   }
      Node *N = backDummy;
      frontDummy = backDummy = beforeCursor = afterCursor = nullptr;
      delete N;
   } else {
      Node* N = frontDummy;
      frontDummy = backDummy = beforeCursor = afterCursor = nullptr;
      delete N;
   }
}


// Access functions -----------------------------------------------------------


// Front()
// Returns the value at the front of List.
// Pre: !isEmpty()
ListElement List::front() const{
   if( List::length() ==0 ){
      throw std::length_error("List: Front(): empty List");
   }
   return(frontDummy->next->data);
}

ListElement List::back() const{
   if( List::length() ==0 ){
      throw std::length_error("List: back(): empty List");
   }
   return(backDummy->prev->data);
}

// getLength()
// Returns the length of List.
int List::length() const{
   return(num_elements);
}

int List::position() const {
   return(pos_cursor);
}

ListElement List::peekNext() const {
   Node* N = frontDummy;
   if (pos_cursor != num_elements) {
      for (int i = 0; i <= pos_cursor; ++i ) {
         N = N->next;
      }
      return N->data;
   }
   else {
      throw std::range_error("List: peekNext(): Position at end of List");
   }
}


ListElement List::peekPrev() const {
   Node* N = frontDummy;
   if (pos_cursor != 0) {
      for (int i = 0; i < pos_cursor; ++i ) {
         N = N->next;
      }
      return N->data;
   }
   else {
      throw std::range_error("List: peekPrev(): Position at start of List");
   }

}

// Manipulation procedures ----------------------------------------------------


void List::clear(){
   if (num_elements != 0) {
      Node* N = frontDummy->next;
      while(N != backDummy) {
         Node* old_n = N;
         N = N->next;
         delete old_n;
      }
   }
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   num_elements = 0;
   pos_cursor = 0;
}

void List::moveFront() {
   pos_cursor = 0;
}

void List::moveBack() {
   pos_cursor = num_elements;
}

ListElement List::moveNext() {
   if (pos_cursor != num_elements) {
      ListElement N = List::peekNext();
      ++this->pos_cursor;
      return N;
   }
   else {
       throw std::range_error("List: moveNext(): Position at end of List");
   }
}

ListElement List::movePrev() {
   if (pos_cursor != 0) {
      ListElement N = List::peekPrev();
      --this->pos_cursor;
      return N;
   }
   else {
      throw std::range_error("List: movePrev(): Position at start of List");
   }
}

void List::insertAfter(ListElement x) {
   Node *X = new Node(x);
   Node *F = frontDummy;
   Node *B = backDummy;
   if (List::length() == 0) {
      F->next = X;
      B->prev = X;
      X->next = B;
      X->prev = F;
      ++num_elements;
   }
   else {
      for (int i = 0; i < pos_cursor; ++i) {
         F = F->next;
      }
      F->next->prev = X;
      X->next = F->next;
      F->next = X;
      X->prev = F;
      ++num_elements;
   }
}

void List::insertBefore(ListElement x) {
   Node *X = new Node(x);
   Node *F = frontDummy;
   Node *B = backDummy;
   if (List::length() == 0) {
      F->next = X;
      B->prev = X;
      X->next = B;
      X->prev = F;
      ++num_elements;
      ++pos_cursor;
   }
   else {
      for (int i = 0; i <= pos_cursor ; ++i) {
         F = F->next;
      }
      F->prev->next = X;
      X->prev = F->prev;
      F->prev = X;
      X->next = F;
      ++num_elements;
      ++pos_cursor;
   }
}

void List::setAfter(ListElement x) {
   Node* N = frontDummy->next;
   if (pos_cursor != num_elements) {
      for (int i = 0; i < pos_cursor; ++i) {
         N = N->next;
      }
      N->data = x;
   }
   else {
      throw std::range_error("List: setAfter(): Position at end of List");
   }
}

void List::setBefore(ListElement x) {
   Node* N = frontDummy;
   if (pos_cursor != 0) {
      for (int i = 0; i < pos_cursor ; ++i) {
         N = N->next;
      }
      N->data = x;
   }
   else {
      throw std::range_error("List: setBefore(): Position at start of List");
   }
}

void List::eraseAfter() {
   if (pos_cursor != num_elements) {
      Node* N = frontDummy;
      for (int i = 0; i <= pos_cursor; ++i) {
         N = N->next;
      }
      Node* old_n = N;
      N->next->prev = N->prev;
      N->prev->next = N->next;
      delete old_n;
      --num_elements;
   }
   else {
      throw std::range_error("List: eraseAfter(): Position at end of List");
   }
}

void List::eraseBefore() {
   if (pos_cursor != 0) {
      Node* N = frontDummy;
      for (int i = 0; i < pos_cursor; ++i) {
         N = N->next;
      }
      Node* old_n = N;
      N->next->prev = N->prev;
      N->prev->next = N->next;
      delete old_n;
      --num_elements;
      --pos_cursor;
   }
   else {
      throw std::range_error("List: eraseBefore(): Position at start of List");
   }
}

// Other Functions ------------------------------------------------------------

int List::findNext(ListElement x) {
   Node* N = frontDummy;
   for (int i = 0; i <= pos_cursor; ++i) {
      N = N->next;
   }
   if (N->data == x) {
      ++pos_cursor;
      return List::position();
   }
   int not_found = 0;
   while (N->data != x) {
      N = N->next;
      ++pos_cursor;
      if (pos_cursor == num_elements) {
         not_found = 1;
         break;
      }
   }
   if (not_found) {
      return -1;
   }
   ++pos_cursor;
   return List::position();
}

int List::findPrev(ListElement x) {
   Node* N = frontDummy;
   for (int i = 0; i < pos_cursor; ++i) {
      N = N->next;
   }
   if (N->data == x) {
      --pos_cursor;
      return List::position();
   }
   int not_found = 0;
   while (N->data != x) {
      N = N->prev;
      --pos_cursor;
      if (pos_cursor == 0) {
         not_found = 1;
         break;
      }
   }
   if (not_found) {
      return -1;
   }
   --pos_cursor;
   return List::position();
}

void List::cleanup() {
   if (List::length() == 0 || List::length() == 1) {
      return;
   }
   else {
      for (Node* rn = frontDummy; rn != backDummy; rn = rn->next) {
         int poscount = -1;
         for (Node* rnn = frontDummy->next; rnn!=backDummy; rnn = rnn->next) {
            ++poscount;
            if (rn->data == rnn->data && rn!=rnn) {
               Node* old_n = rnn;
               rnn->next->prev = rnn->prev;
               rnn->prev->next = rnn->next;
               rnn = rnn->prev;
               delete old_n;
               --num_elements;
               if (poscount < pos_cursor) {
                  --pos_cursor;
                  --poscount;
               }
            }
         }
      }
   }
}

List List::concat(const List& L) const{
   List J;
   Node* N = frontDummy->next;
   Node* M = L.frontDummy->next;
   while( N!=backDummy ){
      J.insertBefore(N->data);
      N = N->next;
   }
   while( M!=L.backDummy ){
      J.insertBefore(M->data);
      M = M->next;
   }
   J.pos_cursor = 0;
   return J;
}


// to_string()
// Returns a string representation of List consisting of a space separated 
// list of data values.
std::string List::to_string() const{
   Node* N = frontDummy->next;
   std::string s = "(";
      if (List::length()) {
         for(; N!=backDummy->prev; N=N->next){
            s += std::to_string(N->data)+", ";
         }
         if (List::length()) {
            s += std::to_string(N->data);
         }
      }
   s += ")";
   return s;
}

// equals()
// Returns true if and only if this is the same sequence as Q.
bool List::equals(const List& L) const{
   bool eq = false;
   Node* N = nullptr;
   Node* M = nullptr;

   eq = ( this->num_elements == L.num_elements );
   N = frontDummy->next;
   M = L.frontDummy->next;
   while( eq && N!=nullptr){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}


// Overloaded Operators --------------------------------------------------------

// operator<<()
// Inserts string representation of Q, as defined by member function 
// to_string(), into stream.
std::ostream& operator<< ( std::ostream& stream,  const List& L ) {
   return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if List A equals List B, as defined by member
// member function equals().
bool operator==(const List& A, const List& B){
   return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L, then returns a reference
// to this List.
List& List::operator=( const List& L ) {
   if( this != &L ){ // not self assignment
      // make a copy of Q
      List temp = L;

      // then swap the copy's fields with fields of this
      std::swap(frontDummy->next, temp.frontDummy->next);
      std::swap(backDummy->prev, temp.backDummy->prev);
      std::swap(num_elements, temp.num_elements);
      std::swap(pos_cursor, temp.pos_cursor);
   }

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return
}