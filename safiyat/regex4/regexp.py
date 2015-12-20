//
//  regexp.cpp
//  Q2
//
//  Created by admin on 26/08/14.
//  Copyright 2014 __MyCompanyName__. All rights reserved.
//

#include "regexp.h"

regexp::regexp()
{
}

regexp::regexp(std::string p)
{
	r = p;
}

regexp::TTYPE regexp::ttype(char p)
{
	if(isalpha(p))
		return OPERAND;
	if(p == '(')
		return OPARA;
	if(p == ')')
		return CPARA;
	if(p == '*')
		return KSTAR;
	if(p == '+')
		return OR;
	return ERROR;
}

int regexp::getClosingPara(std::string p, int i)
{
	int retVal = -1;
	if(p[i]=='(')
	{
		int parCount = 1;
		for(i++; i < p.length(); i++)
		{
			if(p[i]=='(')
				parCount++;
			else if(p[i]==')')
				parCount--;
			if(!parCount)
				break;
		}
		retVal = i;
	}
	else if(p[i]==')')
	{
		int parCount = 1;
		for(i--; i > 0; i--)
		{
			if(p[i]=='(')
				parCount--;
			else if(p[i]==')')
				parCount++;
			if(!parCount)
				break;
		}
		retVal = i;
	}
	return retVal;
}

int regexp::goBlockBeg(std::string p, int i)
{
	if(p[i] == ')')
		return getClosingPara(p, i);
	while(i > 0)
	{
		if(p[i] == '(')
			return i;
		if(p[i] == ')')
		{
			i = getClosingPara(p, i);
			continue;
		}
		i--;
	}
	return i;
}

int regexp::goBlockEnd(std::string p, int i)
{
	if(p[i] == '(')
		return getClosingPara(p, i);
	while(i < p.length())
	{
		if(p[i] == ')')
			return i;
		if(p[i] == '(')
		{
			i = getClosingPara(p, i);
			i++;
			continue;
		}
		i++;
	}
	return i;
}

bool regexp::blockCheck(std::string t, std::string p)
{
    int i = 0;
    char a, b;
    
    std::cout << "Passed " << t << std::endl;
    
    if(t.length() > 5)         //(a+b)*
    {
        a = t[1];
        b = t[3];
        if(t[t.length() - 1] != '*')
        {
            if(p[i] == a || p[i] == b)
            {
                i++;
                if(i < p.length())
                    return false;
                return true;
            }
        }
        while (i < p.length())
        {
            if(p[i] == a || p[i] == b)
                i++;
            else
                return false;
        }
    }
    else if(t.length() < 5)
    {
        a = t[0];
        b = t[1];
        std::cout << "DEBUG: " << t[t.length() - 1] << std::endl;
        if(t[t.length() - 1] != '*')
        {
            if(p[i] == a && p[i+1] == b)
            {
                i+=2;
                if(i < p.length())
                    return false;
                return true;
            }
            return false;
        }
        if(p[i] != a)
            return false;
        i++;
        while (i < p.length())
        {
            if(p[i] == b)
                i++;
            else
                return false;
        }
    }
    if(i < p.length())
        return false;
    return true;
}

std::string regexp::text()
{
	return r;
}

unsigned int regexp::len()
{
	return (unsigned int)r.length();
}

bool regexp::isvalid()
{
	if(strstr(r.data(), "()"))
		return false;
	if(strstr(r.data(), "+*"))
		return false;
	if(strstr(r.data(), "(+"))
		return false;
	if(strstr(r.data(), "((ab*+"))
		return false;
    if(strstr(r.data(), ")("))
		return false;
	return true;
}

bool regexp::validate(char *p)
{
	std::string a;
	a.copy(p, strlen(p));
	return validate(a);
}

bool regexp::validate(std::string p)
{
    std::string t = r;
//	std::cout << "Matching against: " << t << std::endl;
	int t_i, p_i;
    t_i = p_i = 0;
    bool result;
    if(ttype(t[1]) == OPARA)     // (a+b)*+...
    {
        result = blockCheck(t.substr(1, 6), p);
        if(result)
            return true;
        else
        {
//            std::cout << "1.2 len = " << (int)t.length() - 2;
            int temp = t.find('+', 5) + 1;
            if(blockCheck(t.substr(temp, 6), p))
                return true;
            return blockCheck(t.substr(temp, 3), p);
        }
    }
    else if(ttype(t[1]) == OPERAND) // ab*+...
    {
        result = blockCheck(t.substr(1, 3), p);
        if(result)
            return true;
        else
        {
//            std::cout << "2.2";
            int temp = t.find('+', 2) + 1;
            if(blockCheck(t.substr(temp, 6), p))
                return true;
            return blockCheck(t.substr(temp, 3), p);
        }
    }
    std::cout << "Regex not parseable." << std::endl;
    return false;
}