#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// 添加一个新的函数类型定义，用于获取下一个节点
typedef void* (*GetNextFunc)(void* node);

// 修改函数签名，添加获取下一个节点的函数
void displayWithPagination(
    void* records,
    int totalRecords,
    int recordsPerPage,
    PrintRecordFunc print,
    GetNextFunc getNext,
    void* context,
    const char* title
) {
    if (totalRecords == 0) {
        printf("暂无记录！\n");
        return;
    }

    int currentPage = 1;
    int totalPages = (totalRecords + recordsPerPage - 1) / recordsPerPage;
    void* current = records;
    
    while (1) {
        system("clear");
        printf("\n=== %s (第 %d/%d 页) ===\n", title, currentPage, totalPages);
        
        // 跳转到当前页的起始记录
        current = records;
        for (int i = 0; i < (currentPage - 1) * recordsPerPage && current != NULL; i++) {
            current = getNext(current);
        }
        
        // 打印当前页的记录
        int recordsOnPage = 0;
        while (current != NULL && recordsOnPage < recordsPerPage) {
            print(current, context);
            printf("------------------------\n");
            current = getNext(current);
            recordsOnPage++;
        }
        
        // 显示导航选项
        printf("\n操作说明：\n");
        printf("n - 下一页\n");
        printf("p - 上一页\n");
        printf("g - 跳转到指定页\n");
        printf("q - 退出\n");
        printf("请选择操作：");
        
        char choice;
        scanf(" %c", &choice);
        
        switch(choice) {
            case 'n':
            case 'N':
                if (currentPage < totalPages) {
                    currentPage++;
                } else {
                    printf("已经是最后一页了！\n");
                    getchar();
                }
                break;
                
            case 'p':
            case 'P':
                if (currentPage > 1) {
                    currentPage--;
                } else {
                    printf("已经是第一页了！\n");
                    getchar();
                }
                break;
                
            case 'g':
            case 'G':
                printf("请输入要跳转的页码(1-%d)：", totalPages);
                int page;
                scanf("%d", &page);
                if (page >= 1 && page <= totalPages) {
                    currentPage = page;
                } else {
                    printf("无效的页码！\n");
                    getchar();
                }
                break;
                
            case 'q':
            case 'Q':
                return;
                
            default:
                printf("无效的选择！\n");
                getchar();
        }
    }
} 