#pragma once
#include <map>
#include "ConfigToken.h"

namespace ConfigReader
{
	std::map<ConfigStringToken*, ConfigToken*> readConfig(const char* filepath);
};