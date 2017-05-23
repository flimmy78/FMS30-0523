#!/bin/sh

udevno='1.6.5'

# 清理
rm -rf '../build'
rm -f '../dependencies64/cef/bin/linux/libcef.so'
rm -f '../dependencies64/cef/bin/linux/libudev.so'
rm -f '../dependencies64/cef/bin/linux/libudev.so.0'
rm -f '../dependencies64/cef/bin/linux/libudev.so.1'
rm -f '../dependencies64/cef/lib/linux/libcef.so'
rm -f "../dependencies64/cef/lib/linux/libudev.so.${udevno}"
rm -f '../dependencies64/cef/lib/linux/libudev.so'
rm -f '../dependencies64/cef/lib/linux/libudev.so.0'
rm -f '../dependencies64/cef/lib/linux/libudev.so.1'
rm -rf '../dependencies64/ffmpeg/lib/linux'
rm -rf '../dependencies64/freeimage/bin/linux'
rm -rf '../dependencies64/glew/bin/linux'
rm -rf '../dependencies64/ldkdog/bin/linux'
rm -rf '../dependencies64/mainconcept/bin/linux'
rm -rf '../dependencies64/openal/bin/linux'
rm -rf '../dependencies64/tbb/bin/linux'
find '../dependencies64/ffmpeg/bin/linux' -type l -exec rm -rf {} \;
find '../dependencies64/freeimage/lib/linux' -type l -exec rm -rf {} \;
find '../dependencies64/glew/lib/linux' -type l -exec rm -rf {} \;
find '../dependencies64/mainconcept/lib/linux' -type l -exec rm -rf {} \;
find '../dependencies64/openal/lib/linux' -type l -exec rm -rf {} \;
find '../dependencies64/tbb/lib/linux' -type l -exec rm -rf {} \;
if [ $# -eq 1 ]; then
	if [ $1 = 'clean' ]; then
		exit 0
	fi
fi

# dependencies64自动匹配, 动态库依赖于系统, 静态库可以通用
# find ./ -print -exec ldd {} \; 查找依赖
ln -rs "../dependencies64/cef/bin/linux/libudev.so.${udevno}" '../dependencies64/cef/bin/linux/libudev.so'
ln -rs "../dependencies64/cef/bin/linux/libudev.so.${udevno}" '../dependencies64/cef/bin/linux/libudev.so.0'
ln -rs "../dependencies64/cef/bin/linux/libudev.so.${udevno}" '../dependencies64/cef/bin/linux/libudev.so.1'
ln -rs '../dependencies64/cef/bin/linux/libcef.so' '../dependencies64/cef/lib/linux/libcef.so'
ln -rs "../dependencies64/cef/bin/linux/libudev.so.${udevno}" "../dependencies64/cef/lib/linux/libudev.so.${udevno}"
ln -rs '../dependencies64/cef/bin/linux/libudev.so' '../dependencies64/cef/lib/linux/libudev.so'
ln -rs '../dependencies64/cef/bin/linux/libudev.so.0' '../dependencies64/cef/lib/linux/libudev.so.0'
ln -rs '../dependencies64/cef/bin/linux/libudev.so.1' '../dependencies64/cef/lib/linux/libudev.so.1'
ln -rs '../dependencies64/ffmpeg/bin/linux' '../dependencies64/ffmpeg/lib/linux'
ln -rs '../dependencies64/freeimage/lib/linux' '../dependencies64/freeimage/bin/linux'
ln -rs '../dependencies64/glew/lib/linux' '../dependencies64/glew/bin/linux'
ln -rs '../dependencies64/ldkdog/lib/linux' '../dependencies64/ldkdog/bin/linux'
ln -rs '../dependencies64/mainconcept/lib/linux' '../dependencies64/mainconcept/bin/linux'
ln -rs '../dependencies64/openal/lib/linux' '../dependencies64/openal/bin/linux'
ln -rs '../dependencies64/tbb/lib/linux' '../dependencies64/tbb/bin/linux'
cd '../dependencies64/ffmpeg/bin/linux'
../../../../build-scripts/lnso.sh
cd '../../../freeimage/lib/linux'
../../../../build-scripts/lnso.sh
cd '../../../glew/lib/linux'
../../../../build-scripts/lnso.sh
cd '../../../mainconcept/lib/linux'
../../../../build-scripts/lnso.sh
cd '../../../openal/lib/linux'
../../../../build-scripts/lnso.sh
cd '../../../tbb/lib/linux'
../../../../build-scripts/lnso.sh
cd '../../../../build-scripts'

export BUILD_ARCHIVE_NAME='famous'
export BUILD_PARALLEL_THREADS=12

./build-linux.sh
