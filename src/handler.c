#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "handler.h"
#include "cli.h"
#include "dal.h"

// 员工管理处理函数
void handleAddEmployee(EmployeeList* list) {
    Employee emp;
    printf("\n=== 添加员工信息 ===\n");
    printf("请输入员工号：");
    scanf("%s", emp.id);
    
    // 检查是否已存在
    if (findEmployee(list, emp.id) != NULL) {
        printf("该员工号已存在！\n");
        return;
    }
    
    printf("请输入姓名：");
    scanf("%s", emp.name);
    printf("请输入性别：");
    scanf("%s", emp.gender);
    printf("请输入出生年月(YYYY-MM)：");
    scanf("%s", emp.birthDate);
    
    addEmployee(list, emp);
    printf("员工信息添加成功！\n");
}

void handleDisplayAllEmployees(const EmployeeList* list) {
    printf("\n=== 所有员工信息 ===\n");
    EmployeeNode* current = getAllEmployees(list);
    if (current == NULL) {
        printf("暂无员工信息！\n");
        return;
    }
    
    while (current != NULL) {
        printf("员工号：%s\n", current->data.id);
        printf("姓名：%s\n", current->data.name);
        printf("性别：%s\n", current->data.gender);
        printf("出生年月：%s\n", current->data.birthDate);
        printf("------------------------\n");
        current = current->next;
    }
}

void handleFindEmployee(const EmployeeList* list) {
    char id[20];
    printf("\n=== 查找员工信息 ===\n");
    printf("请输入要查找的员工号：");
    scanf("%s", id);
    
    EmployeeNode* node = findEmployee(list, id);
    if (node != NULL) {
        printf("员工号：%s\n", node->data.id);
        printf("姓名：%s\n", node->data.name);
        printf("性别：%s\n", node->data.gender);
        printf("出生年月：%s\n", node->data.birthDate);
    } else {
        printf("未找到该员工！\n");
    }
}

void handleUpdateEmployee(EmployeeList* list) {
    char id[20];
    printf("\n=== 修改员工信息 ===\n");
    printf("请输入要修改的员工号：");
    scanf("%s", id);
    
    if (findEmployee(list, id) == NULL) {
        printf("未找到该员工！\n");
        return;
    }
    
    Employee newData;
    strcpy(newData.id, id);
    printf("请输入新的姓名：");
    scanf("%s", newData.name);
    printf("请输入新的性别：");
    scanf("%s", newData.gender);
    printf("请输入新的出生年月(YYYY-MM)：");
    scanf("%s", newData.birthDate);
    
    updateEmployee(list, id, newData);
    printf("员工信息修改成功！\n");
}

void handleDeleteEmployee(EmployeeList* list) {
    char id[20];
    printf("\n=== 删除员工信息 ===\n");
    printf("请输入要删除的员工号：");
    scanf("%s", id);
    
    if (findEmployee(list, id) == NULL) {
        printf("未找到该员工！\n");
        return;
    }
    
    deleteEmployee(list, id);
    printf("员工信息删除成功！\n");
}

// 产品管理处理函数
void handleAddProduct(ProductList* list) {
    Product prod;
    printf("\n=== 添加产品信息 ===\n");
    printf("请输入产品号：");
    scanf("%s", prod.id);
    
    if (findProduct(list, prod.id) != NULL) {
        printf("该产品号已存在！\n");
        return;
    }
    
    printf("请输入产品名称：");
    scanf("%s", prod.name);
    printf("请输入产品类型：");
    scanf("%s", prod.type);
    printf("请输入产品价格：");
    scanf("%f", &prod.price);
    
    addProduct(list, prod);
    printf("产品信息添加成功！\n");
}

void handleDisplayAllProducts(const ProductList* list) {
    printf("\n=== 所有产品信息 ===\n");
    ProductNode* current = getAllProducts(list);
    if (current == NULL) {
        printf("暂无产品信息！\n");
        return;
    }
    
    while (current != NULL) {
        printf("产品号：%s\n", current->data.id);
        printf("名称：%s\n", current->data.name);
        printf("类型：%s\n", current->data.type);
        printf("价格：%.2f\n", current->data.price);
        printf("------------------------\n");
        current = current->next;
    }
}

