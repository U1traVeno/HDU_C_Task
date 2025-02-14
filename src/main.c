#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "model.h"
#include "cli.h"
#include "dal.h"
#include "handler/handler.h"
#include "test_data.h"
#include "utils.h"

int main() {
    // 设置控制台编码
    #ifdef _WIN32
    setConsoleEncoding();
    #endif
    
    // 创建数据结构
    EmployeeList* empList = createEmployeeList();
    ProductList* prodList = createProductList();
    SaleRecordList* saleList = createSaleRecordList();
    
    // 加载数据
    loadFromFiles(empList, prodList, saleList);
    
    // 如果数据为空，生成测试数据
    if (empList->size == 0) {
        printf("检测到数据为空，是否生成测试数据？(y/n)：");
        char choice;
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            generateTestData(empList, prodList, saleList);
        }
    }
    
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