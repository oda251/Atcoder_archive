from collections import namedtuple

Group = namedtuple('Group', ['arr', 'tier'])
N, D, Q = map(int, input().split())

def compare():
	global Q
	Q -= 1
	return (input())

def devide_in_2_part(g0, start, end):
	mid = (start + end) // 2
	g1 = Group(g0.arr[:mid], g0.tier + 1)
	g2 = Group(g0.arr[mid:], g0.tier + 1)
	if (start + 1 > mid or end - 1 < mid):
		return [g1, g2]
	q = f'{mid} {len(g0.arr) - mid} {" ".join(g1.arr)} {" ".join(g2.arr)}'
	if (not Q):
		return [g1, g2]
	print(q)
	res = compare()
	if res == "<":
		return devide_in_2_part(g0, mid, end)
	elif res == ">":
		return devide_in_2_part(g0, start, mid)
	else:
		return [g1, g2]

groups = [Group([str(i) for i in range(N)], 0)]
while (len(groups) < D):
	groups = [g for group in groups for g in devide_in_2_part(group, 0, len(group.arr))]
	if (len(groups) >= D):
		break

for i in range(len(groups) - D):
	g = groups.pop()
	for j, v in enumerate(g.arr):
		groups[j % len(groups)].arr.append(v)

for g in groups:
	if (len(g.arr) == 0):
		for gg in groups:
			if (len(gg.arr) > 1):
				g.arr.append(gg.arr.pop())
				break

for _ in range(Q):
	print("1 1 0 1")

for i in range(N):
	for j, g in enumerate(groups):
		if str(i) in g.arr:
			if (i < N - 1):
				print(str(j), end=" ")
			else:
				print(str(j))
			break