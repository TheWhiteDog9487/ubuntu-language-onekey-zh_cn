# 一键切换Ubuntu系统到简体中文
## 这个程序有且仅在Ubuntu系统上测试过，18.04及以上应该都不会有问题，非Debian系列应该都用不了  

***

## 编程语言
C++  
原本shell那个版本已经被彻底淘汰了，因为我从头到尾就不会bash，用cpp还能做更多设置  
***

## 使用方法
确保已经安装wget或者有其他方法可以传输文件  
```shell
apt update && apt install -y wget
```
***
下载程序
```shell
wget https://raw.githubusercontent.com/TheWhiteDog9487/ubuntu-language-onekey-zh_cn/main/language
```
运行程序
```shell
sudo chmod o+x language
sudo ./language
```