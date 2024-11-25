File: readme.txt
Author: YOUR NAME HERE
----------------------

gets
1a)
code.c: In function ‘main’:
code.c:92:5: warning: ‘gets’ is deprecated (declared at /usr/include/stdio.h:638)
     if (gets(buf))   // this calls myth's version of gets
     ^
/tmp/ccBEV284.o: In function `main':
/afs/ir/users/c/e/cechang/107/a3/code.c:92: warning: the `gets' function is dangerous and should not be used.

1b) w is printed only during the first time apple_gets is called.
1c) No the buffer's length is still not considered.
1d) 25 total

calloc/realloc
2a) n*m 如果超出最大能表示的数据范围为变为负数，也满足上述要求，但实际会出现错误
2b) 根据数据类型size_t的字节大小，向上取整字节数
2c) 如果内存地址数据已经为0，则不需要进行复制操作。内存地址赋值涉及将数据移动到内存中,检查判断也需要数据拷贝以及判断指令
2d) 减少了原有数据的数据移动开销
2e) 


