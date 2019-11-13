#include<algorithm>
#include<string.h>
#include<math.h>
#include<stdlib.h>
using namespace std;
const int MAXN = 1050;
const double eps = 1e-8;

struct Point
{
	double x, y, z;
	Point() {}
	Point(double xx, double yy, double zz) :x(xx), y(yy), z(zz) {}
	//������֮��
	Point operator -(const Point p1)
	{
		return Point(x - p1.x, y - p1.y, z - p1.z);
	}
	//������֮��
	Point operator +(const Point p1)
	{
		return Point(x + p1.x, y + p1.y, z + p1.z);
	}
	//���
	Point operator *(const Point p)
	{
		return Point(y*p.z - z * p.y, z*p.x - x * p.z, x*p.y - y * p.x);
	}
	Point operator *(double d)
	{
		return Point(x*d, y*d, z*d);
	}
	Point operator / (double d)
	{
		return Point(x / d, y / d, z / d);
	}
	//���
	double  operator ^(Point p)
	{
		return (x*p.x + y * p.y + z * p.z);
	}
};
struct CH3D
{
	struct face
	{
		//��ʾ͹��һ�����ϵ�������ı��
		int a, b, c;
		//��ʾ�����Ƿ���������͹���ϵ���
		bool ok;
		
	};
	//���·���true�����Ϸ���false
	bool judge_direct(face f)
	{
		Point nor = (P[f.a] - P[f.b]) * (P[f.a] - P[f.c]);
		double key_nor = (P[f.a] - key_point) ^ (nor);
		if (key_nor < 0)
		{
			nor.x = -nor.x;
			nor.y = -nor.y;
			nor.z = -nor.z;
		}
		if (nor.z > 0)
			return false;
		else
			return true;
	}
	//��ʼ������
	int n;
	//��ʼ����
	Point P[MAXN];
	//͹���������������
	int num;
	//͹�������������
	face F[8 * MAXN];
	//͹�������������
	int g[MAXN][MAXN];
	Point key_point;
	//��������
	double vlen(Point a)
	{
		return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
	}
	//���
	Point cross(const Point &a, const Point &b, const Point &c)
	{
		return Point((b.y - a.y)*(c.z - a.z) - (b.z - a.z)*(c.y - a.y),
			(b.z - a.z)*(c.x - a.x) - (b.x - a.x)*(c.z - a.z),
			(b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)
		);
	}
	//���������*2
	double area(Point a, Point b, Point c)
	{
		return vlen((b - a)*(c - a));
	}
	//�������������*6
	double volume(Point a, Point b, Point c, Point d)
	{
		return (b - a)*(c - a) ^ (d - a);
	}
	//����������ͬ��
	double dblcmp(Point &p, face &f)
	{
		Point m = P[f.b] - P[f.a];
		Point n = P[f.c] - P[f.a];
		Point t = p - P[f.a];
		return (m*n) ^ t;
	}
	void deal(int p, int a, int b)
	{
		int f = g[a][b];//������ñ����ڵ���һ��ƽ��
		face add;
		if (F[f].ok)
		{
			if (dblcmp(P[p], F[f]) > eps)
				dfs(p, f);
			else
			{
				add.a = b;
				add.b = a;
				add.c = p;//����ע��˳��Ҫ������ϵ
				add.ok = true;
				g[p][b] = g[a][p] = g[b][a] = num;
				F[num++] = add;
			}
		}
	}
	void dfs(int p, int now)//�ݹ���������Ӧ�ô�͹����ɾ������
	{
		F[now].ok = 0;
		deal(p, F[now].b, F[now].a);
		deal(p, F[now].c, F[now].b);
		deal(p, F[now].a, F[now].c);
	}
	bool same(int s, int t)
	{
		Point &a = P[F[s].a];
		Point &b = P[F[s].b];
		Point &c = P[F[s].c];
		return fabs(volume(a, b, c, P[F[t].a])) < eps &&
			fabs(volume(a, b, c, P[F[t].b])) < eps &&
			fabs(volume(a, b, c, P[F[t].c])) < eps;
	}
	//������ά͹��
	void create()
	{
		int i, j, tmp;
		face add;
		num = 0;
		if (n < 4)return;
		//**********************************************
		//�˶���Ϊ�˱�֤ǰ�ĸ��㲻����
		bool flag = true;
		for (i = 1; i < n; i++)
			if (vlen(P[0] - P[i]) > eps)
			{
				swap(P[1], P[i]);
				flag = false;
				break;
			}
		if (flag)return;
		flag = true;
		//ʹǰ�����㲻����
		for (i = 2; i < n; i++)
			if (vlen((P[0] - P[1])*(P[1] - P[i])) > eps)
			{
				swap(P[2], P[i]);
				flag = false;
				break;
			}
		if (flag)return;
		flag = true;
		//ʹǰ�ĸ��㲻����
		for (int i = 3; i < n; i++)
			if (fabs((P[0] - P[1])*(P[1] - P[2]) ^ (P[0] - P[i])) > eps)
			{
				swap(P[3], P[i]);
				flag = false;
				break;
			}
		if (flag)return;
		//*****************************************
		for (i = 0; i < 4; i++)
		{
			add.a = (i + 1) % 4;
			add.b = (i + 2) % 4;
			add.c = (i + 3) % 4;
			add.ok = true;
			if (dblcmp(P[i], add) > 0)swap(add.b, add.c);
			g[add.a][add.b] = g[add.b][add.c] = g[add.c][add.a] = num;
			F[num++] = add;
		}
		for (i = 4; i < n; i++)
			for (j = 0; j < num; j++)
				if (F[j].ok&&dblcmp(P[i], F[j]) > eps)
				{
					dfs(i, j);
					break;
				}
		tmp = num;
		for (i = num = 0; i < tmp; i++)
			if (F[i].ok)
				F[num++] = F[i];
		key_point = barycenter();

	}
	//�����
	double area()
	{
		double res = 0;
		if (n == 3)
		{
			Point p = cross(P[0], P[1], P[2]);
			res = vlen(p) / 2.0;
			return res;
		}
		for (int i = 0; i < num; i++)
			res += area(P[F[i].a], P[F[i].b], P[F[i].c]);
		return res / 2.0;
	}
	//���
	double volume()
	{
		double res = 0;
		Point tmp(0, 0, 0);
		for (int i = 0; i < num; i++)
			res += volume(tmp, P[F[i].a], P[F[i].b], P[F[i].c]);
		return fabs(res / 6.0);
	}
	//���������θ���
	int triangle()
	{
		return num;
	}
	//�������θ���
	int polygon()
	{
		int i, j, res, flag;
		for (i = res = 0; i < num; i++)
		{
			flag = 1;
			for (j = 0; j < i; j++)
				if (same(i, j))
				{
					flag = 0;
					break;
				}
			res += flag;
		}
		return res;
	}
	//��ά͹������
	Point barycenter()
	{
		Point ans(0, 0, 0), o(0, 0, 0);
		double all = 0;
		for (int i = 0; i < num; i++)
		{
			double vol = volume(o, P[F[i].a], P[F[i].b], P[F[i].c]);
			ans = ans + (o + P[F[i].a] + P[F[i].b] + P[F[i].c]) / 4.0*vol;
			all += vol;
		}
		ans = ans / all;
		return ans;
	}
	//�㵽��ľ���
	double ptoface(Point p, int i)
	{
		return fabs(volume(P[F[i].a], P[F[i].b], P[F[i].c], p) / vlen((P[F[i].b] - P[F[i].a])*(P[F[i].c] - P[F[i].a])));
	}
};
