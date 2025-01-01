#ifndef DAL_H
#define DAL_H

#include "model.h"

// 员工管理
EmployeeList* createEmployeeList(void);
void addEmployee(EmployeeList* list, Employee employee);
void deleteEmployee(EmployeeList* list, const char* id);
EmployeeNode* findEmployee(const EmployeeList* list, const char* id);
void updateEmployee(EmployeeList* list, const char* id, Employee newData);
EmployeeNode* getAllEmployees(const EmployeeList* list);

// 产品管理
ProductList* createProductList(void);
void addProduct(ProductList* list, Product product);
void deleteProduct(ProductList* list, const char* id);
ProductNode* findProduct(const ProductList* list, const char* id);
void updateProduct(ProductList* list, const char* id, Product newData);
ProductNode* getAllProducts(const ProductList* list);

// 销售记录管理
SaleRecordList* createSaleRecordList(void);
void addSaleRecord(SaleRecordList* list, SaleRecord record);
void deleteSaleRecord(SaleRecordList* list, const char* employeeId, const char* date);
SaleRecordNode* findSaleRecords(const SaleRecordList* list, const char* employeeId, const char* date);
void updateSaleRecord(SaleRecordList* list, SaleRecord oldRecord, SaleRecord newRecord);
SaleRecordNode* getAllSaleRecords(const SaleRecordList* list);

// 文件操作
void saveToFiles(const EmployeeList* empList, const ProductList* prodList, const SaleRecordList* saleList);
void loadFromFiles(EmployeeList* empList, ProductList* prodList, SaleRecordList* saleList);

// 统计功能
ProductSalesSummary* getProductSalesByMonth(const SaleRecordList* saleList, const ProductList* prodList, const char* month, int* count);
EmployeeSalesSummary* getEmployeeSalesByMonth(const SaleRecordList* saleList, const EmployeeList* empList, 
                                             const ProductList* prodList, const char* month, int* count);
EmployeeMonthlyReport* getEmployeeMonthlyReport(const SaleRecordList* saleList, const EmployeeList* empList, 
                                               const ProductList* prodList, const char* employeeId, int* count);

#endif

