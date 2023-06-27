#include "User.h"

User::User() {}

User::User(const MyString& name, const MyString& surname, const MyString& userName, const MyString& email, const MyString& password, UserType type)
{
	setName(name);
	setSurname(surname);
	setUsername(username);
	setEmail(email);
	setPassword(password);
	setUserType(type);
}
void User::setUsername(const MyString& username)
{
	if (username.length() <= 16 && smallLettersOnly(username))
	{
		this->username = username;
	}
}
void User::setEmail(const MyString& email)
{
	this->email = email;
}
void User::setPassword(const MyString& password)
{
	if (containsADigit(password) && containsABigLetter(password) && containsASmallLetter(password))
	{
		this->password = password;
	}
}
void User::setName(const MyString& name)
{
	if (name.c_str())
	{
		this->name = name;
	}
}
void User::setSurname(const MyString& surname)
{
	if (surname.c_str())
	{
		this->surname = surname;
	}
}

void User::setUserType(UserType type)
{
	if (type != UserType::administrator && type != UserType::player)
	{
		throw std::exception("Error! Invalid user type!");
	}
	this->userType = type;

}

const MyString& User::getUsername() const
{
	return username;
}

UserType User::getUserType() const
{
	return userType;
}

bool User::comparePassword(const MyString& input) const
{
	return password == input;
}
bool User::compareUsername(const MyString& enteredUsername) const
{
	return username == enteredUsername;
}

void User::readFromBinaryFile(const MyString& fileName)
{
	std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary);

	if (!ifs.is_open())
	{
		throw std::exception("Error! File failed to open!");
	}
	name << ifs;
	surname << ifs;
	username << ifs;
	email << ifs;
	password << ifs;

	ifs.close();
}
void User::saveToBinaryFile(const MyString& fileName)
{
	std::ofstream ofs(fileName.c_str(), std::ios::out | std::ios::binary);
	if (!ofs.is_open())
	{
		throw std::exception("Error! File failed to open!");
	}

	ofs.clear();    //clears file's content and saves all thå updated information again 

	name >> ofs;
	surname >> ofs;
	username >> ofs;
	email >> ofs;
	password >> ofs;

	ofs.close();
}

void User::printInfo() const
{
	std::cout << name << std::endl;
	std::cout << surname << std::endl;
	std::cout << username << std::endl;
}

unsigned User::getNumberOfMoves() const
{
	return numberOfMoves;
}

void User::readFromStream(std::ifstream& ifs)
{
	name << ifs;
	surname << ifs;
	username << ifs;
	email << ifs;
	password << ifs;
}
void User::saveToStream(std::ofstream& ofs)
{
	name >> ofs;
	surname >> ofs;
	username >> ofs;
	email >> ofs;
	password >> ofs;
}

void User::generalInfo() const
{
	std::cout << "General information about user:" << std::endl;
	std::cout << name << std::endl;
	std::cout << surname << std::endl;
	std::cout << username << std::endl;
}

void User::incrementMoves()
{
	numberOfMoves++;
}

