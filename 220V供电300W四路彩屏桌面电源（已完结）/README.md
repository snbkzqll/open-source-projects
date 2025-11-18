桌面电源目前已更新为300W四路输出的3.0版彩屏版，想复刻的朋友欢迎加入QQ群 795986316 下载最新开源文件。

B站视频连接：（高颜值）220V供电300W四路彩屏桌面电源

 

300W彩屏版主机外观

玫瑰粉
![a4baf334414849b6b5c4b13256b064d2](https://github.com/user-attachments/assets/cf77cd05-99ca-46b8-a599-259fb3540258)



 

翡翠绿

![574c30c3888748b7bc3f3ae7f1d6d7b0](https://github.com/user-attachments/assets/b71b1b80-fc2a-4494-865b-9d7860e1a1f5)


 

耀星黑

![57b0a25ef39b418086c923d9b1cfff24](https://github.com/user-attachments/assets/be781d28-55a3-4e93-ad4b-8a215565b63c)


 

湖蓝色

![2a82afe49f6346bfa17aaa27181a24c4](https://github.com/user-attachments/assets/3893adee-df76-49f4-b047-74f504c45cac)


 

四路独立显示及固件更新提示

![049132c6d0d34f6a8c037b970f01d41b](https://github.com/user-attachments/assets/cd885d12-a03b-4eb5-9c75-7fdc853ecfa9)


 

OTA远程升级固件

![152d9290d3cf4379b6f0e44fba764fa6](https://github.com/user-attachments/assets/31fb460e-6562-498b-9de3-82642c5c54ec)


 
手机小程序设备管理界面（不仅可以通过蓝牙查看四路输出口的电压、电流、功率和充电时长，还能进行多种功能的设置）

![8affaed3e1f14c9da9585e1fbdada087](https://github.com/user-attachments/assets/9c3ffb73-b293-4620-abcc-ccdff3ededd5)

![8affaed3e1f14c9da9585e1fbdada087](https://github.com/user-attachments/assets/1918f173-afcc-4fd5-bb09-e13c6474f15e)

 

最新300W四路彩屏桌面电源实物图，内置24V12.5A 300W超薄小体积PFC开关电源模块，性能更好，功率更大。

![b4e94f8c65c2423db883a23f981e7e8d](https://github.com/user-attachments/assets/17a4b9d4-3955-48e3-951b-db9653bc27c4)


 

 

项目简介
 

本电源外形小巧美观，内置优质大功率AC-DC开关电源模块，不仅可以为笔记本、手机等电子设备提供三路快充电源，它还设置有独立的DC输出插口，方便为直流焊台、数控可调电源、直流加热台等等其它工具，提供稳定可靠的大功率直流电源，用途非常广泛，值得拥有！

先看看样机的美图吧，喜欢再继续往下看。

 
![18ddb80bf2554fb39e87af37a761c853](https://github.com/user-attachments/assets/28fe8ac3-9185-456e-9098-21ee4538ba6b)



 

 ![3246a113232041bba166eaedea0204c7](https://github.com/user-attachments/assets/abc304d4-f320-4617-831a-6ebd341d91ee)



 

项目功能
本机已内置标准尺寸的小体积开关电源模块，设置了独立的DC输出插口，可为其它电子设备或工具，提供稳定的直流电源供给。

本机支持USB CCA三路快充输出，可以给笔记本，手机等电子设备提供大功率多协议的快充功能。

有电源指示灯和两路快充指示灯，方便了解其工作状态。

 

 
开源协议
CC-BY-NC-SA 4.0

转载时请注明原文作者及链接。

 

项目属性
本项目为首次公开，为本人原创项目。项目未曾在别的比赛中获奖。

 

 

项目参数

主板的快充电路采用了智融科技的SW3538和SW3526两种快充芯片。

SW3538
SW3538S是一款高集成度的多快充协议双口充电芯片，支持 A+C 口任意口快充输出，支持双口独立限流。其集成了 7A 高效率同步降压变换器，支持 PPS/ PD/ QC/ AFC/ FCP/ SCP/ PE/SFCP/TFCP/VOOC 等多种快充协议，最大支持 140W 输出功率，集成 CC/CV 模式、双口管理逻辑等功能。

输出电流高达7A， 输入电压范围 5~36V，支持 CC/CV 模式，支持线损补偿，支持温度控制。
 
快充协议：
支持 PPS/PD3.0/PD2.0
支持 QC5/QC4+/QC3+/QC3.0/QC2.0
支持 AFC
支持 FCP
支持 高低压 SCP
支持 PE2.0/PE1.1
支持 SFCP TFCP VOOC
支持 BC1.2 DCP 模式
支持苹果/三星大电流充电模式
具备软启动/输入过压/欠压保护/输出过流/短路保护，以及DP/DM/CC过压/弱短路保护/芯片过温保护 等多种保护功能
 
SW3526
SW3526S 是一款高集成度的多快充协议充电芯片，支持 C 口或 A 口输出，其集成了 3.5A 高效率同步降压变换器，支持 PPS/PD/QC/AFC/FCP/SCP/PE/SFCP 等多种快充协议以及 CC/CV 模式，最大输出功率65W。

输出电流高达 3.5A， 输入电压范围 6~30V，支持 CC/CV 模式，支持线损补偿
 
快充协议：
支持 PPS/PD3.0/PD2.0
支持 QC4+/QC4/QC3.0/QC2.0
支持 AFC
支持 FCP
支持 低压/高压 SCP
支持 PE2.0/PE1.1
支持 SFCP
支持 BC1.2 DCP 模式
支持苹果/三星模式
具备软启动/输入过压保护/输入欠压保护/输出过流保护/输出短路保护/过温保护功能

 

 

设计原理
作者根据自身的制作经验，在不影响SW3538全部功能的基础上，对官方电路进行了部分优化，仅使用了2只MOS管，来完成SW3538路的二路功率输出，不仅大大缩小了线路板所需的面积，而且经过实测，整机的效率更高，温升更低。在主板没有增加任何辅助散热装置的条件下，可提供稳定的100W功率输出，表现优秀。

 

主板采用4层板设计，经过反复对比验证，电感使用了大电流磁环线绕电感，使其有充分的散热空间。电路设计和器件选型在经过多次调整和优化后，目前大电流输出状态下，温升最高的不是芯片、MOS管和电感，而是成品的电源模块，但因为使用的铝机壳有一定的辅助散热效果，所以在实际使用中，尚未发现电源有过热保护的现象。如果需要长时间大功率工作，可自行按照电源手册的要求增加散热风扇。

 

因为SW3538和SW3526都属于降压芯片，所以输入电压需要高于输出电压，推荐使用输出电压为DC 24V的电源模块。

 

 

整机电路图

 ![026b69eb967841528f18515f77130c32](https://github.com/user-attachments/assets/6a0da05b-d98e-4715-9fc6-af07d12da7a5)




 

 

3D预览图

![ea80268bf49841fd9266044ee29d2cd5](https://github.com/user-attachments/assets/14787264-0b75-4fbd-9362-8da7f9b35930)


 

 

正面布局图

 
![a3fbcbca2e25455eb4462c38c9fa271c](https://github.com/user-attachments/assets/80b2c4d1-171c-49dc-84a1-ec87f0ff64bb)



 

 

实物外形图

 
![9c4b0baeb9ed44e4b7b5113d7f847939](https://github.com/user-attachments/assets/5d157060-ed71-473d-985d-3618acad339f)

![98faa08faa0846108579a893d1893508](https://github.com/user-attachments/assets/5688ef24-f4c2-4751-b999-91b82059911e)


 



 

图示机壳采用了嘉立创FA商城里销售的8838x130mm 铝型材机壳，做工优良散热好，关键每月还有优惠券，推荐购买。网购的8838*130同型号外壳内部高度会稍低一点，安装电源模块时需要从下往上安装，并对底部金属机壳做绝缘处理。

图中样机的面板和背板为作者自行设计，使用嘉立创免费券打的黑色沉金和丝印PCB板，在附件里作者也提供了面板和背板的打板文件，喜欢的朋友可以免费打板。

 

内部接线图

（两台样机分别安装的是中逸光150W和金升阳225W 同标准安装尺寸的电源模块，当前发布的开源版本已对布局和走线做了再次优化，更加美观合理)

![472a86de0e0447fca424440a1657dd0f](https://github.com/user-attachments/assets/59df7304-a0d8-4558-9395-31d402016ddd)


 

140W 输出功率测试

![b18b2d60b2e7463892e627cbca3ec977](https://github.com/user-attachments/assets/349a5ff1-2c57-499a-876e-eac9474739b9)


 

SW3538 PDO报文

![afcc564f78df4811884f9d4236cb411a](https://github.com/user-attachments/assets/42496577-f799-49bd-bc47-3909b068d5cb)

 

SW3526 PDO报文
 

![66f569a024e440da9f6d52838f2cd459](https://github.com/user-attachments/assets/ec1e8a42-456e-4185-bd03-7774e19bdb17)


 

纹波简单测试


![fc7a7485f19649ec946ca1d7e0eefaec](https://github.com/user-attachments/assets/41e9d68e-c96c-4c10-81d9-2dfd22098455)

 
 

其它事项：
 

附件中提供了本项目2.0和3.0版本的包括电路原理图，PCB打板文件，器件采购BOM单 等资料，更多资料请加群下载。
作者自行设计的面板和背板的打板文件也分享到了附件里可以直接在嘉立创免费打板。
想复刻的朋友欢迎加入QQ群 795986316 ，不仅能及时下载最新版本的制作文件和群友们交流制作心得，还能查看作者的其它开源作品。
     

      经过作者对基本参数的测试和实际使用，样机各方面都达到了设计目标，使用效果非常不错，不仅支持更多快充协议，大电流工作时比氮化镓充电头也更稳定。花费不到百元就能复刻一台这么漂亮的大功率桌面快充电源，不仅有多口快充功能，还有150W 24V的直流电源输出，最重要的是看到它就会有慢慢的成就感！这不比花一两百买个充电头香吗？

 

      如您喜欢本项目设计，请您在下方收藏本文，并请为它点赞，以鼓励作者今后为大家奉献更多更好的作品。如果喜欢的人多，作者后续还会陆续发布与桌面电源配套的一些作品，如果您有兴趣为避免迷路，可以加入讨论群和关注作者。

 
