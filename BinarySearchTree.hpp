#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include "BinaryTree.hpp"
template <typename T, typename BSTNode>
class BinarySearchTree : public BinaryTree<T, BSTNode>
{
public:
	BinarySearchTree() : BinaryTree<T, BSTNode>() {}
	BinarySearchTree(const T* _sequence, int _size) : BinaryTree<T, BSTNode>()
	{
		for (int i = 0; i < _size; i++)
			insert(_sequence[i]);
	}
	virtual BSTNode* insert(const T data) 
	{	
		if (this->root == NULL) {
			this->root = new BSTNode(data);
			return this->root;
		}
		BSTNode* cnt = this->root;
		while (true) 
		{
			if (data <= cnt->data)
				if (cnt->LChild)
					cnt = cnt->LChild;
				else 
				{
					cnt->LChild = new BSTNode(data);
					cnt->LChild->parent = cnt;
					return cnt->LChild;
				}
			else
				if (cnt->RChild)
					cnt = cnt->RChild;
				else 
				{
					cnt->RChild = new BSTNode(data);
					cnt->RChild->parent = cnt;
					return cnt->RChild;
				}
		}
	}
	BSTNode* search(const T& data)
	{
		BSTNode* cnt = BinaryTree<T, BSTNode>::root;
		while (cnt)
		{
			if (data == cnt->data)
				return cnt;
			else if (data < cnt->data)
				cnt = cnt->LChild;
			else
				cnt = cnt->RChild;
		}
		return NULL;
	}
	virtual bool remove(const T& e) 
	{
		BSTNode* posi = search(e);
		if (!posi)
			return false;
		removeAt(posi);
		return true;
	}
	BSTNode* removeAt(BSTNode* posi)//返回后继者的指针
	{
		BSTNode* succ = NULL;
		BSTNode* u = NULL;
		if ((!posi->LChild) && (!posi->RChild))
		{
			(posi->parent->LChild == posi) ? posi->parent->LChild = NULL : posi->parent->RChild = NULL;
			u = posi->parent;
			delete posi;
			return u;
			
		}
		else if (!posi->LChild)
		{
			succ = posi->RChild;
			u = posi->parent;
			if (u)
				(u->LChild == posi) ? (u->LChild = succ) : (u->RChild = succ);
			if (succ)
				succ->parent = u;
			delete posi;
			if (succ)
				return succ;
			else
				return u;
		}
		else if (!posi->RChild)
		{
			succ = posi->LChild;
			u = posi->parent;
			if (u)
				(u->LChild == posi) ? (u->LChild = succ) : ( u->RChild = succ);
			if (succ)
				succ->parent = u;
			delete posi;
			if (succ)
				return succ;
			else
				return u;
		}
		else
		{
			BSTNode* w = this->succ(posi);//实际被删除的节点
			std::swap(w->data, posi->data);
			succ = w->RChild;
			u = w->parent;
			if (u)
				(u == posi) ? (u->RChild = succ) : (u->LChild = succ);
			if (succ)
				succ->parent = u;
			delete w;
			if (succ)
				return succ;
			else
				return u;
		}
		
	}
	BSTNode* succ(BSTNode* node)//返回node在中序遍历中的后续节点
	{
		BSTNode* s = node;
		if (node->RChild)
		{
			s = node->RChild;
			while (s->LChild)
				s = s->LChild;
		}
		else
		{
			while (s->parent->RChild == s)
				s = s->parent;
			s = s->parent;
		}
		return s;
	}
	//找从小到大第k个元素
	T find_rank_k(int k)
	{
		std::stack<BSTNode*> node_container;
		BSTNode* cnt_node = this->root;
		int count = 0;
		while (true)
		{
			if (cnt_node)
			{
				node_container.push(cnt_node);
				cnt_node = cnt_node->LChild;
			}
			else if (!node_container.empty())
			{
				cnt_node = node_container.top();
				node_container.pop();
				count++;
				if (count >= k) 
					return cnt_node->data;
				cnt_node = cnt_node->RChild;
			}
			else
				break;
		}
		return NULL;
	}
};
#endif
