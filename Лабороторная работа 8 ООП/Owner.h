#pragma once
#include <iostream>
#include <vector>
#include "Property.h"
#include "Ijsonio.h"
#include "PropertySimpleFactory.h"
class Owner
{
	private:
		std::string fullname;
		std::string INN;
		std::vector<Property*> properties;
	public:
		Owner() = default;
		Owner(std::string fullname, std::string INN);
		void addProperty(Property* property);
		void removeProperty(Property* property);
		std::string getFullname() const;
		std::vector<Property*> getProperties() const;
		void fromJson(nlohmann::json& json);
		double totalTax();
		nlohmann::json toJson();
};

