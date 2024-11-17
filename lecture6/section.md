# Stack 数据结构

* stack.h
```C
// stack.h

typedef struct{
    int * elems;
    int loglength;
    int alloclength;
}stack;

void stackNew(stack* s);
void stackPush(stack* s, int num);
void stackPop(stack* s);
```

* stack.c
```C
// stack.c

void stackNew(stack* s){
    s->loglength = 0;
    s->alloclength = 4;
    s->elems = malloc(4*sizeof(int));
    assert(s->elems != NULL);
}

void stackDispose(stack* s){
    free(s->elems);
}

void stackPush(stack* s, int value){
    if(s->loglength == s->alloclength){
        s->alloclength *= 2;
        s->elems = realloc(s->elems, s->alloclength*sizeof(int));
        assert(s->elems != NULL);
    }
    s->elems[s->loglength] = value;
    s->loglength++;
}


int stackPop(stack* s){
    assert(s->loglength > 0);
    s->loglength--;
    return s->elems[s->loglength];
}
```

# 通用类型的stack实现

* stack.h

```C
typedef struct{
    void* elems;
    int elemSize; // 存储类型所占字节大小
    int loglength;
    int alloclength;
}stack;

void stackNew(stack* s, int elemSize);
void stackDispose(stack* s);
void stackPush(stack* s , void* elemAddr);
void stackPop(stack* s. void* elemAddr);
```

* stack.c

```C

void stackNew(stack*s , int elemSize){
    assert(elemSize > 0);
    s->loglength = 0;
    s->elemSize = elemSize;
    s->alloclength = 4;
    s->elems = malloc(4*elemSize);
    assert(s->elems != NULL);
}

static void stackGrow(stack* s){
    s->alloclength *= 2;
    s->elems = realloc(s->elems, s->alloclength* s->elemSize);
    assert(s->elems != NULL);
}

void stackPush(stack*s , void* elemAddr){
    if(s->loglength == s->alloclength)
        stackGrow(s);
    void* target = (char*)s->elems + s->loglength * s->elemSize;
    memcpy(target, elemAddr, s->elemSize); // 利用内存拷贝，避免了需要知道实际的类型
    s->loglength++;
}

void stackPop(stack* s, void *elemAddr){
    void* source = (char*)s->elems + (s->loglength - 1)*s->elemSize;
    memcpy(elemAddr, source, s->elemSize); // 利用指针存放弹出的元素，用户可以实现类型的转换
    s->loglength--;
}

```

# 如何释放stack上动态分配的内存

```C
typedef struct{
    void* elems;
    int elemSize; // 存储类型所占字节大小
    int loglength;
    int alloclength;
    void (*freeFn)(void*); // 维护一个可以用户传入的函数指针，用于释放元素内存空间
}stack;

void stackNew(stack* s, int elemSize);
void stackDispose(stack* s);
void stackPush(stack* s , void* elemAddr);
void stackPop(stack* s. void* elemAddr);
```

# qsort函数实现

