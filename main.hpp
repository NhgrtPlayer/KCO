
#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

class Item
{
	std::string name;
	float price;

public:
	Item(const std::string& newName, float newPrice) :
	name(newName),
	price(newPrice)
	{}

	Item(const Item& other) :
	name(other.getName()),
	price(other.getPrice())
	{}

	std::string getName() const { return (this->name); }
	float getPrice() const { return (this->price); }
};

#endif