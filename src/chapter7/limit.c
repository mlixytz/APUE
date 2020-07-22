#include "apue.h"
#include <sys/resource.h>

#define doit(name) pr_limits(#name, name)

static void pr_limits(char *, int);

int main(void) {
#ifdef RLIMIT_AS
    doit(RLIMIT_AS); // 进程总的可用存储空间的长度
#endif
    doit(RLIMIT_CORE); // core文件的最大字节数，若其值为0则阻止创建core文件
    doit(RLIMIT_CPU); // cpu时间的最大量值（秒），超过则向该进程发送SIGXCPU信号
    doit(RLIMIT_DATA); // 数据段的最大字节长度，初始化数据、未初始化数据、堆的总和
    doit(RLIMIT_FSIZE); // 可以创建的文件的最大自解长度，超过则向该进程发送SIGXFSZ信号

#ifdef RLIMIT_MEMLOCK
    doit(RLIMIT_MEMLOCK); // 一个进程使用mlock(锁定物理内存页)能够锁定在存储空间中的最大字节长度
#endif

#ifdef RLIMIT_MSGQUEUE
    doit(RLIMIT_MSGQUEUE); // 进程为posix消息队列可分配的最大存储字节数
#endif

#ifdef RLIMIT_NICE
    doit(RLIMIT_NICE); // 为了影响进程的调度优先级，nice值可设置的最大限制
#endif

    doit(RLIMIT_NOFILE); // 每个进程能打开的最多文件数

#ifdef RLIMIT_NPROC
    doit(RLIMIT_NPROC); // 每个实际用户ID可拥有的最大子进程数
#endif

#ifdef RLIMIT_NPTS
    doit(RLIMIT_NPTS); // 用户可同时打开的伪终端的最大数量
#endif

#ifdef RLIMIT_RSS
    doit(RLIMIT_RSS); // 最大驻内存集字节长度，如果可用物理存储器非常少，则内核将从进程处取回超过RSS的部分
#endif

#ifdef RLIMIT_SBSIZE
    doit(RLIMIT_SBSIZE); // 在任一时刻，一个用户可以占用的套接字缓冲区的最大长度（字节）
#endif

#ifdef RLIMIT_RIGPENDING
    doit(RLIMIT_RIGPENDING); // 一个进程可排队的信号最大数量
#endif

    doit(RLIMIT_STACK); // 栈的最大字节长度

#ifdef RLIMIT_SWAP
    doit(RLIMIT_SWAP); // 用户可消耗的交换空间的最大字节数
#endif

#ifdef RLIMIT_VMEM
    doit(RLIMIT_VMEM); // RLIMIT_AS同义词
#endif

    exit(0);
}

static void pr_limits(char *name, int resource) {
    struct rlimit limit;
    unsigned long long lim;

    if (getrlimit(resource, &limit) < 0)
        err_sys("getrlimit error for %s", name);
    printf("%-14s ", name);
    if (limit.rlim_cur == RLIM_INFINITY) {
        printf("(infinite) ");
    } else {
        lim = limit.rlim_cur;
        printf("%10lld ", lim);
    }
    if (limit.rlim_max == RLIM_INFINITY) {
        printf("(infinite)");
    } else {
        lim = limit.rlim_max;
        printf("%10lld", lim);
    }
    putchar((int)'\n');
}