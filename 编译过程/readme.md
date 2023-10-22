## 编译
gcc lib.c -fPIC -shared -o lib.so
gcc -o show_me_poor show_me_poor.c ./lib.so