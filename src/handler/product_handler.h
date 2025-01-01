#ifndef PRODUCT_HANDLER_H
#define PRODUCT_HANDLER_H

#include "../model.h"

void handleAddProduct(ProductList* list);
void handleDisplayAllProducts(const ProductList* list);
void handleFindProduct(const ProductList* list);
void handleUpdateProduct(ProductList* list);
void handleDeleteProduct(ProductList* list);
void handleFindProductsByName(const ProductList* list);

#endif 