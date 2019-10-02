#ifndef TBTNODE_HPP
#define TBTNODE_HPP
template <typename T>
struct TBTNode 
{
	T data;
	TBTNode* LChild;
	TBTNode* RChild;
	bool real_LChild;
	bool real_RChild;
	TBTNode(T data) :data(data) { LChild = NULL; RChild = NULL; real_LChild = true; real_RChild = true; }
};
#endif