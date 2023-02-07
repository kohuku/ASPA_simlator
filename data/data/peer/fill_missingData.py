import subprocess


def get_down_data(num):
    ope="wget https://api.bgpview.io/asn/" +str(num)+ "/downstreams"
    s=subprocess.check_output(ope)
    return str(s)

def get_peer_data(num):
    ope="wget https://api.bgpview.io/asn/" +str(num)+ "/peers"
    s=subprocess.check_output(ope)
    return str(s)

l=[x for x in range(64)]+[x for x in range(130,151)]
l=[40]
now=0
for i in l:
    with open("peer_dic"+str(i)) as fp:
        data=fp.read()
        now=i*1000
        for line in fp:
            now+=1
            if(len(line)<10):
                data[now%1000-1]=get_peer_data(now)
    with open("down_dic"+str(i),'w') as fp1:
        fp1.write(data)

    

