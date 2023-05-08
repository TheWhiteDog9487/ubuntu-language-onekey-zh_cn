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
### **x86_64：**
```shell
apt update && apt install -y wget
wget https://raw.githubusercontent.com/TheWhiteDog9487/ubuntu-language-onekey-zh_cn/main/language
sudo chmod u+x language
sudo ./language
```
### **aarch64：**
```shell
apt update && apt install -y wget
wget https://raw.githubusercontent.com/TheWhiteDog9487/ubuntu-language-onekey-zh_cn/main/language_arm
sudo chmod u+x language_arm
sudo ./language_arm
```
