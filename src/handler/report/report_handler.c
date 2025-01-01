#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "report_handler.h"
#include "../../dal.h"

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