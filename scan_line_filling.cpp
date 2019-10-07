#include <gl/glut.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "AVLTree.hpp"
#include "AVLTNode.hpp"
template <typename T>
T min(T t1, T t2) {
	if (t1 < t2)
		return t1;
	else
		return t2;
}
template <typename T>
T max(T t1, T t2)
{
	if (t1 > t2)
		return t1;
	else
		return t2;
}
GLfloat dis(GLfloat a, GLfloat b)
{
	if (a - b >= 0)
		return (a - b);
	else
		return (b - a);
}
struct Point 
{
	int x;
	int y;
	Point(int x, int y) : x(x), y(y) {}
};
struct Edge
{
	int y_max;
	GLfloat x;
	GLfloat dx;
	Edge(Point* p1, Point* p2) 
	{
		y_max = max<int>(p1->y, p2->y);
		x = (p1->y > p2->y) ? p2->x : p1->x;
		dx = (GLfloat)(p2->x - p1->x) / (GLfloat)(p2->y - p1->y);
	}
	bool operator<(const Edge& e) const
	{
		if (x < e.x)
			return true;
		else
			return false;
	}
	bool operator<=(const Edge& e) const 
	{
		if (x <= e.x)
			return true;
		else
			return false;
	}
	bool operator==(const Edge& e) const
	{
		//考虑到浮点误差,充分接近可以认为相等
		if (this->y_max == e.y_max && dis(this->dx, e.dx) < 0.5f && dis(this->x, e.x) < 3.0f)
			return true;
		else
			return false;
	}
	Edge(const Edge& e) 
	{
		y_max = e.y_max;
		dx = e.dx;
		x = e.x;
	}
};
Point* first = NULL;
Point* last = NULL;
Edge* pre_edge = NULL;
int count = 0;
int cnt_y;
std::vector<AVLTree<Edge, AVLTNode<Edge>>*> edge_container;
std::vector<Edge> remove_container;
AVLTree<Edge, AVLTNode<Edge>>* cnt_edge_set= new AVLTree<Edge, AVLTNode<Edge>>();//动态边表
void drawline(GLfloat first_x_co, GLfloat first_y_co, GLfloat second_x_co, GLfloat second_y_co)
{
	glBegin(GL_LINES);
	glVertex2f(first_x_co, first_y_co);
	glVertex2f(second_x_co, second_y_co);
	glEnd();
	glFlush();
}
void visit(AVLTNode<Edge>* node)
{
	cnt_edge_set->insert(node->data);
	node->data.x -= node->data.dx;
}
void visit_update(AVLTNode<Edge>* node)
{
	node->data.x += node->data.dx;
	if (pre_edge) 
	{
		if (dis(pre_edge->x, node->data.x) >= 3.0f)
		{
			if (!(count & 1)) 
			{
				GLfloat first_x_co = (pre_edge->x - 320.0f) / 320.0f;
				GLfloat first_y_co = (240.0f - cnt_y) / 240.0f;
				GLfloat second_x_co = (node->data.x - 320.0f) / 320.0f;
				GLfloat second_y_co = (240.0f - cnt_y) / 240.0f;
				drawline(first_x_co, first_y_co, second_x_co, second_y_co);
			}
			count++;
		}
		else
		{
			//两个点的横坐标可以认为相等,但平衡树中节点的大小关系需要保持
			if (pre_edge->x > node->data.x)
			{
				GLfloat temp = pre_edge->x;
				pre_edge->x = node->data.x;
				node->data.x = temp;
			}
			if (pre_edge->y_max == cnt_y && node->data.y_max == cnt_y) 
			{
				count++;
			}
			else if (pre_edge->y_max != cnt_y && node->data.y_max != cnt_y)
			{
				count++;
				//dx小于0的应"小"
				if (pre_edge->dx > 0) 
				{
					GLfloat temp = pre_edge->dx;
					pre_edge->dx = node->data.dx;
					node->data.dx = temp;
					int temp_ = pre_edge->y_max;
					pre_edge->y_max = node->data.y_max;
					node->data.y_max = temp_;
				}
			}
		}
	}
	pre_edge = &(node->data);
}
//记录要删除的边
void visit_remove(AVLTNode<Edge>* node)
{
	if (node->data.y_max == cnt_y)
		remove_container.push_back(node->data);
}
void scan_line_fill()
{
	for (int i = 0; i <= 480; i++) 
	{
		cnt_y = i;
		edge_container[i]->in_traversal(&visit);
		cnt_edge_set->in_traversal(&visit_update);
		cnt_edge_set->in_traversal(&visit_remove);
		int len = remove_container.size();
		for (int j = len - 1; j >= 0; j--)
		{
			cnt_edge_set->remove(remove_container[j]);
			remove_container.pop_back();
		}
		pre_edge = NULL;
		count = 0;
	}
}
void myMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		glBegin(GL_POINTS);
		GLfloat x_co, y_co;
		x_co = (x - 320.0f) / 320.0f;
		y_co = (240.0f - y) / 240.0f;
		glVertex2f(x_co, y_co);
		glEnd();
		glFlush();
		Point* pNew = new Point(x, y);
		if (!first)
			first = pNew;
		else
		{
			GLfloat last_x_co = (last->x - 320.0f) / 320.0f;
			GLfloat last_y_co = (240.0f - last->y) / 240.0f;
			GLfloat pNew_x_co = (pNew->x - 320.0f) / 320.0f;
			GLfloat pNew_y_co = (240.0f - pNew->y) / 240.0f;
			drawline(last_x_co, last_y_co, pNew_x_co, pNew_y_co);
			if (last->y != pNew->y)//当两个点的纵坐标相同时，不需要处理
				edge_container[min<int>(last->y, pNew->y)]->insert(Edge(last, pNew));
		}
		last = pNew;
	}
}
void myKeys(unsigned char key, int x, int y)
{
	if (key == 32) 
	{
		GLfloat last_x_co = (last->x - 320.0f) / 320.0f;
		GLfloat last_y_co = (240.0f - last->y) / 240.0f;
		GLfloat first_x_co = (first->x - 320.0f) / 320.0f;
		GLfloat first_y_co = (240.0f - first->y) / 240.0f;
		drawline(last_x_co, last_y_co, first_x_co, first_y_co);
		if (last->y != first->y)
			edge_container[min<int>(last->y, first->y)]->insert(Edge(last, first));
		glutMouseFunc(NULL);
		scan_line_fill();
	}
}
int main(int argc, char *argv[])
{
	for (int i = 0; i <= 480; i++)
		edge_container.push_back(new AVLTree<Edge, AVLTNode<Edge>>());
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("输入完点后，请按空格键");
	glutMouseFunc(&myMouse);
	glutKeyboardFunc(&myKeys);
	glutMainLoop();
	for (int i = 0; i <= 480; i++)
		delete edge_container[i];
	delete cnt_edge_set;
	return 0;
}