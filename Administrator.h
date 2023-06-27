#pragma once
#include "User.h"

class Administrator : public User
{

public:
	Administrator();
	Administrator(const MyString& name, const MyString& surname, const MyString& userName, const MyString& email, const MyString& password);

	User* clone() const override;	

	//void readFromBinaryFile(std::ifstream& ifs);   // we use the base class'es functions
	//void saveToBinaryFile(std::ofstream& ofs);
	//the print function is taken from the base class User
};
