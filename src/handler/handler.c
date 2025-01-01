#include <stdio.h>
#include "handler.h"
#include "../cli.h"
#include "employee_handler.h"
#include "product_handler.h"
#include "sale_handler.h"
#include "report_handler.h"

void handleEmployeeManagement(EmployeeList* empList) {
    int choice;
    do {
        showEmployeeMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: handleAddEmployee(empList); break;
            case 2: handleDisplayAllEmployees(empList); break;
            case 3: handleFindEmployee(empList); break;
            case 4: handleUpdateEmployee(empList); break;
            case 5: handleDeleteEmployee(empList); break;
            case 0: break;
            default: printf("无效的选择！\n");
        }
    } while (choice != 0);
}

void handleProductManagement(ProductList* prodList) {
    int choice;
    do {
        showProductMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: handleAddProduct(prodList); break;
            case 2: handleDisplayAllProducts(prodList); break;
            case 3: handleFindProduct(prodList); break;
            case 4: handleUpdateProduct(prodList); break;
            case 5: handleDeleteProduct(prodList); break;
            case 0: break;
            default: printf("无效的选择！\n");
        }
    } while (choice != 0);
}

void handleSaleManagement(SaleRecordList* saleList, EmployeeList* empList, ProductList* prodList) {
    int choice;
    do {
        showSaleMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: handleAddSaleRecord(saleList, empList, prodList); break;
            case 2: handleDisplaySaleRecords(saleList, empList, prodList); break;
            case 3: handleFindSaleRecord(saleList, empList, prodList); break;
            case 4: handleUpdateSaleRecord(saleList, empList, prodList); break;
            case 5: handleDeleteSaleRecord(saleList); break;
            case 0: break;
            default: printf("无效的选择！\n");
        }
    } while (choice != 0);
}

void handleReportManagement(SaleRecordList* saleList, EmployeeList* empList, ProductList* prodList) {
    int choice;
    do {
        showReportMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: handleProductSalesReport(saleList, prodList); break;
            case 2: handleEmployeeSalesReport(saleList, empList, prodList); break;
            case 3: handleEmployeeMonthlyReport(saleList, empList, prodList); break;
            case 0: break;
            default: printf("无效的选择！\n");
        }
    } while (choice != 0);
} 