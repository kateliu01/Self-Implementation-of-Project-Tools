另外，还有两个原⼦操作的系统调⽤函数来控制信号量的，分别是：
P 操作：将 sem 减 1 ，相减后，如果 sem < 0 ，则进程/线程进⼊阻塞等待，否则继续，表明 P
操作可能会阻塞；
V 操作：将 sem 加 1 ，相加后，如果 sem <= 0 ，唤醒⼀个等待中的进程/线程，表明 V 操作不
会阻塞；