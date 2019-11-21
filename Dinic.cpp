#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <map>
struct Edge
{
	int to;
	double capacity;
	int next;
	Edge(int to, double capacity, int next) : to(to), capacity(capacity), next(next){ }
}; 
struct Network
{
	int v_num;
	int e_num;
	int s;
	int t;
	std::vector<int> head;
	std::vector<Edge> edge_set; 
	Network() 
	{
		std::cout << "请输入点集元素个数、边集元素个数:" << std::endl;
		std::cin >> v_num >> e_num;
		std::cout << "请输入源点、溯点:" << std::endl;
		std::cin >> s >> t;
		head.resize(v_num);
		for (int i = 0; i < v_num; i++)
			head[i] = -1;
		for (int i = 0; i < e_num; i++)
		{
			int from, to;
			double capacity;
			std::cout << "请输入第" + std::to_string(i) + "条边的起点、终点、容量" << std::endl;
			std::cin >> from >> to >> capacity;	
			addEdge(from, to, capacity);
		}
	}
	void addEdge(int from, int to, double capacity)
	{
		edge_set.push_back(Edge(to, capacity, head[from]));
		head[from] = edge_set.size() - 1;
		edge_set.push_back(Edge(from, 0.0, head[to]));
		head[to] = edge_set.size() - 1;
	}
};
bool BFS(std::vector<int>& d, const Network& network)
{
	std::vector<int>::iterator it;
	for (it = d.begin(); it != d.end(); it++)
		*it = -1;
	d[network.s] = 0;
	std::queue<int> container;
	while (!container.empty())
	{
		int cnt = container.front();
		container.pop();
		for (int cnt_edge = network.head[cnt]; cnt_edge != -1; cnt_edge = network.edge_set[cnt_edge].next)
		{
			int dis = network.edge_set[cnt_edge].to;
			if (d[dis] == -1 && network.edge_set[cnt_edge].capacity > 0)
			{
				d[dis] = d[cnt] + 1;
				container.push(dis);
			}
		}
	}
	return (d[network.t] != -1);
}
double DFS(const std::vector<int>& d, std::vector<int>& cur, Network& network)
{
	double flow = 0.0;
	std::map<int, int> pred;
	std::stack<int> container;
	container.push(network.s);
	while (!container.empty())
	{
		int cnt = container.front();
		container.pop();
		if (cnt == network.t)
		{
			int path_cnt = network.t;
			double capacity_lim = DBL_MAX;
			while(path_cnt != network.s)
			{
				
				path_cnt = pred[path_cnt];	
			} 
		}
		else{
			for (int& cnt_edge = cur[cnt]; cnt_edge != -1; cnt_edge = network.edge_set[cnt_edge].next)
			{
				int to = network.edge_set[cnt_edge].to;
				if (d[to] == d[cnt] + 1 && network.edge_set[cnt_edge] > 0)
				{
					pred[to] = cnt;
					container.push(to);	
				}
			}
		}
	}
}
double Dinic(Network network)
{
	std::vector<int> d;
	std::vector<int> cur;
	cur.resize(network.v_num);
	double max_flow = 0.0;
	while(BFS(d, network))
	{
		cur.assign(network.head.begin(), network.head.end());
		max_flow += DFS(d, cur, network);
	}
	return max_flow;
}
int main()
{
	return 0;
}
