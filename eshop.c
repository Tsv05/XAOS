#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "eshop.h"

#define KATALOGOS_SIZE 20  
#define PELATES 5  
#define ORDERS_ANA_PELATHS 10

Product KATALOGOS[KATALOGOS_SIZE];

void initialize_KATALOGOS(Product KATALOGOS[], int size) {
    for (int i = 0; i < size; i++) {
        snprintf(KATALOGOS[i].description, sizeof(KATALOGOS[i].description), "Product %d", i + 1);
        KATALOGOS[i].price = (i + 1) * 10.0;  
        KATALOGOS[i].item_count = 2; 
    }
}

void process_order(int productIndex, Product KATALOGOS[], int responsePipe) {
    if (KATALOGOS[productIndex].item_count > 0) {
        KATALOGOS[productIndex].item_count--;
        write(responsePipe, "Success", sizeof("Success"));
    } else {
        write(responsePipe, "Out of stock", sizeof("Out of stock"));
    }
    sleep(1);  
}

void generate_report(Product KATALOGOS[], int totalOrders, int successfulOrders, int failedOrders) {
    printf("Summary Report:\n");
    for (int i = 0; i < KATALOGOS_SIZE; i++) {
        printf("Product: %s\nAvailable: %d\n", KATALOGOS[i].description, KATALOGOS[i].item_count);
    }
    printf("Total Orders: %d\nSuccessful Orders: %d\nFailed Orders: %d\n", totalOrders, successfulOrders, failedOrders);
}

int main() {
    int pipeOrder[2];
    int piperesponse[2];

    pipe(pipeOrder);
    pipe(piperesponse);

    initialize_KATALOGOS(KATALOGOS, KATALOGOS_SIZE);

    for (int i = 0; i < PELATES; i++) {
        if (fork() == 0) {  
            for (int j = 0; j < ORDERS_ANA_PELATHS; j++) {
                int productIndex = rand() % KATALOGOS_SIZE;
                write(pipeOrder[1], &productIndex, sizeof(productIndex));
                sleep(1);
                
                char response[50];
                read(piperesponse[0], response, sizeof(response));
                printf("PELATHS %d: %s for %s\n", i + 1, productIndex, response);
            }
            exit(0);
        }
    }

    int totalOrders = 0, successfulOrders = 0, failedOrders = 0;

    while (1) {
        int productIndex;
        if (read(pipeOrder[0], &productIndex, sizeof(productIndex)) > 0) {
            process_order(productIndex, KATALOGOS, piperesponse);
            totalOrders++;
        }
    }
    generate_report(KATALOGOS, totalOrders, successfulOrders, failedOrders);
    
    return 0;
}
