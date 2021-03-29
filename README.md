# 这是什么

一门全新的解释型编程语言，可以用来学习编译原理。



# 编译

开发环境：

*   gcc version 9.3.0 +  / Apple clang version 12.0.0 + 
*   cmake VERSION 3.0.0

实际编译环境下限：

*   我也不知道，差不多就行。。。

命令行中输入：

```shell
cmake .
make
```



# 运行

>   目前只完成类词法分析器，将来还会继续完善



## 运行词法分析器

运行命令：

```shell
./toh [source code file]
```

源文件的词法分析结果会输出在屏幕上。