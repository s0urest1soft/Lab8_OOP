#pragma once
#include <json.hpp>
class Ijsonio
{
public:
	virtual void fromJson(nlohmann::json json) = 0;
	virtual nlohmann::json toJson() = 0;
	virtual ~Ijsonio() = default;
};

