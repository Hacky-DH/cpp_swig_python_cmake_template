#/bin/bash
set -e

version=$1
[ -z $version ] && version="0.0.1"

echo "hello version $version"

cwd=$(cd $(dirname $0); pwd)
pushd $cwd > /dev/null

#build
mkdir -p build
pushd build > /dev/null
cmake -DCMAKE_INSTALL_PREFIX=/hello .. && make
popd > /dev/null

#install
buildroot=tarball_build
/bin/rm -fr $buildroot
mkdir -p $buildroot
pushd build > /dev/null
make DESTDIR=$cwd/$buildroot install
popd > /dev/null
rootdir=$cwd/$buildroot/hello
/bin/cp -af bin python/hello.py install.sh $rootdir
pushd $rootdir > /dev/null
/bin/rm -fr include
/bin/ln -srf bin/hello bin/ho
/bin/chmod 0755 bin/* install.sh
popd > /dev/null

tarball="$cwd/hello-$version.tar.gz"
pushd $buildroot > /dev/null
tar -czf $tarball hello
mv $tarball $cwd
popd > /dev/null
/bin/rm -fr $buildroot

echo "build $tarball done"
