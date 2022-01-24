apt update
apt install -y language-pack-zh-hans
locale-gen zh_CN.UTF-8
mv /etc/default/locale /etc/default/locale.backup
touch /etc/default/locale
echo LANG="zh_CN.UTF-8" > /etc/default/locale
reboot