#ifndef DATA_H
#define DATA_H

#include <time.h>

#define NAME_LEN 60
#define AUTHOR_LEN 60
#define ISBN_LEN 20

typedef struct {
	int id;
	char name[NAME_LEN];
	char isbn[ISBN_LEN];
	char author[AUTHOR_LEN];
	int stock;    // 库存
	int loaned;   // 已借出数量
	int state;    // 保留字段，用于状态标志
} Book;

typedef struct BookNode {
	Book book;
	struct BookNode* next;
} BookNode;

/* 数据容器（链表）接口 */
BookNode* createBookNode(const Book* book);
BookNode* insertBookNode_tail(BookNode* head, const Book* book);
BookNode* createBookList(void);
void freeBookList(BookNode* head);
BookNode* queryBookListById(BookNode* head, int id);
BookNode* queryBookListByISBN(BookNode* head, const char* isbn);
int deleteBookListById(BookNode** head, int id);
int getBookListLength(BookNode* head);
void printBookList(BookNode* head);

/* 文件持久化（由 store 模块实现时调用） */
void saveBookListToFile(BookNode* head, const char* filename);
void readBookListFromFile(BookNode** head, const char* filename);

#endif /* DATA_H */

