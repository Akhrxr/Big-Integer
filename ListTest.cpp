//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
#include"List.cpp"
using namespace std;

int main(){

   int i, n=10;
   List E, B, C, D;

 E.insertAfter(3215);
    E.insertAfter(176);
    E.insertAfter(22);
    E.insertAfter(5);
    E.insertAfter(1);
    E.moveNext();
    if (E.moveNext() != 5)
      return 1;

    E.eraseBefore();
    E.eraseBefore();
    E.moveNext();
    E.moveNext();
    if (E.moveNext() != 3215)
      return 2;

    E.moveFront();
    if (E.moveNext() != 22)
      return 3;
      
   C.clear();

   B.insertAfter(22);
    B.insertAfter(5);
    C.insertAfter(1);
    C.insertAfter(22);
    D.insertAfter(5);
    D.insertAfter(1);
    B.insertAfter(22);
    B.insertAfter(5);
    C.insertAfter(1);

   C.clear();
   B.clear();
   D.clear();
   E.clear();

   for(i=1; i<=n; i++){
      E.insertAfter(i);
      B.insertAfter(11-i);
      C.insertBefore(i);
      D.insertBefore(11-i);
   }


   cout << endl;
   cout << "E = " << E << endl;
   cout << "E.position() = " << E.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   E.moveBack();
   B.moveBack();
   C.moveFront();
   D.moveFront();

   cout << "E = " << E << endl;
   cout << "E.position() = " << E.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;

   cout << endl << "B: ";
   for(i=1; i<=7; i++){
      cout << B.movePrev() << " ";
   }
   cout << endl << "B.position() = " << B.position() << endl;
   
   cout << endl << "C: ";
   for(i=1; i<=7; i++){
      cout << C.moveNext() << " ";
   }
   cout << endl << "C.position() = " << C.position() << endl;

   cout << endl;
   cout << "E==B is " << (E==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==D is " << (C==D?"true":"false") << endl;
   cout << "D==E is " << (D==E?"true":"false") << endl;
   cout << endl;

   cout << B.findNext(5) << endl;
   cout << B << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl;
   cout << B.findPrev(2) << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl; 
   cout << B.findNext(20) << endl; 
   cout << B.position() << endl;
   cout << B.findPrev(20) << endl;
   cout << B.position() << endl;
   cout << endl;

   for( i=10; i>=1; i--){
      E.insertAfter(i);
      E.movePrev();
   }
   cout << "E = " << E << endl;
   for( i=1; i<=15; i++){
      E.moveNext();
   }
   cout << E.position() << endl;
   E.cleanup();
   cout << "E = " << E << endl;
   cout << E.position() << endl;
   cout << endl;

   List A = E;
   cout << "E==A is " << (E==A?"true":"false") << endl;

   cout << endl;

   List F = E.concat(B);
   cout << "F = " << F << endl;
   cout << "length: " << F.length() << endl;
   cout << "front: " << F.front() << endl;
   cout << "back: " << F.back() << endl;
   cout << "position: " << F.position() << endl;
   for( i=1; i<=7; i++){
      cout << "peekNext: " << F.peekNext() << endl;
      F.insertBefore(-i);
      cout << F.moveNext() << endl; 
   }
   cout << "F = " << F << endl;

   cout << endl;

   cout << "test exceptions: " << endl;
   cout << "E = " << E << endl;
   E.moveFront();
   try{
      E.peekPrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      E.movePrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      E.setBefore(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      E.eraseBefore();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   E.moveBack();
   try{
      E.peekNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      E.moveNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      E.setAfter(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      E.eraseAfter();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   E.clear();
   try{
      E.front();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      E.back();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;


   return( EXIT_SUCCESS );
}