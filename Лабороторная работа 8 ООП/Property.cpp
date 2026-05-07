#include "Property.h"

Property::Property() :worth(0) {}
Property::Property(unsigned int worth)
{
	this->worth = worth;
}

double Property::IncomeTax() const
{
	return worth * 0.13;
}

void Property::setWorth(unsigned int worth)
{
	this->worth = worth;
}


unsigned int Property::getWorth()
{
	return worth;
}