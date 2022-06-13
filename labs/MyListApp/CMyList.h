#pragma once
#include <iostream>
#include <sstream>

template <typename T>
struct Node
{
	Node(T&& elem)
		: m_elem(std::move(elem))
	{
	}

	Node(const T& elem)
		: m_elem(elem)
	{
	}

	T m_elem;
	Node<T>* next = nullptr;
	Node<T>* prev = nullptr;
};

// template <typename T>

template <class T>
class CMyList
{
public:
	CMyList() = default;
	CMyList(CMyList const& other) = default;

	class Iterator
	{
	public:
		Iterator(Node<T>* node)
			: m_pNode(node)
		{
		}

		Iterator(const Iterator& other) = default;

		Iterator(Iterator&& other)
			: m_pNode(other.m_pNode)
		{
			other.m_pNode = nullptr;
		};

		T getValue() const
		{
			return m_pNode->m_elem;
		}

		T& operator*() const
		{
			return m_pNode->m_elem;
		}

		Node<T>* m_pNode = nullptr;

	private:
	};

	bool push_front(const T& elem)
	{
		Node<T> node(elem);

		if (m_pHead == nullptr && m_pTail == nullptr)
		{
			m_pHead = &node;
			m_pTail = &node;

			std::cout << "push_front Heat ref to " << m_pHead->m_elem << std::endl;
			std::cout << "push_front Tail ref to " << m_pTail->m_elem << std::endl;
		}
		// else
		//{
		//	m_pHead->prev = &node;
		//	node.next = m_pHead;
		//	m_pHead = &node;
		// }

		++m_count;
		return true;
	}

	CMyList::Iterator& begin() const
	{
		CMyList::Iterator* it = new CMyList::Iterator(m_pHead);
		// CMyList::Iterator it(m_pHead);
		//  std::cout << "get value Begin is " << it.getValue() << std::endl;
		//  std::cout << "Begin *it is " << *it << std::endl;
		return *it;
	}

	size_t Size() const
	{
		return m_count;
	}

	CMyList<T> const operator=(const CMyList<T>& list) const
	{
		return *this;
	}

private:
	Node<T>* m_pHead = nullptr;
	Node<T>* m_pTail = nullptr;
	size_t m_count = 0;
};
//
// template <class T>
// std::ostream& operator<<(std::ostream& stream, CMyList<T> const& list)
//{
//	stream << list.m_pHead->m_elem;
//	stream << std::endl;
//
//	return stream;
//}
