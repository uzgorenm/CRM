// CRM <Project4.cpp>
// EE 312 Project 4 submission by
// Mehmet Uzgoren
// msu259
// Slip days used: <0>
// Summer 2022
// Copy-Paste the above lines at the top of your submitted files.

#include <stdio.h>
#include <assert.h>
#include "MyString.h"
#include "Invent.h"

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;
Customer Inventory;
void Init();

int findmaxpurchased(String str, int* max, int* maxindex){
    *max = 0;
    *maxindex = 0;
    String bottlestr = StringCreate("Bottles");
    String rattlestr = StringCreate("Rattles");
    String diaperstr = StringCreate("Diapers");
    for(int i=0; i<num_customers; i++){
        if(StringIsEqualTo(&str, &bottlestr)){
            if(customers[i].bottles> *max){
                *max = customers[i].bottles;
                *maxindex = i;
            }
        }
        else if(StringIsEqualTo(&str, &rattlestr)){
            if(customers[i].rattles> *max){
                *max = customers[i].rattles;
                *maxindex = i;
            }
        }
        else if(StringIsEqualTo(&str, &diaperstr)){
            if(customers[i].diapers> *max){
                *max = customers[i].diapers ;
                *maxindex = i;
            }
        }
    }
    StringDestroy(&bottlestr);
    StringDestroy(&rattlestr);
    StringDestroy(&diaperstr);
    if(*max == 0){
        return NULL;
    }
    else{
        return 1;
    }

}

/* you'll probably need several more global variables */
/* and of course, you have a few functions to write */

void Init(){
    Inventory.bottles = 0;
    Inventory.rattles = 0;
    Inventory.diapers = 0;
    for(int i=0; i<MAX_CUSTOMERS; i++){
        customers[i].name.len = 0;
    }
}

int* CheckItemInv(String item){
    String bottlestr = StringCreate("Bottles");
    String rattlestr = StringCreate("Rattles");
    String diaperstr = StringCreate("Diapers");
    if(StringIsEqualTo(&item, &bottlestr)){
        StringDestroy(&bottlestr);
        StringDestroy(&rattlestr);
        StringDestroy(&diaperstr);
        return (&Inventory.bottles);
    }
    else if(StringIsEqualTo(&item, &rattlestr)){
        StringDestroy(&bottlestr);
        StringDestroy(&rattlestr);
        StringDestroy(&diaperstr);
        return (&Inventory.rattles);
    }
    else if(StringIsEqualTo(&item, &diaperstr)){
        StringDestroy(&bottlestr);
        StringDestroy(&rattlestr);
        StringDestroy(&diaperstr);
        return (&Inventory.diapers);
    }
    else{
        StringDestroy(&bottlestr);
        StringDestroy(&rattlestr);
        StringDestroy(&diaperstr);
        return NULL;
    }
}
/* clear the inventory and reset the customer database to empty */
void reset(void) {
	Inventory.bottles = 0;
    Inventory.diapers = 0;
    Inventory.rattles = 0;

    for(int i=0; i<MAX_CUSTOMERS; i++){
        customers[i].bottles = 0;
        customers[i].diapers = 0;
        customers[i].rattles = 0;
        StringDestroy(&customers[i].name);
    }
    num_customers = 0;

}

void processSummarize() {
    printf("There are %d Bottles %d Diapers and %d Rattles in inventory\n", Inventory.bottles, Inventory.diapers, Inventory.rattles);
    printf("we have had a total of %d different customers\n", num_customers);
    int max = 0;
    int maxindex = 0;
    String bottles = StringCreate("Bottles");
    String rattles = StringCreate("Rattles");
    String diapers = StringCreate("Diapers");
    findmaxpurchased(bottles, &max, &maxindex);
    if(findmaxpurchased(bottles, &max, &maxindex) == NULL){
        printf("no one has purchased any Bottles\n");
    }
    else{
        StringPrint(&customers[maxindex].name);
        printf(" has purchased the most Bottles (%d)\n", customers[maxindex].bottles);
    }

    findmaxpurchased(diapers, &max, &maxindex);
    if(findmaxpurchased(diapers, &max, &maxindex) == NULL){
        printf("no one has purchased any Diapers\n");
    }
    else{
        StringPrint(&customers[maxindex].name);
        printf(" has purchased the most Diapers (%d)\n", customers[maxindex].diapers);
    }

    findmaxpurchased(rattles, &max, &maxindex);
    if(findmaxpurchased(rattles, &max, &maxindex) == NULL){
        printf("no one has purchased any Rattles\n");
    }
    else{
        StringPrint(&customers[maxindex].name);
        printf(" has purchased the most Rattles (%d)\n", customers[maxindex].rattles);
    }
    StringDestroy(&bottles);
    StringDestroy(&rattles);
    StringDestroy(&diapers);
}

void processPurchase() {
    String name;
    String item;
    int quantity;
    readString(&name);
    readString(&item);
    readNum(&quantity);
    int nameflag = 0;
    for (int i = 0; i < num_customers; i++) {
        if (customers[i].name.len != 0) {
            if (StringIsEqualTo(&name, &customers[i].name)) {
                nameflag = 1;
                int lak = *CheckItemInv(item);
                if (*CheckItemInv(item) >= quantity && quantity > 0) {
                    *CheckItemInv(item) -= quantity;
                    String bottlestr = StringCreate("Bottles");
                    String rattlestr = StringCreate("Rattles");
                    String diaperstr = StringCreate("Diapers");
                    if (StringIsEqualTo(&item, &bottlestr)) {
                        customers[i].bottles += quantity;
                    } else if (StringIsEqualTo(&item, &rattlestr)) {
                        customers[i].rattles += quantity;
                    } else if (StringIsEqualTo(&item, &diaperstr)) {
                        customers[i].diapers += quantity;
                    }
                    StringDestroy(&bottlestr);
                    StringDestroy(&rattlestr);
                    StringDestroy(&diaperstr);
                }else if(quantity< 0){

                }
                else {
                    printf("Sorry ");
                    StringPrint(&name);
                    printf(", we only have %d ", *CheckItemInv(item));
                    StringPrint(&item);
                    printf("\n");
                }
            }
        }

    }
    if (nameflag == 0) {
        if (*CheckItemInv(item) >= quantity && quantity > 0) {
            *CheckItemInv(item) -= quantity;
            String bottlestr = StringCreate("Bottles");
            String rattlestr = StringCreate("Rattles");
            String diaperstr = StringCreate("Diapers");
            if (StringIsEqualTo(&item, &bottlestr)) {
                customers[num_customers].bottles += quantity;
            } else if (StringIsEqualTo(&item, &rattlestr)) {
                customers[num_customers].rattles += quantity;
            } else if (StringIsEqualTo(&item, &diaperstr)) {
                customers[num_customers].diapers += quantity;
            }
            StringDestroy(&bottlestr);
            StringDestroy(&rattlestr);
            StringDestroy(&diaperstr);
            customers[num_customers].name = StringDup(&name);
            num_customers++;
        }
        else if(quantity < 0){

        }
        else {
            printf("Sorry ");
            StringPrint(&name);
            printf(", we only have %d ", *CheckItemInv(item));
            StringPrint(&item);
            printf("\n");
        }
    }
    StringDestroy(&name);
    StringDestroy(&item);
}

void processInventory() {
    String item;
    int quantity;
    readString(&item);
    readNum(&quantity);
    int* ptr = CheckItemInv(item);
    if(ptr != NULL & quantity >= 0){
        *ptr += quantity;
    }
    StringDestroy(&item);
}
