# 一键切换Ubuntu(和Debian)系统到简体中文
## 测试通过的系统
### **x86_64：**
|系统名称|版本|
|-|-|
|Debian|11.6.0|
|Ubuntu|22.04 LTS 20.04 LTS|

### **aarch64：**
|系统名称|版本|
|-|-|
|Debian|11.5|

## 使用方法
确保已经安装wget或者有其他方法可以传输文件  
```shell
apt update && apt install -y wget
```

下载程序
### **x86_64：**
```shell
wget https://raw.githubusercontent.com/TheWhiteDog9487/ubuntu-language-onekey-zh_cn/main/language
```
### **aarch64：**
```shell
wget https://raw.githubusercontent.com/TheWhiteDog9487/ubuntu-language-onekey-zh_cn/main/language_arm
```

运行程序
```shell
sudo chmod u+x language
sudo ./language
```