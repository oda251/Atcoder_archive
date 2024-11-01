#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
static const bool Booster = [](){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	return true;
}();
using namespace std;
typedef long long ll;

int _;
clock_t start_time = clock();
void cerr_time(void) {
	cerr << "time: " << (double)(clock() - start_time) / 1000 << "ms" << endl;
}
