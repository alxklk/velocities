#!/usr/bin/python3.5

import subprocess
import re

pipe=subprocess.Popen(['ipcs', '-ma'], stdout=subprocess.PIPE)

for line in pipe.stdout:
	match=re.match(r'.*?(\d+)\W+klk\W+777\W+\d+0.*?', str(line))
	if match:
		print(match.group(1))
		pipe1=subprocess.Popen(['ipcrm', 'shm',  match.group(1)], stdout=subprocess.PIPE)
		for line1 in pipe1.stdout:
			print(line1)

