#ifndef THREADBINARYTREE_HPP
#define THREADBINARYTREE_HPP
#include "TBTNode.hpp"
#include "BinaryTree.hpp"
#include <map>
template <typename T, typename TBTNode>
class ThreadBinaryTree : public BinaryTree<T, TBTNode>
{
protected:
	std::map<TBTNode*, TBTNode*> pred;
	std::map<TBTNode*, TBTNode*> succ;
public:
	ThreadBinaryTree() : BinaryTree<T, TBTNode>() {};
	ThreadBinaryTree(const std::vector<T> first_traversal, const std::vector<T> second_traversal, int type) : BinaryTree<T, TBTNode>(const std::vector<T> first_traversal, const std::vector<T> second_traversal, int type) {};
	//构造中序遍历线索
	void construct_Thread() 
	{
		std::stack<TBTNode*> path;
		TBTNode* pred = NULL;
		TBTNode* cnt = root;
		while (cnt || !path.empty())
		{
			while (cnt)
			{
				path.push(cnt);
				cnt = cnt->LChild;
			}
			cnt = path.top();
			path.pop();
			if (cnt->LChild == NULL)
			{
				cnt->LChild = pred;
				this->pred[cnt] = pred;
				this->succ[pred] = cnt;
				cnt->real_LChild = false;
			}
			pred = cnt;
			if (cnt->RChild == NULL && !path.empty())
			{
				cnt->RChild = path.top();
				this->succ[cnt] = cnt->RChild;
				this->pred[cnt->RChild] = cnt;
				cnt->real_RChild = false;
				cnt = NULL;
			}
			else
				cnt = cnt->RChild;
		}
	}
	typedef void(*fun)(TBTNode*);
	//中序遍历
	void in_traversal(fun visit) 
	{
		TBTNode* cnt = BinaryTree<T, TBTNode>::root;
		while (cnt->LChild)
			cnt = cnt->LChild;
		while (cnt) 
		{
			visit(cnt);
			cnt = succ[cnt];
		}
	}
};
#endif