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
	if(p == '|')
		return BOOLOR;
	if(p == '?')
		return QMARK;
	if(p == '*')
		return KSTAR;
	if(p == '+')
		return OR;
	if(p == '.')
		return CONCAT;
	return ERROR;
}

std::string regexp::normalize()
{
	int i = 0;
	std::string p = r;
	while(i < p.length())
	{
		if(p[i] == '*')
		{
			if(p[i-1] == ')')
			{
				i++;
				continue;
			}
			p.insert(i, 1, ')');
			p.insert(i-1, 1, '(');
		}
		else if(p[i] == '+')
		{
			if(p[i-1] != ')') //Pre '+' part
			{
				p.insert(i, 1, ')');
				int j = goBlockBeg(p, i-1);
				p.insert(j, 1, '(');
				i+=2;
			}
			if(p[i+1] != '(')
			{
				i++;
				p.insert(i, 1, '(');
				int j = goBlockEnd(p, i+1);
				if(j+1 < p.length())
					p.insert(j+1, 1, ')');
				else
					p.append(")");
				i--;
			}
		}
		i++;
	}
	return p;
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

std::string regexp::text()
{
	return r;
}

unsigned int regexp::len()
{
	return r.length();
}

bool regexp::isvalid()
{
	if(strstr(r.data(), "()"))
		return false;
	if(strstr(r.data(), "+*"))
		return false;
	if(strstr(r.data(), "*+"))
		return false;
	if(strstr(r.data(), "(+"))
		return false;
	if(strstr(r.data(), "(*"))
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
	std::string t = normalize();
	std::cout << "Normalized: " << t << std::endl;
	return recursiveCheck(t, p);
}

bool regexp::recursiveCheck(std::string t, std::string p)
{
	int t_i = 0, p_i = 0;

	while(t_i < t.length())
	{
		switch(ttype(t[t_i]))
		{
			case OPERAND:
				if(p[p_i] == t[t_i])
				{
					p_i++;
					t_i++;
					break;
				}
				else
					return false;
			case OPARA:
				if(recursiveCheck(t.substr(t_i+1), p.substr(p_i)) == false)
				{
					t_i = goBlockEnd(t, t_i) + 1;
					if(t[t_i] == '*' || t[t_i] == '+')
						return recursiveCheck(t.substr(t_i + 1), p.substr(p_i));
				}
				if(p_i >= p.length() && t_i >= t.length())
					return true;
				else
					return false;
			case CPARA:
				if(t[t_i + 1] == '*')
				{
					int temp = t_i + 2;
					int temp2 = goBlockBeg(t, t_i);
					if(recursiveCheck(t.substr(temp2), p.substr(p_i)) == false)
					{
						if(temp < t.length())
							return recursiveCheck(t.substr(temp), p.substr(p_i));
						return false;
					}
					if(p_i >= p.length() && t_i >= t.length())
						return true;
					else
						return false;
				}
				else if(t[t_i + 1] == '+')
				{
					t_i = goBlockEnd(t, t_i + 2);
				}
				else
					t_i++;
				break;
			case CONCAT:
				t_i++;
				continue;
		}
	}
	if(p_i >= p.length() && t_i >= t.length())
		return true;
	else
		return false;
}