void handleFindProduct(const ProductList* list) {
    char id[20];
    printf("\n=== 查找产品信息 ===\n");
    printf("请输入要查找的产品号：");
    scanf("%s", id);
    
    ProductNode* node = findProduct(list, id);
    if (node != NULL) {
        printf("产品号：%s\n", node->data.id);
        printf("名称：%s\n", node->data.name);
        printf("类型：%s\n", node->data.type);
        printf("价格：%.2f\n", node->data.price);
    } else {
        printf("未找到该产品！\n");
    }
}

void handleUpdateProduct(ProductList* list) {
    char id[20];
    printf("\n=== 修改产品信息 ===\n");
    printf("请输入要修改的产品号：");
    scanf("%s", id);
    
    if (findProduct(list, id) == NULL) {
        printf("未找到该产品！\n");
        return;
    }
    
    Product newData;
    strcpy(newData.id, id);
    printf("请输入新的产品名称：");
    scanf("%s", newData.name);
    printf("请输入新的产品类型：");
    scanf("%s", newData.type);
    printf("请输入新的产品价格：");
    scanf("%f", &newData.price);
    
    updateProduct(list, id, newData);
    printf("产品信息修改成功！\n");
}

void handleDeleteProduct(ProductList* list) {
    char id[20];
    printf("\n=== 删除产品信息 ===\n");
    printf("请输入要删除的产品号：");
    scanf("%s", id);
    
    if (findProduct(list, id) == NULL) {
        printf("未找到该产品！\n");
        return;
    }
    
    deleteProduct(list, id);
    printf("产品信息删除成功！\n");
}

// 销售记录管理处理函数
void handleAddSaleRecord(SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList) {
    SaleRecord record;
    printf("\n=== 添加销售记录 ===\n");
    
    printf("请输入员工号：");
    scanf("%s", record.employeeId);
    if (findEmployee(empList, record.employeeId) == NULL) {
        printf("该员工不存在！\n");
        return;
    }
    
    printf("请输入产品号：");
    scanf("%s", record.productId);
    if (findProduct(prodList, record.productId) == NULL) {
        printf("该产品不存在！\n");
        return;
    }
    
    printf("请输入销售数量：");
    scanf("%d", &record.quantity);
    printf("请输入销售日期(YYYY-MM-DD)：");
    scanf("%s", record.date);
    
    addSaleRecord(saleList, record);
    printf("销售记录添加成功！\n");
}

void handleDisplaySaleRecords(const SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList) {
    printf("\n=== 所有销售记录 ===\n");
    SaleRecordNode* current = getAllSaleRecords(saleList);
    if (current == NULL) {
        printf("暂无销售记录！\n");
        return;
    }
    
    while (current != NULL) {
        EmployeeNode* emp = findEmployee(empList, current->data.employeeId);
        ProductNode* prod = findProduct(prodList, current->data.productId);
        
        printf("日期：%s\n", current->data.date);
        printf("员工：%s (%s)\n", emp ? emp->data.name : "未知", current->data.employeeId);
        printf("产品：%s (%s)\n", prod ? prod->data.name : "未知", current->data.productId);
        printf("数量：%d\n", current->data.quantity);
        if (prod) {
            printf("金额：%.2f\n", current->data.quantity * prod->data.price);
        }
        printf("------------------------\n");
        current = current->next;
    }
}

// 统计报表处理函数
void handleProductSalesReport(const SaleRecordList* saleList, const ProductList* prodList) {
    char month[8];
    printf("\n=== 产品销售统计报表 ===\n");
    printf("请输入统计月份(YYYY-MM)：");
    scanf("%s", month);
    
    int count;
    ProductSalesSummary* summary = getProductSalesByMonth(saleList, prodList, month, &count);
    
    printf("\n%s 月份产品销售情况：\n", month);
    printf("%-10s %-20s %-10s %-10s\n", "产品号", "产品名称", "销售数量", "销售金额");
    printf("------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        if (summary[i].totalQuantity > 0) {  // 只显示有销售的产品
            printf("%-10s %-20s %-10d %-10.2f\n",
                   summary[i].productId,
                   summary[i].productName,
                   summary[i].totalQuantity,
                   summary[i].totalAmount);
        }
    }
    
    free(summary);
}

