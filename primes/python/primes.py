#!/usr/bin/python

def go():
	for i in range(50000):
		comp=0
		for j in range (2,i):
			rf=float(i)/j
			ri=int(rf)
			if rf==ri:
				comp=1
				break

		if comp==0:
			print(str(i)+" -- simple")

go()
