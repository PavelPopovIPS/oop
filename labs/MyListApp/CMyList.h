#pragma once
#include <iostream>
#include <sstream>

template <typename T>
struct Node
{
	Node(const T& elem)
		: m_elem(elem)
	{
	}

	T m_elem;
	std::shared_ptr<Node<T>> next = nullptr;
	std::shared_ptr<Node<T>> prev = nullptr;
};

template <class T>
class CMyList
{
public:
	CMyList() = default;
	CMyList(CMyList const& other) = default;

	bool Push_front(const T& elem)
	{
		std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(elem);

		if (m_pHead == nullptr && m_pTail == nullptr)
		{
			m_pHead = node;
			m_pTail = node;
		}
		else
		{
			m_pHead->prev = node;
			node->next = m_pHead;
			m_pHead = node;
		}

		++m_count;
		return true;
	}

	size_t Size() const
	{
		return m_count;
	}

	std::shared_ptr<Node<T>> Begin() const
	{
		return m_pHead;
	}

	CMyList<T> const operator=(const CMyList<T>& list) const
	{
		return *this;
	}

private:
	std::shared_ptr<Node<T>> m_pHead = nullptr;
	std::shared_ptr<Node<T>> m_pTail = nullptr;
	size_t m_count = 0;
};

template <class T>
std::ostream& operator<<(std::ostream& stream, CMyList<T> const& list)
{
	auto it = list.Begin();

	if (it == nullptr)
	{
		return stream;
	}

	while (it)
	{
		stream << it->m_elem;
		stream << std::endl;
		it = it->next;
	}

	return stream;
}
