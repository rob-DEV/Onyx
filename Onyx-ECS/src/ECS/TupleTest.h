#pragma once


#include <Onyx/Core/Core.h>
#include <tuple>

namespace Onyx {


	// Forward Declaration & Base Case -----------------------------------------
	template<size_t idx, typename T>
	struct GetHelper { };
	template <typename... T>
	struct Tuple { };

	// -------------------------------------------------------------------------
	// GetHelper ---------------------------------------------------------------
	template<typename T, typename... Rest>
	struct GetHelper<0, Tuple<T, Rest...>> { // Specialization for index 0
		static T get(Tuple<T, Rest...>& data) {
			return data.first;
		}
	};

	template<
		size_t idx,
		typename T,
		typename... Rest
	>
		struct GetHelper<idx, Tuple<T, Rest...>> { // GetHelper Implementation
		static auto get(Tuple<T, Rest...>& data) {
			return GetHelper<idx - 1, Tuple<Rest...>>::get(data.rest);
		}
	};

	// -------------------------------------------------------------------------
	// Tuple Implementation ----------------------------------------------------
	template<
		typename T,
		typename... Rest
	>
		struct Tuple<T, Rest...> {
		T                   first;
		Tuple<Rest...>      rest;
		Tuple(const T& f, const Rest&... r)
			: first(f)
			, rest(r...) {
		}
	};

	// -------------------------------------------------------------------------
	// -------------------------------------------------------------------------
	// get Implementation ------------------------------------------------------
	template<
		size_t idx,
		template <typename...> class Tuple,
		typename... Args
	>
		auto get(Tuple<Args...>& t) {
		return GetHelper<idx, Tuple<Args...>>::get(t);
	}
	// -------------------------------------------------------------------------

}
