#pragma once
#include "Property.h"
#include "tax.h"
#include <string>
class CountryHouse : public Property
{
    private:
        double distance;

    public:
        CountryHouse(unsigned int worth, double distance);
        CountryHouse() = default;
        double calculateTax() const;
        double getDistanse();
        std::string getProp() const;
        void fromJson(nlohmann::json json);
        nlohmann::json toJson();
};  