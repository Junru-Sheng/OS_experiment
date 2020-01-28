# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import matplotlib.pyplot as plt,time
import numpy as np

# 绘制普通图像
scan=[]


with open(r"SCAN.txt","r") as f2:
    data2=f2.readlines()

for line in data2:
    scan.append(int(line.split()[0]))
#X轴，Y轴数据 
#plt.figure(figsize=(10,6)) #创建绘图对象 
for i in range(12):
    
    plt.ion()
    plt.clf()
 #   X, =plt.plot(sstf[:i+1],list(range(1, len(sstf[:i+1]) + 1)),"b*-",linewidth=1)  #在当前绘图对象绘图（X轴，Y轴，线类型，线宽度） 
    X=plt.plot(scan[:i+1],list(range(1, len(scan[:i+1]) + 1)),"ro-",linewidth=1)
    
    #time.sleep(1)
    plt.xlabel("disk_sequence") #X轴标签 
    plt.ylabel("time") #Y轴标签 
    plt.title("disk_schedule",fontsize='large',fontweight='bold',color='blue') #图标题 
    plt.legend(X,  'scan')
#    plt.legend([X, Y], ['sstf', 'scan'])
    plt.pause(0.5)
      #  plt.figure()
#    plt.show() #显示图 
    plt.ioff()
    