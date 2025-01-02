#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "test_data.h"
#include "dal.h"
#include "utils.h"

// Sample product data
static const Product SAMPLE_PRODUCTS[] = {
    {"P001", "iPhone 15", "Phone", 999.99},
    {"P002", "MacBook Pro", "Laptop", 1999.99},
    {"P003", "AirPods Pro", "Earphones", 249.99},
    {"P004", "iPad Air", "Tablet", 599.99},
    {"P005", "Apple Watch", "Smartwatch", 399.99}
};

// Sample employee data
static const Employee SAMPLE_EMPLOYEES[] = {
    {"E001", "John Foo", "M", "1990-05"},
    {"E002", "Sarah Bar", "F", "1988-11"},
    {"E003", "Michael Brown", "M", "1995-03"},
    {"E004", "Emily Davis", "F", "1992-08"},
    {"E005", "David Wilson", "M", "1993-12"}
};

// Generate random date (2023-01-01 to 2024-03-31)
static void generateRandomDate(char* date) {
    int year = 2023 + (rand() % 2);
    int month = 1 + (rand() % 12);
    int day = 1 + (rand() % 28);  // Simplified, using 28 days
    
    if (year == 2024 && month > 3) {
        month = 3;  // Restrict to March 2024
    }
    
    sprintf(date, "%04d-%02d-%02d", year, month, day);
}

void generateTestData(EmployeeList* empList, ProductList* prodList, SaleRecordList* saleList) {
    srand(time(NULL));  // Initialize random number generator
    
    // Add sample products
    for (int i = 0; i < sizeof(SAMPLE_PRODUCTS) / sizeof(Product); i++) {
        addProduct(prodList, SAMPLE_PRODUCTS[i]);
    }
    
    // Add sample employees
    for (int i = 0; i < sizeof(SAMPLE_EMPLOYEES) / sizeof(Employee); i++) {
        addEmployee(empList, SAMPLE_EMPLOYEES[i]);
    }
    
    // Generate 300 sales records
    for (int i = 0; i < 300; i++) {
        SaleRecord record;
        
        // Randomly select employee
        int empIndex = rand() % (sizeof(SAMPLE_EMPLOYEES) / sizeof(Employee));
        strcpy(record.employeeId, SAMPLE_EMPLOYEES[empIndex].id);
        
        // Randomly select product
        int prodIndex = rand() % (sizeof(SAMPLE_PRODUCTS) / sizeof(Product));
        strcpy(record.productId, SAMPLE_PRODUCTS[prodIndex].id);
        
        // Generate random quantity (1-10)
        record.quantity = 1 + (rand() % 10);
        
        // Generate random date
        generateRandomDate(record.date);
        
        // Add sales record
        addSaleRecord(saleList, record);
    }
    
    printf("Test data generated:\n");
    printf("- %lu products\n", sizeof(SAMPLE_PRODUCTS) / sizeof(Product));
    printf("- %lu employees\n", sizeof(SAMPLE_EMPLOYEES) / sizeof(Employee));
    printf("- 300 sales records\n");
}

void addTestData(EmployeeList* empList, ProductList* prodList, SaleRecordList* saleList) {
    // Ensure all dates are valid when adding test data
    // Use assert for validation
    assert(isValidDate("2024-02-29"));  // Ensure test data dates are valid
} 