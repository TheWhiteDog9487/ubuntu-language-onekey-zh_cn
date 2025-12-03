#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

#ifdef __linux__
#include <unistd.h>
#endif

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
LC_ALL="zh_CN.UTF-8"
)"s;

enum class System{
    WSL,
    Linux,
    Unsupported };
enum class User{
    Root,
    Other };

auto GetCurrentSystemType(){
        if (filesystem::exists("/proc/version")) {
        ifstream version_file("/proc/version");
        string version_info = "";
        getline(version_file, version_info);
        if (version_info.find("Microsoft") != string::npos or 
        version_info.find("WSL") != string::npos) {
            return System::WSL; }
        version_file.close(); }
    if (filesystem::exists("/proc/sys/kernel/osrelease")) {
        ifstream osrelease_file("/proc/sys/kernel/osrelease");
        string osrelease_info = "";
        getline(osrelease_file, osrelease_info);
        if (osrelease_info.find("Microsoft") != string::npos or
            osrelease_info.find("WSL") != string::npos) {
            return System::WSL; }
        osrelease_file.close(); }
    #pragma warning(suppress : 4996)
    if (getenv("WSL_DISTRO_NAME") != nullptr){
        return System::WSL; }
    #pragma warning(suppress : 4996)
    if (getenv("WSL_INTEROP") != nullptr){
        return System::WSL; }
    #pragma warning(suppress : 4996)
    else if (getenv("HOME") != nullptr){
        return System::Linux;}
    else{
        return System::Unsupported;} }

auto GetCurrentUser(){
    #pragma warning(suppress : 4996)
    if (getenv("USER") != nullptr){
        string user = getenv("USER");
        if (user == "root" or geteuid() == 0){
            return User::Root; }
        else{
            return User::Other; } }
    else{
        throw runtime_error("无法获取用户信息"); } }

/// @brief  获取当前系统的发行版名称
/// @return 发行版名称，带有版本号
/// @author ChatGPT
auto GetCurrentSystem() {
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

auto WSL(){
    cout << "开始更新语言配置" << endl;
    system("update-locale LANG=zh_CN.UTF-8");
    cout << "语言配置更新完成" << endl;
    cout << "更新语言配置需要重启WSL，要现在重启吗？" << endl;
    check();
    system("cmd.exe /c \"wsl --shutdown\""); }

auto Ubuntu(){
    cout << "即将开始安装并配置简体中文语言包，请输入y或者yes继续，或者按Ctrl+C终止本程序";
    check();
    system("apt install -y language-pack-zh-hans");
    system("locale-gen zh_CN.UTF-8");
    if ( filesystem::exists("/etc/locale.conf") ){
        filesystem::copy_file("/etc/locale.conf", "/etc/locale.conf.backup", filesystem::copy_options::overwrite_existing);
        fstream locale_conf("/etc/locale.conf", ios::out bitor ios::trunc);
        locale_conf << LOCALE << endl;
        locale_conf.close();
        filesystem::permissions("/etc/locale.conf", filesystem::perms::owner_read bitor filesystem::perms::owner_write bitor filesystem::perms::group_read bitor filesystem::perms::others_read);
        cout << "原/etc/locale.conf已经备份为/etc/locale.conf.backup" << endl;}
    else if ( filesystem::exists("/etc/default/locale") ){
        filesystem::copy_file("/etc/default/locale", "/etc/default/locale.backup", filesystem::copy_options::overwrite_existing);
        fstream locale("/etc/default/locale", ios::out bitor ios::trunc);
        locale << LOCALE << endl;
        locale.close();
        filesystem::permissions("/etc/default/locale", filesystem::perms::owner_read bitor filesystem::perms::owner_write bitor filesystem::perms::group_read bitor filesystem::perms::others_read);
        cout << "原/etc/default/locale已经备份为/etc/default/locale.backup" << endl;}
    cout << "即将重启以应用语言设置，请保存您未完成的工作以防数据丢失" << endl;
    cout << "输入y或者yes重启或者按Ctrl+C终止本程序" << endl;
    check();
    system("reboot");}

auto Debian(){
    filesystem::copy_file("/etc/locale.gen", "/etc/locale.gen.backup", filesystem::copy_options::overwrite_existing);
    fstream locale_gen("/etc/locale.gen", ios::out bitor ios::trunc);
    locale_gen << "zh_CN.UTF-8 UTF-8" << endl;
    locale_gen.close();
    system("locale-gen");
    filesystem::permissions("/etc/locale.gen", filesystem::perms::owner_read bitor filesystem::perms::owner_write bitor filesystem::perms::group_read bitor filesystem::perms::others_read);
    if ( filesystem::exists("/etc/default/locale") ){
        filesystem::copy_file("/etc/default/locale", "/etc/default/locale.backup", filesystem::copy_options::overwrite_existing);
        fstream locale("/etc/default/locale", ios::out bitor ios::trunc);
        locale << LOCALE << endl;
        locale.close();
        filesystem::permissions("/etc/default/locale", filesystem::perms::owner_read bitor filesystem::perms::owner_write bitor filesystem::perms::group_read bitor filesystem::perms::others_read);
        cout << "原/etc/default/locale已经备份为/etc/default/locale.backup" << endl;}
    cout << "原/etc/locale.gen已经备份为/etc/locale.gen.backup" << endl;
    cout << "即将重启以应用语言设置，请保存您未完成的工作以防数据丢失" << endl;
    cout << "输入y或者yes重启或者按Ctrl+C终止本程序" << endl;
    check();
    system("reboot");}

int main() {
    auto OSType = GetCurrentSystemType();
    if (OSType == System::WSL) {
        auto OS = GetCurrentSystem();
        cout << "检测到您使用的系统为：" << OS << endl;
        cout << "并且该系统工作于WSL环境" << endl;
        auto CurrentUser = GetCurrentUser();
        if (CurrentUser == User::Root){
            WSL(); }
        else{
            cout << "更改语言配置需要root权限，请使用sudo重新运行本程序" << endl;
            throw runtime_error("权限不足"); } }
    else if (OSType == System::Linux) {
        auto OS = GetCurrentSystem();
        cout << "检测到您使用的系统为：" << OS << endl;
        auto CurrentUser = GetCurrentUser();
        if (CurrentUser == User::Other){
            cout << "更改语言文件需要root权限，请使用sudo重新运行本程序" << endl;
            throw runtime_error("权限不足"); }
        if (OS.find("Ubuntu") != string::npos){
            Ubuntu(); }
        if (OS.find("Debian") != string::npos or
            OS.find("Armbian") != string::npos){
            Debian(); } }
    else if (OSType == System::Unsupported){
        cout << "未知操作系统，为确保数据安全将会强制退出。"
            << endl 
            << "如果是误报，请联系作者修复问题。"
            << endl;
        throw runtime_error("不支持的操作系统"); } }