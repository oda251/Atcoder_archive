#include <bits/stdc++.h>

using namespace std;

int main() {
	int N;
	N = 6508;
	for (int i=1; i*i<N; i++) {
		if (N % i == 0) {
			cout << i << " " << N / i << endl;
		}
	}
}