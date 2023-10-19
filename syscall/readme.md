## 编译
gcc -c -fPIC process.c
gcc -c -fPIC createprocess.c

## 打包静态库
ar cr libstaticprocess.a process.o

## 链接静态库
gcc -o staticcreateprocess createprocess.o -L. -lstaticprocess

## 执行
./staticcreateprocess

## 打包动态库
gcc -shared -fPIC -o libdynamicprocess.so process.o

## 链接动态库
gcc -o dynamiccreateprocess createprocess.o -L. -ldynamicprocess

## 执行 
export LD_LIBRARY_PATH=.
./dynamiccreateprocess
