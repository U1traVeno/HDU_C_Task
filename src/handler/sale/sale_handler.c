#include <stdio.h>
#include <string.h>
#include "sale_handler.h"
#include "../../dal.h"

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