#include <bits/stdc++.h>
using namespace std;
#define YES cout << "YES" << endl
#define NO cout << "NO" << endl

int	rec_check(const string &target, const vector<string> &terms, const int index);

int	main()
{
	string	target;
	cin >> target;
	string	dest;
	vector<string>	terms = {"dream", "dreamer", "erase", "eraser"};

	if (rec_check(target, terms, 0)) YES;
	else NO;
	return (0);
}

int	rec_check(const string &target, const vector<string> &terms, const int index)
{
	string	t_sub;
	int	next;

	if (target.size() == index) return (1);
	for (const auto &term : terms)
	{
		next = index + term.size();
		if (next > target.size()) continue ;
		t_sub = target.substr(index, term.size());
		if (t_sub == term)
			if (rec_check(target, terms, next)) return (1);
	}
	return (0);
}