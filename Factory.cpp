#include "Factory.h"

User* factory(unsigned typeNumber, const MyString& name, const MyString& surname, const MyString& userName, const MyString& email, const MyString& password)
{
	switch (typeNumber)
	{
	case 1: return new Administrator(name, surname, userName, email, password);
	case 2:return new Player(name, surname, userName, email, password);

	default: throw std::exception("Error! Invalid data! This game has only two type of users: administrators and players!");
	}
}
