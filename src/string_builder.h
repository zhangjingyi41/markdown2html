#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *content;      // 内容
    size_t size;        // 当前大小（当前字符列表已使用的空间大小）
    size_t capacity;    // 容量（当前字符列表的最大空间大小）
} string_builder_t;

/**
 * 创建字符串构建器
 */
string_builder_t* sb_create();
/**
 * 创建指定初始容量的字符串构建器
 */
string_builder_t* sb_create_with_capacity(size_t initial_capacity);
/**
 * 创建并初始化为指定字符串的字符串构建器
 */
string_builder_t* sb_create_with_str(const char *initial_str);

/**
 * 销毁字符串构建器，释放内存
 */
void sb_destory(string_builder_t *sb);

/**
 * 向字符串构建器追加字符串
 * @param sb 目标字符串构建器
 * @param str 需要追加的字符串
 */
void sb_append(string_builder_t *sb, const char *str);

/**
 * 在指定位置插入字符串
 * @param sb 目标字符串构建器
 * @param pos 插入位置（0表示开头）
 * @param str 需要插入的字符串
 */
void sb_insert(string_builder_t *sb, size_t pos, const char *str);

/**
 * 获取指定位置的字符
 * @param sb 目标字符串构建器
 */
char sb_char_at(string_builder_t *sb, size_t index);

/**
 * 删除指定范围内的字符串
 * @param sb 目标字符串构建器
 * @param start 起始位置（包含）
 * @param end 结束位置（不包含）
 * @return 删除的字符数
 */
size_t sb_delete(string_builder_t *sb, size_t start, size_t end);

/**
 * 删除指定位置的字符
 * @param sb 目标字符串构建器
 * @param index 位置
 * @return 删除的字符数，0表示失败（索引越界）
 */
size_t sb_delete_char_at(string_builder_t *sb, size_t index);

/**
 * 获取字符串构建器的长度
 * @param sb 目标字符串构建器
 * @return 长度
 */
size_t sb_length(string_builder_t *sb);

/**
 * 查找指定字符串最后一次出现的位置
 * @param sb 目标字符串构建器
 * @param str 需要查找的字符串
 * @return 位置索引，找不到返回 -1
 */
size_t sb_last_index_of(string_builder_t *sb, const char *str);

/**
 * 查找指定字符串第一次出现的位置
 * @param sb 目标字符串构建器
 * @param str 需要查找的字符串
 * @return 位置索引，找不到返回 -1
 */
size_t sb_index_os(string_builder_t *sb, const char *str);

/**
 * 替换指定范围内的字符串
 * @param sb 目标字符串构建器
 * @param start 起始位置（包含）
 * @param end 结束位置（不包含）
 * @param str 替换的字符串
 * @return 替换的字符数
 */
size_t sb_replace(string_builder_t *sb, size_t start, size_t end, const char *str);

/**
 * 反转字符串构建器中的字符串
 * @param sb 目标字符串构建器
 */
void sb_reverse(string_builder_t *sb);

/**
 * 将字符串构建器转换为字符串
 * @param sb 目标字符串构建器
 */
char* sb_to_string(string_builder_t *sb);

/**
 * 获取子字符串构建器
 * @param sb 目标字符串构建器
 * @param start 起始位置（包含）
 * @param end 结束位置（不包含）
 * @return 新的字符串构建器
 */
string_builder_t* sb_sub(string_builder_t *sb, size_t start);

/**
 * 获取子字符串构建器
 * @param sb 目标字符串构建器
 * @param start 起始位置（包含）
 * @param end 结束位置（不包含）
 * @return 新的字符串构建器
 */
string_builder_t* sb_sub_to_end(string_builder_t *sb, size_t start, size_t end);

/**
 * 获取子字符串
 * @param sb 目标字符串构建器
 * @param start 起始位置（包含）
 * @param end 结束位置（不包含）
 * @return 新的字符串
 */
char* sb_substring(string_builder_t *sb, size_t start);

/**
 * 获取子字符串
 * @param sb 目标字符串构建器
 * @param start 起始位置（包含）
 * @param end 结束位置（不包含）
 * @return 新的字符串
 */
char* sb_substring_to_end(string_builder_t *sb, size_t start, size_t end);

/**
 * 分割字符串
 * @param sb 目标字符串构建器
 * @param delimiter 分隔符
 * @return 分割后的字符串构建器数组，需要调用者释放
 */
char** sb_split(string_builder_t *sb, const char *delimiter);

#endif