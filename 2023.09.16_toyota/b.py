str = input()
longest_len = 0
for i in range(len(str)):
	j = 0
	while i - j >= 0 and i + j < len(str) and str[i - j] == str[i + j]:
		j += 1
	length = j * 2 - 1
	if length > longest_len:
		longest_len = length
	j = 0
	if i < len(str) - 1 and str[i] == str[i + 1]:
		while i - j >= 0 and i + j + 1 < len(str) and str[i - j] == str[i + j + 1]:
			j += 1
		length = j * 2
		if length > longest_len:
			longest_len = length
print(longest_len)