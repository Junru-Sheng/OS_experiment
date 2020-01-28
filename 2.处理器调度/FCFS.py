# -*- coding: utf-8 -*-
"""
Created on Tue Jun 11 19:33:17 2019

@author: 君如
"""

from tkinter import *
import numpy as np
import matplotlib.pyplot as plt
import time
FCFS=[]

btn=[]
btn0=[]
btnd=[]
with open(r"FCFS.txt","r") as f1:
    data1=f1.readlines()
for line in data1:
    FCFS.append(line.split()[0])

root = Tk()
root.title("电计1604班盛君如的<FCFS>")
a = LabelFrame(root, height=800, width=900,text='FCFS_Schedule')
a.pack(side='top', fill='both', expand=True)

sb = Scrollbar(root)    #垂直滚动条组件
sb.pack(side=RIGHT,fill=Y)  #设置垂直滚动条显示的位置
listb=Listbox(root,yscrollcommand=sb.set)    #Listbox组件添加Scrollbar组件的set()方法
 
listb = Listbox(root)
for item in FCFS:                 # 第一个小部件插入数据
    listb.insert(END,item)

len_fcfs=len(FCFS)
for i in range(0,len_fcfs):
    btnn=Button(a, text=i,heigh=3,width=5)
    btnn.grid(row=0, column=i)
    btn0.append(btnn)

for i in range(0,len_fcfs):
    btna=Button(a, text=i,heigh=3,width=5,fg='red')
    btna.grid(row=1, column=i)
    btnd.append(btna)
  
def Btn():    
    for i in range(0,len_fcfs):
        if FCFS[i]=='A':
            btn1=Button(a, text=FCFS[i],heigh=3,width=5,bg='wheat')
        elif FCFS[i]=='B':
            btn1=Button(a, text=FCFS[i],heigh=3,width=5,bg='purple')
        elif FCFS[i]=='C':
            btn1=Button(a, text=FCFS[i],heigh=3,width=5,bg='blue')
        elif FCFS[i]=='D':
            btn1=Button(a, text=FCFS[i],heigh=3,width=5,bg='gray')
        elif FCFS[i]=='E':
            btn1=Button(a, text=FCFS[i],heigh=3,width=5,bg='cyan')
  #      btn1=Button(a, text=FCFS[i],heigh=3,width=5)
        btn1.grid(row=1, column=i)
        btn1.update()
        btn.append(btn1)
        time.sleep(0.5)
        #btn[i].update()
        
        #btn[i].update()
    #    time.sleep(1.0)
     #   root.mainloop()
#root.update_idletasks()      
btns=Button(a, text="FCFS",heigh=3,width=5,fg='red',bg='yellow',command=Btn)
btns.grid(row=4, column=9)
#btn.pack()
listb.pack(fill=BOTH)
sb.config(command=listb.yview)
root.mainloop()

 