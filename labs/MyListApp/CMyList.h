#pragma once
#include <iostream>
#include <iterator>
#include <sstream>

template <typename T>
struct Node
{
	Node() = default;

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

template <class T>
class CMyList
{
public:
	CMyList()
		: m_pTail(new Node<T>())
		, m_pHead(m_pTail)
	{
	}

	CMyList(CMyList<T> const& list)
		: m_pTail(new Node<T>())
		, m_pHead(m_pTail)
	{
		if (this != &list)
		{
			for (auto it = list.begin(); it != list.end(); ++it)
			{
				Node<T>* newNode = new Node<T>(*it);

				if (m_pHead == m_pTail)
				{
					newNode->next = m_pTail;
					newNode->prev = m_pTail;

					m_pTail->next = newNode;
					m_pTail->prev = newNode;

					m_pHead = newNode;
				}
				else
				{
					Node<T>* lastNode = m_pTail->prev;

					newNode->next = lastNode->next;
					lastNode->next = newNode;
					newNode->prev = lastNode;
					m_pTail->prev = newNode;
				}
				++m_count;
			}
		}
	}

	~CMyList()
	{
		while (m_pHead)
		{
			m_pTail->next = nullptr;
			Node<T>* tmp = m_pHead;
			m_pHead = m_pHead->next;
			delete tmp;
		}
	}

	template <typename T>
	class ListConstIterator
	{
	public:
		ListConstIterator(Node<T>* node)
			: m_pNode(node)
		{
		}

		using difference_type = T;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::bidirectional_iterator_tag;

		Node<T>* GetNode() const
		{
			return m_pNode;
		}

		const T& operator*() const
		{
			return m_pNode->m_elem;
		}

		const ListConstIterator<T>& operator++()
		{
			m_pNode = m_pNode->next;
			return *this;
		}

		const ListConstIterator<T>& operator++(int d)
		{
			m_pNode = m_pNode->next;
			return *this;
		}

		const ListConstIterator<T>& operator--()
		{
			m_pNode = m_pNode->prev;
			return *this;
		}

		const ListConstIterator<T>& operator--(int d)
		{
			m_pNode = m_pNode->prev;
			return *this;
		}

		bool operator!=(const ListConstIterator<T>& it) const
		{
			return m_pNode != it.m_pNode;
		}

	protected:
		Node<T>* m_pNode = nullptr;
	};

	template <class T>
	class Iterator : public ListConstIterator<T>
	{
	public:
		Iterator(Node<T>* node)
			: ListConstIterator<T>(node)
		{
		}

		T& operator*() const
		{
			return this->m_pNode->m_elem;
		}

		Iterator<T>& operator++()
		{
			this->m_pNode = this->m_pNode->next;
			return *this;
		}

		Iterator<T>& operator++(int d)
		{
			this->m_pNode = this->m_pNode->next;
			return *this;
		}

		Iterator<T>& operator--()
		{
			this->m_pNode = this->m_pNode->prev;
			return *this;
		}

		Iterator<T>& operator--(int d)
		{
			this->m_pNode = this->m_pNode->prev;
			return *this;
		}
	};

	bool Push_front(const T& elem)
	{
		Node<T>* newNode = new Node<T>(elem);

		if (m_pHead == m_pTail)
		{
			AddFirstNode(newNode);

			++m_count;
			return true;
		}

		newNode->prev = m_pHead->prev;
		m_pHead->prev = newNode;
		newNode->next = m_pHead;
		m_pHead = newNode;

		++m_count;
		return true;
	}

	bool Push_back(const T& elem)
	{
		Node<T>* newNode = new Node<T>(elem);

		if (m_pHead == m_pTail)
		{
			AddFirstNode(newNode);

			++m_count;
			return true;
		}

		Node<T>* lastNode = m_pTail->prev;

		newNode->next = lastNode->next;
		lastNode->next = newNode;
		newNode->prev = lastNode;
		m_pTail->prev = newNode;

		++m_count;
		return true;
	}

	ListConstIterator<T> begin() const
	{
		ListConstIterator<T> it = ListConstIterator<T>(m_pHead);
		return it;
	}

	Iterator<T> begin()
	{
		Iterator<T> it = Iterator<T>(m_pHead);
		return it;
	}

	ListConstIterator<T> end() const
	{
		ListConstIterator<T> it = ListConstIterator<T>(m_pTail);
		return it;
	}

	Iterator<T> end()
	{
		Iterator<T> it = Iterator<T>(m_pTail);
		return it;
	}

	std::reverse_iterator<T> rbegin() const
	{
		// Iterator<T> it = Iterator<T>(m_pTail->prev);
		std::reverse_iterator<T> it = std::make_reverse_iterator(end());
		return it;
	}

	std::reverse_iterator<T> rend() const
	{
		// Iterator<T> it = Iterator<T>(m_pHead->prev);
		std::reverse_iterator<T> it = std::make_reverse_iterator(begin());
		return it;
	}

	size_t Size() const
	{
		return m_count;
	}

	bool Insert(Iterator<T>& it, const T& elem)
	{
		Node<T>* newNode = new Node<T>(elem);
		Node<T>* curNode = it.GetNode();

		if (m_pHead == m_pTail)
		{
			AddFirstNode(newNode);

			++m_count;
			return true;
		}

		auto prevNode = curNode->prev;

		if (curNode == m_pTail)
		{
			prevNode->next = newNode;
			newNode->prev = prevNode;
			newNode->next = m_pTail;
			m_pTail->prev = newNode;

			++m_count;
			return true;
		}

		if (curNode == m_pHead)
		{
			m_pHead = newNode;
		}

		newNode->prev = curNode->prev;
		curNode->prev = newNode;

		newNode->next = curNode;
		prevNode->next = newNode;

		++m_count;
		return true;
	}

	bool Erase(Iterator<T>& it)
	{
		if (m_pHead == m_pTail)
		{
			return false;
		}

		Node<T>* curNode = it.GetNode();
		Node<T>* prevNode = curNode->prev;
		Node<T>* nextNode = curNode->next;

		if (curNode == m_pHead)
		{
			m_pHead = nextNode;
		}

		if (curNode == m_pTail)
		{
			return false;
		}

		nextNode->prev = prevNode;
		prevNode->next = nextNode;

		curNode->next = nullptr;
		curNode->prev = nullptr;

		delete curNode;

		--m_count;
		return true;
	}

	CMyList<T>& operator=(CMyList<T> const& list)
	{
		if (this != &list)
		{
			CMyList tmpCopy(list);
			std::swap(m_pTail, tmpCopy.m_pTail);
			std::swap(m_pHead, tmpCopy.m_pHead);
			std::swap(m_count, tmpCopy.m_count);
		}
		return *this;
	}

private:
	void AddFirstNode(Node<T>* newNode)
	{
		newNode->next = m_pTail;
		newNode->prev = m_pTail;

		m_pTail->next = newNode;
		m_pTail->prev = newNode;

		m_pHead = newNode;
	}

	Node<T>* m_pTail = nullptr;
	Node<T>* m_pHead = nullptr;
	size_t m_count = 0;
};
