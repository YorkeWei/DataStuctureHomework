#include <iostream>
template <typename T> class doubleLinkedList
{
protected:
	struct Node
	{
		T data;
		Node* pred;
		Node* succ;
		Node(T data) :data(data) { pred = NULL; succ = NULL; }
	};
	Node* header;
	Node* trailer;
public:
	Node* getHeader()
	{
		return header;
	}
	Node* getTrailer()
	{
		return trailer;
	}
	doubleLinkedList()
	{
		header = NULL;
		trailer = NULL;
	}
	doubleLinkedList operator=(const doubleLinkedList & t) const
	{
		doubleLinkedList r = new doubleLinkedList();
		Node* cursor = t.getHeader();
		while (cursor != NULL)
		{
			Node* cnt = new Node(cursor->data);
			r.insertAsFirst(cnt);
			cursor = cursor->succ;
		}
	}
	Node* insertAsFirst(T e)//将e作为第一个节点插入
	{
		Node* pNew = new Node(e);
		pNew->succ = header;
		if (header != NULL)
			header->pred = pNew;
		else
			trailer = pNew;//插入前链表为空,pNew同时也是尾节点
		header = pNew;
		return pNew;
	}
	Node* insertAsLast(T e)//将e作为最后一个节点插入
	{
		Node* pNew = new Node(e);
		pNew->pred = trailer;
		if (trailer != NULL)
			trailer->succ = pNew;
		else
			header = pNew;//插入前链表为空,pNew同时也是头节点
		trailer = pNew;
		return pNew;
	}
	Node* insertA(Node* pNode,T e)//将e插入为pNode的前驱
	{
		Node* pNew = new Node(e);
		pNew->pred = pNode->pred;
		pNode->pred->succ = pNew;
		pNode->pred = pNew;
		pNew->succ = pNode;
		return pNew;
	}
	Node* insertB(Node* pNode, T e)//将e插入为pNode的后继
	{
		Node* pNew = new Node(e);
		pNew->succ = pNode->succ;
		pNode->succ->pred = pNew;
		pNode->succ = pNew;
		pNew->pred = pNode;
		return pNew;
	}
	void traversal()  const
	{
		Node* cursor = header;
		while (cursor != NULL)
		{
			std::cout << cursor->data << ",";
			cursor = cursor->succ;
		}
		std::cout << std::endl;
	}
	T remove(Node* pNode) //删除中间结点
	{
		if (pNode == NULL)
			return NULL;
		T e = pNode->data;
		pNode->succ->pred = pNode->pred;
		pNode->pred->succ = pNode->succ;
		delete pNode;
		return e;
	}
	T removeFirst()//删除第一个结点
	{
		if (header == NULL)
			return NULL;
		T e = header->data;
		if(header->succ != NULL)
			header->succ->pred = NULL;
		header = header->succ;
		return e;
	}
	T removeLast()//删除最后一个结点
	{
		if (trailer == NULL)
			return NULL;
		T e = trailer->data;
		if (trailer->pred != NULL)
			trailer->pred->succ = NULL;
		trailer = trailer->pred;
		return e;
	}
	Node* find(T e) const//返回第一个值为e的结点的指针
	{
		Node* cursor = header;
		while (cursor != NULL)
		{
			if (cursor->data == e)
				return cursor;
			cursor = cursor->next;
		}
		return NULL;
	}
	bool isempty() const
	{
		return header == NULL;
	}
	~doubleLinkedList()
	{
		while (header != NULL)
			removeFirst();
		
	}
};
template <typename T> class Stack
{
protected:
	doubleLinkedList<T>* dataList;
public:
	Stack()
	{
		dataList = new doubleLinkedList<T>;
	}
	void push(T e) 
	{	
		dataList->insertAsFirst(e);
	}
	T pop()
	{
		return dataList->removeFirst();
	}
	T top() const
	{
		return dataList->getHeader()->data;
	}
	bool isempty() const
	{
		return dataList->isempty();
	}
	~Stack()
	{
		delete dataList;
	}
};
template <typename T> class Queue 
{
protected:
	doubleLinkedList<T>* dataList;
public:
	Queue()
	{
		dataList = new doubleLinkedList<T>;
	}
	void push(T e)
	{
		dataList->insertAsLast(e);
	}
	T pop()
	{
		return dataList->removeFirst();
	}
	T top() const
	{
		return dataList->getHeader()->data;
	}
	bool isempty() const
	{
		return dataList->isempty();
	}
	
	~Queue()
	{
		delete dataList;
	}
	
};
/*
int main() 
{
	Queue<int> q;
	q.push(1);
	q.push(2);
	//getchar();
	Stack<int> s;
	s.push(1);
	s.push(2);
	std::cout << q.isempty() << std::endl;
	std::cout << q.pop() << std::endl;
	std::cout << q.top() << std::endl;
	std::cout << q.pop() << std::endl;
	std::cout << q.isempty() << std::endl;
	std::cout << s.pop() << std::endl;
	std::cout << s.pop() << std::endl;
	doubleLinkedList<int> list;
	list.insertAsFirst(1);
	list.insertAsFirst(2);
	list.traversal();
	doubleLinkedList<int> list2 = list;
	list2.traversal();
	return 0;
}
*/