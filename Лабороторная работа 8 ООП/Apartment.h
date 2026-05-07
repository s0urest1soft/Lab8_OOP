#pragma once
#include "Property.h"
#include "tax.h"
class Apartment : public Property
{
	private:
		double square;
	public:
		Apartment() = default;
		Apartment( unsigned int worthV, double square);
		double calculateTax() const;
		double getSquare();
		void setSquare(double square);
		std::string getProp() const;
		void fromJson(nlohmann::json json);
		nlohmann::json toJson();
};

