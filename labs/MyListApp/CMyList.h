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

template <typename T>
struct BaseIterator
{
	~BaseIterator() = default;
	virtual std::shared_ptr<Node<T>> GetNode() const = 0;
};

template <typename T>
struct Iterator : public BaseIterator<T>
{
	Iterator(std::shared_ptr<Node<T>> node)
		: m_pNode(node)
	{
	}

	bool Next()
	{
		if (!hasNext())
		{
			return false;
		}

		m_pNode = m_pNode->next;
		return true;
	}

	bool hasNext() const
	{
		if (m_pNode->next == nullptr)
		{
			return false;
		}
		return true;
	}

	std::shared_ptr<Node<T>> GetNode() const override
	{
		return m_pNode;
	}

private:
	std::shared_ptr<Node<T>> m_pNode = nullptr;
};

template <typename T>
struct RIterator : public BaseIterator<T>
{
	RIterator(std::shared_ptr<Node<T>> node)
		: m_pNode(node)
	{
	}

	bool Prev()
	{
		if (!hasPrev())
		{
			return false;
		}

		m_pNode = m_pNode->prev;
		return true;
	}

	bool hasPrev() const
	{
		if (m_pNode->prev == nullptr)
		{
			return false;
		}
		return true;
	}

	std::shared_ptr<Node<T>> GetNode() const override
	{
		return m_pNode;
	}

private:
	std::shared_ptr<Node<T>> m_pNode = nullptr;
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

	bool Push_back(const T& elem)
	{
		std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(elem);

		if (m_pHead == nullptr && m_pTail == nullptr)
		{
			m_pHead = node;
			m_pTail = node;
		}
		else
		{
			m_pTail->next = node;
			node->prev = m_pTail;
			m_pTail = node;
		}

		++m_count;
		return true;
	}

	Iterator<T> Begin() const
	{
		Iterator<T> it(m_pHead);
		return it;
	}

	Iterator<T> End() const
	{
		Iterator<T> it(m_pTail);
		return it;
	}

	RIterator<T> RBegin() const
	{
		RIterator<T> it(m_pTail);
		return it;
	}

	Iterator<T> REnd() const
	{
		Iterator<T> it(m_pHead);
		return it;
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
	std::shared_ptr<Node<T>> m_pHead = nullptr;
	std::shared_ptr<Node<T>> m_pTail = nullptr;
	size_t m_count = 0;
};

template <class T>
std::ostream& operator<<(std::ostream& stream, CMyList<T> const& list)
{
	Iterator<T> it = list.Begin();
	if (it.GetNode() == nullptr)
	{
		return stream;
	}

	while (it.hasNext())
	{
		stream << it.GetNode()->m_elem;
		stream << std::endl;
		it.Next();
	}
	stream << it.GetNode()->m_elem;

	return stream;
}
