#pragma once
#include "Property.h"
#include "tax.h"
#include <string>
class Car : public Property
{
private:
    double horsepower;
public:
    Car() = default;
    Car(unsigned int worth, double horsepower);
    double calculateTax() const;
    std::string getProp() const;
    void fromJson(nlohmann::json json);
    nlohmann::json toJson();

};
