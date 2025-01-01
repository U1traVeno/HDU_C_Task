#include <stdio.h>
#include <string.h>
#include "product_handler.h"
#include "../../dal.h"

void handleAddProduct(ProductList* list) {
    Product prod;
    printf("\n=== 添加产品信息 ===\n");
    printf("请输入产品号：");
    scanf("%s", prod.id);
    
    if (findProduct(list, prod.id) != NULL) {
        printf("该产品号已存在！\n");
        return;
    }
    
    printf("请输入产品名称：");
    scanf("%s", prod.name);
    printf("请输入产品类型：");
    scanf("%s", prod.type);
    printf("请输入产品价格：");
    scanf("%f", &prod.price);
    
    addProduct(list, prod);
    printf("产品信息添加成功！\n");
}

void handleDisplayAllProducts(const ProductList* list) {
    printf("\n=== 所有产品信息 ===\n");
    ProductNode* current = getAllProducts(list);
    if (current == NULL) {
        printf("暂无产品信息！\n");
        return;
    }
    
    while (current != NULL) {
        printf("产品号：%s\n", current->data.id);
        printf("名称：%s\n", current->data.name);
        printf("类型：%s\n", current->data.type);
        printf("价格：%.2f\n", current->data.price);
        printf("------------------------\n");
        current = current->next;
    }
}

void handleFindProduct(const ProductList* list) {
    char id[20];
    printf("\n=== 查找产品信息 ===\n");
    printf("请输入要查找的产品号：");
    scanf("%s", id);
    
    ProductNode* node = findProduct(list, id);
    if (node != NULL) {
        printf("产品号：%s\n", node->data.id);
        printf("名称：%s\n", node->data.name);
        printf("类型：%s\n", node->data.type);
        printf("价格：%.2f\n", node->data.price);
    } else {
        printf("未找到该产品！\n");
    }
}

void handleUpdateProduct(ProductList* list) {
    char id[20];
    printf("\n=== 修改产品信息 ===\n");
    printf("请输入要修改的产品号：");
    scanf("%s", id);
    
    if (findProduct(list, id) == NULL) {
        printf("未找到该产品！\n");
        return;
    }
    
    Product newData;
    strcpy(newData.id, id);
    printf("请输入新的产品名称：");
    scanf("%s", newData.name);
    printf("请输入新的产品类型：");
    scanf("%s", newData.type);
    printf("请输入新的产品价格：");
    scanf("%f", &newData.price);
    
    updateProduct(list, id, newData);
    printf("产品信息修改成功！\n");
}

void handleDeleteProduct(ProductList* list) {
    char id[20];
    printf("\n=== 删除产品信息 ===\n");
    printf("请输入要删除的产品号：");
    scanf("%s", id);
    
    if (findProduct(list, id) == NULL) {
        printf("未找到该产品！\n");
        return;
    }
    
    deleteProduct(list, id);
    printf("产品信息删除成功！\n");
} 