#/bin/bash
set -e

version=$1
[ -z $version ] && version="0.0.1"

echo "hello version $version"

CMAKE=cmake
cmake3 --version > /dev/null 2>&1 && CMAKE=cmake3

cwd=$(cd $(dirname $0); pwd)
pushd $cwd > /dev/null

#build
mkdir -p build
pushd build > /dev/null
$CMAKE -DCMAKE_INSTALL_PREFIX=/hello .. && make && make testcpp
popd > /dev/null

#install
buildroot=$cwd/tarball_build
/bin/rm -fr $buildroot
mkdir -p $buildroot
pushd build > /dev/null
make DESTDIR=$buildroot install
popd > /dev/null
rootdir=$buildroot/hello
mkdir -p $rootdir
/bin/cp -af bin python/hello.py install.sh $rootdir
pushd $rootdir > /dev/null
mkdir -p py_package
/bin/cp -af $buildroot/usr/local/hello/py_package/* py_package
/bin/ln -srf bin/hello bin/ho
/bin/chmod 0755 bin/* install.sh
popd > /dev/null

tarball="$cwd/hello-$version.tar.gz"
pushd $buildroot > /dev/null
tar -czf $tarball hello
popd > /dev/null
/bin/rm -fr $buildroot

echo "build $tarball done"
