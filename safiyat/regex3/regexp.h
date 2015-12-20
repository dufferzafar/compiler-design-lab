#ifndef REGEXP_H
#define REGEXP_H

#include <string.h>
#include <iostream>

class regexp
{
		std::string r;
		enum TTYPE {OPERAND, OPARA, CPARA, BOOLOR, QMARK, KSTAR, KPLUS, ERROR};
		TTYPE ttype(char);
		bool checkAlternate(std::string, unsigned int);
		unsigned int skipBlock(std::string, unsigned int);
		unsigned int goBlockBeg(std::string, unsigned int);
		int recursiveTest(std::string, std::string);
		std::string normalize();
	public:
		regexp();
		regexp(std::string);
		bool isvalid();
		std::string text();
		void setText(std::string);
		unsigned int len();
		bool validate(char *);
		bool validate(std::string);

};

#endif // REGEXP_H
