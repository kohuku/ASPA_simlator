import subprocess
import pandas as pd

program="./sim.out < in"
excel_file="test.xlsx"

attack_list=['777', '35123', '59488', '197065', '203158', '204044', '204920', '50831', '210004', '61005']
target_list=['48864', '35061', '212913', '211752', '20813', '202633', '39369', '25094', '3311', '197944']


def res_to_int(line):
    s=line.split('\n')
    return [int(s[0]),int(s[1])]

def attack(num):

    res_sum_before=0
    res_sum_after=0

    for a in attack_list:
        t=" "+a
        for v in target_list:
            s=t+" "+v+" "+str(num)
            res=subprocess.check_output(program+s,shell=True).decode('utf-8')
            # print(res)
            res_i=res_to_int(res)
            res_sum_before+=res_i[0]
            res_sum_after+=res_i[1]

    return (res_sum_before-res_sum_after)/res_sum_before

res=[]
for i in range(101,401):
    print(i)
    res.append(attack(i))

print(res)

