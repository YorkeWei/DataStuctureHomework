#ifndef BTNODE_HPP 
#define BTNODE_HPP
template <typename T>
struct BTNode 
{
	T data;
	BTNode* LChild;
	BTNode* RChild;
	BTNode* parent;
	BTNode(T data) :data(data) { parent = NULL; LChild = NULL; RChild = NULL; }
};
#endif 
