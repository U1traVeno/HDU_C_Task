#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dal.h"

// 员工管理实现
EmployeeList* createEmployeeList(void) {
    EmployeeList* list = (EmployeeList*)malloc(sizeof(EmployeeList));
    list->head = NULL;
    list->size = 0;
    return list;
}

void addEmployee(EmployeeList* list, Employee employee) {
    EmployeeNode* newNode = (EmployeeNode*)malloc(sizeof(EmployeeNode));
    newNode->data = employee;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

void deleteEmployee(EmployeeList* list, const char* id) {
    EmployeeNode* current = list->head;
    EmployeeNode* prev = NULL;
    
    while (current != NULL && strcmp(current->data.id, id) != 0) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) return;
    
    if (prev == NULL) {
        list->head = current->next;
    } else {
        prev->next = current->next;
    }
    
    free(current);
    list->size--;
}

EmployeeNode* findEmployee(const EmployeeList* list, const char* id) {
    EmployeeNode* current = list->head;
    while (current != NULL) {
        if (strcmp(current->data.id, id) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void updateEmployee(EmployeeList* list, const char* id, Employee newData) {
    EmployeeNode* node = findEmployee(list, id);
    if (node != NULL) {
        node->data = newData;
    }
}

EmployeeNode* getAllEmployees(const EmployeeList* list) {
    return list->head;
}

// 产品管理实现
ProductList* createProductList(void) {
    ProductList* list = (ProductList*)malloc(sizeof(ProductList));
    list->head = NULL;
    list->size = 0;
    return list;
}

void addProduct(ProductList* list, Product product) {
    ProductNode* newNode = (ProductNode*)malloc(sizeof(ProductNode));
    newNode->data = product;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

void deleteProduct(ProductList* list, const char* id) {
    ProductNode* current = list->head;
    ProductNode* prev = NULL;
    
    while (current != NULL && strcmp(current->data.id, id) != 0) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) return;
    
    if (prev == NULL) {
        list->head = current->next;
    } else {
        prev->next = current->next;
    }
    
    free(current);
    list->size--;
}

ProductNode* findProduct(const ProductList* list, const char* id) {
    ProductNode* current = list->head;
    while (current != NULL) {
        if (strcmp(current->data.id, id) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void updateProduct(ProductList* list, const char* id, Product newData) {
    ProductNode* node = findProduct(list, id);
    if (node != NULL) {
        node->data = newData;
    }
}

ProductNode* getAllProducts(const ProductList* list) {
    return list->head;
}

// 销售记录管理实现
SaleRecordList* createSaleRecordList(void) {
    SaleRecordList* list = (SaleRecordList*)malloc(sizeof(SaleRecordList));
    list->head = NULL;
    list->size = 0;
    return list;
}

void addSaleRecord(SaleRecordList* saleList, SaleRecord record) {
    if (saleList == NULL) {
        printf("错误：销售记录列表未初始化！\n");
        return;
    }
    
    SaleRecordNode* newNode = (SaleRecordNode*)malloc(sizeof(SaleRecordNode));
    if (newNode == NULL) {
        printf("错误：内存分配失败！\n");
        return;
    }
    
    newNode->data = record;
    newNode->next = saleList->head;
    saleList->head = newNode;
    saleList->size++;
}

void deleteSaleRecord(SaleRecordList* list, const char* employeeId, const char* date) {
    SaleRecordNode* current = list->head;
    SaleRecordNode* prev = NULL;
    
    while (current != NULL) {
        if (strcmp(current->data.employeeId, employeeId) == 0 && 
            strcmp(current->data.date, date) == 0) {
            break;
        }
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) return;
    
    if (prev == NULL) {
        list->head = current->next;
    } else {
        prev->next = current->next;
    }
    
    free(current);
    list->size--;
}

SaleRecordNode* findSaleRecords(const SaleRecordList* list, const char* employeeId, const char* date) {
    SaleRecordNode* current = list->head;
    while (current != NULL) {
        if (strcmp(current->data.employeeId, employeeId) == 0 && 
            strcmp(current->data.date, date) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void updateSaleRecord(SaleRecordList* list, SaleRecord oldRecord, SaleRecord newRecord) {
    SaleRecordNode* current = list->head;
    while (current != NULL) {
        if (strcmp(current->data.employeeId, oldRecord.employeeId) == 0 && 
            strcmp(current->data.date, oldRecord.date) == 0 &&
            strcmp(current->data.productId, oldRecord.productId) == 0) {
            current->data = newRecord;
            break;
        }
        current = current->next;
    }
}

SaleRecordNode* getAllSaleRecords(const SaleRecordList* list) {
    return list->head;
}

// 文件操作实现
void saveToFiles(const EmployeeList* empList, const ProductList* prodList, const SaleRecordList* saleList) {
    // 保存员工信息
    FILE* empFile = fopen("employees.dat", "wb");
    if (empFile) {
        EmployeeNode* current = empList->head;
        while (current != NULL) {
            fwrite(&current->data, sizeof(Employee), 1, empFile);
            current = current->next;
        }
        fclose(empFile);
    }
    
    // 保存产品信息
    FILE* prodFile = fopen("products.dat", "wb");
    if (prodFile) {
        ProductNode* current = prodList->head;
        while (current != NULL) {
            fwrite(&current->data, sizeof(Product), 1, prodFile);
            current = current->next;
        }
        fclose(prodFile);
    }
    
    // 保存销售记录
    FILE* saleFile = fopen("sales.dat", "wb");
    if (saleFile) {
        SaleRecordNode* current = saleList->head;
        while (current != NULL) {
            fwrite(&current->data, sizeof(SaleRecord), 1, saleFile);
            current = current->next;
        }
        fclose(saleFile);
    }
}

void loadFromFiles(EmployeeList* empList, ProductList* prodList, SaleRecordList* saleList) {
    // 加载员工信息
    FILE* empFile = fopen("employees.dat", "rb");
    if (empFile) {
        Employee emp;
        while (fread(&emp, sizeof(Employee), 1, empFile) == 1) {
            addEmployee(empList, emp);
        }
        fclose(empFile);
    }
    
    // 加载产品信息
    FILE* prodFile = fopen("products.dat", "rb");
    if (prodFile) {
        Product prod;
        while (fread(&prod, sizeof(Product), 1, prodFile) == 1) {
            addProduct(prodList, prod);
        }
        fclose(prodFile);
    }
    
    // 加载销售记录
    FILE* saleFile = fopen("sales.dat", "rb");
    if (saleFile) {
        SaleRecord sale;
        while (fread(&sale, sizeof(SaleRecord), 1, saleFile) == 1) {
            addSaleRecord(saleList, sale);
        }
        fclose(saleFile);
    }
}

// 统计功能实现
ProductSalesSummary* getProductSalesByMonth(const SaleRecordList* saleList, const ProductList* prodList, 
                                          const char* month, int* count) {
    // 分配足够大的空间存储所有产品的销售汇总
    ProductSalesSummary* summary = malloc(sizeof(ProductSalesSummary) * prodList->size);
    *count = 0;
    
    // 初始化汇总数组
    ProductNode* prodCurrent = prodList->head;
    while (prodCurrent != NULL) {
        strcpy(summary[*count].productId, prodCurrent->data.id);
        strcpy(summary[*count].productName, prodCurrent->data.name);
        summary[*count].totalQuantity = 0;
        summary[*count].totalAmount = 0;
        (*count)++;
        prodCurrent = prodCurrent->next;
    }
    
    // 统计销售记录
    SaleRecordNode* saleCurrent = saleList->head;
    while (saleCurrent != NULL) {
        // 检查是否是指定月份的记录
        if (strncmp(saleCurrent->data.date, month, 7) == 0) {
            // 查找对应产品的汇总记录
            for (int i = 0; i < *count; i++) {
                if (strcmp(summary[i].productId, saleCurrent->data.productId) == 0) {
                    summary[i].totalQuantity += saleCurrent->data.quantity;
                    // 查找产品价格
                    ProductNode* prod = findProduct(prodList, saleCurrent->data.productId);
                    if (prod != NULL) {
                        summary[i].totalAmount += saleCurrent->data.quantity * prod->data.price;
                    }
                    break;
                }
            }
        }
        saleCurrent = saleCurrent->next;
    }
    
    // 按销售金额排序（冒泡排序）
    for (int i = 0; i < *count - 1; i++) {
        for (int j = 0; j < *count - i - 1; j++) {
            if (summary[j].totalAmount < summary[j + 1].totalAmount) {
                ProductSalesSummary temp = summary[j];
                summary[j] = summary[j + 1];
                summary[j + 1] = temp;
            }
        }
    }
    
    return summary;
}

EmployeeSalesSummary* getEmployeeSalesByMonth(const SaleRecordList* saleList, const EmployeeList* empList, 
                                             const ProductList* prodList, const char* month, int* count) {
    *count = 0;
    
    // 获取所有员工
    EmployeeNode* empCurrent = empList->head;
    if (empCurrent == NULL) return NULL;
    
    // 为每个员工创建一个汇总记录
    EmployeeSalesSummary* summary = malloc(sizeof(EmployeeSalesSummary) * empList->size);
    while (empCurrent != NULL) {
        strcpy(summary[*count].employeeId, empCurrent->data.id);
        strcpy(summary[*count].employeeName, empCurrent->data.name);
        summary[*count].totalAmount = 0;
        (*count)++;
        empCurrent = empCurrent->next;
    }
    
    // 遍历销售记录，统计每个员工的销售额
    SaleRecordNode* saleCurrent = saleList->head;
    while (saleCurrent != NULL) {
        // 检查是否是目标月份的记录
        if (strncmp(saleCurrent->data.date, month, 7) == 0) {
            // 查找对应的员工汇总记录
            for (int i = 0; i < *count; i++) {
                if (strcmp(summary[i].employeeId, saleCurrent->data.employeeId) == 0) {
                    ProductNode* prod = findProduct(prodList, saleCurrent->data.productId);
                    if (prod != NULL) {
                        summary[i].totalAmount += saleCurrent->data.quantity * prod->data.price;
                    }
                    break;
                }
            }
        }
        saleCurrent = saleCurrent->next;
    }
    
    return summary;
}

EmployeeMonthlyReport* getEmployeeMonthlyReport(const SaleRecordList* saleList, const EmployeeList* empList, 
                                               const ProductList* prodList, const char* employeeId, int* count) {
    // 最多12个月的报表
    EmployeeMonthlyReport* report = malloc(sizeof(EmployeeMonthlyReport) * 12);
    *count = 0;
    
    // 获取员工信息
    EmployeeNode* emp = findEmployee(empList, employeeId);
    if (emp == NULL) return NULL;
    
    // 遍历销售记录，按月份统计
    SaleRecordNode* saleCurrent = saleList->head;
    while (saleCurrent != NULL) {
        if (strcmp(saleCurrent->data.employeeId, employeeId) == 0) {
            char month[8];
            strncpy(month, saleCurrent->data.date, 7);
            month[7] = '\0';
            
            // 查找或创建月份记录
            int monthIndex = -1;
            for (int i = 0; i < *count; i++) {
                if (strcmp(report[i].month, month) == 0) {
                    monthIndex = i;
                    break;
                }
            }
            
            if (monthIndex == -1) {
                monthIndex = *count;
                strcpy(report[*count].employeeId, employeeId);
                strcpy(report[*count].employeeName, emp->data.name);
                strcpy(report[*count].month, month);
                report[*count].totalAmount = 0;
                (*count)++;
            }
            
            // 累加销售金额
            ProductNode* prod = findProduct(prodList, saleCurrent->data.productId);
            if (prod != NULL) {
                report[monthIndex].totalAmount += saleCurrent->data.quantity * prod->data.price;
            }
        }
        saleCurrent = saleCurrent->next;
    }
    
    return report;
} 