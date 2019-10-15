#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
struct Node
{
	int id;
	Node(int id) 
	{
		this->id = id;
	}
};
struct Graph 
{
	std::vector<Node> myNodeList;
	std::map<int, std::map<int, double>> Edges;
	Graph(int node_num, std::vector<int> first, std::vector<int> second, std::vector<double> weight)
	//��һ������Ϊ����������ڶ�������Ϊ�ߵĶ˵㼯�ϣ�����������Ϊ�ߵ���һ���˵㼯�ϣ����ĸ�����Ϊ�ߵ�Ȩֵ���ϣ��������������ж�Ӧ��ϵ
	{
		int i;
		for (i = 0; i < node_num; i++) 
			myNodeList.push_back(Node(i));
		int len = first.size();
		for (i = len - 1; i >= 0; i--) 
		{
			int a = first[i];
			first.pop_back();
			int b = second[i];
			second.pop_back();
			double w = weight[i];
			weight.pop_back();
			Edges[a][b] = w;
			Edges[b][a] = w;
		}
	}
};
class Dijkstra
{
private:
	Graph* g;
	std::vector<std::pair<double, int>> info;
public:
	Dijkstra(Graph* g) 
	{
		this->g = g;
		int len = g->myNodeList.size();
		info.resize(len);
	}
	std::vector<std::pair<double, int>> getInfo()
	{
		return this->info;
	}
	void Run(int source)//����ΪԴ��
	{ 
		struct Event
		{
			double dis;
			int parent;
			int self;
			bool operator>(const Event& e) const
			{
				return this->dis > e.dis;
			}
			Event(double dis, int parent, int self) 
			{
				this->dis = dis;
				this->parent = parent;
				this->self = self;
			}
		};
		int len = g->myNodeList.size();
		std::vector<bool> fixed(len, false);
		std::priority_queue<Event, std::vector<Event>, std::greater<Event>> pending;
		Event e(0.0, -1, source);
		pending.push(e);
		while (!pending.empty()) 
		{
			Event top_evt = pending.top();
			pending.pop();
			int self_id = top_evt.self;
			if (!fixed[self_id])
			{
				fixed[self_id] = true;
				double dis = top_evt.dis;
				int parent = top_evt.parent;
				info[self_id] = std::make_pair(dis, parent);
				std::map<int, double> self_edge = g->Edges[self_id];
				std::map<int, double>::iterator it = self_edge.begin();
				for (; it != self_edge.end(); ++it) 
				{
					int succ = it->first;
					double w = it->second;
					Event new_event(dis + w, self_id, succ);
					pending.push(new_event);
				}
			}
		}
	}
};
int main()
{
	int node_num;
	int edge_num;
	int source;
	std::vector<int> first;
	std::vector<int> second;
	std::vector<double> weight;
	std::cin >> node_num;
	std::cin >> edge_num;
	for (int i = 0; i < edge_num; i++) 
	{
		int a, b;
		double w;
		std::cin >> a >> b >> w;
		first.push_back(a);
		second.push_back(b);
		weight.push_back(w);
	}
	std::cin >> source;
	Graph g(node_num, first, second, weight);
	Dijkstra dij(&g);
	dij.Run(source);
	std::vector<std::pair<double, int>> res = dij.getInfo();
	int len = res.size();
	for (int i = 0; i < len; i++) 
	{
		std::stack<int> path;
		int cnt = i;
		while (cnt != -1) 
		{
			path.push(cnt);
			cnt = res[cnt].second;
		}
		std::cout << "���:" << i << std::endl;
		std::cout << "���·��:";
		while (!path.empty())
		{
			std::cout << path.top() << "->";
			path.pop();
		}
		std::cout << std::endl;
		std::cout << "���·������:" << res[i].first << std::endl;
	}
	return 0;
}