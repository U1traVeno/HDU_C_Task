#ifndef HANDLER_H
#define HANDLER_H

#include "model.h"

// 员工管理
void handleAddEmployee(EmployeeList* list);
void handleDisplayAllEmployees(const EmployeeList* list);
void handleFindEmployee(const EmployeeList* list);
void handleUpdateEmployee(EmployeeList* list);
void handleDeleteEmployee(EmployeeList* list);

// 产品管理
void handleAddProduct(ProductList* list);
void handleDisplayAllProducts(const ProductList* list);
void handleFindProduct(const ProductList* list);
void handleUpdateProduct(ProductList* list);
void handleDeleteProduct(ProductList* list);

// 销售记录管理
void handleAddSaleRecord(SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList);
void handleDisplaySaleRecords(const SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList);
void handleFindSaleRecord(const SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList);
void handleUpdateSaleRecord(SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList);
void handleDeleteSaleRecord(SaleRecordList* saleList);

// 统计报表
void handleProductSalesReport(const SaleRecordList* saleList, const ProductList* prodList);
void handleEmployeeSalesReport(const SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList);
void handleEmployeeMonthlyReport(const SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList);

#endif 