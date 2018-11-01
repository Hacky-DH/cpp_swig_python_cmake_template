#/bin/bash
set -e

prog="hello"
cwd=$(cd $(dirname $0); pwd)
pushd $cwd > /dev/null

sed -i "s#@INSTALL_PATH@#$cwd#" ${prog}.py
sed -i "s#@INSTALL_PATH@#$cwd#" bin/${prog}

if [[ $(whoami) == "root" ]];then
    ln -rsf bin/* /usr/bin/
else
    mkdir -p $HOME/bin
    ln -rsf bin/* $HOME/bin/
fi

echo "install ${prog} DONE"

