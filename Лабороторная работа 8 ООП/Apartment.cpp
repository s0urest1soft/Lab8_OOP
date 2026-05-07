#include "Apartment.h"

Apartment::Apartment(unsigned int worthV, double square)
{
	worth = worthV;
	this->square = square;
}

double Apartment::calculateTax() const
{
	if (square <= TAX::LIMIT_APARTMENT_SQUARE) return worth * TAX::APARTMENT_TAX;
	else return worth * TAX::APARTMENT_LUXURY_TAX;
}

double Apartment::getSquare()
{
	return square;
}

void Apartment::setSquare(double square)
{
	this->square = square;
}

std::string Apartment::getProp() const
{
	return " вартира";
}

void Apartment::fromJson(nlohmann::json json)
{
	if (json.contains("worth")) worth = json["worth"];
	if (json.contains("square")) square = json["square"];
}

nlohmann::json Apartment::toJson()
{
	nlohmann::json json;
	json["Apartmemt"]["tax"] = calculateTax();
	return json;
}
