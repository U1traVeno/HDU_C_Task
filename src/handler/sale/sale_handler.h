#ifndef SALE_HANDLER_H
#define SALE_HANDLER_H

#include "../../model.h"

void handleAddSaleRecord(SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList);
void handleDisplaySaleRecords(const SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList);
void handleFindSaleRecord(const SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList);
void handleUpdateSaleRecord(SaleRecordList* saleList, const EmployeeList* empList, const ProductList* prodList);
void handleDeleteSaleRecord(SaleRecordList* saleList);

#endif 