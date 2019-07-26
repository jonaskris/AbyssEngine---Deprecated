#pragma once
#include <vector>
#include <utility>

namespace entitysystem
{
	/*
		Returns index of element in sorted vector equal to key using binary search.
	*/
	template <typename V, typename K, typename TypeToKey>
	int binarySearch(const std::vector<V>& vec, const K& key, const int& low, const int& high, TypeToKey typeToKey)
	{
		if (low > high)
			return -1;

		int mid = (int)low + (((int)high - (int)low) >> 1);

		if (typeToKey(vec.at(mid)) == key) return mid;
		if (typeToKey(vec.at(mid)) > key)
			return binarySearch(vec, key, low, mid - 1, typeToKey);
		else
			return binarySearch(vec, key, mid + 1, high, typeToKey);
	}

	/*
		Returns indices span of elements in sorted vector equal to element at index.
	*/
	template <typename T, typename TypeToKey>
	std::pair<size_t, size_t> getEqualNeighbours(const std::vector<T>& vec, const int& index, TypeToKey typeToKey)
	{
		if (index < 0)
			return std::pair(0, 0);

		T value = vec.at(index);

		int low = index;
		int high = index;

		while (!(low <= 0) && (typeToKey(vec.at(low - 1)) == typeToKey(value)))
			low--;

		while (!(high >= vec.size() - 1) && (typeToKey(vec.at(high + 1)) == typeToKey(value)))
			high++;

		return std::pair(low, high + 1);
	}


	/*
		Returns indices span of elements in sorted vector equal to key using binary search.
	*/
	template <typename V, typename K, typename TypeToKey>
	std::pair<size_t, size_t> binarySearchGroup(const std::vector<V>& vec, const K& key, const size_t& low, const size_t& high, TypeToKey typeToKey)
	{
		return getEqualNeighbours(vec, binarySearch(vec, key, low, high, typeToKey), typeToKey);
	}

	template <typename V, typename TypeToKey>
	void insertSorted(std::vector<V>& vec, const V& newElement, TypeToKey typeToKey)
	{
		bool inserted = false;
		for (auto it = vec.begin(); it != vec.end(); it++)
		{
			if (typeToKey(newElement) < typeToKey(*it))
			{
				vec.insert(it, newElement);
				inserted = true;
				break;
			}
		}
		if (!inserted)
			vec.push_back(newElement);
	}

	template <typename T, typename TypeToKey>
	void insertSortedReverse(std::vector<T>& vec, const T& newElement, TypeToKey typeToKey)
	{
		bool inserted = false;
		for (auto it = vec.rbegin(); it != vec.rend(); it++)
			if (typeToKey(*it) < typeToKey(newElement)) // <
			{
				vec.insert(it.base(), newElement);
				inserted = true;
				break;
			}

		if (!inserted)
			vec.push_back(newElement);
	}
}