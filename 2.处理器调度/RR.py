# -*- coding: utf-8 -*-
"""
Created on Tue Jun 11 21:11:12 2019

@author: 君如
"""


from tkinter import *
import numpy as np
import matplotlib.pyplot as plt
import time

RR=[]
btn=[]
btnd=[]
btn0=[]
with open(r"RR.txt","r") as f1:
    data1=f1.readlines()
for line in data1:
    RR.append(line.split()[0])

root = Tk()
root.title("电计1604班盛君如的<RR>")
a = LabelFrame(root, height=800, width=900,text='RR_Schedule')
a.pack(side='top', fill='both', expand=True)

sb = Scrollbar(root)    #垂直滚动条组件
sb.pack(side=RIGHT,fill=Y)  #设置垂直滚动条显示的位置
listb=Listbox(root,yscrollcommand=sb.set)    #Listbox组件添加Scrollbar组件的set()方法
 
listb = Listbox(root)
for item in RR:                 # 第一个小部件插入数据
    listb.insert(END,item)

len_RR=len(RR)
for i in range(0,len_RR):
    btnn=Button(a, text=i,heigh=3,width=5)
    btnn.grid(row=0, column=i)
    btn0.append(btnn)

for i in range(0,len_RR):
    btna=Button(a, text=i,heigh=3,width=5,fg='red')
    btna.grid(row=1, column=i)
    btnd.append(btna)


def Btn():    
    for i in range(0,len_RR):
        if RR[i]=='A':
            btn1=Button(a, text=RR[i],heigh=3,width=5,bg='wheat')
        elif RR[i]=='B':
            btn1=Button(a, text=RR[i],heigh=3,width=5,bg='purple')
        elif RR[i]=='C':
            btn1=Button(a, text=RR[i],heigh=3,width=5,bg='blue')
        elif RR[i]=='D':
            btn1=Button(a, text=RR[i],heigh=3,width=5,bg='gray')
        elif RR[i]=='E':
            btn1=Button(a, text=RR[i],heigh=3,width=5,bg='cyan')
  #      btn1=Button(a, text=RR[i],heigh=3,width=5)
        btn1.grid(row=1, column=i)
        btn1.update()
        btn.append(btn1)
        time.sleep(0.5)    

        
btns=Button(a, text="RR",heigh=3,width=5,fg='red',bg='yellow',command=Btn)
btns.grid(row=4, column=9)
#btn.pack()
listb.pack(fill=BOTH)
sb.config(command=listb.yview)
root.mainloop()
