#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

auto check() {
    cout << "请输入您的选项（输入y或者yes继续）";
    string userin;
    cin >> userin;
    if (userin == "y" or userin == "yes")
        return;
    else
        cout << "输入不正确欸，如果想停止本程序的话请按下Ctrl+C" << endl;
        check();}

int main(){
    cout << "提示：本程序需要root权限，如果您不是以root运行的本程序，请Ctrl+C终止并重新提权运行" << endl;
    cout << "如果确认权限没有问题，请输入y或者yes";
    check();
    cout << "即将开始安装并配置简体中文语言包，请输入y或者yes继续，或者按Ctrl+C终止本程序";
    check();
    system("apt install -y language-pack-zh-hans");
    system("locale-gen zh_CN.UTF-8");
    system("mv /etc/default/locale /etc/default/locale.backup");
    system("touch /etc/default/locale");
    system("echo LANG=\"zh_CN.UTF-8\" > /etc/default/locale");
    system("echo LANGUAGE=\"zh_CN:zh\" > /etc/default/locale");
    cout << "原/etc/default/locale已经备份为/etc/default/locale.backup" << endl;
    cout << "即将重启以应用语言设置，请保存您未完成的工作以防数据丢失" << endl;
    cout << "输入y或者yes重启或者按Ctrl+C终止本程序" << endl;
    check();
    system("reboot");}