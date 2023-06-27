#pragma once
#include <iostream>
#include "MyString.h"

const unsigned MIN_POWER_SIZE = 1;
const unsigned MAX_POWER_SIZE = 50;   
const unsigned MIN_PRICE = 1;
const unsigned MAX_PRICE = 100;  
const unsigned POWER_UPGRATION = 15;

enum class PowerType   					 
{
	fire,
	water,
	earth
};
enum class Mode
{
	attack,
	defense,
	neutral   //in case the hero is not bought yet
};
class Superhero
{
	MyString name;
	MyString surname;
	MyString nickname;

	size_t powerSize;
	unsigned price;
	PowerType power;
	Mode mode = Mode::neutral;
	bool isBought = false;

public:
	Superhero();
	Superhero(const MyString& name, const MyString& surname, const MyString& nickname, size_t powerSize, unsigned price, Mode mode, const char* powerStr);
	void setNickname(const MyString& nickname);
	void setName(const MyString& name);
	void setSurname(const MyString& surname);
	void setPowerSize(size_t powerSize);
	void setPrice(unsigned price);
	void setMode(Mode mode);
	void setIsBought(bool bought);
	void setPower(const char* powerStr);  //we use char* since the creation of a whole object
										  //of type 'MyString' in this case is pointless
	size_t getPowerSize() const;
	PowerType getPower() const;
	Mode getMode() const;
	const MyString& getNickname() const;
	bool getIsBought() const;

	void upgrade();
	bool compareNickname(const MyString& enteredNickname) const;
	int comparePowerTypes(PowerType first, PowerType second) const;   // returns 1 if (first>second), -1 - in the opposite case, and 0 if first=second

	void readFromBinaryFile(std::ifstream& ifs);
	void saveToBinaryFile(std::ofstream& ofs);
	void printAll() const;
	void printGeneralInfo() const;
};

