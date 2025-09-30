#include "string_builder.h"

string_builder_t* sb_create()
{
    return sb_create_with_capacity(16);
}

string_builder_t* sb_create_with_capacity(size_t inital_capacity)
{
    if(inital_capacity <= 0){
        inital_capacity = 16;
    }
    string_builder_t *sb = malloc(sizeof(string_builder_t));
    sb->content = malloc(inital_capacity);
    sb->content[0] = '\0'; // 初始化为空字符串
    sb->size = 0;
    sb->capacity = inital_capacity;
    return sb;
}

string_builder_t* sb_create_with_str(const char *initial_str)
{
    if(initial_str == NULL){
        return sb_create();
    }
    size_t len = strlen(initial_str);
    string_builder_t *sb = sb_create_with_capacity(len + 1);
    sb->size = len;
    strcpy(sb->content, initial_str);
    return sb;
}

void sb_destory(string_builder_t *sb)
{
    if(sb == NULL) return;
    free(sb->content);
    free(sb);
}

void sb_append(string_builder_t *sb, const char *str)
{
    sb_insert(sb, sb->size, str);
}

void sb_insert(string_builder_t *sb, size_t pos, const char *str)
{
    size_t str_len = strlen(str);
    if(pos > sb->size){
        pos = sb->size; // 插入到末尾
    }
    if(pos < 0){
        pos = 0;
    }
    if(sb->size + str_len + 1 > sb->capacity){
        while(sb->size + str_len + 1 > sb->capacity){
            sb->capacity *= 2;
        }
        sb->content = realloc(sb->content, sb->capacity);
    }
    // 移动原字符串
    char *end_pos = sb->content + pos + str_len;
    char *start_pos = sb->content + pos;
    size_t move_len = sb->size - pos + 1; // +1是为了移动末尾的'\0'
    memmove(end_pos, start_pos, move_len);
    sb->size += str_len;
    // 插入新字符串
    memcpy(start_pos, str, str_len);
}

char sb_char_at(string_builder_t *sb, size_t index)
{
    if(index > sb->size || index < 0){
        return '\0'; // 越界返回空字符
    }
    return sb->content[index];
}

size_t sb_delete(string_builder_t *sb, size_t start, size_t end)
{
    if(start > sb->size || end > sb->size || start < 0 || end < 0 || start >= end){
        return 0; // 越界或无效范围返回0
    }
    // hello,world
    // 删除 ,wor (5,9)
    size_t delete_len = end - start;
    // 移动指针：
    //          h e l l o , w o r l d
    // start:             ↑ 
    // end:                       ↑
    char *start_pos = sb->content + start;
    char *end_pos = sb->content + end;
    size_t move_len = sb->size - end + 1; // +1是为了移动末尾的'\0'
    // 进行内存移动
    // 从end_pos开始的move_len个字节，移动到start_pos位置
    memmove(start_pos, end_pos, move_len);
    sb->size -= delete_len;
    return delete_len;
}

size_t sb_delete_char_at(string_builder_t *sb, size_t index)
{
    return sb_delete(sb, index, index + 1);
}

size_t sb_length(string_builder_t *sb)
{
    return sb->size;
}

size_t sb_index_of(string_builder_t *sb, const char *str)
{
    if(str == NULL || sb->size == 0){
        return -1;
    }
    char *pos = strstr(sb->content, str);
    if(pos == NULL) {
        return -1;  // 未找到
    }
    return pos - sb->content;  // 返回索引位置
}

size_t sb_last_index_of(string_builder_t *sb, const char *str)
{
    if(str == NULL || sb->size == 0){
        return -1;
    }
    char *last_pos = NULL;
    char *current_pos = sb->content;
    while((current_pos = strstr(current_pos, str)) != NULL){
        last_pos = current_pos;
        current_pos++; // 继续向后查找
    }
    if(last_pos == NULL){
        return -1; // 未找到
    }
    return last_pos - sb->content; // 返回索引位置
}

size_t sb_replace(string_builder_t *sb, size_t start, size_t end, const char *str)
{
    if(start > sb->size || end > sb->size || start < 0 || end < 0 || start >= end){
        return 0; // 越界或无效范围返回-1
    }
    size_t delete_len = end - start;
    size_t str_len = strlen(str);

    // 扩容
    if(sb->size - delete_len + str_len + 1 > sb->capacity){
        while(sb->size - delete_len + str_len + 1 > sb->capacity){
            sb->capacity *= 2;
        }
        sb->content = realloc(sb->content, sb->capacity);
    }

    // 移动原字符串
    /*
        hello,best world
        best替换为beautiful
        位置:             6     9
             h e l l o , b e s t   w o r l d \0
                         ↑     ↑
                       start  end
        beautiful长度为10，需要从end位置开始向后移动10-4=6个位置
             h e l l o , b e s t _ _ _ _ _ _   w o r l d \0
                         ↑                   ↑
                       start               new_end
    */
    char *start_pos = sb->content + start;
    char *end_pos = sb->content + end;
    char *new_end_pos = start_pos + str_len;
    size_t move_len = sb->size - end + 1; // 需要向后移动的字符数量，+1是为了移动末尾的'\0'
    if(str_len != delete_len){
        // 从end_pos开始的move_len个字节，移动到new_end_pos位置
        memmove(new_end_pos, end_pos, move_len);
    }

    // 插入新字符串
    memcpy(start_pos, str, str_len);
    sb->size = sb->size - delete_len + str_len;
}


