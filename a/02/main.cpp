#include <bits/stdc++.h>
using namespace std;

int main()
{
	string S;
	cin >> S;

	int ans = 1;
	for (int i=0; i<S.size(); i++)
	{
		auto itr = find(S.begin()+i+1, S.end(), S[i]);
		while (itr != S.end())
		{
			int tmp = 0;
			bool detected = true;
			for (int j=0; j * 2 <= itr - (S.begin() + i); j++)
			{
				if (*(itr - j) != S[i+j])
				{
					detected = false;
					break;
				}
				if ((itr - (S.begin() + i)) / 2 == j && (itr - (S.begin() + i)) % 2 == 0) tmp++;
				else tmp += 2;
			}
			if (detected == true)
			{
				ans = max(ans, tmp);
			}
			itr = find(itr + 1, S.end(), S[i]);
		}
	}
	cout << ans << endl;
}