#include <string>
#include <map>
#include <iostream>
void creat_BC(const std::string& pattern, std::map<char, int>& BC)
{
	int len = pattern.size();
	int i;
	for (i = 0; i < 256; i++)
		BC[i] = -1;
	for (i = 0; i < len; i++)
		BC[pattern[i]] = i;
	
}
void creat_ss(const std::string& pattern, std::map<int, int>& ss)
{
	int len = pattern.size();
	ss[len - 1] = len;
	for (int lo = len - 1, hi = len - 1, i = lo - 1; i >=0 ; i--)
	{
		if ((lo < i) && (ss[len - hi + i - 1] <= i - lo))
			ss[i] = ss[len - hi + i - 1];
		else
		{
			hi = i;
			lo = std::min (lo, hi);
			while ((0 <= lo) && (pattern[lo] == pattern[len - hi + lo - 1]))
				lo--;
			ss[i] = hi - lo;
		}
	}
}
void creat_gs(const std::string& pattern, std::map<int, int>& gs)
{
	std::map<int, int> ss;
	creat_ss(pattern, ss);
	int len = pattern.size();
	int i, j;
	for (i = 0; i < len; i++)
		gs[i] = len;
	for (j = 0, i = len - 1; i >= 0; i--)
	{
		if (i + 1 == ss[i])
			while(j < len - i - 1)
				gs[j++] = len - i - 1;
	}
	for (i = 0; i < len - 1; i++)
		gs[len - ss[i] - 1] = len - i - 1;

}
int BM_Search(const std::string& text, const std::string& pattern)
{
	std::map<char, int> BC;
	std::map<int, int> gs;
	creat_BC(pattern, BC);
	creat_gs(pattern, gs);
	int i = 0;
	int text_len = text.size();
	int pattern_len = pattern.size();
	while (i <= text_len - pattern_len)
	{
		int j = pattern_len - 1;
		while(pattern[j] == text[i + j])
			if (0 > --j) break;
		if (0 > j)
			break;
		else
			i += std::max(gs[j], j - BC[ text[i + j] ]);
	}
	return i;
}
int main()
{
	std::string text;
	std::string pattern;
	std::cin >> text >> pattern;
	std::cout << BM_Search(text, pattern) << std::endl;
	return 0;
}
