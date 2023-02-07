import subprocess

start=int(input())
l=[x for x in range(64)]+[x for x in range(130,140)]
for i in l:
    if(i<start//1000):continue
    
    l=[str(x) for x in range(max(1000*i+1,start),1000*(i+1)+1)]

    s=str(i)+" "
    s+=" ".join(l)
    s="./add_data.sh "+s
    subprocess.call(s,shell=True)
    
