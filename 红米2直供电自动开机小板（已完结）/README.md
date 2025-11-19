概述
 

红米2供电、上电自动开机、OTG三合一小板。提供10~28V宽电压输入支持。

有使用XH2.54线供电，使用typeC数据线，直接使用USB数据线输出供电三种供电方案

更新了usb2.0拓展坞功能，拓展坞具备3A独立供电，可以向外围器件供电。

购买现成的DC-DC模块直接焊接在主板的对应区域

也可以买元件焊接在DCDC区域的焊盘上，这样看起来更美观

关于如何实现与手机的连接
 

有两种方案实现与手机的数据连接，兼容不同的动手能力！

使用BTB排线座子
将手机后壳取下，从底部副板中取出排线，将排线扣接在HUB上。
<img width="362" height="322" alt="W6b2am8ESxUPhJ6nvjLnsdYkt6LVbEkM4NaFBx0i" src="https://github.com/user-attachments/assets/93a7f5df-1dd1-4a8b-83f8-9f8b03f6d5c8" />
![Nhmk8deQBCwPfOqhLb9IUkVmuN1LgUssjts3Dvcg](https://github.com/user-attachments/assets/e7fce629-f7b5-4bbe-b70b-7392056fb5b2)
<img width="441" height="370" alt="UR8C5kH8zJ4LtWdXPkZIIk07xr7J88t8bGhskoOn" src="https://github.com/user-attachments/assets/53c8719b-ad8a-4336-bca7-84cb857905c1" />



通过板上开关选择功能，HUB代表作为上位机连接从机使用，Flash代表作为从机使用，可利用TypeC接口连接电脑，使用刷机或者ADB功能。

 

关于接口
 

板载4个全功能USB接口，可以实现多下位机控制，挂载U盘，连接USB摄像头，连接rp2040的振动补偿传感器等功能。

设计了与大鱼DIY的小政系列主板连接的专用接口，使用该接口时请空置usb4。

<img width="454" height="448" alt="yGlcxAovRFOcIWI12XmXMkWitlnj0KMtyH53G5l9" src="https://github.com/user-attachments/assets/9b2d2d8d-5922-4f42-ae70-75d58fd5b036" />


 

关于电池加密芯片
从手机原装电池中拆解出电池保护板焊接到该供电主板的上方是最常用的方案。但是拆解电池很容易损坏电池保护板导致无法正常工作，此时可以将保护板上的通讯模块焊接在本电路板上方的副板对应的焊盘上，制作出可用的简易电池保护板。但是拆解电池具有危险性，废旧电芯也具有污染性，可以考虑支持作者，直接购买通讯模块使用。

<img width="555" height="291" alt="NrNDmImF5mXjikFUAp9fWkiJ4YgwIY0g3x7K0afz" src="https://github.com/user-attachments/assets/98c5f1c2-14b7-49b3-bf3c-52ab42b96491" />

原理图
<img width="1360" height="660" alt="616f653b50ee438fac089b5889a6062f" src="https://github.com/user-attachments/assets/e896d324-6276-494d-8fed-1d9e523f9d1d" />

PCB图

<img width="440" height="421" alt="4684dc5c323a4d40860cc06e66eb3875" src="https://github.com/user-attachments/assets/a665b76e-6e97-4b31-a308-2d2995ef0125" />
<img width="552" height="499" alt="edf26f016f49453c80174cf5e9527f3d" src="https://github.com/user-attachments/assets/261ca5cb-1285-4f70-b494-2a7a1202a424" />



