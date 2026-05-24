#pragma once
#include "OrderedMapTraits.h"

namespace FIEAGameEngine
{
	template <typename Key, typename Value, typename LessThanFunctor = std::less<Key>>
	class OrderedMap final : public RedBlackTree<OrderedMapTraits<Key, Value, LessThanFunctor, false>>
	{
	public:
		using BaseClass = RedBlackTree<OrderedMapTraits<Key, Value, LessThanFunctor, false>>;
		using KeyType = typename BaseClass::KeyType;
		using ValueType = typename BaseClass::ValueType;
		using KeyValueType = typename BaseClass::KeyValueType;
		using KeyCompare = typename BaseClass::KeyCompare;
		using KeyValueCompare = typename BaseClass::KeyValueCompare;
		using Iterator = typename BaseClass::Iterator;
		using ConstIterator = typename BaseClass::ConstIterator;

		OrderedMap() = default;
		OrderedMap(std::initializer_list<KeyValueType> iList);
		OrderedMap(OrderedMap const& other);
		OrderedMap(OrderedMap&& other);
		OrderedMap& operator=(OrderedMap const& other);
		OrderedMap& operator=(OrderedMap&& other);
		virtual ~OrderedMap() = default;

		using BaseClass::Insert;		//Disables function hiding by moving base Insert into derived scope.
		std::pair<Iterator, bool> Insert(KeyType const& key, ValueType const& value);
	};
}
#include "OrderedMap.inl"