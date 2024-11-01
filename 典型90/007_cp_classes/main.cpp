#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll N, Q;
vector<ll> A, B;
int	main()
{
	cin >> N;
	A.resize(N);
	for (int i=0; i<N; i++) {
		cin >> A[i];
	}
	cin >> Q;
	B.resize(Q);
	for (int i=0; i<Q; i++) {
		cin >> B[i];
	}
	sort(A.begin(), A.end());
	auto nibunho = [&](ll x) -> ll {
		size_t left = 0;
		size_t right = N - 1;
		while (true) {
			size_t mid = (left + right) / 2;
			if (A[mid] == x) {
				return 0;
			} else if (mid == left || mid == right) {
				return min(abs(A[left] - x), abs(A[right] - x));
			}
			if (A[mid] < x) {
				left = mid;
			} else {
				right = mid;
			}
		}
	};
	for (int i=0; i<Q; i++) {
		ll ans = nibunho(B[i]);
		cout << ans << endl;
	}
	return 0;
}