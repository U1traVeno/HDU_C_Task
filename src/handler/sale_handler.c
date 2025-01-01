#include <stdio.h>
#include <string.h>
#include "sale_handler.h"
#include "../dal.h"

// 日期验证函数
static int isValidDate(const char* date) {
    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3) {
        return 0;
    }
    
    if (year < 2000 || year > 2100 ||    // 合理的年份范围
        month < 1 || month > 12 ||        // 月份范围
        day < 1 || day > 31) {           // 日期范围
        return 0;
    }
    
    return 1;
}

void handleAddSaleRecord(SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList) {
    if (saleList == NULL || empList == NULL || prodList == NULL) {
        printf("错误：数据列表未初始化！\n");
        return;
    }

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
    if (record.quantity <= 0) {
        printf("销售数量必须大于0！\n");
        return;
    }
    
    printf("请输入销售日期(YYYY-MM-DD)：");
    scanf("%s", record.date);
    if (!isValidDate(record.date)) {
        printf("无效的日期格式或日期范围！\n");
        return;
    }
    
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
    if (saleList == NULL || empList == NULL || prodList == NULL) {
        printf("错误：数据列表未初始化！\n");
        return;
    }

    SaleRecord oldRecord, newRecord;
    printf("\n=== 修改销售记录 ===\n");
    
    printf("请输入要修改的记录信息：\n");
    printf("员工号：");
    scanf("%s", oldRecord.employeeId);
    printf("日期(YYYY-MM-DD)：");
    scanf("%s", oldRecord.date);
    if (!isValidDate(oldRecord.date)) {
        printf("无效的日期格式或日期范围！\n");
        return;
    }
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
    if (newRecord.quantity <= 0) {
        printf("销售数量必须大于0！\n");
        return;
    }
    
    printf("日期(YYYY-MM-DD)：");
    scanf("%s", newRecord.date);
    if (!isValidDate(newRecord.date)) {
        printf("无效的日期格式或日期范围！\n");
        return;
    }
    
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