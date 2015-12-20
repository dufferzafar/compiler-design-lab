#ifndef REGEXP_H
#define REGEXP_H

#include <string.h>
#include <iostream>

class regexp
{
		std::string r;
		enum TTYPE {OPERAND, OPARA, CPARA, BOOLOR, QMARK, KSTAR, OR, CONCAT, ERROR};
		TTYPE ttype(char);
		std::string normalize();
		int getClosingPara(std::string, int);
		int goBlockBeg(std::string, int);
		int goBlockEnd(std::string, int);
		bool recursiveCheck(std::string, std::string);
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
