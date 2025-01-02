#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "report_handler.h"
#include "../dal.h"
#include "../utils.h"

// 定义打印产品销售统计的回调函数
static void printProductSalesSummary(void* record, void* context) {
    ProductSalesSummary* summary = (ProductSalesSummary*)record;
    printf("产品号：%s\n", summary->productId);
    printf("产品名称：%s\n", summary->productName);
    printf("销售数量：%d\n", summary->totalQuantity);
    printf("销售金额：%.2f\n", summary->totalAmount);
}

// 定义打印员工销售统计的回调函数
static void printEmployeeSalesSummary(void* record, void* context) {
    EmployeeSalesSummary* summary = (EmployeeSalesSummary*)record;
    printf("员工号：%s\n", summary->employeeId);
    printf("员工姓名：%s\n", summary->employeeName);
    printf("销售金额：%.2f\n", summary->totalAmount);
}

// 定义打印月度销售统计的回调函数
static void printMonthlySalesSummary(void* record, void* context) {
    MonthlySalesSummary* summary = (MonthlySalesSummary*)record;
    printf("月份：%s\n", summary->month);
    printf("销售总额：%.2f\n", summary->totalAmount);
    printf("销售笔数：%d\n", summary->totalTransactions);
}

// 定义打印员工月度报表的回调函数
static void printEmployeeMonthlyReport(void* record, void* context) {
    EmployeeMonthlyReport* report = (EmployeeMonthlyReport*)record;
    printf("月份：%s\n", report->month);
    printf("员工号：%s\n", report->employeeId);
    printf("员工姓名：%s\n", report->employeeName);
    printf("销售总额：%.2f\n", report->totalAmount);
}

// 用于数组形式的getNext方法
static void* getNextArrayRecord(void* current) {
    if (current == NULL) return NULL;
    
    // 将void*转换为char*以进行指针运算
    return (char*)current + sizeof(ProductSalesSummary);
}

// 用于员工销售统计的getNext方法
static void* getNextEmployeeSalesRecord(void* current) {
    if (current == NULL) return NULL;
    return (char*)current + sizeof(EmployeeSalesSummary);
}

// 用于员工月度报表的getNext方法
static void* getNextEmployeeMonthlyRecord(void* current) {
    if (current == NULL) return NULL;
    return (char*)current + sizeof(EmployeeMonthlyReport);
}

// 用于月度销售统计的getNext方法
static void* getNextMonthlySalesRecord(void* current) {
    if (current == NULL) return NULL;
    return (char*)current + sizeof(MonthlySalesSummary);
}

void handleProductSalesReport(const SaleRecordList* saleList, const ProductList* prodList) {
    char month[8];
    printf("\n=== 产品销售统计报表 ===\n");
    printf("请输入统计月份(YYYY-MM)：");
    scanf("%s", month);
    
    // 添加年月验证
    if (!isValidYearMonth(month)) {
        printf("错误：月份格式不正确或无效！\n");
        return;
    }
    
    int count;
    ProductSalesSummary* summary = getProductSalesByMonth(saleList, prodList, month, &count);
    
    if (summary == NULL || count == 0) {
        printf("该月份无销售记录！\n");
        return;
    }

    displayWithPagination(
        summary,                    // 记录列表
        count,                      // 总记录数
        5,                         // 每页显示5条记录
        printProductSalesSummary,  // 打印函数
        getNextArrayRecord,        // 数组形式的getNext函数
        NULL,                      // 不需要上下文
        "产品销售统计报表"          // 标题
    );
    
    free(summary);
}

void handleEmployeeSalesReport(const SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList) {
    char month[8];
    printf("\n=== 员工销售统计报表 ===\n");
    printf("请输入统计月份(YYYY-MM)：");
    scanf("%s", month);
    
    // 添加年月验证
    if (!isValidYearMonth(month)) {
        printf("错误：月份格式不正确或无效！\n");
        return;
    }
    
    int count;
    EmployeeSalesSummary* summary = getEmployeeSalesByMonth(saleList, empList, prodList, month, &count);
    
    if (summary == NULL || count == 0) {
        printf("该月份无销售记录！\n");
        return;
    }

    displayWithPagination(
        summary,                      // 记录列表
        count,                        // 总记录数
        5,                           // 每页显示5条记录
        printEmployeeSalesSummary,   // 打印函数
        getNextEmployeeSalesRecord,  // 数组形式的getNext函数
        NULL,                        // 不需要上下文
        "员工销售统计报表"            // 标题
    );
    
    free(summary);
}

void handleEmployeeMonthlyReport(const SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList) {
    char employeeId[20];
    printf("\n=== 员工月度销售报表 ===\n");
    printf("请输入员工号：");
    scanf("%s", employeeId);
    
    // 验证员工是否存在
    if (findEmployee(empList, employeeId) == NULL) {
        printf("该员工不存在！\n");
        return;
    }
    
    int count;
    EmployeeMonthlyReport* report = getEmployeeMonthlyReport(saleList, empList, prodList, employeeId, &count);
    
    if (report == NULL || count == 0) {
        printf("该员工无月度销售记录！\n");
        return;
    }

    displayWithPagination(
        report,                        // 记录列表
        count,                        // 总记录数
        5,                           // 每页显示5条记录
        printEmployeeMonthlyReport,  // 打印函数
        getNextEmployeeMonthlyRecord, // 数组形式的getNext函数
        NULL,                        // 不需要上下文
        "员工月度销售报表"           // 标题
    );
    
    free(report);
}

void handleMonthlySalesReport(const SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList) {
    char startMonth[8], endMonth[8];
    printf("\n=== 月度销售统计报表 ===\n");
    printf("请输入起始月份(YYYY-MM)：");
    scanf("%s", startMonth);
    
    // 添加起始月份验证
    if (!isValidYearMonth(startMonth)) {
        printf("错误：起始月份格式不正确或无效！\n");
        return;
    }
    
    printf("请输入结束月份(YYYY-MM)：");
    scanf("%s", endMonth);
    
    // 添加结束月份验证
    if (!isValidYearMonth(endMonth)) {
        printf("错误：结束月份格式不正确或无效！\n");
        return;
    }
    
    // 添加起始月份不能大于结束月份的验证
    if (strcmp(startMonth, endMonth) > 0) {
        printf("错误：起始月份不能大于结束月份！\n");
        return;
    }
    
    int count;
    MonthlySalesSummary* summary = getMonthlySales(saleList, empList, prodList, startMonth, endMonth, &count);
    
    if (summary == NULL || count == 0) {
        printf("该时间段无销售记录！\n");
        return;
    }

    displayWithPagination(
        summary,                     // 记录列表
        count,                      // 总记录数
        5,                         // 每页显示5条记录
        printMonthlySalesSummary,  // 打印函数
        getNextMonthlySalesRecord, // 数组形式的getNext函数
        NULL,                      // 不需要上下文
        "月度销售统计报表"          // 标题
    );
    
    free(summary);
} 