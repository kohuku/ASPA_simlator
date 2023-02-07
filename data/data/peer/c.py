#graph(map) --> LOTUS command set

import yaml

FILE_NAME1="down_dic"
FILE_NAME2="peer_dic"

l=[x for x in range(64)]+[x for x in range(130,151)]
l=[40]
for i in l:
    with open(FILE_NAME2+str(i)) as fp:
        for line in fp:
            if(len(line)<10):
                print(len(line))
                print(line.split()[0])