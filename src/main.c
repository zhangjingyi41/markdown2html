#include "md_parser.h"

int main()
{
    system("chcp 65001"); // 设置控制台为UTF-8编码，防止中文乱码
    const char *text = "# 你好，我是**张靖易**";
    char *result = parse_line(text);
    printf("%s\n", result);
    return 0;
}