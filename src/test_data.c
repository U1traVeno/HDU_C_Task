#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "test_data.h"
#include "dal.h"

// 示例产品数据
static const Product SAMPLE_PRODUCTS[] = {
    {"P001", "iPhone 15", "手机", 6999.0},
    {"P002", "MacBook Pro", "笔记本", 12999.0},
    {"P003", "AirPods Pro", "耳机", 1999.0},
    {"P004", "iPad Air", "平板", 4799.0},
    {"P005", "Apple Watch", "智能手表", 3299.0}
};

// 示例员工数据
static const Employee SAMPLE_EMPLOYEES[] = {
    {"E001", "张三", "男", "1990-05"},
    {"E002", "李四", "女", "1988-11"},
    {"E003", "王五", "男", "1995-03"},
    {"E004", "赵六", "女", "1992-08"},
    {"E005", "孙七", "男", "1993-12"}
};

// 生成随机日期 (2023-01-01 到 2024-03-31)
static void generateRandomDate(char* date) {
    int year = 2023 + (rand() % 2);
    int month = 1 + (rand() % 12);
    int day = 1 + (rand() % 28);  // 简化处理，统一用28天
    
    if (year == 2024 && month > 3) {
        month = 3;  // 限制在2024年3月之前
    }
    
    sprintf(date, "%04d-%02d-%02d", year, month, day);
}

void generateTestData(EmployeeList* empList, ProductList* prodList, SaleRecordList* saleList) {
    srand(time(NULL));  // 初始化随机数生成器
    
    // 添加示例产品
    for (int i = 0; i < sizeof(SAMPLE_PRODUCTS) / sizeof(Product); i++) {
        addProduct(prodList, SAMPLE_PRODUCTS[i]);
    }
    
    // 添加示例员工
    for (int i = 0; i < sizeof(SAMPLE_EMPLOYEES) / sizeof(Employee); i++) {
        addEmployee(empList, SAMPLE_EMPLOYEES[i]);
    }
    
    // 生成300条销售记录
    for (int i = 0; i < 300; i++) {
        SaleRecord record;
        
        // 随机选择员工
        int empIndex = rand() % (sizeof(SAMPLE_EMPLOYEES) / sizeof(Employee));
        strcpy(record.employeeId, SAMPLE_EMPLOYEES[empIndex].id);
        
        // 随机选择产品
        int prodIndex = rand() % (sizeof(SAMPLE_PRODUCTS) / sizeof(Product));
        strcpy(record.productId, SAMPLE_PRODUCTS[prodIndex].id);
        
        // 生成随机数量 (1-10)
        record.quantity = 1 + (rand() % 10);
        
        // 生成随机日期
        generateRandomDate(record.date);
        
        // 添加销售记录
        addSaleRecord(saleList, record);
    }
    
    printf("已生成测试数据：\n");
    printf("- %lu 个产品\n", sizeof(SAMPLE_PRODUCTS) / sizeof(Product));
    printf("- %lu 个员工\n", sizeof(SAMPLE_EMPLOYEES) / sizeof(Employee));
    printf("- 300 条销售记录\n");
}

void addTestData(EmployeeList* empList, ProductList* prodList, SaleRecordList* saleList) {
    // 添加测试数据时确保所有日期格式正确
    // 可以使用 assert 进行验证
    assert(isValidDate("2024-02-29"));  // 确保测试数据中的日期有效
} 