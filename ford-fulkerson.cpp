#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <map>
//v终点
struct edge
{
	int v;
	double capacity;
	edge(int v, double capacity) :  v(v), capacity(capacity) {}
};
struct Network
{
	int v_num;
	int e_num;
	int s;
	int t;
	std::vector<std::vector<edge>> relate_edge;
	Network()
	{
		std::cout << "请输入点的个数:" << std::endl;
		std::cin >> v_num;
		std::cout << "请输入边的个数:" << std::endl;
		std::cin >> e_num;
		relate_edge.resize(v_num);
		for (int i = 0; i < e_num; i++)
		{
			int u;
			int v;
			double capacity;
			std::cout << "请输入第" + std::to_string(i) + "条边的起点、终点、容量:" << std::endl;
			std::cin >> u >> v >> capacity;
			relate_edge[u].push_back(edge(v, capacity));
		}
		std::cout << "请输入源点:" << std::endl;
		std::cin >> s;
		std::cout << "请输入溯点:" << std::endl;
		std::cin >> t;
	}
	Network(int v_num, int e_num, int s, int t, std::vector<std::pair<int, int>>& edge_set, std::vector<double>& edge_wei)
		: v_num(v_num), e_num(e_num), s(s), t(t)
	{
		relate_edge.resize(v_num);
		std::vector<std::pair<int, int>>::iterator it;
		std::vector<double>::iterator _it;
		for (it = edge_set.begin(), _it = edge_wei.begin(); it != edge_set.end(); it++, _it++)
		{
			relate_edge[it->first].push_back(edge(it->second, *_it));
		}
	}
};
//为了不破坏原始网络, 进行拷贝操作
//network也即是初始残差网络
double max_flow(Network network)
{
	double max_flow = 0.0;
	std::vector<edge>::iterator it;
	while (true) {
		std::stack<int> path;
		std::queue<int> container;
		std::map<int, int> pre_node;
		for (int i = 0; i < network.v_num; i++)
			pre_node[i] = -1;
		double capacity_lim = DBL_MAX;
		container.push(network.s);
		bool flag = false;
		while (!container.empty())
		{
			int cnt = container.front();
			container.pop();
			if (cnt == network.t)
			{
				flag = true;
				int path_cnt = network.t;
				while (path_cnt != network.s)
				{
					path.push(path_cnt);
					double cnt_capacity;
					for (it = network.relate_edge[pre_node[path_cnt]].begin(); it != network.relate_edge[pre_node[path_cnt]].end(); it++)
					{
						if (it->v == path_cnt)
						{
							cnt_capacity = it->capacity;
							break;
						}
					}
					capacity_lim = std::min(capacity_lim, cnt_capacity);
					path_cnt = pre_node[path_cnt];
				}
				path.push(network.s);
				break;
			}
			std::vector<edge>& cnt_relate_edge = network.relate_edge[cnt];
			for (it = cnt_relate_edge.begin(); it != cnt_relate_edge.end(); it++)
				if (it->capacity > 0 && pre_node[it->v] < 0)
				{
					pre_node[it->v] = cnt;
					container.push(it->v);
				}
		}
		if (flag)
		{
			max_flow += capacity_lim;
			int pre = path.top();
			path.pop();
			while (!path.empty())
			{
				int cnt = path.top();
				path.pop();
				bool exist = false;
				for (it = network.relate_edge[cnt].begin(); it != network.relate_edge[cnt].end(); it++)
				{
					if (it->v == pre)
					{
						it->capacity += capacity_lim;
						exist = true;
						break;
					}
				}
				if (!exist)
					network.relate_edge[cnt].push_back(edge(pre, capacity_lim));
				for (it = network.relate_edge[pre].begin(); it != network.relate_edge[pre].end(); it++)
				{
					if (it->v == cnt)
					{
						it->capacity -= capacity_lim;
					}
				}
				pre = cnt;
			}
		}
		else
			return max_flow;
	}
}
//解决二分图问题
double bipartite_graphs()
{
	int num_a;
	int num_b;
	int e_num;
	std::cout << "请分别输入点集A、B的元素个数:" << std::endl;
	std::cin >> num_a >> num_b;
	std::cout << "请输入边集元素个数:" << std::endl;
	std::cin >> e_num;
	std::vector<std::pair<int, int>> edge_set;
	std::vector<double> edge_wei;
	edge_set.resize(e_num + num_a + num_b);
	edge_wei.resize(e_num + num_a + num_b);
	for (int i = 0; i < e_num; i++) 
	{
		int u, v;
		std::cout << "请输入第" + std::to_string(i) + "条边的起点(A)、终点(B)" << std::endl;
		std::cin >> u >> v;
		edge_set[i] = std::make_pair(u, v);
		edge_wei[i] = 1.0;
	}
	for (int i = 0; i < num_a; i++)
	{
		edge_set[i + e_num] = std::make_pair(num_a + num_b, i);
		edge_wei[i + e_num] = 1.0;
	}
	for (int i = 0; i < num_b; i++)
	{
		edge_set[i + e_num + num_a] = std::make_pair(i + num_a, num_a + num_b + 1);
		edge_wei[i + e_num + num_a] = 1.0;
	}
	Network network(num_a + num_b + 2,  e_num + num_a + num_b, num_a + num_b, num_a + num_b + 1, edge_set, edge_wei);
	return max_flow(network);
}
int main()
{
	Network network;
	std::cout << max_flow(network);
	std::cout << bipartite_graphs();
	return 0;
}