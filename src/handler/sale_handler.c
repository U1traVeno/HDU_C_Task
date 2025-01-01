#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sale_handler.h"
#include "../dal.h"
#include "../utils.h"


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
        printf("错误：日期格式不正确或日期无效！\n");
        return;
    }
    
    addSaleRecord(saleList, record);
    printf("销售记录添加成功！\n");
}

// 定义打印单个销售记录的回调函数
static void printSaleRecord(void* record, void* context) {
    SaleRecordNode* saleRecord = (SaleRecordNode*)record;
    struct {
        const EmployeeList* empList;
        const ProductList* prodList;
    }* ctx = context;
    
    EmployeeNode* emp = findEmployee(ctx->empList, saleRecord->data.employeeId);
    ProductNode* prod = findProduct(ctx->prodList, saleRecord->data.productId);
    
    printf("日期：%s\n", saleRecord->data.date);
    printf("员工：%s (%s)\n", emp ? emp->data.name : "未知", saleRecord->data.employeeId);
    printf("产品：%s (%s)\n", prod ? prod->data.name : "未知", saleRecord->data.productId);
    printf("数量：%d\n", saleRecord->data.quantity);
    if (prod) {
        printf("金额：%.2f\n", saleRecord->data.quantity * prod->data.price);
    }
}

// 获取下一个销售记录节点的函数
static void* getNextSaleRecord(void* node) {
    return ((SaleRecordNode*)node)->next;
}

void handleDisplaySaleRecords(const SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList) {
    if (saleList == NULL || saleList->head == NULL) {
        printf("暂无销售记录！\n");
        return;
    }

    struct {
        const EmployeeList* empList;
        const ProductList* prodList;
    } context = {empList, prodList};

    displayWithPagination(
        saleList->head,       // 记录列表
        saleList->size,       // 总记录数
        5,                    // 每页显示5条记录
        printSaleRecord,      // 打印函数
        getNextSaleRecord,    // 获取下一个节点的函数
        &context,             // 上下文数据
        "所有销售记录"        // 标题
    );
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