#include <cstdlib>
using namespace std;
int main(){
    system("apt install -y language-pack-zh-hans");
    system("locale-gen zh_CN.UTF-8");
    system("mv /etc/default/locale /etc/default/locale.backup");
    system("touch /etc/default/locale");
    system("echo LANG=\"zh_CN.UTF-8\" > /etc/default/locale");
    system("reboot");}