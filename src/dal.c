#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dal.h"
#include "utils.h"

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
    if (empList == NULL || prodList == NULL || saleList == NULL) {
        return;
    }

    // 保存员工信息
    FILE* empFile = fopen("employees.dat", "wb");
    if (!empFile) {
        return;
    }
    
    for (EmployeeNode* current = empList->head; current != NULL; current = current->next) {
        fwrite(&current->data, sizeof(Employee), 1, empFile);
    }
    fclose(empFile);
    
    // 保存产品信息
    FILE* prodFile = fopen("products.dat", "wb");
    if (!prodFile) {
        return;
    }
    
    for (ProductNode* current = prodList->head; current != NULL; current = current->next) {
        fwrite(&current->data, sizeof(Product), 1, prodFile);
    }
    fclose(prodFile);
    
    // 保存销售记录
    FILE* saleFile = fopen("sales.dat", "wb");
    if (!saleFile) {
        return;
    }
    
    for (SaleRecordNode* current = saleList->head; current != NULL; current = current->next) {
        fwrite(&current->data, sizeof(SaleRecord), 1, saleFile);
    }
    fclose(saleFile);
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
    // 参数检查
    if (!saleList || !empList || !prodList || !employeeId || !count) {
        printf("Invalid parameters in getEmployeeMonthlyReport\n");
        return NULL;
    }
    // 最多12个月的报表
    EmployeeMonthlyReport* report = malloc(sizeof(EmployeeMonthlyReport) * 12);
    if (!report) {
        printf("Memory allocation failed in getEmployeeMonthlyReport\n");
        return NULL;
    }
    *count = 0;
    
    // 获取员工信息
    EmployeeNode* emp = findEmployee(empList, employeeId);
    if (emp == NULL) {
        printf("Employee not found in getEmployeeMonthlyReport\n");
        free(report);
        return NULL;
    };
    
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
    // 如果没有任何销售数据，则返回NULL
    if (*count == 0) {
        printf("No sales data found for the specified employee\n");
        free(report);
        return NULL;
    }

    return report;
}

// 模糊查找员工
EmployeeList* findEmployeesByName(const EmployeeList* list, const char* name) {
    if (list == NULL || name == NULL) return NULL;
    
    EmployeeList* result = createEmployeeList();
    EmployeeNode* current = list->head;
    
    while (current != NULL) {
#ifdef _WIN32
        // Windows下使用编码转换比较
        if (compareStringWithEncoding(current->data.name, name)) {
            addEmployee(result, current->data);
        }
#else
        // Linux下直接比较
        if (strstr(current->data.name, name) != NULL) {
            addEmployee(result, current->data);
        }
#endif
        current = current->next;
    }
    
    return result;
}

// 模糊查找产品
ProductList* findProductsByName(const ProductList* list, const char* name) {
    if (list == NULL || name == NULL) return NULL;
    
    ProductList* result = createProductList();
    ProductNode* current = list->head;
    
    while (current != NULL) {
#ifdef _WIN32
        // Windows下使用编码转换比较
        if (compareStringWithEncoding(current->data.name, name)) {
            addProduct(result, current->data);
        }
#else
        // Linux下直接比较
        if (strstr(current->data.name, name) != NULL) {
            addProduct(result, current->data);
        }
#endif
        current = current->next;
    }
    
    return result;
}

MonthlySalesSummary* getMonthlySales(const SaleRecordList* saleList, const EmployeeList* empList, 
                                    const ProductList* prodList, const char* startMonth, 
                                    const char* endMonth, int* count) {
    *count = 0;
    if (saleList == NULL || startMonth == NULL || endMonth == NULL) {
        return NULL;
    }

    // 最多统计60个月的数据
    MonthlySalesSummary* summary = malloc(sizeof(MonthlySalesSummary) * 60);
    if (summary == NULL) {
        return NULL;
    }

    // 遍历销售记录
    SaleRecordNode* current = saleList->head;
    while (current != NULL) {
        // 提取销售记录的年月
        char recordMonth[8];
        strncpy(recordMonth, current->data.date, 7);
        recordMonth[7] = '\0';

        // 检查是否在指定时间范围内
        if (strcmp(recordMonth, startMonth) >= 0 && strcmp(recordMonth, endMonth) <= 0) {
            // 查找是否已有该月份的记录
            int monthIndex = -1;
            for (int i = 0; i < *count; i++) {
                if (strcmp(summary[i].month, recordMonth) == 0) {
                    monthIndex = i;
                    break;
                }
            }

            // 如果是新月份，创建新记录
            if (monthIndex == -1) {
                monthIndex = *count;
                strcpy(summary[*count].month, recordMonth);
                summary[*count].totalAmount = 0;
                summary[*count].totalTransactions = 0;
                (*count)++;
            }

            // 更新统计数据
            ProductNode* prod = findProduct(prodList, current->data.productId);
            if (prod != NULL) {
                summary[monthIndex].totalAmount += current->data.quantity * prod->data.price;
                summary[monthIndex].totalTransactions++;
            }
        }
        current = current->next;
    }

    // 按月份排序（冒泡排序）
    for (int i = 0; i < *count - 1; i++) {
        for (int j = 0; j < *count - i - 1; j++) {
            if (strcmp(summary[j].month, summary[j + 1].month) > 0) {
                MonthlySalesSummary temp = summary[j];
                summary[j] = summary[j + 1];
                summary[j + 1] = temp;
            }
        }
    }

    return summary;
} 