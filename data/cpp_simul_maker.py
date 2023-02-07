#graph(map) --> LOTUS(cpp) command set

import yaml

FILE_NAME1="graph_data/jp_graph.yaml"
FILE_NAME2="graph_data/ripe_graph.yaml"


with open(FILE_NAME1) as fp:
    for line in fp:
        data=yaml.safe_load(line)
        downs=data["downstreams"]
        for d in downs:
            print("{} {} d".format(data["asn"],d))

        peers=data["peers"]
        for p in peers:
            print("{} {} p".format(data["asn"],p))


print("0 0 end")