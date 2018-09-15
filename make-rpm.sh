#/bin/bash
set -e

version=$1
[ -z $version ] && version="0.0.1"

echo "version $version"

cwd=$(cd $(dirname $0); pwd)

spec_in=hello.spec.in
spec=$(echo $spec_in | sed 's/.in$//')
cat $cwd/$spec_in | sed "s/@VERSION@/$version/g" |
        sed "s#@ROOT@#$cwd#g" > $cwd/$spec
rpmbuild -bb $cwd/$spec
