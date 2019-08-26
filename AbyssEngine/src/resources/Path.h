#pragma once
#include <iostream>
#include <filesystem>
#include <regex>
#include <iostream>
#include <string>

namespace abyssengine {
	namespace resources {
		struct Path
		{
			std::vector<std::string> components;

			std::string parentPath;
			std::string name;
			std::string extension;

			/*
				Parses parentPath, name and extension from string.
			*/
			Path(const std::string& path)
			{
				size_t lastSeparatorPos = path.find_last_of("\\/");
				size_t extensionPos = path.find_last_of(".");

				if (lastSeparatorPos != std::string::npos) // If has parentPath
				{
					parentPath = path.substr(0, lastSeparatorPos);
					if (extensionPos != std::string::npos && extensionPos > lastSeparatorPos) // If has extension
					{
						extension = path.substr(extensionPos + 1, path.size() - extensionPos - 1);
						name = path.substr(lastSeparatorPos + 1, extensionPos - lastSeparatorPos - 1);
					}
					else { // Doesent have extension
						extension = "";
						name = path.substr(lastSeparatorPos + 1, path.size() - lastSeparatorPos - 1);
					}
				}
				else { // Doesent have parentPath
					parentPath = "";
					if (extensionPos != std::string::npos) // If has extension
					{
						extension = path.substr(extensionPos + 1, path.size() - extensionPos - 1);
						name = path.substr(0, extensionPos);
					}
					else { // Doesent have extension
						extension = "";
						name = path;
					}
				}

				components = splitPath(path);
			}


			Path(const Path & path) : parentPath(path.parentPath), name(path.name), extension(path.extension), components(path.components) { };

			/*
				entry: filesystem directory entry.
			*/
			Path(const std::filesystem::directory_entry & entry) :
				parentPath(entry.path().parent_path().string()),
				name(entry.path().stem().generic_string()),
				extension([&]() { std::string lambdaExtension = entry.path().extension().generic_string(); return lambdaExtension.substr(lambdaExtension.find('.') + 1, std::string::npos); }()),
				components(splitPath(entry.path().string()))
			{ }

			bool isFile() const { return !extension.empty(); };
			bool isDirectory() const { return !isFile(); };

			const std::vector<std::string>& getComponents() const { return components; }

			std::string getFullPath() const
			{
				return parentPath + ((parentPath.empty()) ? ("") : ("/")) + name + (!extension.empty() ? ("." + extension) : (""));
			}

			/*
				Retrieves paths of children.
			*/
			std::vector<Path> getChildren()
			{
				std::vector<Path> returnVector;
				if (!isDirectory())
					return returnVector;

				try {
					for (const auto& entry : std::filesystem::directory_iterator(getFullPath()))
						returnVector.emplace_back(entry);

				}
				catch (std::exception & e) {
					std::cerr << e.what() << std::endl;
					/// Todo: log
				}
				return returnVector;
			}

			/*
				Retrieves paths to all children, including children of children.
			*/
			std::vector<Path> getChildrenRecursive()
			{
				std::vector<Path> paths = getChildren();
				for (size_t i = 0; i < paths.size(); i++)
				{
					std::vector<Path> childPaths = paths.at(i).getChildrenRecursive();
					std::copy(childPaths.begin(), childPaths.end(), std::back_inserter(paths));
				}

				return paths;
			}

			/*
				Retrieves paths of siblings.
			*/
			std::vector<Path> getSiblings()
			{
				std::vector<Path> returnVector;

				for (const auto& entry : std::filesystem::directory_iterator(parentPath))
					returnVector.emplace_back(entry);

				return returnVector;
			}

			/*
				Checks in reverse order if lhs is a subset of rhs.
			*/
			bool isSubset(const Path & other)
			{
				const std::vector<std::string> otherComponents = other.getComponents();

				if (components.size() > otherComponents.size())
					return false;

				for (size_t i = 0; i < components.size(); i++)
					if (components.at(components.size() - i - 1) != otherComponents.at(otherComponents.size() - i - 1))
						return false;

				return true;
			}

			static std::vector<std::string> splitPath(const std::string & path)
			{
				std::vector<std::string> components;

				std::regex delimiterSplitter(R"(\.\.|[^\\/.]+)");

				auto begin = std::sregex_iterator(path.begin(), path.end(), delimiterSplitter);
				auto end = std::sregex_iterator();

				for (auto it = begin; it != end; it++)
					components.push_back((*it).str());

				return components;
			}

			friend std::ostream& operator<<(std::ostream & out, const Path & path);
		};

		inline std::ostream& operator<<(std::ostream & out, const Path & path)
		{
			out << path.getFullPath();
			return out;
		}
	}
}