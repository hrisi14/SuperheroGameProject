#include "Administrator.h"

Administrator::Administrator() :User()
{
	userType = UserType::administrator;
}

Administrator::Administrator(const MyString& name, const MyString& surname, const MyString& userName, const MyString& email, const MyString& password):
	User(name, surname, userName, email, password, UserType::administrator)
{
	userType = UserType::administrator;
}


User* Administrator::clone() const
{
	return new Administrator(*this);
}

