#!/usr/bin/python3.5
import sys
import re
import collections

if len(sys.argv)<2:
	print("Use bnf2c.py <file.bnf>")
	exit()

f=open(sys.argv[1])

name=None

out=''

def pr(s):
	global out
	out+=s

def Camel(s):
	names=s.split('-')
	ready=''
	for n in names:
		ready+=n[0:1].upper()+n[1:]
	return ready

def predicate(s):

	match=re.match(r'^<(.*?)>$',s)
	if match:
		return (Camel(match.group(1)),)

	match=re.match(r'\{(.*?)\}\*',s)
	if match:
		return ('ZeroOrMore',predicate(match.group(1)))

	match=re.match(r'\{(.*?)\}\+',s)
	if match:
		return ('OneOrMore',predicate(match.group(1)))

	match=re.match(r'\{(.*?)\}\?',s)
	if match:
		return ('Optional',predicate(match.group(1)))

	match=re.match(r'"(.*?)"',s)
	if match:
		return ('Expect',match.group(1))

	return ('Expect',s)

grammar=collections.OrderedDict()

def clause(rules):
	global out1

	for rule in rules.split('|'):
		items=rule.split(' ')
		items[:] = (v for v in items if v != '')

		if len(items)==1:
			first=predicate(items[0])
			if first in grammar[name].keys():
				grammar[name][first].append([]);
			else:
				grammar[name][first]=[];
			continue

		if len(items)>1:
			first=predicate(items[0])
			seq=[]
			for i in items[1:]:
				seq.append(predicate(i))

			if first in grammar[name].keys():
				grammar[name][first].append(seq);
			else:
				grammar[name][first]=[seq];


for s in f:
	match=re.match(r'<(.*?)>\s*::=\s(.*)',s)
	if match:
		name=Camel(match.group(1))
		if name:
			if name not in grammar.keys():
				grammar[name]=collections.OrderedDict()
		clause(match.group(2))

	match=re.match(r'\s*\|\s*(.*)',s)
	if match:
		clause(match.group(1))


def st(t):
	if len(t)==1:
		return t[0]+'(c,t)'
	elif len(t)==2:
		if t[0]=='Expect':
			return 'Expect(c,"'+t[1]+'",t)'
		else:
			return t[0]+'(c,t,'+t[1][0]+')'
	else:
			return t[0]+'(c,'+t[1]+str(t[2:])+',t)'

pr("\n//Declarations\n")
for func in grammar.keys():
	pr('inline int '+func+'(SParseContext& c, SParseTree& t);\n')

pr("\n//Definitions\n")

def keyRule(item):
	pr('\t\t\t{// Many nonterminals\n');
	n=0
	ts=['tn0']
	line=''
	end=''
	for i in item:
		n+=1;
		tni='tn'+str(n);
		line+='\t\t\t'+'\t'*n+'int '+tni+'='+st(i)+';\n'
		line+='\t\t\t'+'\t'*n+'if('+tni+')\n'
		line+='\t\t\t'+'\t'*n+'{\n'
		ts.append(tni)
		end='\t\t\t'+'\t'*n+'}'+'/*'+str(n)+'*/'+'\n'+end
	line+='\t\t\t\t'+'\t'*n+'return TreeItem(t,"'+key+'", {'+', '.join(ts)+'});\n'
	pr(line+end)
	pr('\t\t\t}\n');



for key in grammar.keys():
	pr('inline int '+key+'(SParseContext& c, SParseTree& t)\n{\n')

	for first in grammar[key].keys():
		if len(grammar[key][first])==0:
			pr('\t{// Single rule single nonterminal\n\t\tint tn='+st(first)+';\n\t\tif(tn){return TreeItem(t,"'+key+'",{tn});}\n\t}\n')
		elif len(grammar[key][first])==1:
			pr('\t{// Single rule multiple nonterminals\n\t\tint tn0='+st(first)+';\n')
			pr('\t\tif(tn0)\n\t\t{\n')
			item=grammar[key][first][0];
			keyRule(item)
			pr('\t\t}\n')
			pr('\t}\n')

		else:
			pr('\t{// Many rules\n\t\tint tn0='+st(first)+';\n',)
			pr('\t\tif(tn0)\n\t\t{\n')
			for item in grammar[key][first]:
				if len(item)==0:
					pr('\t\t\treturn TreeItem(t,"'+key+'",{tn0});\n')
				else:
					keyRule(item)
			pr('\t\t}// Multiple nonterms\n')
			pr('\t}// Many rules\n')
	pr('\treturn 0;\n}\n')

sys.stdout.write(out)