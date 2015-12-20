//
//  regexp.h
//  Q2
//
//  Created by admin on 26/08/14.
//  Copyright 2014 __MyCompanyName__. All rights reserved.
//
#ifndef REGEXP_H
#define REGEXP_H

#include <string.h>
#include <iostream>

class regexp
{
    std::string r;
    enum TTYPE {OPERAND, OPARA, CPARA, KSTAR, OR, ERROR};
    TTYPE ttype(char);
    int getClosingPara(std::string, int);
    int goBlockBeg(std::string, int);
    int goBlockEnd(std::string, int);
    bool blockCheck(std::string, std::string);               //Returns index of first non-matching symbol from second string 
public:
    regexp();
    regexp(std::string);
    bool isvalid();
    std::string text();
    unsigned int len();
    bool validate(char *);
    bool validate(std::string);
};

#endif // REGEXP_H
