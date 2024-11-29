1a) continue 关键字用于跳过此次循环后续的过程
2b) realloc若传入的指针为NULL，等价于重新分配指定的内存空间
3c) 首先需要检查 malloc 返回的指针是否为空，若为空，则是分配空间失败
4d)
    <errno.h>头文件定义了变量 errno 表示最后一次错误的错误码
    该错误码一般有系统调用或者库函数进行设置，用于提示可能发生的错误。
    $ errno -l 可以查看不同错误码是什么类型的错误
    malloc 分配失败产生的错误码是 ENOMEM
5e)
6f) qsort 针对是 sturct dirent指针数组