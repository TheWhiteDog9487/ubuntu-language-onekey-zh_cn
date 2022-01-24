# 一键切换Ubuntu系统到简体中文
## 两个版本
1.C++  
2.纯Shell  
## 不同版本区别
这两个版本的唯一区别就是运行方式不一样，功能和结构没有任何区别  
不信你可以去看源代码，C++版本我只是用了system函数执行shell语句，效果不能说天差地别吧，至少也能说是一模一样
***
## 使用方法
# **注意！程序运行完之后会自动重启目标电脑/服务器，请确保没有未保存的工作！否则后果自负！**
确保已经安装wget或者有其他方法可以传输文件  
```shell
apt update && apt install -y wget
```
***
下面两个版本选一个就行
***
下载程序(Shell)
```shell
wget
```
下载程序(C++)
```shell
wget
```
运行程序(Shell)
```shell
sudo bash language.sh
```
运行程序(C++)
```shell
sudo chmod o+x language
sudo ./language
```