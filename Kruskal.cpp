#include "union_set.hpp"
#include <queue>
#include <iostream>
struct Edge
{
	//u, v为关联该边两个顶点的编号，w为边的权重
	int u;
	int v;
	double w;
	bool operator<(const Edge& e) const
	{
		return this->w < e.w;
	}
	bool operator>(const Edge& e) const
	{
		return this->w > e.w;
	}
	bool operator==(const Edge& e) const
	{
		return (this->u == e.u) && (this->v == e.v) && (this->w == w);
	}
	Edge(int u, int v, double w) : u(u), v(v), w(w) {}
	Edge(const Edge& e) : u(e.u), v(e.v), w(e.w){}
};
void Kruskal(const std::set<Edge>& edge_set, int v)//v表示顶点个数
{
	std::set<Edge> mst_edge_set;
	double mst_weight = 0.0;
	std::set<int> vertex;
	for (int i = 0; i < v; i++)
		vertex.insert(i);
	union_set<int> u_set(vertex);
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> edge_container;
	std::set<Edge>::iterator it;
	for (it = edge_set.begin(); it != edge_set.end(); it++)
		edge_container.push(*it);
	while (!edge_container.empty())
	{
		Edge e = edge_container.top();
		edge_container.pop();
		if (u_set.merge(e.u, e.v))
		{
			mst_edge_set.insert(e);
			mst_weight += e.w;
		}
	}
	std::cout << "最小生成树的权值为:" << mst_weight << std::endl;
	std::cout << "最小生成树的边集为:" << std::endl << "{";
	for (it = mst_edge_set.begin(); it != mst_edge_set.end(); it++) 
	{
		int u = it->u;
		int v = it->v;
		std::cout << "<" << u << "," << v << ">" << ",";
	}
	std::cout << "}" << std::endl;
}

int main()
{
	std::set<Edge> edge_set;
	int v = 7;
	edge_set.insert(Edge(0, 1, 6.0));
	edge_set.insert(Edge(0, 2, 6.0));
	edge_set.insert(Edge(0, 3, 6.0));
	edge_set.insert(Edge(1, 3, 3.0));
	edge_set.insert(Edge(1, 4, 2.0));
	edge_set.insert(Edge(2, 3, 7.0));
	edge_set.insert(Edge(3, 4, 2.0));
	edge_set.insert(Edge(2, 5, 8.0));
	edge_set.insert(Edge(3, 5, 3.0));
	edge_set.insert(Edge(3, 6, 4.0));
	edge_set.insert(Edge(4, 6, 2.0));
	edge_set.insert(Edge(5, 6, 1.0));
	Kruskal(edge_set, v);
	return 0;
}
