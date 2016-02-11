// Copyright  2016 Vlad Joss. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla
// Public License, v. 2.0.If a copy of the MPL was not distributed
// with this file, You can obtain one at http ://mozilla.org/MPL/2.0/.

#include <assert.h> 
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <numeric>

#pragma once

namespace rh
{
	extern std::default_random_engine RandomEngine;

	template<typename Iterator>
	auto randomElement(Iterator begin, Iterator end) -> decltype(*begin)
	{
		size_t size = end - begin;
		assert(size);

		std::uniform_int_distribution<size_t> distribution(0, size - 1);
		size_t pos = distribution(RandomEngine);

		return *(begin + pos);
	}

	template<typename Container>
	auto randomElement(const Container& container) -> decltype(*container.begin())
	{
		return randomElement(std::begin(container), std::end(container));
	} 
	
	template <template<class, class> class Container, class T, class A>
	size_t positionInRange(const Container<T, A>& container, T val)
	{
		T lowerBound = 0;
		for (Container<T, A>::const_iterator& it = container.begin(); it < container.end(); ++it)
		{
			assert(*it > 0);
			if ((lowerBound <= val) && (val < (lowerBound + *it)))
			{
				return it - container.cbegin();
			}
			lowerBound += *it;
		}

		return 0;
	}

	template<typename T> 
	size_t randomPositionInt(const std::vector<T>& weights)
	{
		auto second = ++weights.begin(); 
		T sum = std::accumulate(second, weights.end(), *weights.begin());
		assert(sum); 

		std::uniform_int_distribution<T> distribution(0, sum - 1);
		T val = (T)distribution(RandomEngine); 

		return positionInRange(weights, val);
	} 

	template<typename T>
	size_t randomPositionReal(const std::vector<T>& weights)
	{
		auto second = ++weights.begin();
		T sum = std::accumulate(second, weights.end(), *weights.begin());
		assert(sum);

		std::uniform_real_distribution<T> distribution(0, sum);
		T val = distribution(RandomEngine);  

		return positionInRange(weights, val);
	}
}






