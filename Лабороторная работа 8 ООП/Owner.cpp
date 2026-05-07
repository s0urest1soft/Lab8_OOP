#include "Owner.h"
#include "Property.h"
#include <string>
#include <vector>
#include <iostream>

Owner::Owner(std::string fullname, std::string INN)
{
	this->fullname = fullname;
	if (INN.length() == 12)
	{
		bool not_digit_flag = false;
		for (char c : INN)
			if (!isdigit(c)) {
				not_digit_flag = true;
				break;
			}
		if (not_digit_flag) throw std::invalid_argument("ָֽֽ המכזום סמסעמÿעü טח צטפנ");
		else this->INN = INN;
	}
	else throw std::invalid_argument("ָֽֽ המכזום סמסעמÿעü טח 12 צטפנ");
}

void Owner::addProperty(Property* property) {
	if (property != nullptr) properties.push_back(property);
}

void Owner::removeProperty(Property* property) {
	for (size_t i = 0; i < properties.size(); ++i) {
		if (properties[i] == property) {
			properties.erase(properties.begin() + i);
			break;
		}
	}
}

std::string Owner::getFullname() const
{ 
	return fullname; 
}

std::vector<Property*> Owner::getProperties() const
{ 
	return properties;
}

void Owner::fromJson(nlohmann::json& json){
    if (json.contains("fullname")) fullname = json["fullname"];
    if (json.contains("inn")) INN = json["inn"];
    if (json.contains("properties") && json["properties"].is_array()) {
        for (const auto& elem : json["properties"]) {
            std::string key = elem.items().begin().key();
            Property* prop = PropertySimpleFactory::getProperty(key);

            if (prop) {
                prop->fromJson(elem[key]);
                properties.push_back(prop);
            }
        }
    }
}

double Owner::totalTax(){
    double total = 0;
    for (Property* prop : properties) total += prop->calculateTax();
    return total;
}

nlohmann::json Owner::toJson(){
    nlohmann::json res_json;
    res_json["fullname"] = fullname;  
	res_json["sumtax"] = totalTax();
    res_json["inn"] = INN;

    nlohmann::json prop_arr = nlohmann::json::array();
    for (Property* prop : properties) prop_arr.push_back(prop->toJson());   
    res_json["properties"] = prop_arr;
    return res_json;
}

