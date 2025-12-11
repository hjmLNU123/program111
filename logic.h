/*
 * logic.h
 * 业务逻辑接口（排序、统计、模糊搜索等）
 */

#ifndef LOGIC_H
#define LOGIC_H

#include "data.h"

/* 添加/删除/更新 等业务接口（最小声明） */
void addBook(BookNode** head, const Book* book);
void updateBook(BookNode* head, int id, const Book* book);
int BorrowBook(BookNode* head, const char* isbn, int quantity);
int ReturnBook(BookNode* head, const char* isbn, int quantity);

/* 排序（按 stock 升序） */
void sort_by_stock(BookNode** head);

/* 生成统计报告 */
void generate_report(BookNode* head);

/* 模糊搜索 */
int FuzzySearchBook(BookNode* head, const char* keyword, int search_type);

#endif /* LOGIC_H */
