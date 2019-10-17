#include <iostream>
#include <string>
#include <map>
//以下索引均为从0开始
int KMP(std::string& str, std::string& sub_str)
//返回第一次匹配位置,如无匹配位置，返回-1
{
	//先求解匹配函数值
	//A = {k : sub_str[f^(k)[i - 1] + 1] == sub_str[i]}
	//若A不为空集f[i] = f^(k)[i - 1] + 1其中k = min A
	//若A为空集 则 f[i] = -1
	//f[0] = -1 f[-1](空串) = -1
	int size = sub_str.size();
	std::map<int, int> f;
	f[-1] = -1;
	f[0] = -1;
	for (int i = 1; i < size; i++) 
	{
		for (int j = f[i - 1];; j = f[j]) 
		{
			if (sub_str[j + 1] == sub_str[i])
			{
				f[i] = j + 1;
				break;
			}
			if (j == -1) 
			{
				f[i] = -1;
				break;
			}
		}
	}
	//匹配算法
	int sum_size = str.size();
	int count = 0;
	for (int i = 0; i < sum_size;)
	{
		if (str[i] == sub_str[count])
		{
			i++;
			count++;
		}
		else
		{
			if (count == 0)
				i++;
			count = f[count - 1] + 1;
		}
		if (count == size)
			return (i - count);
	}
	return -1;
}
int main() 
{
	std::string str = "Please send this message to those people who mean something to you,to those who have touched your life in one way or another,to those who make you smile when you really need it,to those that make you see the brighter side of things when you are really down,to those who you want to let them know that you appreciate their friendship.And if you don’t, don’t worry,nothing bad will happen to you,you will just miss out on the opportunity to brighten someone’s day with this message.";
	std::string sub_str = "really";
	int kmp_res = KMP(str, sub_str);
	std::cout << kmp_res << std::endl;
	if (kmp_res != -1)
		for (int i = kmp_res; str[i] != ' '; i++) 
		{
			std::cout << str[i];
		}
	return 0;
}