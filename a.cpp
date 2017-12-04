#include <stdio.h>
#include <stdarg.h>


int log(char *s, int size, const char *fmt, ...) //该自定义函数，与系统提供的snprintf()函数相同。
{
    va_list ap;
    int n = 0;
    va_start(ap, fmt); //获得可变参数列表,分析fmt，得出各个参数的类型，也是分析参数中类似”%d%s“的字符串
    n = vsnprintf(s, size, fmt, ap); //写入字符串s
    va_end(ap); //释放资源,必须与va_start成对调用
    return n; //返回写入的字符个数
}

int main()
{
    char s[1000];
    log(s, 1000, "im ok:%d %j\n", 1000, "abc");
    printf("%s", s);
    return 0;
}