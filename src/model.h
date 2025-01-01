#ifndef MODEL_H
#define MODEL_H

typedef struct {
    char id[20];         // 员工号
    char name[50];       // 姓名
    char gender[10];     // 性别
    char birthDate[20];  // 出生年月
} Employee;

typedef struct {
    char id[20];        // 产品号
    char name[50];      // 产品名称
    char type[30];      // 产品类型
    float price;        // 价格
} Product;

typedef struct {
    char productId[20];   // 产品号
    char employeeId[20];  // 销售员工号
    int quantity;         // 销售数量
    char date[20];        // 销售日期 (格式：YYYY-MM-DD)
} SaleRecord;

// 用于统计报表的结构
typedef struct {
    char productId[20];
    char productName[50];
    int totalQuantity;
    float totalAmount;
} ProductSalesSummary;

typedef struct {
    char employeeId[20];
    char employeeName[50];
    float totalAmount;
} EmployeeSalesSummary;

typedef struct {
    char employeeId[20];
    char employeeName[50];
    char month[8];        // 格式：YYYY-MM
    float totalAmount;
} EmployeeMonthlyReport;

// 链表节点定义
typedef struct EmployeeNode {
    Employee data;
    struct EmployeeNode* next;
} EmployeeNode;

typedef struct ProductNode {
    Product data;
    struct ProductNode* next;
} ProductNode;

typedef struct SaleRecordNode {
    SaleRecord data;
    struct SaleRecordNode* next;
} SaleRecordNode;

// 链表结构定义
typedef struct {
    EmployeeNode* head;
    int size;
} EmployeeList;

typedef struct {
    ProductNode* head;
    int size;
} ProductList;

typedef struct {
    SaleRecordNode* head;
    int size;
} SaleRecordList;

#endif 