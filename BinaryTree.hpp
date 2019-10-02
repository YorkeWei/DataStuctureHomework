#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP
#include <vector>
#include <stack>
#include <queue>
template <typename T, typename BTNode>
class BinaryTree 
{
protected:
	BTNode* root;
public:
	BinaryTree() { root = NULL; };
	//若第一个遍历序列为前序遍历序列,则type应为0;若第一个遍历序列为后序遍历序列，则type应为其他整数
	//第二个遍历序列始终为中序遍历序列
	BinaryTree(const std::vector<T> first_traversal, const std::vector<T> second_traversal, int type)
	{
		if (type == 0)
			root = pre_in_construct(first_traversal, second_traversal);
		else
			root = post_in_construct(first_traversal, second_traversal);
	}
	//由前序遍历和中序遍历序列构造二叉树
	BTNode* pre_in_construct(const std::vector<T> pre_traversal, const std::vector<T> in_traversal)
	{
		int len = pre_traversal.size();
		if (len == 0)
			return NULL;
		T sub_root_data = pre_traversal[0];
		BTNode* sub_root = new BTNode(sub_root_data);
		int i;
		for (i = 0; ; i++)
		{
			if (in_traversal[i] == sub_root->data)
			{
				break;
			}
		}
		std::vector<T> left_in_traversal(i);
		std::vector<T> left_pre_traversal(i);
		std::vector<T> right_in_traversal(len - i - 1);
		std::vector<T> right_pre_traversal(len - i - 1);
		int j;
		for (j = 0; j < i; j++)
		{
			left_in_traversal[j] = in_traversal[j];
			left_pre_traversal[j] = pre_traversal[j + 1];
		}
		for (j = i + 1; j < len; j++)
		{
			right_in_traversal[j - i - 1] = in_traversal[j];
			right_pre_traversal[j - i - 1] = pre_traversal[j];
		}
		BTNode* LChild = pre_in_construct(left_pre_traversal, left_in_traversal);
		BTNode* RChild = pre_in_construct(right_pre_traversal, right_in_traversal);
		sub_root->LChild = LChild;
		sub_root->RChild = RChild;
		if (LChild != NULL)
			LChild->parent = sub_root;
		if (RChild != NULL)
			RChild->parent = sub_root;
		return sub_root;
	}
	//由后序遍历和中序遍历序列构造二叉树
	BTNode* post_in_construct(const std::vector<T> post_traversal, const std::vector<T> in_traversal)
	{
		int len = post_traversal.size();
		if (len == 0)
			return NULL;
		T sub_root_data = post_traversal[len - 1];
		BTNode* sub_root = new BTNode(sub_root_data);
		int i;
		for (i = 0; ; i++)
		{
			if (in_traversal[i] == sub_root->data)
				break;
		}
		std::vector<T> left_in_traversal(i);
		std::vector<T> left_post_traversal(i);
		std::vector<T> right_in_traversal(len - i - 1);
		std::vector<T> right_post_traversal(len - i - 1);
		int j;
		for (j = 0; j < i; j++)
		{
			left_in_traversal[j] = in_traversal[j];
			left_post_traversal[j] = post_traversal[j];
		}
		for (j = i + 1; j < len; j++)
		{
			right_in_traversal[j - i - 1] = in_traversal[j];
			right_post_traversal[j - i - 1] = post_traversal[j - 1];
		}
		BTNode* LChild = post_in_construct(left_post_traversal, left_in_traversal);
		BTNode* RChild = post_in_construct(right_post_traversal, right_in_traversal);
		sub_root->LChild = LChild;
		sub_root->RChild = RChild;
		if (LChild != NULL)
			LChild->parent = sub_root;
		if (RChild != NULL)
			RChild->parent = sub_root;
		return sub_root;
	}
	typedef void(*fun)(BTNode*);
	//前序遍历
	void pre_traversal(fun visit)
	{
		std::stack<BTNode*> node_container;
		BTNode* cnt_node = root;
		while (true)
		{
			while (cnt_node)
			{
				visit(cnt_node);
				node_container.push(cnt_node->RChild);
				cnt_node = cnt_node->LChild;
			}
			if (node_container.empty())
				break;
			cnt_node = node_container.top();
			node_container.pop();
		}
	}
	//中序遍历
	virtual void in_traversal(fun visit)
	{
		std::stack<BTNode*> node_container;
		BTNode* cnt_node = root;
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
				visit(cnt_node);
				cnt_node = cnt_node->RChild;
			}
			else
				break;
		}
	}
	//后序遍历_方法1
	void post_traversal(fun visit)
	{
		std::stack<BTNode*> node_container;
		BTNode* cnt_node = root;
		if (cnt_node)
			node_container.push(cnt_node);
		while (!node_container.empty())
		{
			//每次操作将0到最高左侧可见叶节点(即后续遍历首先访问的结点)(此节点有可能为左孩子，也可能为右孩子)推入栈
			//此时剩余部分为以与最高左侧叶节点祖先同层的右节点为根的树(除该节点自身)(满足条件的最近祖先),剩余部分重复操作,直到剩余部分为空集
			//除根节点外,如果栈顶元素不为当前节点的父节点，一定为当前节点的右兄第
			//根节点的操作与此相同
			if (node_container.top() != cnt_node->parent)
			{
				BTNode* x;
				while (x = node_container.top())
				{
					if (x->LChild)
					{
						if (x->RChild)
							node_container.push(x->RChild);
						node_container.push(x->LChild);
					}
					else
						node_container.push(x->RChild);
				}
				node_container.pop();
			}
			cnt_node = node_container.top();
			node_container.pop();
			visit(cnt_node);
		}
	}
	//后序遍历_方法2
	//考虑后序遍历序列的反序字符串
	void _post_traversal(fun visit)
	{
		std::stack<BTNode*> turn;
		std::stack<BTNode*> node_container;
		BTNode* cnt_node = root;
		while (true)
		{
			while (cnt_node)
			{
				turn.push(cnt_node);
				node_container.push(cnt_node->LChild);
				cnt_node = cnt_node->RChild;
			}
			if (node_container.empty())
				break;
			cnt_node = node_container.top();
			node_container.pop();
		}
		while (!turn.empty())
		{
			visit(turn.top());
			turn.pop();
		}
	}
	//层次遍历
	void level_traversal(fun visit)
	{
		std::queue<BTNode*> node_container;
		BTNode* cnt_node = root;
		if (cnt_node)
			node_container.push(cnt_node);
		while (!node_container.empty())
		{
			cnt_node = node_container.front();
			node_container.pop();
			visit(cnt_node);
			if (cnt_node->LChild)
				node_container.push(cnt_node->LChild);
			if (cnt_node->RChild)
				node_container.push(cnt_node->RChild);
		}
	}
	static void visit(BTNode* node)
	{
		std::cout << node->data << ",";
	}
	~BinaryTree()
	{
		init(root);
	}
	void init(BTNode* root)
	{
		BTNode* LC = root->LChild;
		BTNode* RC = root->RChild;
		if (LC != NULL)
			init(LC);
		if (RC != NULL)
			init(RC);
		delete root;
	}
};
#endif
