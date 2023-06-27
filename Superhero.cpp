#include "Superhero.h"

Superhero::Superhero() {}

Superhero::Superhero(const MyString& name, const MyString& surname, const MyString& nickname, size_t powerSize, unsigned price, Mode mode, const char* powerStr)
{
	setNickname(nickname);
	setName(name);
	setSurname(surname);
	setPowerSize(powerSize);
	setPrice(price);
	setPower(powerStr);
	setMode(mode);
}

void Superhero::setNickname(const MyString& nickname)
{
	if (nickname.c_str())
	{
		this->nickname = nickname;
	}
}
void Superhero::setName(const MyString& name)
{
	if (name.c_str())
	{
		this->name = name;
	}
}
void Superhero::setSurname(const MyString& surname)
{
	if (surname.c_str())
	{
		this->surname = surname;
	}
}
void Superhero::setPowerSize(size_t powerSize)
{
	if (powerSize >= MIN_POWER_SIZE && powerSize <= MAX_POWER_SIZE)
	{
		this->powerSize = powerSize;
	}
}
void Superhero::setPrice(unsigned price)
{
	if (price >= MIN_PRICE && price <= MAX_PRICE)
	{
		this->price = price;
	}
}

void Superhero::setPower(const char* powerStr)
{
	if (strcmp(powerStr, "fire") == 0)
	{
		power = PowerType::fire;
	}
	else if (strcmp(powerStr, "water") == 0)
	{
		power = PowerType::water;
	}
	else  if (strcmp(powerStr, "earth") == 0)
	{
		power = PowerType::earth;
	}
	else
	{
		throw std::exception("Error! Invalid power type!");
	}
}

void Superhero::setMode(Mode mode)
{
	if (mode != Mode::attack && mode != Mode::defense && mode != Mode::neutral)
	{
		throw std::exception("Error! Invalid hero's mode!");
	}

	if (isBought && mode == Mode::neutral)
	{
		throw std::exception("Error! A hero that has been bought can NOT be in a neutral mode!");
	}

	this->mode = mode;
}

void Superhero::setIsBought(bool bought)
{
	isBought = bought;
}

PowerType Superhero::getPower() const
{
	return power;
}

size_t Superhero::getPowerSize() const
{
	return powerSize;
}

Mode Superhero::getMode() const
{
	return mode;
}
const MyString& Superhero::getNickname() const
{
	return nickname;
}
bool Superhero::getIsBought() const
{
	return isBought;
}

void Superhero::readFromBinaryFile(std::ifstream& ifs)
{
	name << ifs;
	surname << ifs;
	nickname << ifs;
	size_t powerNumber, modeNumber;

	ifs.read((char*)&powerSize, sizeof(powerSize));
	ifs.read((char*)&price, sizeof(price));
	ifs.read((char*)&powerNumber, sizeof(powerNumber));
	ifs.read((char*)&modeNumber, sizeof(modeNumber));

	switch (powerNumber)
	{
	case 1: power = PowerType::fire; break;
	case 2: power = PowerType::water; break;
	case 3: power = PowerType::earth; break;
	}

	switch (modeNumber)
	{
	case 1: mode = Mode::attack; break;
	case 2: mode = Mode::defense; break;
	}
}

void Superhero::saveToBinaryFile(std::ofstream& ofs)
{
	name >> ofs;
	surname >> ofs;
	nickname >> ofs;
	size_t powerNumber, modeNumber;

	switch (power)
	{
	case PowerType::fire: powerNumber = 1; break;
	case PowerType::water: powerNumber = 2; break;
	case PowerType::earth: powerNumber = 3; break;
	}
	switch (mode)
	{
	case Mode::attack: modeNumber = 1; break;
	case Mode::defense: modeNumber = 2; break;
	}
	ofs.write((char*)&powerSize, sizeof(powerSize));
	ofs.write((char*)&price, sizeof(price));
	ofs.write((char*)&powerNumber, sizeof(powerNumber));
	ofs.write((char*)&modeNumber, sizeof(modeNumber));
}

void Superhero::printAll() const
{
	std::cout << "Superhero's detailed information:" << std::endl;
	std::cout << "Name: " << name << std::endl;
	std::cout << "Surname: " << surname << std::endl;
	std::cout << "Nickname: " << nickname << std::endl;

	std::cout << "Power: ";
	switch (power)
	{
	case PowerType::fire: std::cout << "fire" << std::endl; break;
	case PowerType::water: std::cout << "water" << std::endl; break;
	case PowerType::earth: std::cout << "earth" << std::endl; break;
	}
	std::cout << "Power size: " << powerSize << std::endl;
	std::cout << "Price: " << price << std::endl;
}

int Superhero::comparePowerTypes(PowerType first, PowerType second) const
{
	if (first == second)
	{
		return 0;
	}

	if (first == PowerType::fire)
	{
		if (second == PowerType::earth)
		{
			return 1;
		}
		if (second == PowerType::water)
		{
			return -1;
		}
	}
	if (first == PowerType::earth)
	{
		if (second == PowerType::fire)
		{
			return -1;
		}
		if (second == PowerType::water)
		{
			return 1;
		}
	}

	if (first == PowerType::water)
	{
		if (second == PowerType::earth)
		{
			return -1;
		}
		if (second == PowerType::fire)
		{
			return 1;
		}
	}


}
void Superhero::printGeneralInfo() const
{
	std::cout << "Name: " << name << std::endl;
	std::cout << "Surname: " << surname << std::endl;
	std::cout << "Nickname: " << nickname << std::endl;

	std::cout << "Power: ";
	switch (power)
	{
	case PowerType::fire: std::cout << "fire" << std::endl; break;
	case PowerType::water: std::cout << "water" << std::endl; break;
	case PowerType::earth: std::cout << "earth" << std::endl; break;
	}

	std::cout << "Price: " << price << std::endl;
}
bool Superhero::compareNickname(const MyString& enteredNickname) const
{
	return nickname == enteredNickname;
}

void Superhero::upgrade()            //upgrades a hero's powerType to the next level and adds up a
{								     //constant amount of points to their power size
	if (power == PowerType::earth)
	{
		power = PowerType::fire;      //(fire->earth->water->fire according to the task)
	}
	else if (power == PowerType::fire)
	{
		power = PowerType::water;
	}
	else
	{
		power = PowerType::earth;
	}
	setPowerSize(powerSize + POWER_UPGRATION);

}


