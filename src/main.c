#include "md_parser.h"
#include "string_builder.h"

int main()
{
    system("chcp 65001"); // 设置控制台为UTF-8编码，防止中文乱码
    // const char *text = "# 你好，我是**张靖易**";
    // char *result = parse_line(text);
    // printf("%s\n", result);
 
    string_builder_t *sb = sb_create();
    printf("content: %s\nsize:%d\ncapcity:%d\n", sb->content, sb->size, sb->capacity);

    sb_append(sb, "hello best world");
    sb_replace(sb, 6, 10, "beautiful");
    printf("content: %s\nsize:%d\ncapcity:%d\n", sb->content, sb->size, sb->capacity);

    size_t start = sb_index_of(sb, "beautiful");
    size_t end = start + strlen("beautiful");
    sb_replace(sb, start, end, "maybe better");
    printf("content: %s\nsize:%d\ncapcity:%d\n", sb->content, sb->size, sb->capacity);
    sb_destory(sb);
    return 0;
}