import os

def f(directory):
	count = 0
	sum = 0
	# 指定したディレクトリ内のすべてのファイルを走査
	for filename in os.listdir(directory):
		if filename.endswith(".txt"):
			file_path = os.path.join(directory, filename)
			# ファイルを開いて一行目を読み込む
			with open(file_path, "r", encoding="utf-8") as file:
				first_line = file.readline().strip()  # strip()で改行文字を削除
				sum += int(first_line)
				count += 1

	return sum / count

print(f("./result/"))