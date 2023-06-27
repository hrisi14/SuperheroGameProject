#pragma once
#include "MyString.h"

bool isASmallLetter(char letter);  
bool isABigLetter(char letter);
bool isADigit(char digit);
bool smallLettersOnly(const MyString& strToCheck);
bool isConditionFilled(const char* str, bool (*pred)(char));
bool containsADigit(const MyString& str);
bool containsABigLetter(const MyString& str);
bool containsASmallLetter(const MyString& str);
