## 编译
gcc lib.c -fPIC -shared -o lib.so
gcc -o show_me_poor show_me_poor.c ./lib.so

## 反编译
objdump -d -S show_me_poor