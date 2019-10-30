#include <set>
#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
struct Edge
{
	//u, v为关联该边两个顶点的编号
	int u;
	int v;
	int ran;
	bool operator==(const Edge& e) const
	{
		return (this->u == e.u) && (this->v == e.v);
	}
	bool operator<(const Edge& e) const
	{
		return this->ran < e.ran;
	}
	Edge(int u, int v) : u(u), v(v)
	{
		srand((int)time(0));
		ran = rand();
	}
	Edge(const Edge& e) : u(e.u), v(e.v), ran(ran) {}
};
//深度优先搜索闭迹
void search_close_trail(int cnt, std::vector<std::vector<bool>>& e, int v, std::stack<int>& path)
{
	std::stack<int> event_container;
	event_container.push(cnt);
	int cur;
	while (!event_container.empty())
	{
		cur = event_container.top();
		event_container.pop();
		path.push(cur);
		for (int i = 0; i < v; i++)
		{
			if (e[cur][i]) 
			{
				event_container.push(i);
				e[cur][i] = false;
				e[i][cur] = false;
				break;
			}
		}
	}
}
void Hierholzer(const std::set<Edge>& edge_set, int v)//v表示顶点个数
{
	std::vector<std::vector<bool>> e(v, std::vector<bool>(v, false));
	std::set<Edge>::iterator it;
	for (it = edge_set.begin(); it != edge_set.end(); it++) 
	{
		int u = it->u;
		int v = it->v;
		e[u][v] = true;
		e[v][u] = true;
	}
	std::stack<int> path;
	path.push(0);
	std::vector<int> euler;
	while (!path.empty())
	{
		int cnt = path.top();
		path.pop();
		bool flag = false;
		for (int i = 0; i < v; i++) 
		{
			if (e[cnt][i])
			{
				flag = true;
				break;
			}
		}
		if (flag)
			search_close_trail(cnt, e, v, path);
		else
			euler.push_back(cnt);
	}
	std::cout << "欧拉回路为:";
	int size = euler.size();
	for (int i = 0; i < size; i++)
		std::cout << euler[i] << ",";
}

int main()
{
	std::set<Edge> edge_set;
	int v = 10;
	edge_set.insert(Edge(0, 1));
	edge_set.insert(Edge(1, 2));
	edge_set.insert(Edge(1, 4));
	edge_set.insert(Edge(2, 3));
	edge_set.insert(Edge(3, 4));
	edge_set.insert(Edge(1, 5));
	edge_set.insert(Edge(0, 6));
	edge_set.insert(Edge(5, 6));
	edge_set.insert(Edge(6, 7));
	edge_set.insert(Edge(6, 9));
	edge_set.insert(Edge(7, 8));
	edge_set.insert(Edge(8, 9));
	Hierholzer(edge_set, v);
	return 0;
}
