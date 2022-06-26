#pragma once
#include <iostream>
#include <iterator>
#include <sstream>
#include <utility>

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
	CMyList() = default;

	CMyList(CMyList<T> const& list)
		: CMyList()
	{
		CMyList<T> tmpList;

		for (auto it = list.begin(); it != list.end(); ++it)
		{
			tmpList.PushBack(*it);
		}

		std::swap(m_pTail, tmpList.m_pTail);
		std::swap(m_pHead, tmpList.m_pHead);
		std::swap(m_count, tmpList.m_count);
	}

	~CMyList()
	{
		m_pTail->next = nullptr;
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
		// конструктор по умолчанию объявить
		ListConstIterator(Node<T>* node)
			: m_pNode(node)
		{
		}

		using difference_type = std::ptrdiff_t;
		using value_type = const T;
		using pointer = const T*;
		using reference = const T&;
		using iterator_category = std::bidirectional_iterator_tag;

		//сделать метод приватным, объявить список своим другом
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

		// добавить пергрузку оператора ==
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
		// Нужно переопреелить типы pointer reference
		Iterator(Node<T>* node)
			: ListConstIterator<T>(node)
		{
		}

		// добавить перегрузку оператора стрелочка ->
		// Для * -> выбрасывать исключение

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

	void PushFront(const T& elem)
	{
		Node<T>* newNode = new Node<T>(elem);

		if (m_pHead == m_pTail)
		{
			AddFirstNode(newNode);

			++m_count;
		}
		else
		{
			newNode->prev = m_pHead->prev;
			m_pHead->prev = newNode;
			newNode->next = m_pHead;
			m_pHead = newNode;

			++m_count;
		}
	}

	void PushBack(const T& elem)
	{
		Node<T>* newNode = new Node<T>(elem);

		if (m_pHead == m_pTail)
		{
			AddFirstNode(newNode);

			++m_count;
		}
		else
		{
			Node<T>* lastNode = m_pTail->prev;

			newNode->next = lastNode->next;
			lastNode->next = newNode;
			newNode->prev = lastNode;
			m_pTail->prev = newNode;

			++m_count;
		}
	}

	ListConstIterator<T> begin() const
	{
		return ListConstIterator<T>(m_pHead);
	}

	Iterator<T> begin()
	{
		return Iterator<T>(m_pHead);
	}

	ListConstIterator<T> end() const
	{
		return ListConstIterator<T>(m_pTail);
	}

	Iterator<T> end()
	{
		return Iterator<T>(m_pTail);
	}

	std::reverse_iterator<ListConstIterator<T>> rbegin() const
	{
		return std::make_reverse_iterator(end());
	}

	std::reverse_iterator<Iterator<T>> rbegin()
	{
		return std::make_reverse_iterator(end());
	}

	std::reverse_iterator<ListConstIterator<T>> rend() const
	{
		return std::make_reverse_iterator(begin());
	}

	std::reverse_iterator<Iterator<T>> rend()
	{
		return std::make_reverse_iterator(begin());
	}

	size_t Size() const
	{
		return m_count;
	}

	//убрать булеан - будет слишком кудряво
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

	void Erase(Iterator<T>& it)
	{
		if (m_pHead == m_pTail)
		{
			throw std::runtime_error("List is empty\n");
		}
		else
		{
			Node<T>* curNode = it.GetNode();
			Node<T>* prevNode = curNode->prev;
			Node<T>* nextNode = curNode->next;

			if (curNode == m_pHead)
			{
				m_pHead = nextNode;
			}

			if (curNode == m_pTail)
			{
				throw std::runtime_error("Element not exist\n");
			}

			nextNode->prev = prevNode;
			prevNode->next = nextNode;

			curNode->next = nullptr;
			curNode->prev = nullptr;

			delete curNode;

			--m_count;
		}
	}

	CMyList<T>& operator=(CMyList<T> const& list)
	{
		if (this != &list)
		{
			CMyList<T> tmpCopy(list);
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

	Node<T>* m_pTail = new Node<T>();
	Node<T>* m_pHead = m_pTail;
	size_t m_count = 0;
};
