#include "Utils.h"

bool isASmallLetter(char letter)  
{
	return letter >= 'a' && letter <= 'z' || letter >= 'A' && letter <= 'Z';
}
bool isABigLetter(char letter)
{
	return letter >= 'A' && letter <= 'Z';
}
bool isADigit(char digit)
{
	return digit >= '0' && digit <= '9';
}
bool smallLettersOnly(const MyString& strToCheck)     
{
	const char* str = strToCheck.c_str(); 
	while (*str)
	{
		if (!isASmallLetter(*str))
		{
			return false;
		}
		str++;
	}
	return true;
}

bool isConditionFilled(const char* str, bool (*pred)(char))
{
	while (*str)
	{
		if (pred(*str))
		{
			return true;
		}
		str++;
	}
	return false;
}

bool containsADigit(const MyString& str)
{
	return isConditionFilled(str.c_str(), isADigit);
}
bool containsABigLetter(const MyString& str)
{
	return isConditionFilled(str.c_str(), isABigLetter);
}
bool containsASmallLetter(const MyString& str)
{
	return isConditionFilled(str.c_str(), isASmallLetter);
}

