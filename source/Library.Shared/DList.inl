#pragma once

/// <summary>
/// The inline file containing the definition of each DList function declared in DList.h.
/// </summary>

#include "DList.h"

namespace FIEAGameEngine
{
	template<typename T>
	inline DList<T>::Node::Node(T const& data, Node* next, Node* previous)
		: mData(data), mNext(next), mPrevious(previous)
	{
	}

	template<typename T> typename
		inline DList<T>::Iterator& DList<T>::Iterator::operator++()
	{
		if (mNode != nullptr && mOwner != nullptr)
		{
			mNode = mNode->mNext;
		}
		return *this;
	}

	template<typename T> typename
		inline DList<T>::Iterator DList<T>::Iterator::operator++(int)
	{
		Iterator iteratorBeforeIncrement = *this;
		operator++();
		return iteratorBeforeIncrement;
	}

	template<typename T> typename
		inline DList<T>::Iterator& DList<T>::Iterator::operator--()
	{
		if (mNode != nullptr && mOwner != nullptr)
		{
			mNode = mNode->mPrevious;
		}
		return *this;
	}

	template<typename T> typename
		inline DList<T>::Iterator DList<T>::Iterator::operator--(int)
	{
		Iterator iteratorBeforeDecrement = *this;
		operator--();
		return iteratorBeforeDecrement;
	}

	template<typename T>
	inline bool DList<T>::Iterator::operator==(Iterator const& rhs) const
	{
		return (mOwner == rhs.mOwner) && (mNode == rhs.mNode);
	}

	template<typename T>
	inline bool DList<T>::Iterator::operator!=(Iterator const& rhs) const
	{
		return !(*this == rhs);
	}

	template<typename T>
	inline T& DList<T>::Iterator::operator*() const
	{
		return mNode->mData;
	}

	template<typename T>
	inline DList<T>::Iterator::Iterator(const DList& owner, Node* node) :
		mOwner(&owner), mNode(node)
	{

	}

	template<typename T>
	inline DList<T>::ConstIterator::ConstIterator(const Iterator& it)
	{
		mNode = it.mNode;
		mOwner = it.mOwner;
	}

	template<typename T> typename
		inline DList<T>::ConstIterator& DList<T>::ConstIterator::operator++()
	{
		if (mNode != nullptr && mOwner != nullptr)
		{
			mNode = mNode->mNext;
		}
		return *this;
	}

	template<typename T> typename
		inline DList<T>::ConstIterator DList<T>::ConstIterator::operator++(int)
	{
		ConstIterator iteratorBeforeIncrement = *this;
		mNode = mNode->mNext;
		return iteratorBeforeIncrement;
	}

	template<typename T> typename
		inline DList<T>::ConstIterator& DList<T>::ConstIterator::operator--()
	{
		if (mNode != nullptr && mOwner != nullptr)
		{
			mNode = mNode->mPrevious;
		}
		return *this;
	}

	template<typename T> typename
		inline DList<T>::ConstIterator DList<T>::ConstIterator::operator--(int)
	{
		ConstIterator iteratorBeforeDecrement = *this;
		operator--();
		return iteratorBeforeDecrement;
	}

	template<typename T>
	inline bool DList<T>::ConstIterator::operator==(ConstIterator const& rhs) const
	{
		return (mOwner == rhs.mOwner) && (mNode == rhs.mNode);
	}

	template<typename T>
	inline bool DList<T>::ConstIterator::operator!=(ConstIterator const& rhs) const
	{
		return !(*this == rhs);
	}

	template<typename T>
	inline T const& DList<T>::ConstIterator::operator*() const
	{
		return mNode->mData;
	}

	template<typename T>
	inline DList<T>::ConstIterator::ConstIterator(const DList& owner, Node* node) :
		mOwner(&owner), mNode(node)
	{

	}

	template<typename T>
	inline DList<T>::DList()
	{

	}

	template<typename T>
	inline DList<T>::DList(DList const& other)
	{
		*this = other;
	}

	template<typename T>
	inline DList<T>::DList(DList && other) :
		mFront(std::move(other.mFront)), mBack(std::move(other.mBack))
	{
		other.mFront = nullptr;
		other.mBack = nullptr;
		other.mSize = 0;
	}

	template<typename T>
	inline DList<T>::DList(std::initializer_list<T> iList)
	{
		for (auto& i: iList)
		{
			PushBack(i);
		}
	}

	template<typename T>
	inline DList<T>::~DList()
	{
		Clear();
	}

