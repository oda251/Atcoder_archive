#include <bits/stdc++.h>
using namespace std;

int main()
{
	int M;
	string S1, S2, S3;
	cin >> M >> S1 >> S2 >> S3;

	vector<pair<char, int>> candy;
	for (auto a : S1)
	{
		if (find(S2.begin(), S2.end(), a) != S2.end() && find(S3.begin(), S3.end(), a) != S3.end()) candy.emplace_back(a, -1);
	}
	if (candy.empty())
	{
		cout << -1 << endl;
		return (0);
	}
	auto zurasu = [M](int &t1, int &t2, string &S1, string &S2, char num){
		int t1_tmp = INT_MAX;
		int t2_tmp = INT_MAX;
		if (find(S1.begin() + t1, S1.end(), num) != S1.end())
		{
			t1_tmp = find(S1.begin() + t1, S1.end(), num) - S1.begin();
		}
		if (find(S2.begin() + t2, S2.end(), num) != S2.end())
		{
			t2_tmp = find(S2.begin() + t2, S2.end(), num) - S2.begin();
		}
		if (t1_tmp > t2_tmp) t2 = t2_tmp;
		else if (t1_tmp < t2_tmp) t1 = t1_tmp;
		else if (t1_tmp != INT_MAX) t1 = t1_tmp;
		else t1 += M;
	};
	for (auto &p : candy)
	{
		int t1 = find(S1.begin(), S1.end(), p.first) - S1.begin();
		int t2 = find(S2.begin(), S2.end(), p.first) - S2.begin();
		int t3 = find(S3.begin(), S3.end(), p.first) - S3.begin();
		while (t1 == t2 || t2 == t3 || t3 == t1)
		{
			if (t1 == t2) zurasu(t1, t2, S1, S2, p.first);
			if (t1 == t3) zurasu(t1, t3, S1, S3, p.first);
			if (t2 == t3) zurasu(t2, t3, S2, S3, p.first);
		}
		p.second = max(t1, t2);
		p.second = max(p.second, t3);
	}
	sort(candy.begin(), candy.end(), [](auto &a, auto &b){ return b.second > a.second; });
	cout << candy[0].second << endl;
}