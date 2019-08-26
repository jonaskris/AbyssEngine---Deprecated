#pragma once
#include <exception>
#include <string>

namespace abyssengine {
	namespace resources {
		struct FileCreationException : public std::exception
		{
			const std::string details;

			FileCreationException(const std::string& details) : details(details) { }

			const char* what() const throw()
			{
				return details.c_str();
			}
		};
	}
}