	template<typename T>
	inline DList<T>& DList<T>::operator=(const DList& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			for (auto& i : rhs)
			{
				PushBack(i);
			}
		}
		return *this;
	}

	template<typename T>
	inline DList<T>& DList<T>::operator=(DList&& rhs)
	{
		mFront = rhs.mFront;
		mBack = rhs.mBack;
		mSize = rhs.mSize;

		rhs.mFront = nullptr;
		rhs.mBack = nullptr;
		rhs.mSize = 0;

	}

	template<typename T>
	inline bool DList<T>::operator==(DList const& rhs) const
	{
		if (mSize == rhs.mSize)
		{
			ConstIterator left = cbegin(), right = rhs.cbegin();
			for (; left != cend() && right != rhs.cend(); left++, right++)
			{
				if (*left != *right)
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}

	template<typename T>
	inline bool DList<T>::operator!=(DList const& rhs) const
	{
		return !(*this == rhs);
	}

	template<typename T> typename
	inline DList<T>::Iterator DList<T>::begin() const
	{
		return DList<T>::Iterator(*this, mFront);
	}

	template<typename T> typename
	inline DList<T>::ConstIterator DList<T>::cbegin() const
	{
		return DList<T>::ConstIterator(*this, mFront);
	}

	template<typename T> typename
	inline DList<T>::Iterator DList<T>::end() const
	{
		return DList<T>::Iterator(*this, nullptr);
	}

	template<typename T> typename
	inline DList<T>::ConstIterator DList<T>::cend() const
	{
		return DList<T>::ConstIterator(*this, nullptr);
	}

	template<typename T> typename
	inline DList<T>::Iterator DList<T>::PushFront(T const& value)
	{
		Node * newFront = new Node(value);
		newFront->mNext = mFront;
		
		if (mSize)
		{
			mFront->mPrevious = newFront;
		}

		mFront = newFront;

		if (!mSize)
		{
			mBack = mFront;
		}
		mSize++;

		return Iterator(*this, newFront);
	}

	template <typename T> typename
	inline DList<T>::Iterator DList<T>::PopFront()
	{
		if (mSize == 0)
		{
			throw std::exception(listEmptyExceptionText.c_str());
		}

		Node* newFront = mFront->mNext;
		newFront->mPrevious = nullptr;

		delete mFront;

		if (mSize == 1)
		{
			mFront = mBack = nullptr;
		}
		else
		{
			mFront = newFront;
		}
		mSize--;

		return Iterator(*this, mFront);
	}

	template<typename T> typename
	inline DList<T>::Iterator DList<T>::PushBack(T const& value)
	{
		Node* newBack = new Node(value);

		if (mSize)
		{
			mBack->mNext = newBack;
			newBack->mPrevious = mBack;
		}

		mBack = newBack;
		
		if (!mSize)
		{
			mFront = mBack;
		}
		
		mSize++;

		return Iterator(*this, newBack);
	}

	template<typename T> typename
	inline DList<T>::Iterator DList<T>::PopBack()
	{
		if (!mSize)
		{
			throw std::exception(listEmptyExceptionText.c_str());
		}

		

		if (mSize == 1)
		{
			delete mBack;
			
			mFront = mBack = nullptr;
		}
		else
		{
			Node* newBack = mBack->mPrevious;
			newBack->mNext = nullptr;
			delete mBack;
			mBack = newBack;			
		}
		mSize--;

		return Iterator(*this, mBack);
	}

	template<typename T>
	inline bool DList<T>::IsEmpty() const
	{
		return mSize <= 0;
	}

	template<typename T>
	inline T & DList<T>::Front()
	{
		if (mSize == 0)
		{
			throw std::exception(listEmptyExceptionText.c_str());
		}
		return mFront->mData;
	}

	template<typename T>
	inline const T& DList<T>::Front() const
	{
		return const_cast<DList*>(this)->Front();
	}

	template<typename T>
	inline T& DList<T>::Back()
	{
		if (mSize == 0)
		{
			throw std::exception(listEmptyExceptionText.c_str());
		}
		return mBack->mData;
	}

	template<typename T>
	inline const T& DList<T>::Back() const
	{
		return const_cast<DList*>(this)->Back();
	}

	
	template<typename T>
	inline void DList<T>::Clear()
	{
		Node *currentNode = mFront, *nextNode = nullptr;

		while (currentNode != nullptr)
		{
			nextNode = currentNode->mNext;
			delete currentNode;
			currentNode = nextNode;
		}

		mFront = mBack = nullptr;
		mSize = 0;
	}

	template<typename T>
	inline size_t DList<T>::Size() const
	{
		return mSize;
	}

	template<typename T> typename
	inline DList<T>::Iterator DList<T>::InsertAfter(Iterator const& it, T const& value)
	{
		if (it.mOwner != this)
		{
			throw std::exception(iteratorFromOtherListExceptionText.c_str());
		}
		if (it == end())
		{
			return PushBack(value);
		}
		else
		{
			Node* node = new Node(value, it.mNode->mNext, it.mNode);
			node->mNext->mPrevious = node;
			node->mPrevious->mNext = node;
			mSize++;
			return it;
		}
		
	}

	template<typename T> typename
	inline DList<T>::Iterator DList<T>::Find(T const& value)
	{
		Iterator indexFound = end();
		DList<T>::Iterator it = begin();
		for (; it != end(); it++)
		{
			if (*it == value)
			{
				indexFound = it;
			}
		}
		return indexFound;
	}

	template<typename T> typename
	inline DList<T>::ConstIterator DList<T>::Find(T const& value) const
	{
		ConstIterator indexFound = cend();
		DList<T>::ConstIterator it = cbegin();
		for (; it < end(); it++)
		{
			if (*it == value)
			{
				indexFound = it;
			}
		}
		return indexFound;
	}

	template<typename T>
	inline void DList<T>::Remove(T const& value)
	{
		Iterator foundIt = Find(value);
		Remove(foundIt);
	}

	template<typename T>
	inline void DList<T>::Remove(Iterator const& it)
	{
		if (it.mOwner != this)
		{
			throw std::exception(iteratorFromOtherListExceptionText.c_str());
		}
		Node* nodeToRemove = it.mNode;
		if (nodeToRemove != nullptr)
		{
			if (nodeToRemove == mFront)
			{
				PopFront();
			}
			else if (nodeToRemove != mBack)
			{
				nodeToRemove->mPrevious->mNext = nodeToRemove->mNext;
				nodeToRemove->mNext->mPrevious = nodeToRemove->mPrevious;
				delete nodeToRemove;
				mSize--;
			}
			else
			{
				PopBack();
			}
		}
	}

	template <typename T>
	void DList<T>::Reverse()
	{
		Node* previous = nullptr;
		Node* current = mFront;
		Node* next = mFront ? mFront->mNext : nullptr;
		while (current)
		{
			current->mNext = previous;
			current->mPrevious = next;
			previous = current;
			current = next;
			next = next ? next->mNext : nullptr;			
		}
	}
}