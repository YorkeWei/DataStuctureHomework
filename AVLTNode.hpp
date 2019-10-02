#ifndef AVLTNODE_HPP
#define AVLTNODE_HPP
template <typename T>
struct AVLTNode 
{
	T data;
	AVLTNode* LChild;
	AVLTNode* RChild;
	AVLTNode* parent;
	int height;
	AVLTNode(T data) : data(data) { height = 1; LChild = NULL; RChild = NULL; parent = NULL; }
};
#endif