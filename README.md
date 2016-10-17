# Discreption
iNode for Mac 
Mac下兼容iNode的H3C8021x认证命令行客户端。

#Usage
>方便食用请将程序放置在系统环境变量指定的目录下`echo $PATH`。  
>请务必以管理员权限运行！！
>添加可执行权限 `sudo chmod +x RealNode`。  
>于系统报告中确认自己的认证网卡，Mac下一般以en开头，老款有网线接口的MacBookPro一般为en0，新款需要转换头的MacBookPro en0默认为无线网卡，请细心甄别。

![](http://ww3.sinaimg.cn/large/801b780agw1f8n7vnc9r4j21by0z4449.jpg)

* 前台运行(终端不可关闭) `sudo RealNode username password interface`
* 后台运行 `nohup sudo RealNode username password interface >${HOME}/RealNode.log 2>&1`
![](http://ww1.sinaimg.cn/large/801b780agw1f8n7vnd49ng21040rw0we.gif)

* * 检查日志请 `tail -f ${HOME}/RealNode.log`

#Get Application
请于release中获取最新可执行文件。

#Build From Source
### Dependence
Xcode >3.2  

libpcap

`git clone https://github.com/megachweng/RealNode.git`

#Thanks To

liuqun : https://github.com/liuqun/njit8021xclient/
