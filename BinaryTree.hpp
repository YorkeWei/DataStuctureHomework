#include <iostream>
#include <stack>
#include <queue>
#include <vector>
template <typename T>
class BinaryTree 
{
protected:
	struct BTNode
	{
		T data;
		BTNode* parent;
		BTNode* LChild;
		BTNode* RChild;
		BTNode(T data) :data(data) { parent = NULL; LChild = NULL; RChild = NULL; }
	};
	BTNode* root;
public:
	//����һ����������Ϊǰ���������,��typeӦΪ0;����һ����������Ϊ����������У���typeӦΪ��������
	//�ڶ�����������ʼ��Ϊ�����������
	BinaryTree(const std::vector<T> first_traversal, const std::vector<T> second_traversal, int type)
	{
		if(type == 0)
			root = pre_in_construct(first_traversal, second_traversal);
		else
			root = post_in_construct(first_traversal, second_traversal);
	}
	//��ǰ�����������������й��������
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
		for(j = i + 1; j < len; j++)
		{
			right_in_traversal[j - i - 1] = in_traversal[j];
			right_pre_traversal[j - i - 1] = pre_traversal[j];
		}
		BTNode* LChild = pre_in_construct(left_pre_traversal, left_in_traversal);
		BTNode* RChild = pre_in_construct(right_pre_traversal, right_in_traversal);
		sub_root->LChild = LChild;
		sub_root->RChild = RChild;
		if(LChild != NULL)
			LChild->parent = sub_root;
		if(RChild != NULL)
			RChild->parent = sub_root;
		return sub_root;
	}
	//�ɺ������������������й��������
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
		if(LChild != NULL)
			LChild->parent = sub_root;
		if(RChild != NULL)
			RChild->parent = sub_root;
		return sub_root;
	}
	typedef void(*fun)(BTNode*);
	//ǰ�����
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
	//�������
	void in_traversal(fun visit) 
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
	//�������_����1
	void post_traversal(fun visit) 
	{
		std::stack<BTNode*> node_container;
		BTNode* cnt_node = root;
		if (cnt_node)
			node_container.push(cnt_node);
		while (!node_container.empty())
		{
			//ÿ�β�����0��������ɼ�Ҷ�ڵ�(�������������ȷ��ʵĽ��)(�˽ڵ��п���Ϊ���ӣ�Ҳ����Ϊ�Һ���)����ջ
			//��ʱʣ�ಿ��Ϊ����������Ҷ�ڵ�����ͬ����ҽڵ�Ϊ������(���ýڵ�����)(�����������������),ʣ�ಿ���ظ�����,ֱ��ʣ�ಿ��Ϊ�ռ�
			//�����ڵ���,���ջ��Ԫ�ز�Ϊ��ǰ�ڵ�ĸ��ڵ㣬һ��Ϊ��ǰ�ڵ�����ֵ�
			//���ڵ�Ĳ��������ͬ
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
	//�������_����2
	//���Ǻ���������еķ����ַ���
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
	//��α���
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
/*
int main()
{
	std::vector<int> pre_traversal = { 1, 2, 4, 7, 5, 3, 6, 8 };
	std::vector<int> in_traversal =  { 7, 4, 2, 5, 1, 8, 6, 3 };
	
	BinaryTree<int> bin_tree(pre_traversal, in_traversal, 0);

	bin_tree.level_traversal(&(BinaryTree<int>::visit));
	std::cout << std::endl;
	bin_tree.pre_traversal(&(BinaryTree<int>::visit));
	std::cout << std::endl;
	bin_tree.in_traversal(&(BinaryTree<int>::visit));
	std::cout << std::endl;
	bin_tree.post_traversal(&(BinaryTree<int>::visit));
	std::cout << std::endl;
	bin_tree._post_traversal(&(BinaryTree<int>::visit));
	std::cout << std::endl;
	return 0;
}
*/