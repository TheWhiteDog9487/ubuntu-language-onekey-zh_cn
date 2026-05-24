# 一键切换Ubuntu(和Debian)系统到简体中文
## 测试通过的系统
### **x86_64：**
|系统名称|版本|
|-|-|
|Debian|13.2 <br/> 11.6|
|Ubuntu|26.04 LTS <br/> 25.04 <br/> 24.10 <br/> 24.04.1 LTS <br/> 22.04 LTS <br/> 20.04 LTS|

### **aarch64：**
|系统名称|版本|
|-|-|
|Debian|11.5|

## 使用方法
### **x86_64：**
```shell
sudo -E su
# 如果是WSL环境必须使用-E参数保留环境变量，否则权限提升之后WSL_DISTRO_NAME会消失
# 如果不是WSL，可以不加这个参数，只提权就好
apt update && apt install -y wget
wget https://github.com/TheWhiteDog9487/ubuntu-language-onekey-zh_cn/releases/latest/download/language
chmod +x language
./language
```
### **aarch64：**
```shell
sudo -E su
# 如果是WSL环境必须使用-E参数保留环境变量，否则权限提升之后WSL_DISTRO_NAME会消失
# 如果不是WSL，可以不加这个参数，只提权就好
apt update && apt install -y wget
wget https://github.com/TheWhiteDog9487/ubuntu-language-onekey-zh_cn/releases/latest/download/language_arm
chmod +x language_arm
./language_arm
```
