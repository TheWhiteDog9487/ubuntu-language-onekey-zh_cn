# 一键切换Ubuntu(和Debian)系统到简体中文
## 测试通过的系统
|系统名称|版本|
|-|-|
|Debian|11.6.0|
|Ubuntu|22.04 LTS 20.04 LTS|

## 使用方法
确保已经安装wget或者有其他方法可以传输文件  
```shell
apt update && apt install -y wget
```

下载程序
```shell
wget https://raw.githubusercontent.com/TheWhiteDog9487/ubuntu-language-onekey-zh_cn/main/language
```
运行程序
```shell
sudo chmod o+x language
sudo ./language
```

## 提示
这个程序现在只适配了Debian和Ubuntu的x86版本，ARM架构和采用这两个系统作为底板的下游分支可用性未知。  
短时间内我无法适配ARM架构，我根本就没这个设备。  
如果你需要，可以尝试修改源代码之后自行构建。  
