# -*- coding: utf-8 -*-
"""
Created on Mon Jun 10 22:00:02 2019

@author: 君如
"""

'''
动态折线图演示示例
'''
 
import numpy as np
import matplotlib.pyplot as plt

FCFS=[]
RR=[]
SJF=[]
HRN=[]

with open(r"FCFS.txt","r") as f1:
    data1=f1.readlines()
for line in data1:
    FCFS.append(line.split()[0])
print(FCFS)
with open(r"RR.txt","r") as f2:
    data2=f2.readlines()

for line in data2:
    RR.append(line.split()[0])
print(RR)    
    
with open(r"SJF.txt","r") as f3:
    data3=f3.readlines()
for line in data3:
    SJF.append(line.split()[0])
print(SJF)
with open(r"HRN.txt","r") as f4:
    data4=f4.readlines()

for line in data4:
    HRN.append(line.split()[0])
print(HRN)

plt.ion()
plt.figure(1)
t_list = []
result_list = []
t = 0
 
for i in range(10):
    t =1
#    t_list.append(t)
#    result_list.append(t)
    plt.plot(i,t,c='r',ls='-', marker='o', mec='r',mfc='w')  ## 保存历史数据
       #plt.plot(t, np.sin(t), 'o')
    plt.legend()
    plt.pause(0.1)
#    if t >= 10 * np.pi:
 #       plt.clf()
  #      t = 0
   #     t_list.clear()
    #    result_list.clear()
    #else:
    
plt.show()





