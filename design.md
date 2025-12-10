# 图书馆管理系统设计文档

## 1. 数据结构设计

### 1.1 图书节点

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NAME_LEN 60 
#define AUTHOR_LEN  60
#define BOOK_FINE"books.txt"

typedef struct Book {
    int id;
    char name[50];
    char isbn[20];
    char author[50];
    int state;
} BookNode;

struct node{
    BOOK book;
    struct node*next;
};

void ShowMenu(struct node*head);
void addBook(struct node*head);
void queryBook(struct node*head);
void deleteBook(struct node*head);
void updateBook(struct node*head);
void BorrowBook(struct node*head);
void ReturnBook(struct node*head);
...
定义链表基础功能函数('data.c')

int main(){
    //创建链表保存数据

    //显示功能主菜单
}
//创建图书结点
struct node* createBookNode(BOOK *book){
    ...
}
//表尾增加图书结点
struct node* insertBookNode(BOOK *book){
    ...
}
//创建带头结点的图书空链表
struct node* createBookList(){
    return createBookList(NULL);
}
//释放图书链表内存空间
void freeBookList(struct node*head){
    ...
}
//根据图书ID查找图书结点
struct node* queryBookListById(struct node*head){
    ...
}
//根据图书ID删除图书结点
int DeleteBookListById(struct node*head){
    ...
}
//获取图书链表的长度
int getBookListById(struct node*head){
    ...
}
//获取出链表所有节点保存的图书信息
void printfBookListById(struct node*head){
    ...
}
//文件保存图书链表信息
void saveBookListById(struct node*head){
    ...
}
//从文件读取图书信息保存到链表
void readBookListById(struct node*head){
    ...
} 
//ISBN冲突检测
void error(const char* err){
    //若 ISBN 已存在，返回`-1`并打印`"Error: ISBN [xxx] already exists"
}
//下面续写在4.算法设计的内容
...

-   **ISBN 格式**：符合国际标准（13 位数字，如 9787532781234）,得查书上的ISBN
-   **链表特性**：单向链表，头插法实现

### 1.2 借阅记录
`void log_loan(const char* isbn, int quantity)`
        -   将借阅记录写入**二进制文件** `loan.bin`，格式：
```c
typedef struct Time {
    char isbn[20];
    int quantity;
    time_t timestamp;//用time()获取当前的时间
} LoanLog;

struct node{
    Time time;
    struct node*next;
};
//显示借阅时间和还书时间
```

-   **持久化格式**：二进制文件`loan.bin`
-   **时间记录**：使用`time_t`类型，可转换为可读时间
-   **导出格式**：CSV 文件`loan.csv`

### 1.3 书籍信息

```json
{
	"metadata": {
		"version": "1.0",
		"created": "1726704000"
	},
	"books": [
		{
			"isbn": "9787532781234",
			"title": "三体",
			"author": "刘慈欣",
			"stock": 5,
			"BorrowBook": 3
		},
		{
			"isbn": "9787532782345",
			"title": "流浪地球",
			"author": "刘慈欣",
			"stock": 2,
			"BorrowBook": 1
		},
        {
            "isbn":"9787020152490",
            "title":"哈利波特1",
            "author":"J.K.罗琳",
            "stock":3,
            "BorrowBook":2
        }
	]
}
```

-   **持久化格式**：JSON 文件`books.json`
-   **元数据**：包含版本和创建时间，便于未来格式升级
-   **可读性**：格式化输出，便于人工查看
-   **完整性**：包含所有业务所需字段（包括`BorrowBook`）

### 1.4 数据导出('store,c')
//其实不太明白这个要怎么设计

-   **需求**：
    -   `void export_to_csv(const char* filename, BookNode* head)`
        -   生成 CSV 格式：`isbn,title,author,stock,loaned`（每行一条记录）。
    -   `void export_to_json(const char* filename, BookNode* head)`
        -   生成 JSON 格式：`[{"isbn":"...","title":"..."}, ...]`
        -   **禁止用第三方库**（需手动拼接字符串）。
-   **示例输出**（`books.csv`）：
    ```csv
    9787532781234,三体,刘慈欣,5,3
    9787532782345,流浪地球,刘慈欣,2,1
    ```

## 2. 模块划分

| 模块    | 职责               | 依赖     |
| ------- | ------------------ | -------- |
| `data`  | 数据容器操作       | 无       |
| `logic` | 业务逻辑处理       | `data`   |
| `store` | 文件 I/O 操作      | `data`   |
| `main`  | 用户界面和命令解析 | 所有模块 |

## 3. 小组分工

| 成员     | 负责模块 | 具体任务                                  |
| -------- | -------- | ----------------------------------------- |
| [裴芯南] | `data.c`   | 实现`数据容器：链表操作`          |
| [黄俊铭] | `logic.c`   | 实现`业务逻辑：查询、排序、统计` |
| [裴芯南、黄俊铭] | `store.c`和`main.c`  | 实现`文件接口`和`程序入口`       |
| [现干]   | 所有     | 指导、代码审查、集成测试                  |

## 4. 关键算法设计('main.c')
void ShowMenu(struct node*head){
    printf("\n");
    ...
}

void addBook(struct node*head){
    ...
}

void queryBook(struct node*head){
    ...
}

void deleteBook(struct node*head){
    ...
}

void updateBook(struct node*head){
    ...
}

void BorrowBook(struct node*head){
    ...
}

void ReturnBook(struct node*head){
    ...
}

### 4.1 快速排序实现('logic.c')
`void sort_by_stock(BOOKNode** head)`
        -   **实现快速排序**（禁用`qsort`），按`stock`升序排列。
        -   提供伪代码：
            ```c
            int partition(BOOKNode** arr, int low, int high) {
                //选择基准、交换节点指针
            }
            void quick_sort(BOOKNode** arr, int low, int high) {
                //递归调用partition
            }
            ```
    -   `void generate_report(BOOKNode* head)`
        -   输出统计：库存>5 的图书数量、最热门图书（`BorrowBook`最高）。



### 4.2 模糊搜索('logic.c')
int FuzzySearchBook(struct node*head,const char* keyword,int search_type){
    ...
}

### 4.3 JSON 解析
1.cJSON_Parse：将 JSON 字符串解析为 cJSON 树形结构，返回根节点指针；
2。cJSON_GetObjectItem：从对象中提取指定键的节点（键名必须和 JSON 完全一致，包括大小写，比如BorrowBook不能写成borrowBook）；
3.cJSON_GetArraySize/cJSON_GetArrayItem：处理数组类型（books 是数组），遍历每个元素；
4.内存释放：cJSON_Delete(root)必须调用，否则会造成内存泄漏；
5.字符串处理：JSON 中的字符串是指针，需用strncpy拷贝到结构体数组中，避免指针指向已释放的内存。

## 5. 风险与应对

| 风险          | 影响       | 应对措施               |
| ------------- | ---------- | ---------------------- |
| 内存泄漏      | 程序崩溃   | 使用 Valgrind 定期检测 |
| 链表操作错误  | 数据丢失   | 单元测试覆盖边界情况   |
| 文件 I/O 失败 | 数据不一致 | 增加错误处理和日志     |


## 6，注意事项
1.每个函数头必须有注释（功能、参数、返回值）。
    -   关键逻辑行注释（如快速排序的递归条件）。
    -   注释行占比 ≥20%（用`cloc`验证）
    -   做有意义的注释
