#pragma once
#include <iostream>
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

	CMyList(CMyList const& other) = default;

	~CMyList()
	{
		while (m_pHead)
		{
			Node<T>* tmp = m_pHead;
			m_pHead = m_pHead->next;
			delete tmp;
		}
	}

	template <typename T>
	class ListConstIterator
	{
	public:
		// так стандартные библиотеки смогут работать с итераторами
		using iterator_category = std::bidirectional_iterator_tag;

		// const T& operator*() const;
	};

	template <class T>
	class Iterator : public ListConstIterator<T>
	{
	public:
		Iterator(Node<T>* node)
			: m_pNode(node)
		{
		}

		Iterator(const Iterator<T>&) = default;

		Iterator(Iterator<T>&& other)
			: m_pNode(other.m_pNode)
		{
			other.m_pNode = nullptr;
		}

		Node<T>* GetNode() const
		{
			return m_pNode;
		}

		T& operator*() const
		{
			return m_pNode->m_elem;
		}

		Iterator<T>& operator++()
		{
			m_pNode = m_pNode->next;
			return *this;
		}

		Iterator<T>& operator--()
		{
			m_pNode = m_pNode->prev;
			return *this;
		}

		Iterator<T>& operator=(const Iterator<T>&& it)
		{
			m_pNode = it.m_pNode;
			return *this;
		}

		bool operator!=(const Iterator<T>& it) const
		{
			return m_pNode != it.m_pNode;
		}

	private:
		Node<T>* m_pNode = nullptr;
	};

	bool push_front(const T& elem)
	{
		Node<T>* newNode = new Node<T>(elem);

		if (m_pHead == m_pTail)
		{
			m_pHead = newNode;

			m_pHead->next = m_pTail;
			m_pHead->prev = m_pTail;

			m_pTail->prev = m_pHead;
		}
		else
		{
			newNode->prev = m_pHead->prev;
			m_pHead->prev = newNode;
			newNode->next = m_pHead;
			m_pHead = newNode;
		}

		++m_count;
		return true;
	}

	bool push_back(const T& elem)
	{
		Node<T>* newNode = new Node<T>(elem);

		if (m_pHead == m_pTail)
		{
			m_pHead = newNode;

			m_pHead->next = m_pTail;
			m_pHead->prev = m_pTail;

			m_pTail->prev = m_pHead;
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
		return true;
	}

	Iterator<T> begin() const
	{
		Iterator<T> it = Iterator<T>(m_pHead);
		return it;
	}

	Iterator<T> end() const
	{
		Iterator<T> it = Iterator<T>(m_pTail);
		return it;
	}

	size_t size() const
	{
		return m_count;
	}

	bool insert(Iterator<T>& it, const T& elem)
	{
		Node<T>* newNode = new Node<T>(elem);
		Node<T>* curNode = it.GetNode();
		if (m_pHead == m_pTail)
		{
			m_pHead = newNode;

			m_pHead->next = m_pTail;
			m_pHead->prev = m_pTail;

			m_pTail->prev = m_pHead;

			++m_count;
			return true;
		}

		auto prevNode = curNode->prev;

		newNode->prev = curNode->prev;
		curNode->prev = newNode;
		newNode->next = curNode;
		prevNode->next = newNode;

		// TODO не работает с  пограничными знаениями

		++m_count;
		return true;
	}

	bool erase(Iterator<T>& it)
	{
		if (m_pHead == m_pTail)
		{
			return false;
		}
		else
		{
			Node<T>* curNode = it.GetNode();

			Node<T>* prevNode = curNode->prev;
			Node<T>* nextNode = curNode->next;

			prevNode->next = nextNode;
			nextNode->prev = prevNode;

			curNode->next = nullptr;
			curNode->prev = nullptr;

			delete curNode;
		}

		// TODO не работает с  пограничными знаениями

		--m_count;
		return true;
	}

	CMyList<T>& operator=(const CMyList<T>& list)
	{
		m_pHead = list.m_pHead;
		m_pTail = list.m_pTail;
		m_count = list.m_count;
		return *this;
	}

private:
	Node<T>* m_pTail = nullptr;
	Node<T>* m_pHead = nullptr;
	size_t m_count = 0;
};
