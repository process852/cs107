# 知识巩固

## 饱和加法

* 产生指定位宽的有符号数最大值和最小值

```C
// 0000 0001
// 1000 0000 
// 0111 1111 ==> 2^7 - 1 = 127
long signed_max(int bitwidth){
    return (1L << (bitwidth - 1)) - 1;
}

// 1111 ... 1111 1111 1111
// 1111 ... 1111 1000 0000 ==> -2^7 = -128
long signed_min(int bitwidth){
    return ~0L << (bitwidth - 1);
}
```