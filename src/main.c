#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "cli.h"
#include "dal.h"
#include "handler.h"

void handleEmployeeManagement(EmployeeList* empList) {
    int choice;
    do {
        showEmployeeMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                handleAddEmployee(empList);
                break;
            case 2:
                handleDisplayAllEmployees(empList);
                break;
            case 3:
                handleFindEmployee(empList);
                break;
            case 4:
                handleUpdateEmployee(empList);
                break;
            case 5:
                handleDeleteEmployee(empList);
                break;
            case 0:
                break;
            default:
                printf("无效的选择！\n");
        }
    } while (choice != 0);
}

void handleProductManagement(ProductList* prodList) {
    int choice;
    do {
        showProductMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                handleAddProduct(prodList);
                break;
            case 2:
                handleDisplayAllProducts(prodList);
                break;
            case 3:
                handleFindProduct(prodList);
                break;
            case 4:
                handleUpdateProduct(prodList);
                break;
            case 5:
                handleDeleteProduct(prodList);
                break;
            case 0:
                break;
            default:
                printf("无效的选择！\n");
        }
    } while (choice != 0);
}

void handleSaleManagement(SaleRecordList* saleList, EmployeeList* empList, ProductList* prodList) {
    int choice;
    do {
        showSaleMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                handleAddSaleRecord(saleList, empList, prodList);
                break;
            case 2:
                handleDisplaySaleRecords(saleList, empList, prodList);
                break;
            case 3:
                handleFindSaleRecord(saleList, empList, prodList);
                break;
            case 4:
                handleUpdateSaleRecord(saleList, empList, prodList);
                break;
            case 5:
                handleDeleteSaleRecord(saleList);
                break;
            case 0:
                break;
            default:
                printf("无效的选择！\n");
        }
    } while (choice != 0);
}

void handleReportManagement(SaleRecordList* saleList, EmployeeList* empList, ProductList* prodList) {
    int choice;
    do {
        showReportMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                handleProductSalesReport(saleList, prodList);
                break;
            case 2:
                handleEmployeeSalesReport(saleList, empList, prodList);
                break;
            case 3:
                handleEmployeeMonthlyReport(saleList, empList, prodList);
                break;
            case 0:
                break;
            default:
                printf("无效的选择！\n");
        }
    } while (choice != 0);
}

int main() {
    // 创建数据结构
    EmployeeList* empList = createEmployeeList();
    ProductList* prodList = createProductList();
    SaleRecordList* saleList = createSaleRecordList();
    
    // 加载数据
    loadFromFiles(empList, prodList, saleList);
    
    int choice;
    do {
        showMainMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                handleEmployeeManagement(empList);
                break;
            case 2:
                handleProductManagement(prodList);
                break;
            case 3:
                handleSaleManagement(saleList, empList, prodList);
                break;
            case 4:
                handleReportManagement(saleList, empList, prodList);
                break;
            case 0:
                printf("正在保存数据...\n");
                saveToFiles(empList, prodList, saleList);
                printf("感谢使用，再见！\n");
                break;
            default:
                printf("无效的选择！\n");
        }
    } while (choice != 0);
    
    // 释放内存
    while (empList->head != NULL) {
        EmployeeNode* temp = empList->head;
        empList->head = empList->head->next;
        free(temp);
    }
    free(empList);
    
    while (prodList->head != NULL) {
        ProductNode* temp = prodList->head;
        prodList->head = prodList->head->next;
        free(temp);
    }
    free(prodList);
    
    while (saleList->head != NULL) {
        SaleRecordNode* temp = saleList->head;
        saleList->head = saleList->head->next;
        free(temp);
    }
    free(saleList);
    
    return 0;
} 