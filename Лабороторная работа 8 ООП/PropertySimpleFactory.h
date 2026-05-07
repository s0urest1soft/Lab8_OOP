#pragma once
#include <string>
#include "Property.h"
#include "Apartment.h"
#include "Car.h"
#include "CountryHouse.h"
class PropertySimpleFactory
{
public:
	static Property* getProperty(std::string key);
};

