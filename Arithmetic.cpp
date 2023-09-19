/***************************************************************************************
* Akhror Rakhmatov,1794798 arakhmat@ucsc.edu, PA6
*  Arithmetic.cpp
*  Uses functions in List.cpp and BigInteger to calculate big numbers
****************************************************************************************/
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"BigInteger.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf( stderr, "Incorrect number of command line arguments, please include a file in and file out only\n" );
        exit(1);
    }
    std::ifstream in;
    std::ofstream out;
    in.open(argv[1]);
    if( !in.is_open() ){
      std::cerr << "Unable to open file " << argv[1] << " for reading" << std::endl;
      return(EXIT_FAILURE);
    }
    out.open(argv[2]);
    if( !out.is_open() ){
      std::cerr << "Unable to open file " << argv[2] << " for writing" << std::endl;
      return(EXIT_FAILURE);
    }
    std::string As = "";
    std::string Bs = "";
    std::string token;
    std::getline(in, As);
    std::getline(in, token);
    std::getline(in, Bs);
    BigInteger A = BigInteger(As);
    BigInteger B = BigInteger(Bs);
    out << A << '\n';
    out <<'\n';
    out << B << '\n';
    out <<'\n';
    BigInteger C;
    out << A+B << '\n';
    out <<'\n';
    C = A-B;
    out << C << '\n';
    out <<'\n';
    C = A-A;
    out << C << '\n';
    out <<'\n';
    BigInteger D = BigInteger("3");
    BigInteger E = A*D;
    D = BigInteger("2");
    BigInteger F = B*D;
    C = E-F;
    out << C << '\n';
    out <<'\n';
    C = A*B;
    out << C << '\n';
    out <<'\n';
    C = A*A;
    out << C <<'\n';
    out <<'\n';
    C = B*B;
    out << C <<'\n';
    out <<'\n';
    BigInteger A_2 = A;
    BigInteger B_2 = B;
    for (int i = 0; i < 3; ++i) {
        A = A*A_2;
    }
    for (int i = 0; i < 4; ++i) {
        B = B*B_2;
    }
    D = BigInteger("9");
    E = A*D;
    D = BigInteger("16");
    F = B*D;
    C = E+F;
    out << C << '\n';
    out <<'\n';
    in.close();
    out.close();
    return(EXIT_SUCCESS);
}