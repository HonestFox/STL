#pragma once
#include "Iterator.h"

template<typename T>
struct __ListNode
{
	__ListNode<T> *_next;
	__ListNode<T> *_prev;
	T _data;

	__ListNode(const T &x = T())
		:_next(NULL)
		, _prev(NULL)
		, _data(x)
	{}
};

template<typename T>
struct __ListIterator
{
	typedef __ListIterator Self;
	typedef __ListNode<T> Node;

	__ListIterator()
	{}
	__ListIterator(Node *node)
		:_node(node)
	{}
	bool operator==(const Self &s)
	{
		return _node == s._node;
	}
	bool operator!=(const Self &s)
	{
		return _node != s._node;
	}
	Self& operator++()				//前置
	{
		_node = _node->_next;
		return *this;
	}
	Self operator++(int)			//后置
	{
		Self tmp = *this;
		_node = _node->_next;
		return tmp;
	}
	Self& operator--()			//前置
	{
		_node = _node->_prev;
		return *this;
	}
	Self operator--(int) 			 //后置
	{
		Self tmp = *this;
		_node = _node->_next;
		return tmp;
	}
	T operator*()
	{
		return _node->_data;
	}

	Node *_node;
};

template<typename T >
class List
{
protected:
	typedef __ListNode<T>  Node;
public:
	typedef  __ListIterator<T> ListIterator;
public:
	List()
		:_head(new Node)
	{
		_head->_next = _head;
		_head->_prev = _head;
	}

	bool Empty()
	{
		return _head->_next == _head;
	}

	ListIterator Begin()
	{
		return ListIterator(_head->_next);
	}

	ListIterator End()
	{
		return ListIterator(_head);
	}

	Node* CreateNode(const T &x)
	{
		return (new Node(x));
	}

	ListIterator Insert(ListIterator pos, const T &x)    //在位置的前面插入
	{
		Node *tmp = CreateNode(x);
		tmp->_next = pos._node;
		tmp->_prev = (pos._node)->_prev;
		pos._node->_prev->_next = tmp;
		pos._node->_prev = tmp;
		return ListIterator(tmp);
	}

	void PushBack(const T &x)
	{
		Insert((*this).End(), x);
	}

	void PushFront(const T &x)
	{
		Insert((*this).Begin(), x);
	}

protected:
	Node *_head;
};


