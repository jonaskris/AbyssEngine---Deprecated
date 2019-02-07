#pragma once
#include <map>
#include "ConfigToken.h"
namespace abyssengine { namespace ConfigReader {
	std::map<ConfigStringToken*, ConfigToken*> readConfig(const char* filepath);
}}