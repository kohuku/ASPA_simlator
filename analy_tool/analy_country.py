import yaml
FILE_NAME="graph_data/ripe_graph_with_cntcode.yaml"

##国ごとのAS数を数える

s=set()
d=dict()
with open(FILE_NAME) as fp:
    for line in fp:
        data=yaml.safe_load(line)
        s.add(data["country"])
        if(data["country"] in d):
            d[data["country"]]+=1
        else:
            d[data["country"]]=0
print(len(s))
li=[]
for x in d.values():
    li.append(x)

li=sorted(d.items(),key= lambda x :x[1],reverse=True)
print(li)