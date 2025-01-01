#ifndef HANDLER_H
#define HANDLER_H

#include "../model.h"

// 主要管理函数
void handleEmployeeManagement(EmployeeList* empList);
void handleProductManagement(ProductList* prodList);
void handleSaleManagement(SaleRecordList* saleList, EmployeeList* empList, ProductList* prodList);
void handleReportManagement(SaleRecordList* saleList, EmployeeList* empList, ProductList* prodList);

#endif 