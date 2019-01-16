import sys

def str2flt(s):
    return tuple(float(f) for f in s.split(' '))

def str2iii(s):
    return tuple(tuple(int(i) for i in f.split('/')) for f in s.split(' '))


f=open(sys.argv[1])

objects = []
vertices = []

for s in f:
    if s[:2]=='o ':
        objects.append({'name':'','v':[],'n':[],'t':[],'f':[]})
        objects[-1]['name']=s[2:-1].replace('.','_')
    if s[:2]=='v ':
        objects[-1]['v'].append(str2flt(s[2:-1]))
    if s[:3]=='vn ':
        objects[-1]['n'].append(str2flt(s[3:-1]))
    if s[:3]=='vt ':
        objects[-1]['t'].append(str2flt(s[3:-1]))
    if s[:2]=='f ':
        objects[-1]['f'].append(str2iii(s[2:-1]))
    
o=open('objects.inc', mode='w')

v0=0
t0=0
n0=0

for s in objects:
    o.write('#declare '+s['name']+'=mesh2\n{\n')

    o.write('\tvertex_vectors\n\t{\n')
    o.write('\t\t'+str(len(s['v']))+',\n')
    for v in s['v']:
        o.write('\t\t<'+', '.join((str(i) for i in v))+'>,\n')
    o.write('\t}\n')

    o.write('\tuv_vectors\n\t{\n')
    o.write('\t\t'+str(len(s['t']))+',\n')
    for v in s['t']:
        o.write('\t\t<'+', '.join((str(i) for i in v))+'>,\n')
    o.write('\t}\n')

    o.write('\tnormal_vectors\n\t{\n')
    o.write('\t\t'+str(len(s['n']))+',\n')
    for v in s['n']:
        o.write('\t\t<'+', '.join((str(i) for i in v))+'>,\n')
    o.write('\t}\n')

    ts=[]
    for v in s['f']:
        if len(v)==3:
            ts.append((v[0],v[1],v[2],))
        elif len(v)==4:
            ts.append((v[0],v[1],v[2],))
            ts.append((v[0],v[2],v[3],))
    s['f']=tuple(ts)

    o.write('\tface_indices\n\t{\n')
    o.write('\t\t'+str(len(s['f']))+',\n')
    for v in s['f']:
        o.write('\t\t<'+', '.join((str(i[0]-1-v0) for i in v))+'>,\n')
    o.write('\t}\n')

    o.write('\tuv_indices\n\t{\n')
    o.write('\t\t'+str(len(s['f']))+',\n')
    for v in s['f']:
        o.write('\t\t<'+', '.join((str(i[1]-1-t0) for i in v))+'>,\n')
    o.write('\t}\n')

    o.write('\tnormal_indices\n\t{\n')
    o.write('\t\t'+str(len(s['f']))+',\n')
    for v in s['f']:
        o.write('\t\t<'+', '.join((str(i[2]-1-n0) for i in v))+'>,\n')
    o.write('\t}\n')

    o.write('}\n')

    v0+=len(s['v'])
    t0+=len(s['t'])
    n0+=len(s['n'])

o=open('scene.inc', mode='w')
o.write('#include "objects.inc"\n')
for s in objects:
    o.write('object{'+s['name']+'}\n')
