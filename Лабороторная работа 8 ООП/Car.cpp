#include "Car.h"

Car::Car(unsigned int worth, double horsepower)
{
    this->worth = worth;
    this->horsepower = horsepower;
}

double Car::calculateTax() const
{
    if (horsepower < TAX::LOW_HORSEPOWER) return worth * TAX::CAR_TAX;
    else if (horsepower > TAX::HIGH_HORSEPOWER) return worth * TAX::CAR_LUXURY_TAX;
    else return worth * TAX::CAR_TRUCK_TAX;
}
std::string Car::getProp() const
{
    return "Машина";
}
void Car::fromJson(nlohmann::json json)
{
    if (json.contains("worth")) worth = json["worth"];
    if (json.contains("horsepower")) horsepower = json["horsepower"];
}
nlohmann::json Car::toJson()
{
    nlohmann::json json;
    json["Car"]["tax"] = calculateTax();
    return json;
}

