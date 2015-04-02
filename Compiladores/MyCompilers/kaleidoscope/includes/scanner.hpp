#ifndef SCANNER_H
#define SCANNER_H
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum Token {
  tok_eof = -1,

  tok_def = -2, tok_extern = -3,

  tok_identifier = -4, tok_number = -5
};

class Scanner {
public:
    string IdentifierStr;  
    double NumVal;              
    int gettok();
    int LastChar = ' ';
};
#endif
