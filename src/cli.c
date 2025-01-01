#include <stdio.h>
#include "cli.h"

void showMainMenu(void) {
    printf("\n=== 销售信息管理系统 ===\n");
    printf("1. 员工管理\n");
    printf("2. 产品管理\n");
    printf("3. 销售记录管理\n");
    printf("4. 统计报表\n");
    printf("0. 退出系统\n");
    printf("请选择功能(0-4)：");
}

void showEmployeeMenu(void) {
    printf("\n=== 员工管理 ===\n");
    printf("1. 添加员工\n");
    printf("2. 显示所有员工\n");
    printf("3. 查找员工\n");
    printf("4. 修改员工信息\n");
    printf("5. 删除员工\n");
    printf("0. 返回主菜单\n");
    printf("请选择功能(0-5)：");
}

void showProductMenu(void) {
    printf("\n=== 产品管理 ===\n");
    printf("1. 添加产品\n");
    printf("2. 显示所有产品\n");
    printf("3. 查找产品\n");
    printf("4. 修改产品信息\n");
    printf("5. 删除产品\n");
    printf("0. 返回主菜单\n");
    printf("请选择功能(0-5)：");
}

void showSaleMenu(void) {
    printf("\n=== 销售记录管理 ===\n");
    printf("1. 添加销售记录\n");
    printf("2. 显示所有销售记录\n");
    printf("3. 查找销售记录\n");
    printf("4. 修改销售记录\n");
    printf("5. 删除销售记录\n");
    printf("0. 返回主菜单\n");
    printf("请选择功能(0-5)：");
}

void showReportMenu(void) {
    printf("\n=== 统计报表 ===\n");
    printf("1. 月度产品销售统计\n");
    printf("2. 月度员工销售统计\n");
    printf("3. 员工月度销售报表\n");
    printf("0. 返回主菜单\n");
    printf("请选择功能(0-3)：");
} 