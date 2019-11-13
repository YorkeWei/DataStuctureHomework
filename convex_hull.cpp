#include <gl/glut.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include "quickSort.h"
struct g_vector
{
	int x;
	int y;
	g_vector(int x, int y) : x(x), y(y) {}
};
struct Point
{
	int x;
	int y;
	double angle;
	Point() {}
	Point(int x, int y) : x(x), y(y) {}
	Point(const Point& p) : x(p.x), y(p.y), angle(p.angle) {}
	bool operator==(const Point& p) const
	{
		return (this->x == p.x) && (this->y == p.y);
	}
	bool operator<(const Point& p) const 
	{
		return this->angle < p.angle;
	}
	bool operator<=(const Point& p) const
	{
		return this->angle <= p.angle;
	}
	g_vector operator-(const Point& p) const
	{
		return g_vector(p.x - this->x, p.y - this->y);
	}
};
int cross_product(const g_vector& p1, const g_vector& p2)
{
	return p1.x * p2.y - p1.y * p2.x;
}
void drawline(const Point& p1, const Point& p2)
{
	GLfloat first_x_co = (p1.x - 320.0f) / 320.0f;
	GLfloat first_y_co = (240.0f - p1.y) / 240.0f;
	GLfloat second_x_co = (p2.x - 320.0f) / 320.0f;
	GLfloat second_y_co = (240.0f - p2.y) / 240.0f;
	glBegin(GL_LINES);
	glVertex2f(first_x_co, first_y_co);
	glVertex2f(second_x_co, second_y_co);
	glEnd();
	glFlush();
}
void get_convex_hull()
{
	int num;
	std::cout << "请输入点数:";
	std::cin >> num;
	std::vector<Point> point_vec;
	int min_x = 640, min_y = 480;
	
	unsigned seed;
	seed = time(0);
	for (int i = 0; i < num; i++)
	{
		int x = rand() % 640;
		int y = rand() % 480;
		point_vec.push_back(Point(x, y));
		if ((y < min_y) || ((y == min_y) && (x < min_x)))
		{
			
			min_x = x;
			min_y = y;
		}
		glBegin(GL_POINTS);
		GLfloat x_co, y_co;
		x_co = (x - 320.0f) / 320.0f;
		y_co = (240.0f - y) / 240.0f;
		glVertex2f(x_co, y_co);
		glEnd();
		glFlush();
	}
	for (int i = 0; i < num; i++)
	{
		int x = point_vec[i].x;
		int y = point_vec[i].y;
		point_vec[i].angle = atan2(y - min_y, x - min_x);
	}
	quickSort_non_rec(point_vec, 0, num - 1);
	std::map<Point, Point> pre_p;//保存前一个结点
	pre_p[point_vec[0]] = point_vec[num - 1];
	for (int i = 1; i < num; i++)
		pre_p[point_vec[i]] = point_vec[i - 1];
	std::stack<Point> path;
	path.push(point_vec[0]);
	Point cnt_p1;
	Point cnt_p2;
	Point pre;
	int cross = 0;
	for (int i = 1; i < num; i++)
	{
		cnt_p1 = path.top();
		cnt_p2 = point_vec[i];
		pre = pre_p[cnt_p1];
		cross = cross_product(cnt_p2 - cnt_p1, cnt_p1 - pre);
		if (cross <= 0)
		{
			pre_p[cnt_p2] = cnt_p1;
			path.push(cnt_p2);
		}
		else
		{
			while (cross > 0)
			{
				path.pop();
				if (path.empty())
				{
					cnt_p1 = point_vec[num - 1];
					break;
				}
				cnt_p1 = path.top();
				pre = pre_p[cnt_p1];
				cross = cross_product(cnt_p2 - cnt_p1, cnt_p1 - pre);
			}
			pre_p[cnt_p2] = cnt_p1;
			path.push(cnt_p2);
		}
	}
	while (!path.empty())
	{
		Point cnt_p = path.top();
		path.pop();
		drawline(cnt_p, pre_p[cnt_p]);
	}
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("求凸包");
	glutDisplayFunc(&get_convex_hull);
	glutMainLoop();
	return 0;
}