# dic --> graph_map(ref....asns file)

import yaml

asn_file="ripe_data/ripe_as"
peer_file="ripe_data/peer_dic"
down_file="ripe_data/down_dic"
detail_file="ripe_data/detail_dic"
valid_asns=set()

def get_country(line,asn):
  yam=line[len(asn)+1:]
  content=yaml.safe_load(yam)
  return content["data"]["country_code"]

def get_next(p_or_d,line,asn,tmp):
  yam=line[len(asn)+1:]
  content=yaml.safe_load(yam)
  data=content["data"][p_or_d]
  
  res=[]
  for d in data:
    if(str(d["asn"]) in valid_asns):
      if(p_or_d=="ipv4_peers"):
        if(d["asn"] in tmp):continue
      res.append(d["asn"])
  return res
  
def pick_v4_graph():
  
  with open(peer_file) as p_fp, open(down_file) as d_fp, open(detail_file) as x_fp :
    for p_line,d_line,x_line in zip(p_fp,d_fp,x_fp):
      asn=(p_line.split()[0])
      
      downstreams=get_next("ipv4_downstreams",d_line,asn,[]) 
      peers=get_next("ipv4_peers",p_line,asn,downstreams)
      country=get_country(x_line,asn)
      print({"asn": int(asn), "peers": peers, "downstreams": downstreams, "country" : country})
  
  
  
def make_asn_table():
  with open(asn_file) as fp:
    asns=set(fp.readline().split())
  return asns

valid_asns=make_asn_table()
pick_v4_graph()
