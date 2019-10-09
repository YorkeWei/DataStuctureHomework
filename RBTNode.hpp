#ifndef RBTNODE_HPP
#define RBTNODE_HPP
template <typename T>
struct RBTNode 
{
	T data;
	RBTNode* parent;
	RBTNode* LChild;
	RBTNode* RChild;
	int color;
	RBTNode(T data) : data(data) { parent = NULL; LChild = NULL; RChild = NULL; color = 1;  }
};
#endif
