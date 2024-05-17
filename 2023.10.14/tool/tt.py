import subprocess
import os

dir_path = ".\in\\"
file_names = os.listdir(dir_path)
scores = {}

for testfile in file_names:
	print(f'testing {testfile}')
	res = subprocess.run(["powershell.exe", f'cat {dir_path}{testfile} | .\\tester.exe py .\\v12.py'], capture_output=True)
	if res.stderr:
		scores[testfile] = int(res.stderr.decode("shift-jis").split()[2])

sorted_dict = {k: v for k, v in sorted(scores.items(), key=lambda item: item[1])}
for k, v in sorted_dict.items():
	print(f'{k}: {v}')
print(f'sum: {sum(sorted_dict.values())}')