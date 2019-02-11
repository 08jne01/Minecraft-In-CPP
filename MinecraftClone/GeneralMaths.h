#pragma once
#include <vector>

template<typename T> std::vector<T> offVec(std::vector<T> vec, T val)

{
	std::vector<T> returnVec;
	for (int i = 0; i < vec.size(); i++)

	{
		returnVec.push_back(vec[i] + val);
	}
	return returnVec;
}

template<typename T> std::vector<T>  scalVec(std::vector<T> vec, T val)

{
	std::vector<T> returnVec;
	for (int i = 0; i < vec.size(); i++)

	{
		returnVec.push_back(vec[i] * val);
	}
	return returnVec;
}