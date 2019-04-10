d=[6,9,7,3]
arr_time=[0,0,0,0]
p={}
for i,j in enumerate(d):
	p[j]=i+1
print(p)
ord_list=[]

d.sort()
orig=d[:]
from collections import defaultdict
comp=defaultdict(list)
new=defaultdict(list)
total=0
while d!=[]:
	val=d.pop(0)
	ord_list.append(p[val])
	comp[p[val]].append([val,(total,total+val)])
	total+=val
pri=0
key=[x for x in range(1,len(comp)+1)]

print('process  burst   sched   comp  turn  wait')
for i in key:
	bu,sc,ct=comp[i][0][0],comp[i][0][1][0],comp[i][0][1][1]
	at=arr_time[i-1]
	tt=ct-at
	wt=tt-bu
	new[i].append([at,bu,sc,ct,tt,wt,pri])
for j in new.keys():
	print(j,new[j)
