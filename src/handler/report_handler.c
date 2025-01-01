#include <stdio.h>
#include <string.h>
#include "report_handler.h"
#include "../dal.h"
#include "../utils.h"

// 定义打印产品销售统计的回调函数
static void printProductSalesSummary(void* record, void* context) {
    ProductSalesSummary* summary = (ProductSalesSummary*)record;
    printf("产品号：%-10s\n", summary->productId);
    printf("产品名称：%-20s\n", summary->productName);
    printf("销售数量：%-10d\n", summary->totalQuantity);
    printf("销售金额：%-10.2f\n", summary->totalAmount);
}

// 定义打印员工销售统计的回调函数
static void printEmployeeSalesSummary(void* record, void* context) {
    EmployeeSalesSummary* summary = (EmployeeSalesSummary*)record;
    printf("员工号：%-10s\n", summary->employeeId);
    printf("员工姓名：%-20s\n", summary->employeeName);
    printf("销售金额：%-10.2f\n", summary->totalAmount);
}

void handleProductSalesReport(const SaleRecordList* saleList, const ProductList* prodList) {
    char month[8];
    printf("\n=== 产品销售统计报表 ===\n");
    printf("请输入统计月份(YYYY-MM)：");
    scanf("%s", month);
    
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
    
    int count;
    EmployeeSalesSummary* summary = getEmployeeSalesByMonth(saleList, empList, prodList, month, &count);
    
    if (summary == NULL || count == 0) {
        printf("该月份无销售记录！\n");
        return;
    }

    displayWithPagination(
        summary,                    // 记录列表
        count,                      // 总记录数
        5,                         // 每页显示5条记录
        printEmployeeSalesSummary,  // 打印函数
        NULL,                      // 不需要上下文
        "员工销售统计报表"          // 标题
    );
    
    free(summary);
}

void handleEmployeeMonthlyReport(const SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList) {
    char employeeId[20];
    printf("\n=== 员工月度销售报表 ===\n");
    printf("请输入员工号：");
    scanf("%s", employeeId);
    
    int count;
    EmployeeMonthlyReport* report = getEmployeeMonthlyReport(saleList, empList, prodList, employeeId, &count);
    
    if (report == NULL || count == 0) {
        printf("该员工无月度销售记录！\n");
        return;
    }

    displayWithPagination(
        report,                    // 记录列表
        count,                      // 总记录数
        5,                         // 每页显示5条记录
        printEmployeeSalesSummary,  // 打印函数
        NULL,                      // 不需要上下文
        "员工月度销售报表"          // 标题
    );
    
    free(report);
} 