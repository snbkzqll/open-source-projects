更新日志
2024-06-06 首次发布

 

产品概述

1.基本的双向电压电流监测，能实时监测D+ D-电压，可通过读取PD报文监测当前使用的PD协议档位。

2.可进行PD与QC诱骗，包括QC2、QC3，PD3.0的FIX、PPS，PD3.1的EPR、AVS。

3.软件库仑计，可以计算充电的电量，创新性的使用不同电压档位对应不同电流积分倍率，对于使用电荷泵(现在主流手机快充方式）充电的设备容量计算更精准。

4.NTC监测采样电阻温度，实现采样电阻温飘校准。

5.本表带有几乎完全的PD逻辑抓包功能与常用PD数据包分析功能，可以监测充电器的PDO，实时显示当前申请的RDO，可以记录并显示通信过程中的每一个数据包，并对常用数据包进行存储解析。

6.可以进行Emarker模拟，不使用数据线即可直接诱骗充电器的5A电流、PD3.1协议。可以伪装线缆，通过伪装对应的私有线缆，可以不使用私有线缆即可使手机握手私有协议。

7.具有最高5M采样率采样纹波，可以调节多档采样率，通过FFT计算纹波幅值最高的频率，并绘制FFT频谱图大致看出频率分布。

8.可搭配HID底板实现独立供电，消除表自身供电的干扰。

9.可搭配开尔文测线板，实现对线阻的测量。

 

固件更新，翻车交流群：788013120

本表需收费注册激活，注册方式看群内公告

本表体积小巧，元件密度较大！！！请量力而行！！！

原理图详见硬创社开源连接https://x.jlc.com/platform/detail/0c3b391fe85f4ef8b20c6e9b307abc51

 

 

功能介绍

本项目为开源广场旧项目基于ESP32的USB电压电流表的迭代升级，重写框架与功能，旧项目免费使用，停止维护，无重大BUG不再更新。新项目含有注册机制，需要收费注册。

旧项目开源链接：https://oshwhub.com/qaxslk/dai-PD-QCyou-pian-jian-ce-yi-ji-

旧项目的功能全部保留，包括基本的电压电流采样，PD、QC与米私有诱骗，PD抓包，Emarker读取，软件库仑计等，并在多方面优化，使运行效率更好，操作逻辑更顺手，兼容性更好。

与旧项目相比，本项目目前新增功能：

1.Emarker模拟，可单表诱骗或伪装私有线缆

2.纹波，最高5M采样

3.伪四线开尔文测线阻，需搭配开尔文测线板

4.独立供电，需搭配HID底板

5.PD3.1 EPR/AVS诱骗

6.C口充电器的QC协议诱骗

7.充电全程大致曲线

目前优化方面：

1.屏幕居中，长度变短，宽度不变

2.启动速度加快，PD协议识别与抓包更准确

3.重写诱骗逻辑，兼容性更好

4.PD监听抓包数量提升，显示更直观

5.Emarker读取新增厂商

6.取消独立诱骗按键，与三个主按键复用

7.优化电流路径，发热略有降低

8.更换阴间封装，制作难度降低

9.元器件成本在淘宝比较靠谱的商家买大概24，在立创商城买预计50左右

主界面

<img width="256" height="169" alt="191811f0f57646388272308c2ad91d0e" src="https://github.com/user-attachments/assets/c03721fa-d130-40ac-b58d-b7544a739962" />

PD诱骗界面

<img width="381" height="286" alt="5d1b15e01639405a86798604e3510036" src="https://github.com/user-attachments/assets/084dbdee-6a7e-4405-81a1-791f80671769" />

PPS诱骗界面

<img width="324" height="140" alt="3847d11fee4a4791a0f1c95c5e752dbc" src="https://github.com/user-attachments/assets/7c733ddb-1fb0-46b6-aaea-b192e744c280" />


纹波界面

<img width="436" height="208" alt="75e7315483424876ae6559e752dc61ee" src="https://github.com/user-attachments/assets/f27a8862-2c7b-409f-9a9a-52c79331bfb1" />


Emarker测试界面

<img width="443" height="196" alt="99f11d3bb5e34fafbe2cbf1ad92c339e" src="https://github.com/user-attachments/assets/83f8092d-5056-46ad-bf73-2d2ef430107c" />


开尔文测线界面

<img width="435" height="193" alt="df04fbc5b96049278965bfcc9a33c2ce" src="https://github.com/user-attachments/assets/77abec14-cd76-49f3-a39c-38ba76521d58" />


上位机界面（目前仅有OTA与注册功能）

<img width="522" height="581" alt="7b6d5fd9ec634d38ba7e5cd7b2b72821" src="https://github.com/user-attachments/assets/5588a304-812d-42a6-9991-d16814f88210" />



详细功能演示见底部视频

 

 

产品参数

1.电压测量范围3.8~36V(无独立供电),0~36V(有独立供电)

2.电流测量范围±0~6A(长时间),16A MAX（短时间）

3.PCB尺寸4.02CM*1.61CM

4.电压精度±4mV

5.电流精度±5mA(需校准）

6.线阻测量精度±1mΩ

7.电压分辨率0.001V

8.电流分辨率0.0005A

9.纹波采样率：125Khz~5Mhz

10.支持协议：标准PD,米私有PD,QC

 

附焊接对照图

<img width="1189" height="599" alt="ccf53a25113247d79534a731017f41fe" src="https://github.com/user-attachments/assets/eecceb60-c3c3-4f31-b148-5ab9486535d2" />


 

 

使用说明

1.关于制作：附件中有详细的配图制作说明书，说明书中有部分常见问题排查指南

2.关于使用：附件中有详细的使用说明书，包括界面参数解释，操作逻辑等

3.母头输入不包含表自身功耗，用于测量手机、充电宝等的输入功率，公头输入包含表自身功耗(约0.11W），用于测量充电头的输出功率



 

 

BOM清单

主板BOM

<img width="1317" height="720" alt="ae12b2e9c9e14492be22e141e15d238c" src="https://github.com/user-attachments/assets/6e4870ff-c7d7-4492-90ee-763c67c57fa2" />


HID底板BOM

<img width="930" height="177" alt="66fd5cec6e7f408ab616174428e919d5" src="https://github.com/user-attachments/assets/60027d7a-a913-46f7-b995-8af4c375574b" />


开尔文内阻测试仪BOM

<img width="913" height="197" alt="763fc42b18f04d4487d94a09dac1b89e" src="https://github.com/user-attachments/assets/0e46caaa-1fae-4f48-a5b3-0329e78d8743" />
