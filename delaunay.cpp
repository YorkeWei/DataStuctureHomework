#include "convex.h"
#include <iostream>
#include <gl/glut.h>
#include <set>
CH3D hull;
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
void dispaly()
{
	std::cout << "请输入点的个数:";
	std::cin >> hull.n;
	for (int i = 0; i < hull.n; i++)
	{
		std::cin >> hull.P[i].x >> hull.P[i].y;
		hull.P[i].z = (hull.P[i].x) * (hull.P[i].x) + (hull.P[i].y) * (hull.P[i].y);
		glBegin(GL_POINTS);
		GLfloat x_co, y_co;
		x_co = (hull.P[i].x - 320.0f) / 320.0f;
		y_co = (240.0f - hull.P[i].y) / 240.0f;
		glVertex2f(x_co, y_co);
		glEnd();
		glFlush();
	}
	hull.create();
	std::cout << hull.num << std::endl;
	std::set<std::pair<int, int>> edge;
	for (int i = 0; i < hull.num; i++)
	{
		bool dir = hull.judge_direct(hull.F[i]);
		if (dir)
		{
			edge.insert(std::make_pair(hull.F[i].a, hull.F[i].b));
			edge.insert(std::make_pair(hull.F[i].a, hull.F[i].c));
			edge.insert(std::make_pair(hull.F[i].b, hull.F[i].c));
		}
	}
	std::set<std::pair<int, int>>::iterator it;
	for (it = edge.begin(); it != edge.end(); it++) 
	{
		drawline(hull.P[it->first], hull.P[it->second]);
	}
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Delaunay");
	glutDisplayFunc(&dispaly);
	glutMainLoop();
	return 0;
}