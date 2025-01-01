#ifndef EMPLOYEE_HANDLER_H
#define EMPLOYEE_HANDLER_H

#include "../../model.h"

void handleAddEmployee(EmployeeList* list);
void handleDisplayAllEmployees(const EmployeeList* list);
void handleFindEmployee(const EmployeeList* list);
void handleUpdateEmployee(EmployeeList* list);
void handleDeleteEmployee(EmployeeList* list);

#endif 