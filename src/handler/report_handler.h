#ifndef REPORT_HANDLER_H
#define REPORT_HANDLER_H

#include "../model.h"

void handleProductSalesReport(const SaleRecordList* saleList, const ProductList* prodList);
void handleEmployeeSalesReport(const SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList);
void handleEmployeeMonthlyReport(const SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList);

#endif 