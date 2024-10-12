#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
using namespace std;

auto LOCALE = R"(
LANG="zh_CN.UTF-8"
LANGUAGE="zh_CN:zh:en_US:en"
LC_NUMERIC="zh_CN.UTF-8"
LC_TIME="zh_CN.UTF-8"
LC_MONETARY="zh_CN.UTF-8"
LC_PAPER="zh_CN.UTF-8"
LC_IDENTIFICATION="zh_CN.UTF-8"
LC_NAME="zh_CN.UTF-8"
LC_ADDRESS="zh_CN.UTF-8"
LC_TELEPHONE="zh_CN.UTF-8"
LC_MEASUREMENT="zh_CN.UTF-8"
LC_ALL=zh_CN.UTF-8
)"s;

string get_linux_distro_name() {
    // ChatGPT
    string distro_name = "";
    ifstream release_file("/etc/os-release");
    if (release_file.is_open()) {
        string line = "";
        while (getline(release_file, line)) {
            if (line.find("PRETTY_NAME=") != string::npos) {
                distro_name = line.substr(line.find("=") + 1);
                distro_name.erase(0, 1); // remove opening quote
                distro_name.erase(distro_name.size() - 1); // remove closing quote
                break;}}
        release_file.close();}
    return distro_name;}

auto check() {
    cout << "请输入您的选项（输入y或者yes继续）";
    string userin = "";
    cin >> userin;
    if (userin == "y" or userin == "yes")
        return;
    else{
        cout << "输入不正确欸，如果想停止本程序的话请按下Ctrl+C" << endl;
        check();}}

auto Ubuntu(){
    cout << "提示：本程序需要root权限，如果您不是以root运行的本程序，请Ctrl+C终止并重新提权运行" << endl;
    cout << "如果确认权限没有问题，请输入y或者yes";
    check();
    cout << "即将开始安装并配置简体中文语言包，请输入y或者yes继续，或者按Ctrl+C终止本程序";
    check();
    system("apt install -y language-pack-zh-hans");
    system("locale-gen zh_CN.UTF-8");
    if ( filesystem::exists("/etc/locale.conf") ){
        filesystem::copy_file("/etc/locale.conf", "/etc/locale.conf.backup", filesystem::copy_options::update_existing);
        fstream locale_conf("/etc/locale.conf", ios::out | ios::trunc);
        locale_conf << LOCALE << endl;
        locale_conf.close();
        filesystem::permissions("/etc/locale.conf", filesystem::perms::owner_read | filesystem::perms::owner_write | filesystem::perms::group_read | filesystem::perms::others_read);
        cout << "原/etc/locale.conf已经备份为/etc/locale.conf.backup" << endl;}
    else if ( filesystem::exists("/etc/default/locale") ){
        filesystem::copy_file("/etc/default/locale", "/etc/default/locale.backup", filesystem::copy_options::update_existing);
        fstream locale("/etc/default/locale", ios::out | ios::trunc);
        locale << LOCALE << endl;
        locale.close();
        filesystem::permissions("/etc/default/locale", filesystem::perms::owner_read | filesystem::perms::owner_write | filesystem::perms::group_read | filesystem::perms::others_read);
        cout << "原/etc/default/locale已经备份为/etc/default/locale.backup" << endl;}
    cout << "即将重启以应用语言设置，请保存您未完成的工作以防数据丢失" << endl;
    cout << "输入y或者yes重启或者按Ctrl+C终止本程序" << endl;
    check();
    system("reboot");}

auto Debian(){
    cout << "提示：本程序需要root权限，如果您不是以root运行的本程序，请Ctrl+C终止并重新提权运行" << endl;
    cout << "如果确认权限没有问题，请输入y或者yes";
    check();
    filesystem::copy_file("/etc/locale.gen", "/etc/locale.gen.backup", filesystem::copy_options::update_existing);
    fstream locale_gen("/etc/locale.gen", ios::out | ios::trunc);
    locale_gen << "zh_CN.UTF-8 UTF-8" << endl;
    locale_gen.close();
    system("locale-gen");
    filesystem::permissions("/etc/locale.gen", filesystem::perms::owner_read | filesystem::perms::owner_write | filesystem::perms::group_read | filesystem::perms::others_read);
    if ( filesystem::exists("/etc/default/locale") ){
        filesystem::copy_file("/etc/default/locale", "/etc/default/locale.backup", filesystem::copy_options::update_existing);
        fstream locale("/etc/default/locale", ios::out | ios::trunc);
        locale << LOCALE << endl;
        locale.close();
        filesystem::permissions("/etc/default/locale", filesystem::perms::owner_read | filesystem::perms::owner_write | filesystem::perms::group_read | filesystem::perms::others_read);
        cout << "原/etc/default/locale已经备份为/etc/default/locale.backup" << endl;}
    cout << "原/etc/locale.gen已经备份为/etc/locale.gen.backup" << endl;
    cout << "即将重启以应用语言设置，请保存您未完成的工作以防数据丢失" << endl;
    cout << "输入y或者yes重启或者按Ctrl+C终止本程序" << endl;
    check();
    system("reboot");}

int main() {
    auto OS = [](){
        #pragma warning(suppress : 4996)
        if (getenv("OS") != nullptr){
            return "Windows";}
        #pragma warning(suppress : 4996)
        else if (getenv("HOME") != nullptr){
            return "Linux";}
        else{
            return "未知";}}();

	if (OS == "Windows"){
		cout << "Windows请在“设置”应用中调整语言(❁´◡`❁)。" << endl;
        exit(-1);}
    else if (OS == "Linux") {
        if (get_linux_distro_name().find("Ubuntu") != string::npos){
            cout << "检测到您使用的系统为：" << get_linux_distro_name() << endl;
            Ubuntu();}
        if (get_linux_distro_name().find("Debian") != string::npos){
            cout << "检测到您使用的系统为：" << get_linux_distro_name() << endl;
            Debian();}
        if (get_linux_distro_name().find("Armbian") != string::npos){
            cout << "检测到您使用的系统为：" << get_linux_distro_name() << endl;
            Debian();}
        else { exit(-1); }}
	else if (OS == "未知"){
        cout << "未知操作系统，为确保数据安全将会强制退出。"
            << endl 
            << "如果是误报，请联系作者修复问题。"
            << endl;
        exit(-1);}
}