#pragma once

#include "stdafx.h"

template <typename T, typename Less = std::less<T>>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less = Less())
{
	if (arr.empty())
	{
		return false;
	}

	auto pmaxValue = &arr[0];

	for (auto& item : arr)
	{
		if (less(*pmaxValue, item))
		{
			pmaxValue = &item;
		}
	}

	maxValue = *pmaxValue;
	return true;
}
