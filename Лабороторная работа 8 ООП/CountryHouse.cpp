#include "CountryHouse.h"

CountryHouse::CountryHouse(unsigned int worth, double distance)
{
	this->worth = worth;
	this->distance = distance;
}
double CountryHouse::calculateTax() const
{
	if (distance <= TAX::LIMIT_DISTANCE_FROM_CITY) return worth * TAX::COUNTRY_HOUSE_BASE_TAX;
	else return worth * TAX::COUNTRY_HOUSE_TAX;
}

double CountryHouse::getDistanse()
{
	return distance;
}
std::string CountryHouse::getProp() const
{
	return "Загородный дом";
}
void CountryHouse::fromJson(nlohmann::json json)
{
	if (json.contains("worth")) worth = json["worth"];
	if (json.contains("distance")) distance = json["distance"];
}
nlohmann::json CountryHouse::toJson()
{
	nlohmann::json json;
	json["CountryHouse"]["tax"] = calculateTax();
	return json;
}