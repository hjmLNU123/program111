#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NAME_LEN 60 //定义图书名称的最大长度
#define AUTHOR_LEN 60//定义作者名称的最大长度
#define ISBN_LEN 20//定义图书ISBN的最大长度
#define BOOK_FINE"books.txt"//定义存储图书信息的文件名

typedef struct Book {//BookNode用于存储图书信息
    int id;
    char name[NAME_LEN];
    char isbn[ISBN_LEN];
    char author[AUTHOR_LEN];
    int state;// 0表示已借出，1表示可借
} BookNode;

typedef Node { //链表节点操作使用的结构体
    BookNode book;//一本书的定义对应到上面的BookNode结构体
    Node* next;//指向下一个节点的指针
}Node;



目前需要完成的东西
void ShowMenu(Node*head);//显示功能主菜单
void addBook(Node*head);//添加图书
void queryBook(Node*head);//查询图书
void deleteBook(Node*head);//删除图书
void updateBook(Node*head);//更新图书信息
void BorrowBook(Node*head);//借阅图书
void ReturnBook(Node*head);//归还图书
Node* createBookNode(BookNode *book);//创建图书结点
void addBookToEnd(Node* head, BookNode *book);//在链表的表尾增加一个新的图书节点
Node* createBookList();//创建带头结点的图书空链表
void freeBookList(Node*head);//释放图书链表内存空间 


后续在写的函数
Node* queryBookListById(Node*head);//根据图书ID查找图书结点
int DeleteBookListById(Node*head);//根据图书ID删除图书结点
int getBookListById(Node*head);//获取图书链表的长度
void printfBookListById(Node*head);//获取出链表所有节点保存的图书信息
void saveBookListById(Node*head);//文件保存图书链表信息
void readBookListById(Node*head);//从文件读取图书信息保存到链表
void error(const char* err);//ISBN冲突检测



//1.1主函数部分
int main(){
    int choice;
    //初始化链表头为NULL
    Node* head = NULL;
    while (1) {
        //显示功能主菜单
        ShowMenu(head);
        //输入用户选择
        scanf("%d", &choice);
        //功能选择实现
        switch (choice) {
            case 1:
                addBook(head);//添加图书
                break;
            case 2:
                queryBook(head);//查询图书
                break;
            case 3:
                deleteBook(head);//删除图书
                break;
            case 4:
                updateBook(head);//更新图书信息
                break;
            case 5:
                BorrowBook(head);//借阅图书
                break;
            case 6:
                ReturnBook(head);//归还图书
                break;
            case 7:
                return 0;
            default:
                printf("无效的选择，请重新输入。\n");
        }
    }
    //接着后续操作。。。
}
...main的部分

/*1.2核心功能模块函数*/
//显示功能主菜单的函数
void ShowMenu(Node*head) {
    printf("\n图书管理系统\n");
    printf("1. 添加图书\n");
    printf("2. 查询图书\n");
    printf("3. 删除图书\n");
    printf("4. 更新图书信息\n");
    printf("5. 借阅图书\n");
    printf("6. 归还图书\n");
    printf("7. 退出系统\n");
    printf("请选择操作(1-7):");
}



//添加图书
void addBook(Node** head){//注意这里head是二级指针，因为需要修改主函数中的head指针
    BookNode newBook;
    printf("输入图书ID:");
    scanf("%d", &newBook.id);
    printf("输入图书名称:");
    scanf("%s", newBook.name);
    printf("输入图书ISBN:");
    scanf("%s", newBook.isbn);
    printf("输入图书作者:");
    scanf("%s", newBook.author);
    printf("输入图书状态(0-已借出,1-可借）:");
    scanf("%d", &newBook.state);

    addBookToEnd(*head, &newBook);

}
//查询图书
void queryBook(Node*head){
}
//删除图书
void deleteBook(Node*head){
}
//更新图书信息
void updateBook(Node*head){
}
//借阅图书
void BorrowBook(Node*head){
}
//归还图书
void ReturnBook(Node*head){
}

/*1.3链表操作函数*/

//创建图书结点（基本函数，供后续函数调用）
Node* createBookNode(BookNode *book){
    Node* newNode = (Node*)malloc(sizeof(Node));//动态分配内存空间方便后续操作
    if(newNode == NULL){
        printf("内存分配失败！\n");
        return NULL;
    }
    newNode->book = *book;//定义原因在第18行定义的结构体 要创建一个节点必须有指针域和数据域
    newNode->next = NULL;
    return newNode;
}

// 在链表的表尾增加一个新的图书节点（与上面的addBook函数配合使用）尾插法的应用
void addBookToEnd(Node** head, BookNode *book){
    Node*newNode = createBookNode(book);//调用上面的创建节点函数
    if(newNode == NULL){
        return ;
    }
    if(*head == NULL){
        *head = newNode;//如果链表为空，则新节点为头节点
    }
    else{
        Node* current = *head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newNode;//将新节点添加到链表末尾
    }
}

//创建带头结点的图书空链表
Node* createBookList(){
}
//释放图书链表内存空间
void freeBookList(Node*head){
}
//根据图书ID查找图书结点
Node* queryBookListById(Node*head){
}
//根据图书ID删除图书结点
int DeleteBookListById(Node*head){
}
//获取图书链表的长度
int getBookListById(Node*head){
}
//获取出链表所有节点保存的图书信息
void printfBookListById(Node*head){
}
//文件保存图书链表信息
void saveBookListById(Node*head){
}
//从文件读取图书信息保存到链表
void readBookListById(Node*head){
} 
//ISBN冲突检测
void error(const char* err){
    //若 ISBN 已存在，返回`-1`并打印`"Error: ISBN [xxx] already exists"
}