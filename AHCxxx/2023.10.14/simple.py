N, D, Q = map(int, input().split())

dest = []
for i in range(D):
	for j in range(int(N / D)):
		dest.append(i)
for _ in range(N % D):
	dest.append(i)
ans = " ".join(map(str, dest))
for _ in range(Q):
	print("1 1 0 1")
print(ans)