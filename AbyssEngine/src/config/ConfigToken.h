#pragma once
#include <string>

namespace abyssengine {
	struct ConfigToken
	{
		enum types { STRING, INT, FLOAT, BOOL };
		types type;

		ConfigToken(types type)
		{
			this->type = type;
		}

		virtual std::string toString() = 0;
	};

	struct ConfigStringToken : public ConfigToken
	{
		std::string data;

		ConfigStringToken(const std::string& data) : ConfigToken(types::STRING)
		{
			this->data = data;
		}

		std::string toString()
		{
			return data;
		}
	};

	struct ConfigfloatToken : public ConfigToken
	{
		float data;

		ConfigfloatToken(float data) : ConfigToken(types::FLOAT)
		{
			this->data = data;
		}

		std::string toString()
		{
			return std::to_string(data);
		}
	};

	struct ConfigBoolToken : public ConfigToken
	{
		bool data;

		ConfigBoolToken(bool data) : ConfigToken(types::BOOL)
		{
			this->data = data;
		}

		std::string toString()
		{
			return (data) ? "true" : "false";
		}
	};
}