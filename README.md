# msp430
msp430 USB-Debug-Interface  MSP-FET430UIF安装及相关问题解决

//==============================2016.6.24======================================//

MSP430 USB-Debug-Interface MSP-FET430UIF安装
初次安装，接入USB口，打开串口管理器，找到IAR版本下的相关驱动安装添加即可。注意	IAR版本和仿真器版本一定要一致。

错误更新固件口的还原办法：
卸载错误和已有的驱动，拔插USB插口，出现其他设备，选择右键更新驱动，浏览本地的高版本USB_CDC证书，就可以识别到新仿真器口，再使用V32V2降固件dot，按照步骤等待，拔插后重新更新IAR对应的固件，等待完成，期间分别重新写入了FIREMAN和***文件
首次DEBUG，会要求更新固件，若版本正确则确定，等待后成功。版本过高则取消。
