FileName="detail_dicx"
output_file="detail_dic"

for i in range(65):
    with open(output_file+str(i),'w') as fp:
        pass

with open(FileName) as fp:
    i=0
    cnt=0
    for line in fp:
        with open(output_file+str(i),'a') as out_f:
            print(line,file=out_f,end='')
            cnt+=1
            if(cnt==1000):
                i+=1
                cnt=0