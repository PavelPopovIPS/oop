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

	template <class T>
	class Iterator
	{
	public:
		Iterator(Node<T>* node)
			: m_pNode(node)
		{
			std::cout << "Iterator(Node<T>* node)\n ";
		}

		Iterator(const Iterator<T>&) = default;

		Iterator<T>(Iterator<T>&& other)
			: m_pNode(other.m_pNode)
		{
			std::cout << "Iterator<T>(Iterator<T>&& other)\n";
			other.m_pNode = nullptr;
		}

		Iterator<T>& operator=(Iterator<T>&&)
		{
			std::cout << "Iterator<T> & operator=(Iterator<T>&&)\n ";
			return *this;
		}

		~Iterator<T>()
		{
			std::cout << "~Iterator<T>() \n ";
		}

		void update(Node<T>* node)
		{
			m_pNode = node;
		}

		const T& operator*() const
		{
			return m_pNode->m_elem;
		}

	private:
		Node<T>* m_pNode = nullptr;
	};

	bool push_front(const T& elem)
	{
		Node<T> node(elem);

		if (m_pHead == nullptr && m_pTail == nullptr)
		{
			m_pHead = &node;
			// bg->update(m_pHead);
			m_pTail = &node;

			// std::cout << "push_front Heat ref to " << m_pHead->m_elem << std::endl;
			// std::cout << "push_front Tail ref to " << m_pTail->m_elem << std::endl;
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

	Iterator<T> begin() const
	{
		Iterator<T> it = Iterator<T>(m_pHead);
		return it;
		//  return *new Iterator<T>(m_pHead);
		// return *bg;
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
	// Iterator<T>* bg = new Iterator<T>(m_pHead);
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
