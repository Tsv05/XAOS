#ifndef ESHOP_H  
#define ESHOP_H

typedef struct {
    char description[50];
    float price;
    int item_count;
} Product;

void initialize_katalogos(Product katalogos[], int size);
void process_order(int productIndex, Product katalogos[], int responsePipe);
void generate_report(Product katalogos[], int totalOrders, int successfulOrders, int failedOrders);

#endif
