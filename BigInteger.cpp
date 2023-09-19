//-----------------------------------------------------------------------------
// BigInteger.cpp
// Cpp file for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<cmath>
#include"BigInteger.h"

int power = 2;
ListElement base = 100;
List scalar(List A, long multi, int shift);
List ListAdd(const List& P, const List& Q);

BigInteger::BigInteger() {
    this->signum = 0;
}

BigInteger::BigInteger(std::string s){
    int s_len = s.length() -1;
    if (!s.length()) throw std::invalid_argument("BigInteger: Constructor: empty string");
    if (s.length() == 1 && !isdigit(s[0])) throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    if (s.length() != 0) {
        for (int i = 1; i <=s_len; ++i) {
            if (!isdigit(s[i])) {
                throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
            }
        }
        if (isdigit(s[0]) || s[0] == '+') {
            this->signum = 1;
        }
        else if (s[0] == '-') {
            this->signum = -1;
        }
        else {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
        int i = s_len;
        int lim;
        if (isdigit(s[0])) {
            lim = 0;
        }
        else {
            lim = 1;
        }
        if (i < power) {
            if (s[0] == '-') {
                s = s.substr(1,s_len);
            }
            if (s[0] == '+') {
                s = s.substr(1,s_len);
            }
            long val_si = stol(s);
            digits.insertAfter(val_si);
        }
        else {
            for (; i>=power; i = i - power) {
                std::string val_s = s.substr(i-power+1,power); // fix this. Not storing correct value;
                long val_si = stol(val_s);
                digits.insertAfter(val_si);
            }
            std::string val_s;
            for (; i>=lim; --i) {
                val_s = s[i] + val_s;
            }
            long val_si = stol(val_s);
            digits.insertAfter(val_si);
        }
    }
}

BigInteger::BigInteger(const BigInteger& N){
    this->signum = N.signum;
    this->digits = N.digits;
}

// Access functions --------------------------------------------------------

int BigInteger::sign() const{
    if (this->digits.length() != 0) {
        return this->signum;
    }
    else return 0;
}

int BigInteger::compare(const BigInteger& N) const{
    BigInteger G = BigInteger::sub(N);
    return G.signum;
}

// Manipulation procedures -------------------------------------------------

void BigInteger::makeZero(){
    List C = this->digits;
    C.clear();
    this->digits = C;
    this->signum = 0;
}

void BigInteger::negate() {
    if (this->signum) {
        this->signum = (this->signum * -1);
    }
}

// BigInteger Arithmetic operations ---------------------------------------
void copier(List& L, List N) {
    L.clear();
    for (N.moveBack(); N.position();) {
        long val = N.movePrev();
        L.insertAfter(val);
    }
}

void normalize(List& L) {
    L.moveBack();
    int max = base;
    if (L.length() == 1) {
        long value = L.movePrev();
        if (value >= max) {
            long adder = value/base;
            long new_val = value%base;
            L.setAfter(new_val);
            L.insertBefore(adder);
        }
        return;
    }
    while (L.position() > 2) {
        long value = L.movePrev();
        if (value >= base) {
            long adder = value/base;
            long new_val = value%base;
            L.setAfter(new_val);
            long before_val = L.peekPrev();
            L.setBefore(before_val + adder);
        }
        if (value < 0) {
            long new_val = value + base;
            L.setAfter(new_val);
            long before_val = L.peekPrev();
            L.setBefore(before_val -1);
        }
    }
    //position is now at 1
    long value = L.movePrev();
    while (L.position()) {
        if (value >= max) {
            long adder = value/base;
            long new_val = value%base;
            L.setAfter(new_val);
            long before_val = L.peekPrev();
            if (adder == 0) break;
            before_val = before_val + adder;
            //if (L.position() == 1)
            L.setBefore(before_val);
        }
        if (value < 0) {
            long new_val = value + base;
            L.setAfter(new_val);
            long before_val = L.peekPrev();
            L.setBefore(before_val-1);
        }
        value = L.movePrev();
    }
    if (value != 0 && value >= max) {
        long adder = value/base;
        long new_val = value%base;
        L.setAfter(new_val);
        L.insertBefore(adder);
    }
}

BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger Q;
    if (N.signum == -1 && this->signum == 1) {
        BigInteger NT = N;
        BigInteger TT = *this;
        NT.signum = 1;
        Q = TT.sub(NT);
        return Q;
    }
    else if (this->signum == -1 && N.signum == 1) {
        BigInteger P = *this;
        P.signum = 1;
        Q = N.sub(P);
        return Q;
    }
    else {
        Q.signum = this->signum;
        List A = this->digits;
        List B = N.digits;
        List C; 
        if (A.length() >= B.length()) {
            B.moveBack();
            for (A.moveBack(); B.position() != 0;) {
                long A_val = A.movePrev();
                long B_val = B.movePrev();
                long C_val = A_val+B_val;
                C.insertAfter(C_val);
            }
            while (A.position()!= 0) {
                long A_val = A.movePrev();
                C.insertAfter(A_val);
            }
        }
        else {
            A.moveBack();
            for (B.moveBack(); A.position() != 0;) {
                long A_val = A.movePrev();
                long B_val = B.movePrev();
                long C_val = A_val+B_val;
                C.insertAfter(C_val);
            }
            while (B.position()!= 0) {
                long B_val = B.movePrev();
                C.insertAfter(B_val);
            }
        }
        normalize(C);
        Q.digits = C;
    }
    for (Q.digits.moveBack(); Q.digits.position();) {
        long val = Q.digits.movePrev();
        if (val != 0) {
            if (N.signum == this->signum) {
                Q.signum = N.signum;
                break;
            }
        }
    }
    return Q;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger Q;
    List A = this->digits;
    List B = N.digits;
    List C;
    if (this->signum == N.signum) {
        if(A.equals(B)) {
            Q.signum = 0;
            C.insertBefore(0);
            Q.digits = C;
            return Q;
        }
    }
    if (N.signum == -1 && this->signum == 1) {
        BigInteger NT = N;
        BigInteger TT = *this;
        NT.signum = 1;
        Q = TT.add(NT);
        return Q;
    }
    if (this->signum == -1 && N.signum == 1) {
        BigInteger NT = N;
        BigInteger TT = *this;
        NT.signum = -1;
        Q = TT.add(NT);
        return Q;
    }
    if (A.length() >= B.length()) {
        B.moveBack();
        for (A.moveBack(); B.position() != 0;) {
            long A_val = A.movePrev();
            long B_val = B.movePrev();
            long C_val = A_val-B_val;
            C.insertAfter(C_val);
        }
        while (A.position()!= 0) {
            long A_val = A.movePrev();
            C.insertAfter(A_val);
        }
    }
    else {
        A.moveBack();
        for (B.moveBack(); A.position() != 0;) {
            long A_val = A.movePrev();
            long B_val = B.movePrev();
            long C_val = A_val-B_val;
            C.insertAfter(C_val);
        }
        while (B.position()!= 0) {
            long B_val = B.movePrev();
            C.insertAfter(-1*(B_val));
        }
    }
   normalize(C);
   int tempsign = this->signum;
   if (C.front() < 0) {
        tempsign = tempsign*(-1);
        for (C.moveBack(); C.position();) {
            long val = C.movePrev();
            val = (val*-1);
            C.setAfter(val);
        }
        normalize(C);
   }
   Q.digits = C;
   Q.signum = tempsign;
   return Q;
}

BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger Q;
    if (this->signum == 0 || N.signum == 0) {
        Q.digits.insertBefore(0);
        Q.signum = 0;
        return Q;
    }
    if (this->signum == N.signum) {
        Q.signum = 1;
    }
    if (this->signum != N.signum) {
        Q.signum = -1;
    }
    List A, B, C;
    if (this->digits.length() > N.digits.length()) {
        A  = this->digits;
        B = N.digits;
    }
    else {
        A = N.digits;
        B = this->digits;
    }
    C.insertBefore(0);
    B.moveBack();
    for (int shift = 0; B.position(); ++shift) {
        long multi = B.movePrev();
        if (multi != 0) {
            List D = scalar(A, multi, shift);
            List CD = ListAdd(C, D); //make an addlist function;
            copier(C, CD);
            normalize(C);
        }
    }
    Q.digits = C;
    return Q;

}

List ListAdd(const List& P, const List& Q) {
    List C; 
    List A = P;
    List B = Q;
    if (A.length() >= B.length()) {
        B.moveBack();
        for (A.moveBack(); B.position() != 0;) {
            long A_val = A.movePrev();
            long B_val = B.movePrev();
            long C_val = A_val+B_val;
            C.insertAfter(C_val);
        }
        while (A.position()!= 0) {
            long A_val = A.movePrev();
            C.insertAfter(A_val);
        }
    }
    else {
        A.moveBack();
        for (B.moveBack(); A.position() != 0;) {
            long A_val = A.movePrev();
            long B_val = B.movePrev();
            long C_val = A_val+B_val;
            C.insertAfter(C_val);
        }
        while (B.position()!= 0) {
            long B_val = B.movePrev();
            C.insertAfter(B_val);
        }
    }
    return C;
}


List scalar(List L, long multi, int shift) {
    List S;
    if (multi == 0) {
        S.insertAfter(0);
        return S;
    }
    for (int i = 0; i < shift; ++i) {
        S.insertAfter(0);
    }
    for (L.moveBack(); L.position();) {
        long val = L.movePrev();
        long new_val = multi*val;
        S.insertAfter(new_val);
    }
    normalize(S);
    return S;
}

std::string BigInteger::to_string() {
    std::string s = "";
    if (this->signum == 0) {
        s+= '0';
        return s;
    }
    else {
        if (this->signum == -1) {
            s+= '-';
        }
        digits.moveFront();
        long valq = digits.moveNext();
        while (valq == 0) {
            valq = digits.moveNext();
        }
        digits.movePrev();
        std::string val = std::to_string(digits.moveNext());
        for (int i = 0; i < val.length(); ++i) {
            if (val[i] != '0') {
                val = val.substr(i, val.length());
                break;
            }
        }
        s+= val;
        while(digits.position() != digits.length()) {
            val = std::to_string(digits.moveNext());
            if (val.length() != power && digits.position() != 1) {
                for (int i = val.length(); i < power; ++i) val = "0" + val;
            }
            s += val;
        }
        return s;
    }
}

// Overriden Operators -----------------------------------------------------

std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.BigInteger::to_string();
}

bool operator==( const BigInteger& A, const BigInteger& B ){
    if (A.signum != B.signum) return 0;
    BigInteger A2 = A;
    BigInteger B2 = B;
    std::string a_num = A2.to_string();
    std::string b_num = B2.to_string();
    return (a_num == b_num);

}

bool operator<( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == -1 ) return 1;
    return 0;
}

bool operator<=( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == -1 || A.compare(B) == 0 ) return 1;
    return 0;
}

bool operator>( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == 1 ) return 1;
    return 0;
}

bool operator>=( const BigInteger& A, const BigInteger& B ){
    if (A.compare(B) == 1 || A.compare(B) == 0 ) return 1;
    return 0;
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.add(B);
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    return A = A.add(B);
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}

BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    return A = (A.sub(B));
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    return A = A.mult(B);
}



