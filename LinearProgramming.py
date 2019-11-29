from scipy import optimize
import numpy as np
#利用线性规划求解最大流问题
print("请输入点的个数,边的个数")
v_num, e_num = map(int, input().split())
c_list = [0 for i in range(e_num)]
A_list = [[0 for i in range(e_num)] for j in range(e_num)]
b_list = [0 for i in range(e_num)]
Aeq_list = [[0 for i in range(e_num)] for j in range(v_num)]
beq_list = [0 for i in range(v_num)]
for i in range(e_num):
    print("请输入第%d条边的起点、终点、权值" % i)
    u, v, w = map(int, input().split())
    A_list[i][i] = 1
    b_list[i] = w
    Aeq_list[u][i] = 1
    Aeq_list[v][i] = -1
print("请输入源点、溯点")
s, t = map(int, input().split())
for i in range(e_num):
    Aeq_list[s][i] = 0
    if Aeq_list[t][i] == -1:
        c_list[i] = 1
    elif Aeq_list[t][i] == 1:
        c_list[i] = -1
    Aeq_list[t][i] = 0
c = np.array(c_list)
A = np.array(A_list)
b = np.array(b_list)
Aeq = np.array(Aeq_list)
beq = np.array(beq_list)
bounds = [(0, None) for i in range(e_num)]
res = optimize.linprog(-c, A, b, Aeq, beq, bounds=tuple(bounds))
print("最大流为:")
print(-res.fun)
print("取得最大流时，一种各条弧流量值")
print(res.x)



