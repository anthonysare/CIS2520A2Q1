//
// Created by Anthony on 10/13/2018.
//

#ifndef INC_2520A2_PROGRAMS_H
#define INC_2520A2_PROGRAMS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




typedef struct car{
    int mileage;
    int expectedReturn;
    char plate[7];
    int list;
}car_t;

typedef struct carList {

    car_t data;
    struct carList *next;

} carList_t;

void pushAvailable(carList_t **head, car_t toAdd);

void pushRented(carList_t **head, car_t toAdd);

void pushRepair(carList_t **head, car_t toAdd);

int popCar(carList_t **head, car_t toPop);

void printList(carList_t *head);

void printCar(car_t car);
void printAll(carList_t *availableHead, carList_t *rentedHead, carList_t *repairHead);

void toFile(carList_t **listHead, char file[]);

void fromFile(carList_t **listHead, char file[]);

double calcCharge(int km);

car_t newCar(char plate[6], int mileage, int expectedReturn);


#endif //INC_2520A2_PROGRAMS_H
