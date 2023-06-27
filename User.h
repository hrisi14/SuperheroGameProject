#pragma once
#include <iostream>

#include "MyString.h"
#include "Utils.h"
#include <cstdlib> //for the random generation of heroes in one of the functions

const unsigned int m = 20;
const unsigned int j = 10;
const unsigned int x = 50;
const unsigned int z = 40;   //compensation
const unsigned int k = 30;

enum class UserType
{
	player,
	administrator
};
class User
{
protected:
	MyString name;
	MyString surname;
	MyString email;
	MyString username;   //MAX LENGTH: 16; small letters only
	MyString password;   // at least one big letter, a small one and a digit	
	UserType userType;
	unsigned numberOfMoves = 0;

public:
	bool loggedIn = false;
	User();
	User(const MyString& name, const MyString& surname, const MyString& userName, const MyString& email, const MyString& password, UserType type);
	virtual ~User() = default;

	void setUsername(const MyString& userName);   
	void setPassword(const MyString& password);
	void setEmail(const MyString& email);
	void setName(const MyString& name);
	void setSurname(const MyString& surname);
	void setUserType(UserType type);

	const MyString& getUsername() const;
	UserType getUserType() const;
	unsigned getNumberOfMoves() const;
	void incrementMoves();

	bool compareUsername(const MyString& enteredUsername) const;
	bool comparePassword(const MyString& input) const;

	virtual User* clone() const = 0;
	virtual void readFromBinaryFile(const MyString& fileName);         //there would be a separate file for every user named after them
	virtual void saveToBinaryFile(const MyString& fileName);          //that is why the parameters of these functions are 
	virtual void printInfo() const;                                   //names of files, not already opened streams
	virtual void generalInfo() const;
	virtual void readFromStream(std::ifstream&);
	virtual void saveToStream(std::ofstream&);
};


