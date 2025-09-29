#include "md_parser.h"

void init_buffer(html_buffer_t *buffer)
{
    // 必须使用 -> 因为 buffer 是指针
    // 如果用 buffer.capacity 会编译错误！
    // buffer.capacity = 1024;  // 错误！buffer是指针，不是结构体
    buffer->capacity = 1024;    // 初始容量
    buffer->size = 0;           // 初始大小
    buffer->content = malloc(buffer->capacity); // 分配内存
    buffer->content[0] = '\0'; // 初始化为空字符串
}


/**
 * 向缓冲区追加字符串
 * @param buffer 目标缓冲区
 * @param str 需要追加的字符串
 */
void append_string(html_buffer_t *buffer, const char *str)
{
    size_t len = strlen(str);
    while(buffer->size + len + 1 > buffer->capacity){
        // 扩展缓冲区
        buffer->capacity *= 2;
        buffer->content = realloc(buffer->content, buffer->capacity);
    }
    strcat(buffer->content, str);
    buffer->size += len;

}
/**
 * 释放缓冲区内存
 * @param buffer 需要释放的缓冲区
 */
void free_buffer(html_buffer_t *buffer)
{
    free(buffer->content);
}

/**
 * 解析 Markdown 并返回 HTML 字符串
 * @param markdown 输入的 Markdown 字符串
 */
char* parse_markdown2html(const char *markdown)
{
    
}


char* parse_line(const char *line)
{
    static char result[2048];
    result[0] = '\0'; 

    /*
        处理标题
        # 一级标题
        ## 二级标题
        ......
        ###### 六级标题
    */
    if(line[0] == '#'){
        int level = 0;
        while (line[level] == '#' && level < 6){
            level++;
        }
        if(line[level] == ' '){
            sprintf(result, "<h%d>%s</h%d>\n", level, line+level+1, level);
            return result;
        }
    }

    // 处理粗体 **text**
    char *temp = malloc(strlen(line) + 100); // 预留足够空间
    strcpy(temp, line);
    char *pos = strstr(temp, "**");
    while(pos != NULL){
        char *end = strstr(pos+2, "**");
        if(end != NULL){
            memmove(pos + 3, pos + 2, end - pos - 2);
            memcpy(pos, "<b>", 3);
            end += 1;
            memmove(end + 4, end + 2, strlen(end + 2) + 1);
            memcpy(end, "</b>", 4);
        }
        pos = strstr(end ? end + 4 : pos + 2, "**");
    }

    sprintf(result, "<p>%s</p>\n", temp);
    free(temp);
    return result;

}

void handle_title(const char *line)
{
    // 临时变量
    
    if(line[0] == '#'){
        int level = 0;
        while(line[level] == '#' && level < 6){
            level++;
        }
        // 确保 '#' 后面有空格
        if(line[level] == ' '){
            // 生成 HTML 标题
            sprintf(line, "<h%d>%s</h%d>\n", level, line+level+1, level);
        }
    }
}