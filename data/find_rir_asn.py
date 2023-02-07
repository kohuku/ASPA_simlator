# detail_xxx ---> 見つけたいAS番号列

import yaml

RIR_NAME="RIPE"
FILE_NAME="./data/detail/detail_dic"

def check_rir(line):
    yam=line[len(asn)+1:]
    content=yaml.safe_load(yam)
    if(content["status_message"]!="Query was successful"):
        return 0
        
    # if(dic_num%1000==0):print(dic_num)
    if(content["data"]["rir_allocation"]["rir_name"]!=RIR_NAME):return 0

        
    asn=content["data"]["asn"]
    return asn

start=int(input("please input start file number"))
end=int(input("please input final file number"))

for dic_num in range(start,end+1):
    with open(FILE_NAME+str(dic_num)) as fp:
        for line in fp:
            res=check_rir(line)
            if res : print(res,end=' ')

print()