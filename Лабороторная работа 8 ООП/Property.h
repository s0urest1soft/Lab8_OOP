#pragma once
#include <string>
#include "Ijsonio.h"
class Property : public Ijsonio
{
	protected:
		unsigned int worth;
	public:
		Property();
		Property(unsigned int worth);
		virtual double calculateTax() const = 0;
		double IncomeTax() const;
		void setWorth(unsigned int worth);
		virtual std::string getProp() const = 0;
		unsigned int getWorth();
		
};


