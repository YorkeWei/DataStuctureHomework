#ifndef AVLTREE_HPP
#define AVLTREE_HPP
#include "BinarySearchTree.hpp" 
template <typename T, typename AVLTNode>
class AVLTree : public BinarySearchTree<T, AVLTNode>
{
public:
	AVLTree(const T* _sequence, int _size) : BinarySearchTree<T, AVLTNode>()
	{
		for (int i = 0; i < _size; i++)
			insert(_sequence[i]);
	}
	AVLTNode* insert(T e)
	{
		if (this->root == NULL) {
			this->root = new AVLTNode(e);
			return this->root;
		}
		AVLTNode* cnt = this->root;
		while (true)
		{
			if (e <= cnt->data)
				if (cnt->LChild)
					cnt = cnt->LChild;
				else
				{
					cnt->LChild = new AVLTNode(e);
					cnt->LChild->parent = cnt;
					break;
				}
			else
				if (cnt->RChild)
					cnt = cnt->RChild;
				else
				{
					cnt->RChild = new AVLTNode(e);
					cnt->RChild->parent = cnt;
					break;
				}
		}
		update_to_root(cnt);
		return cnt;
	}
	void push_up(AVLTNode* node)
	{	
		if (node->LChild && node->RChild)
			node->height = std::max(node->LChild->height, node->RChild->height) + 1;
		else if (node->LChild)
			node->height = node->LChild->height + 1;
		else if (node->RChild)
			node->height = node->RChild->height + 1;
		else
			node->height = 1;
	}
	void update_to_root(AVLTNode* node) 
	{
		while (node) 
		{
			push_up(node);
			if (ban_val(node) > 1)
			{
				if (ban_val(node->LChild) >= 0) 
				{
					r_rotate(node);
				}
				else
				{
					l_rotate(node->LChild);
					r_rotate(node);
				}
			}
			else if (ban_val(node) < -1)
			{
				if (ban_val(node->RChild) <= 0)
				{
					l_rotate(node);
				}
				else
				{
					r_rotate(node->RChild);
					l_rotate(node);
				}
			}
			node = node->parent;
	
		}
	}
	void r_rotate(AVLTNode* node)//顺时针旋转 
	{
		
		AVLTNode* p = node->LChild;
		node->LChild = p->RChild;
		if(p->RChild)
			p->RChild->parent = node;
		AVLTNode* u = node->parent;
		p->RChild = node;
		node->parent = p;
		if (u)
			(u->LChild == node) ? u->LChild = p : u->RChild = p;
		else
			this->root = p;
		p->parent = u;
		push_up(node);
		push_up(p);
	}
	void l_rotate(AVLTNode* node)//逆时针旋转
	{
		
		AVLTNode* p = node->RChild;
		node->RChild = p->LChild;
		if(p->LChild)
			p->LChild->parent = node;
		AVLTNode* u = node->parent;
		p->LChild = node;
		node->parent = p;
		if (u)
			(u->LChild == node) ? u->LChild = p : u->RChild = p;
		else
			this->root = p;
		p->parent = u;
		push_up(node);
		push_up(p);
	}
	int ban_val(AVLTNode* node)
	{
		int l_val, r_val;
		if (node->LChild)
			l_val = node->LChild->height;
		else
			l_val = 0;
		if (node->RChild)
			r_val = node->RChild->height;
		else
			r_val = 0;
		return l_val - r_val;
	}
	bool remove(const T& e)
	{
		AVLTNode* posi = this->search(e);
		if (!posi)
			return false;
		AVLTNode* succ = this->removeAt(posi);
		update_to_root(succ);
		return true;
	}
};
#endif