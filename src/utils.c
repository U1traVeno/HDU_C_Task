#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void displayWithPagination(
    void* records,
    int totalRecords,
    int recordsPerPage,
    PrintRecordFunc print,
    void* context,
    const char* title
) {
    if (totalRecords == 0) {
        printf("暂无记录！\n");
        return;
    }

    int currentPage = 1;
    int totalPages = (totalRecords + recordsPerPage - 1) / recordsPerPage;
    
    while (1) {
        system("clear");  // Linux/Unix 系统使用 clear，Windows 系统使用 cls
        printf("\n=== %s (第 %d/%d 页) ===\n", title, currentPage, totalPages);
        
        // 计算当前页的起始和结束索引
        int startIndex = (currentPage - 1) * recordsPerPage;
        int endIndex = startIndex + recordsPerPage;
        if (endIndex > totalRecords) {
            endIndex = totalRecords;
        }
        
        // 打印当前页的记录
        for (int i = startIndex; i < endIndex; i++) {
            print(records, context);  // 调用回调函数打印记录
            printf("------------------------\n");
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