#ifndef RBTREE_HPP
#define RBTREE_HPP
#include "BinarySearchTree.hpp"
#define RED 0
#define BLACK 1
#define IS_RED(i) (((i) != NULL) && ((i)->color == 0))
#define IS_BLACK(i) (((i) == NULL) || ((i)->color == 1))
template <typename T, typename RBTNode>
class RBTree : public BinarySearchTree<T, RBTNode>
{
public:
	RBTree(const T* _sequence, int _size) : BinarySearchTree<T, RBTNode>()
	{
		for (int i = 0; i < _size; i++)
			insert(_sequence[i]);
	}
	void r_rotate(RBTNode* node)//顺时针旋转 
	{

		RBTNode* p = node->LChild;
		node->LChild = p->RChild;
		if (p->RChild)
			p->RChild->parent = node;
		RBTNode* u = node->parent;
		p->RChild = node;
		node->parent = p;
		if (u)
			(u->LChild == node) ? u->LChild = p : u->RChild = p;
		else
			this->root = p;
		p->parent = u;
	}
	void l_rotate(RBTNode* node)//逆时针旋转
	{

		RBTNode* p = node->RChild;
		node->RChild = p->LChild;
		if (p->LChild)
			p->LChild->parent = node;
		RBTNode* u = node->parent;
		p->LChild = node;
		node->parent = p;
		if (u)
			(u->LChild == node) ? u->LChild = p : u->RChild = p;
		else
			this->root = p;
		p->parent = u;
	}
	RBTNode* insert(T e)
	{
		if (this->root == NULL)
		{
			this->root = new RBTNode(e);
			return this->root;
		}
		RBTNode* cnt = this->root;
		while (true)
		{
			if (e <= cnt->data)
				if (cnt->LChild)
					cnt = cnt->LChild;
				else
				{
					cnt->LChild = new RBTNode(e);
					cnt->LChild->parent = cnt;
					break;
				}
			else
				if (cnt->RChild)
					cnt = cnt->RChild;
				else
				{
					cnt->RChild = new RBTNode(e);
					cnt->RChild->parent = cnt;
					break;
				}
		}
		RBTNode* posi = cnt;
		while (this->root != cnt && IS_RED(cnt->parent))
		{
			if (IS_RED(cnt->parent))
			{
				if (cnt->parent->parent->LChild == cnt->parent)
				{
					if (IS_RED(cnt->parent->parent->RChild))
					{
						cnt->parent->color = BLACK;
						cnt->parent->parent->RChild->color = BLACK;
						cnt->parent->parent = RED;
						cnt = cnt->parent->parent;
					}
					else
					{
						if (cnt == cnt->parent->RChild)
						{
							cnt = cnt->parent;
							l_rotate(cnt);
						}
						else 
						{
							cnt->parent->color = BLACK;
							cnt->parent->parent->color = RED;
							r_rotate(cnt->parent->parent);
							break;
						}
					}
				}
				else
				{
					if (IS_RED(cnt->parent->parent->RChild))
					{
						cnt->parent->color = BLACK;
						cnt->parent->parent->LChild->color = BLACK;
						cnt->parent->parent->color = RED;
						cnt = cnt->parent->parent;
					}
					else
					{
						if (cnt->parent->LChild == cnt) 
						{
							cnt = cnt->parent;
							r_rotate(cnt);
						}
						else 
						{
							cnt->parent->color = BLACK;
							cnt->parent->parent->color = RED;
							l_rotate(cnt->parent->parent);
							break;
						}
					}
				}
			}
		}
		if (this->root == cnt)
			cnt->color = BLACK;
		return posi;
	}
	bool remove(const T& e)
	{
		RBTNode* posi = this->search(e);
		if (!posi)
			return false;
		int del_node_color;
		if ((!posi->LChild) || (!posi->RChild))
			del_node_color = posi->color;
		else
			del_node_color = this->succ(posi)->color;
		RBTNode* cnt = this->removeAt(posi);
		if (del_node_color == BLACK)
		{
			while (this->root != cnt && IS_BLACK(cnt))
			{
				if (cnt == cnt->parent->LChild)
				{
					if (IS_RED(cnt->parent->RChild))
					{
						std::swap(cnt->parent->RChild->color, cnt->parent->color);
						l_rotate(cnt->parent);
					}
					if (IS_BLACK(cnt->parent->RChild->LChild) && IS_BLACK(cnt->parent->RChild->RChild)) 
					{
						cnt->parent->RChild->color = RED;
						cnt = cnt->parent;
					}
					else
					{
						if (IS_BLACK(cnt->parent->RChild))
						{
							std::swap(cnt->parent->RChild->color, cnt->parent->RChild->LChild->color);
							r_rotate(cnt->parent->RChild);
						}
						std::swap(cnt->parent->color, cnt->parent->RChild->color);
						cnt->parent->RChild->RChild->color = BLACK;
						l_rotate(cnt->parent);
						cnt = this->root;
					}
				}
				else
				{
					if (IS_RED(cnt->parent->LChild))
					{
						std::swap(cnt->parent->color, cnt->parent->LChild->color);
						r_rotate(cnt->parent);
					}
					if (IS_BLACK(cnt->parent->LChild->RChild) && IS_BLACK(cnt->parent->LChild->LChild))
					{
						cnt->parent->LChild->color = RED;
						cnt = cnt->parent;
					}
					else
					{
						if (IS_RED(cnt->parent->LChild->RChild))
						{
							std::swap(cnt->parent->LChild->color, cnt->parent->LChild->RChild->color);
							l_rotate(cnt->parent->LChild);
						}
						std::swap(cnt->parent->color, cnt->parent->LChild->color);
						cnt->parent->LChild->color = BLACK;
						r_rotate(cnt->parent);
						cnt = this->root;
					}
				}
			}
			cnt->color = BLACK;
		}
		return true;
	}
	RBTNode* removeAt(RBTNode* posi)//返回后继结点的指针
	{
		RBTNode* succ = NULL;
		RBTNode* u = NULL;
		if ((!posi->LChild) && (!posi->RChild))
		{
			u = posi->parent;
			if (u)
				(u->LChild == posi) ? u->LChild = NULL : u->RChild = NULL;
			if (posi == this->root)
				this->root = NULL;
			delete posi;
		}
		else if (!posi->LChild)
		{
			succ = posi->RChild;
			u = posi->parent;
			if (u)
				(u->LChild == posi) ? (u->LChild = succ) : (u->RChild = succ);
			succ->parent = u;
			if (posi == this->root)
				this->root = succ;
			delete posi;
		}
		else if (!posi->RChild)
		{
			succ = posi->LChild;
			u = posi->parent;
			if (u)
				(u->LChild == posi) ? (u->LChild = succ) : (u->RChild = succ);
			succ->parent = u;
			if (posi == this->root)
				this->root = succ;
			delete posi;
		}
		else
		{
			RBTNode* w = this->succ(posi);//实际被删除的节点
			std::swap(w->data, posi->data);
			succ = w->RChild;
			u = w->parent;
			if (u)
				(u == posi) ? (u->RChild = succ) : (u->LChild = succ);
			if (succ)
				succ->parent = u;
			delete w;
		}
		return succ;
	}
};
#endif