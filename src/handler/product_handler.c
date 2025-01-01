#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product_handler.h"
#include "../dal.h"
#include "../utils.h"

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

// 定义打印单个产品记录的回调函数
static void printProductRecord(void* record, void* context) {
    ProductNode* prod = (ProductNode*)record;
    printf("产品号：%s\n", prod->data.id);
    printf("名称：%s\n", prod->data.name);
    printf("类型：%s\n", prod->data.type);
    printf("价格：%.2f\n", prod->data.price);
}

// 获取下一个产品节点的函数
static void* getNextProduct(void* node) {
    return ((ProductNode*)node)->next;
}

void handleDisplayAllProducts(const ProductList* list) {
    if (list == NULL || list->head == NULL) {
        printf("暂无产品信息！\n");
        return;
    }

    displayWithPagination(
        list->head,           // 记录列表
        list->size,           // 总记录数
        5,                    // 每页显示5条记录
        printProductRecord,   // 打印函数
        getNextProduct,       // 获取下一个节点的函数
        NULL,                // 不需要上下文
        "所有产品信息"        // 标题
    );
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

void handleFindProductsByName(const ProductList* list) {
    char name[50];
    printf("\n=== 按名称查找产品 ===\n");
    printf("请输入要查找的产品名称（支持模糊查找）：");
    scanf("%s", name);
    
    ProductList* results = findProductsByName(list, name);
    if (results == NULL || results->size == 0) {
        printf("未找到匹配的产品！\n");
        if (results != NULL) {
            free(results);
        }
        return;
    }
    
    printf("\n找到 %d 个匹配的产品：\n", results->size);
    displayWithPagination(
        results->head,         // 记录列表
        results->size,         // 总记录数
        5,                     // 每页显示5条记录
        printProductRecord,    // 打印函数
        getNextProduct,        // 获取下一个节点的函数
        NULL,                  // 不需要上下文
        "查找结果"             // 标题
    );
    
    // 清理内存
    ProductNode* current = results->head;
    while (current != NULL) {
        ProductNode* next = current->next;
        free(current);
        current = next;
    }
    free(results);
} 