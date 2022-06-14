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

template <class T>
class CMyList
{
public:
	CMyList() = default;
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

	protected:
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
		Node<T>* node = new Node<T>(elem);

		if (m_pHead != nullptr)
		{
			m_pHead->prev = node;
			node->next = m_pHead;
			m_pHead = node;
		}

		if (m_pHead == nullptr && m_pTail == nullptr)
		{
			m_pHead = node;
			m_pTail = node;
		}

		++m_count;
		return true;
	}

	bool push_back(const T& elem)
	{
		Node<T>* node = new Node<T>(elem);

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
		if (m_pHead == nullptr && m_pTail == nullptr)
		{
			m_pHead = newNode;
			m_pTail = newNode;
		}
		else
		{
			Node<T>* curNode = it.GetNode();

			auto prevNode = curNode->prev;

			newNode->prev = prevNode;
			newNode->next = curNode;
			curNode->prev = newNode;
			prevNode->next = newNode;
		}

		// TODO не работает с  пограничными знаениями

		++m_count;
		return true;
	}

	bool erase(Iterator<T>& it)
	{
		if (m_pHead == nullptr && m_pTail == nullptr)
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
	Node<T>* m_pHead = nullptr;
	Node<T>* m_pTail = nullptr;
	size_t m_count = 0;
};
