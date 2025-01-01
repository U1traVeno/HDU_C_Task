#include <stdio.h>
#include <string.h>
#include "employee_handler.h"
#include "../dal.h"

void handleAddEmployee(EmployeeList* list) {
    Employee emp;
    printf("\n=== 添加员工信息 ===\n");
    printf("请输入员工号：");
    scanf("%s", emp.id);
    
    if (findEmployee(list, emp.id) != NULL) {
        printf("该员工号已存在！\n");
        return;
    }
    
    printf("请输入姓名：");
    scanf("%s", emp.name);
    printf("请输入性别：");
    scanf("%s", emp.gender);
    printf("请输入出生年月(YYYY-MM)：");
    scanf("%s", emp.birthDate);
    
    addEmployee(list, emp);
    printf("员工信息添加成功！\n");
}

void handleDisplayAllEmployees(const EmployeeList* list) {
    printf("\n=== 所有员工信息 ===\n");
    EmployeeNode* current = getAllEmployees(list);
    if (current == NULL) {
        printf("暂无员工信息！\n");
        return;
    }
    
    while (current != NULL) {
        printf("员工号：%s\n", current->data.id);
        printf("姓名：%s\n", current->data.name);
        printf("性别：%s\n", current->data.gender);
        printf("出生年月：%s\n", current->data.birthDate);
        printf("------------------------\n");
        current = current->next;
    }
}

void handleFindEmployee(const EmployeeList* list) {
    char id[20];
    printf("\n=== 查找员工信息 ===\n");
    printf("请输入要查找的员工号：");
    scanf("%s", id);
    
    EmployeeNode* node = findEmployee(list, id);
    if (node != NULL) {
        printf("员工号：%s\n", node->data.id);
        printf("姓名：%s\n", node->data.name);
        printf("性别：%s\n", node->data.gender);
        printf("出生年月：%s\n", node->data.birthDate);
    } else {
        printf("未找到该员工！\n");
    }
}

void handleUpdateEmployee(EmployeeList* list) {
    char id[20];
    printf("\n=== 修改员工信息 ===\n");
    printf("请输入要修改的员工号：");
    scanf("%s", id);
    
    if (findEmployee(list, id) == NULL) {
        printf("未找到该员工！\n");
        return;
    }
    
    Employee newData;
    strcpy(newData.id, id);
    printf("请输入新的姓名：");
    scanf("%s", newData.name);
    printf("请输入新的性别：");
    scanf("%s", newData.gender);
    printf("请输入新的出生年月(YYYY-MM)：");
    scanf("%s", newData.birthDate);
    
    updateEmployee(list, id, newData);
    printf("员工信息修改成功！\n");
}

void handleDeleteEmployee(EmployeeList* list) {
    char id[20];
    printf("\n=== 删除员工信息 ===\n");
    printf("请输入要删除的员工号：");
    scanf("%s", id);
    
    if (findEmployee(list, id) == NULL) {
        printf("未找到该员工！\n");
        return;
    }
    
    deleteEmployee(list, id);
    printf("员工信息删除成功！\n");
} 