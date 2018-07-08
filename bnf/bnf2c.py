#!/usr/bin/python3.5
import re

f=open('c.bnf')

name=None

out0=""
out1=""


def Camel(s):
	names=s.split('-')
	ready=''
	for n in names:
		ready+=n[0:1].upper()+n[1:];
	return ready

def predicate(s, s1='(c0)'):

	match=re.match('^<(.*?)>$',s)
	if match:
		return Camel(match.group(1))+s1

	match=re.match('\{(.*?)\}\*',s)
	if match:
		return "ZeroOrMore(c0,"+predicate(match.group(1),'')+')'

	match=re.match('\{(.*?)\}\+',s)
	if match:
		return "OneOrMore(c0,"+predicate(match.group(1),'')+')'

	match=re.match('\{(.*?)\}\?',s)
	if match:
		return "Optional(c0,"+predicate(match.group(1),'')+')'

	return 'Expect(c0,"'+s+'")'

def clause(s):
	global out1

	items=s.split(' ')
	if len(items)==1:
		s=predicate(items[0])
		if s:
			out1+=('\tif('+s+'){return true;}'+'\n')
		return

	if len(items)>1:
		out1+="\tc=c0;if("
		out1+=predicate(items[0])
		for i in items[1:]:
			if i=='':
				continue

			s=predicate(i)
			if s:
				out1+='&&'+s

		out1+='){c0=c;return true;}\n'

for s in f:
	match=re.match('<(.*?)>\s*::=\s(.*)',s)
	if match:
		if name:
			out1+=('\treturn false;\n}'+'\n')

		name=match.group(1)
		header='inline bool '+Camel(name)+'(SParseContext& c0)'
		out0+=(header+';\n')
		out1+=('\n'+header+'\n{'+'\n')
		out1+="\tSParseContext c=c0;\n"
		clause(match.group(2))

	match=re.match('\s*\|\s*(.*)',s)
	if match:
		clause(match.group(1))

out1+=('\treturn false;\n}'+'\n')

print("\n//Declarations\n")
print(out0)
print("\n//Definitions\n")
print(out1)