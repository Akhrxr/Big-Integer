//-----------------------------------------------------------------------------
//  BigIntegerClient.cpp 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"
#include"BigInteger.cpp"
#include"List.cpp"

using namespace std;

int main(){

   string s1 = "9128734667000004389234563456345619187236478";
   //string s2 = "-330293847502398475";
   string s3 = "9876545439000000000000000200000000000006543654365346534";
   string s4 = "442233";
   string s5 = "563467";
   //string s4 = "9876545439000000000000000100000000000006543654365346534";
   //string s5 = "98765454390000000000000000000000000000065436543";
   //string s6 = "9876545439000000000000000000000000000006543";

   BigInteger A,B,C,D;
    A = BigInteger("132381");
    B = BigInteger("522092");
    //C = BigInteger();
    //D = BigInteger("15237927364");

    // pos * pos = pos
   //C = A * B;
   cout << "A-B = " << A-B << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << "D = " << D << endl;
    if (C.sign() != 1)
      return 1;
    if (!(C == D))
      return 2;

    // pos * neg = neg
    B.negate();
    D.negate();
    C = A * B;
    if (C.sign() != -1)
      return 3;
    if (!(C == D))
      return 4;

    B.makeZero();
    C = A * B;
    if (C.sign() != 0)
      return 5;

   A = BigInteger(s4);
   B = BigInteger(s5);

   cout << endl;

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << endl;
   C = A+B;
   cout << "C = " << C << endl;

   //BigInteger Q = A*B;
   //cout << "A*B = " << Q << endl;
   BigInteger O = BigInteger("6");
   O = O*A;
   cout << "A*6 = " << O << endl;
   BigInteger Asq = A*A;
   cout << "A^2 = " << Asq << endl;
   BigInteger Acub = Asq*A;
   cout << "A^3 = " << Acub << endl;
   cout << "(A==B) = " << ((A==B)?"True":"False") << endl;
   cout << "(A<B)  = " << ((A<B)? "True":"False") << endl;
   cout << "(A<=B) = " << ((A<=B)?"True":"False") << endl;
   cout << "(A>B)  = " << ((A>B)? "True":"False") << endl;
   cout << "(A>=B) = " << ((A>=B)?"True":"False") << endl << endl;


    C = A+B;
   cout << "C = " << C << endl;
    D = B+A;
   cout << "D = " << D << endl;
   cout << "(C==D) = " << ((C==D)?"True":"False") << endl;
   BigInteger E = A-A;
   BigInteger F = B-A;
   cout << "F = " << F << endl;
   cout << "E = " << E << endl;
   BigInteger G = A*B;
   BigInteger H = B*A;
   BigInteger I = C*E;


   cout << "C = " << C << endl;
   cout << "D = " << D << endl;
   cout << "(C==D) = " << ((C==D)?"True":"False") << endl;
   cout << "E = " << E << endl;
   cout << "F = " << F << endl;
   cout << "G = " << G << endl;
   cout << "H = " << H << endl;
   cout << "(G==H) = " << ((G==H)?"True":"False") << endl;
   cout << "I = " << I << endl << endl;

   cout << endl;

   A += B; //check
   B -= C; //check
   C *= D;
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << endl;

   cout << A*B*C*D*F*G*H << endl << endl;

   cout << endl;

   // test exceptions
   try{
      BigInteger J = BigInteger("");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("+");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("12329837492387492837492$4982379487293847");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("5298374902837409+82734098729287349827398");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;

   return EXIT_SUCCESS;
}