void handleEmployeeSalesReport(const SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList) {
    char month[8];
    printf("\n=== 员工销售统计报表 ===\n");
    printf("请输入统计月份(YYYY-MM)：");
    scanf("%s", month);
    
    int count;
    EmployeeSalesSummary* summary = getEmployeeSalesByMonth(saleList, empList, prodList, month, &count);
    
    printf("\n%s 月份员工销售情况：\n", month);
    printf("%-10s %-20s %-10s\n", "员工号", "员工姓名", "销售金额");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        if (summary[i].totalAmount > 0) {  // 只显示有销售的员工
            printf("%-10s %-20s %-10.2f\n",
                   summary[i].employeeId,
                   summary[i].employeeName,
                   summary[i].totalAmount);
        }
    }
    
    free(summary);
}

void handleEmployeeMonthlyReport(const SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList) {
    char employeeId[20];
    printf("\n=== 员工月度销售报表 ===\n");
    printf("请输入员工号：");
    scanf("%s", employeeId);
    
    int count;
    EmployeeMonthlyReport* report = getEmployeeMonthlyReport(saleList, empList, prodList, employeeId, &count);
    
    if (report == NULL) {
        printf("未找到该员工！\n");
        return;
    }
    
    printf("\n员工 %s (%s) 的月度销售情况：\n", report[0].employeeName, employeeId);
    printf("%-10s %-10s\n", "月份", "销售金额");
    printf("--------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-10s %-10.2f\n", report[i].month, report[i].totalAmount);
    }
    
    free(report);
}

void handleFindSaleRecord(const SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList) {
    char employeeId[20], date[20];
    printf("\n=== 查找销售记录 ===\n");
    printf("请输入员工号：");
    scanf("%s", employeeId);
    printf("请输入日期(YYYY-MM-DD)：");
    scanf("%s", date);
    
    SaleRecordNode* record = findSaleRecords(saleList, employeeId, date);
    if (record != NULL) {
        EmployeeNode* emp = findEmployee(empList, record->data.employeeId);
        ProductNode* prod = findProduct(prodList, record->data.productId);
        
        printf("日期：%s\n", record->data.date);
        printf("员工：%s (%s)\n", emp ? emp->data.name : "未知", record->data.employeeId);
        printf("产品：%s (%s)\n", prod ? prod->data.name : "未知", record->data.productId);
        printf("数量：%d\n", record->data.quantity);
        if (prod) {
            printf("金额：%.2f\n", record->data.quantity * prod->data.price);
        }
    } else {
        printf("未找到相关销售记录！\n");
    }
}

void handleUpdateSaleRecord(SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList) {
    SaleRecord oldRecord, newRecord;
    printf("\n=== 修改销售记录 ===\n");
    
    printf("请输入要修改的记录信息：\n");
    printf("员工号：");
    scanf("%s", oldRecord.employeeId);
    printf("日期(YYYY-MM-DD)：");
    scanf("%s", oldRecord.date);
    printf("产品号：");
    scanf("%s", oldRecord.productId);
    
    printf("\n请输入新的记录信息：\n");
    printf("员工号：");
    scanf("%s", newRecord.employeeId);
    if (findEmployee(empList, newRecord.employeeId) == NULL) {
        printf("该员工不存在！\n");
        return;
    }
    
    printf("产品号：");
    scanf("%s", newRecord.productId);
    if (findProduct(prodList, newRecord.productId) == NULL) {
        printf("该产品不存在！\n");
        return;
    }
    
    printf("数量：");
    scanf("%d", &newRecord.quantity);
    printf("日期(YYYY-MM-DD)：");
    scanf("%s", newRecord.date);
    
    updateSaleRecord(saleList, oldRecord, newRecord);
    printf("销售记录修改成功！\n");
}

void handleDeleteSaleRecord(SaleRecordList* saleList) {
    char employeeId[20], date[20];
    printf("\n=== 删除销售记录 ===\n");
    printf("请输入员工号：");
    scanf("%s", employeeId);
    printf("请输入日期(YYYY-MM-DD)：");
    scanf("%s", date);
    
    deleteSaleRecord(saleList, employeeId, date);
    printf("销售记录删除成功！\n");
} 