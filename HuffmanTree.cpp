#include "heap.hpp"
#include "Huffman_Node.hpp"
#include <vector>
#include <iostream>
#include <queue>
#include <windows.h>
bool cmp(Huffman_Node<double>* t1, Huffman_Node<double>* t2)
{
	if (t1->data < t2->data)
		return true;
	else
		return false;
}
void HuffmanTree(double* f, char* ch, int _size)
{
	std::vector<Huffman_Node<double>*> t;
	for (int i = 0; i < _size; i++)
	{
		t.push_back(new Huffman_Node<double>(f[i], ch[i]));
	}
	heap<Huffman_Node<double>*> container(t, cmp);
	while (container._size > 1) {
		Huffman_Node<double>* t1 = container.delMin();
		Huffman_Node<double>* t2 = container.delMin();
		Huffman_Node<double>* n_t = new Huffman_Node<double>(t1->data + t2->data, '\0');
		n_t->LChild = t1;
		n_t->RChild = t2;
		t1->parent = n_t;
		t2->parent = n_t;
		container.insert(n_t);
	}
	Huffman_Node<double>* root = container.delMin();
	std::queue<Huffman_Node<double>*> node_container;
	Huffman_Node<double>* cnt_node = root;
	if (cnt_node)
		node_container.push(cnt_node);
	while (!node_container.empty())
	{
		cnt_node = node_container.front();
		node_container.pop();
		if (cnt_node->ch != '\0')
			std::cout << cnt_node->ch << ":" << cnt_node->code << std::endl;
		if (cnt_node->LChild)
		{
			cnt_node->LChild->code = cnt_node->code + "0";
			node_container.push(cnt_node->LChild);
		}
		if (cnt_node->RChild)
		{
			cnt_node->RChild->code = cnt_node->code + "1";
			node_container.push(cnt_node->RChild);
		}
		delete cnt_node;
	}
}
int main() 
{
	double* f = new double[5];
	char* ch = new char[5];
	f[0] = 0.2;
	f[1] = 0.4;
	f[2] = 0.1;
	f[3] = 0.6;
	f[4] = 0.7;
	ch[0] = '0';
	ch[1] = '1';
	ch[2] = '2';
	ch[3] = '3';
	ch[4] = '4';
	HuffmanTree(f, ch, 5);
	return 0;
}
