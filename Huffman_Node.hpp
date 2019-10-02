#ifndef HUFFMAN_NODE_HPP 
#define HUFFMAN_NODE_HPP
#include <string>
template <typename T>
struct Huffman_Node
{
	T data;
	char ch;
	Huffman_Node* LChild;
	Huffman_Node* RChild;
	Huffman_Node* parent;
	std::string code;
	Huffman_Node(T data, char ch) :data(data), ch(ch) { parent = NULL; LChild = NULL; RChild = NULL; code = ""; }
};
#endif 
