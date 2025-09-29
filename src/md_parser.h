#ifndef MD_PARSER_H
#define MD_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// html 缓冲区结构体
typedef struct {
    char *content;      // 内容
    size_t size;        // 当前大小
    size_t capacity;    // 容量
} html_buffer_t;

// 函数声明
// 初始化缓冲区
void init_buffer(html_buffer_t *buffer);
// 向缓冲区追加字符串
void append_string(html_buffer_t *buffer, const char *str);
// 释放缓冲区内存
void free_buffer(html_buffer_t *buffer);
// 解析 Markdown 并返回 HTML 字符串
char* parse_markdown2html(const char *markdown);
// 解析单行 Markdown 并返回 HTML 字符串
char* parse_line(const char *line);

#endif // MD_PARSER_H