// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cstddef>
#include "utils/mpl.h"

// Implementation 1:
//
// Tuple<T1,...,Tn> is TupleHelper<0,T1,...,Tn> where TupleHelper is expanded to
//
// struct TupleHelper<0,T1,...,Tn> : TupleValue<0,T1>, TupleHelper<1,T2,...,Tn> {
// }
//
// struct TupleHelper<1,T2,...,Tn> : TupleValue<1,T1>, TupleHelper<2,T2,...,Tn> {
// }
// ...
// struct Tuple3<n-1,Tn> : TupleValue<n-1,Tn> {
// }
//

template<std::size_t n, typename T>
struct TupleValue {
	T value;
};

template<std::size_t n, typename ...Ts>
struct TupleHelper;

template<std::size_t n, typename T, typename ...Ts>
struct TupleHelper<n, T, Ts...> : TupleValue<n, T>, TupleHelper<n + 1, Ts...> {
};

template<std::size_t n, typename T>
struct TupleHelper<n, T> : TupleValue<n, T> {
};

template<typename ...Ts>
struct Tuple: TupleHelper<0, Ts...> {
};

template<std::size_t n, typename ...Ts>
inline auto& get(Tuple<Ts...> &t) {
	using nth_type = typename mpl::Ith<n,mpl::TypeList<Ts...>>::type;
	return t.TupleValue<n, nth_type>::value;
}

template<std::size_t n, typename ...Ts>
inline const auto& get(const Tuple<Ts...> &t) {
	using nth_type = typename mpl::Ith<n,mpl::TypeList<Ts...>>::type;
	return t.TupleValue<n, nth_type>::value;
}

// Implementation2 2:
//
// Like implementation 1, but does not use TupleValue
//
// Tuple2<T1,...,Tn> is TupleHelper2<0,T1,...,Tn> where TupleHelper2 is expanded to
//
// struct TupleHelper2<0,T1,...,Tn> : TupleHelper2<1,T2,...,Tn> {
//	  T1 value
// }
//
// struct TupleHelper2<1,T2,...,Tn> : Tuple2<2,T2,...,Tn> {
//	  T2 value
// }
// ...
// struct TupleHelper2<n-1,Tn> {
//	  Tn value
// }
//
//

template<std::size_t n, typename ...Ts>
struct TupleHelper2;

template<std::size_t n, typename T1, typename T2, typename ...Ts>
struct TupleHelper2<n, mpl::TypeList<T1, T2, Ts...>> : TupleHelper2<n + 1,
		mpl::TypeList<T2, Ts...>> {
	T1 value;
};

template<std::size_t n, typename T>
struct TupleHelper2<n, mpl::TypeList<T>> {
	T value;
};

template<typename ...Ts>
struct Tuple2: TupleHelper2<0, mpl::TypeList<Ts...>> {
};

template<std::size_t n, typename ...Ts>
inline auto& get(Tuple2<Ts...> &t) {
	using nth_type = typename mpl::RemovePrefix<n,mpl::TypeList<Ts...>>::type;
	return t.TupleHelper2<n, nth_type>::value;
}

template<std::size_t n, typename ...Ts>
inline const auto& get(const Tuple2<Ts...> &t) {
	using nth_type = typename mpl::RemovePrefix<n,mpl::TypeList<Ts...>>::type;
	return t.TupleHelper2<n, nth_type>::value;
}


