#include <iostream>
#include <algorithm>
#include <stack>
#include <map>
int gcd(int a, int b)
{
	int a0, b0;
	while (b != 0)
	{
		a0 = a;
		b0 = b;
		a = b0;
		b = a0 % b0;
	}
	return a;
}
void pour_water(int a, int b, int m)
{	
	int max = std::max(a, b);
	if (m % gcd(a, b) != 0  || m > max)
		std::cout << "нч╫Б" << std::endl;
	else 
	{
		std::stack<std::pair<int, int>> event_container;
 		std::map<std::pair<int, int>, bool> visited;
		std::map<std::pair<int, int>, std::pair<int, int>> pred;
		std::pair<int, int> ini_event = std::make_pair(0, 0);
		std::pair<int, int>  cnt_event;
		event_container.push(ini_event);
		while (!event_container.empty())
		{
			cnt_event = event_container.top();
			event_container.pop();
			if (visited[cnt_event])
				continue;
			visited[cnt_event] = true;
			int first = cnt_event.first;
			int second = cnt_event.second;
			if (first == m || second == m)
				break;
			std::pair<int, int> new_event;
			if (first < a)
			{
				new_event = std::make_pair(a, second);
				if (!visited[new_event])
				{
					event_container.push(new_event);
					pred[new_event] = cnt_event;
				}
			}
			if (second < b)
			{
				new_event = std::make_pair(first, b);
				if (!visited[new_event])
				{
					event_container.push(new_event);
					pred[new_event] = cnt_event;
				}
			}
			if (first > 0)
			{
				new_event = std::make_pair(0, second);
				if (!visited[new_event])
				{
					event_container.push(new_event);
					pred[new_event] = cnt_event;
				}
			}
			if (second > 0)
			{
				new_event = std::make_pair(first, 0);
				if (!visited[new_event])
				{
					event_container.push(new_event);
					pred[new_event] = cnt_event;
				}
			}
			if (a - first >= second)
			{
				new_event = std::make_pair(first + second, 0);
				if (!visited[new_event])
				{
					event_container.push(new_event);
					pred[new_event] = cnt_event;
				}
			}
			else
			{
				new_event = std::make_pair(a, second + first - a);
				if (!visited[new_event])
				{
					event_container.push(new_event);
					pred[new_event] = cnt_event;
				}
			}
			if (b - second >= first)
			{
				new_event = std::make_pair(0, second + first);
				if (!visited[new_event])
				{
					event_container.push(new_event);
					pred[new_event] = cnt_event;
				}
			}
			else 
			{
				new_event = std::make_pair(first + second - b, b);
				if (!visited[new_event])
				{
					event_container.push(new_event);
					pred[new_event] = cnt_event;
				}
			}
		}
		std::stack<std::pair<int, int>> path;
		while (cnt_event != ini_event)
		{
			path.push(cnt_event);
			cnt_event = pred[cnt_event];
		}
		path.push(ini_event);
		while (!path.empty())
		{
			cnt_event = path.top();
			path.pop();
			std::cout << "(" << cnt_event.first << "," << cnt_event.second << ")" << std::endl;
		}
	}
}
int main() 
{
	pour_water(10, 7, 1);
	return 0;
}