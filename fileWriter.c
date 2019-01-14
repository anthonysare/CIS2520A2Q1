#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "helper.h"



int main() {
    carList_t *availableHead = NULL;
    carList_t *rentedHead = NULL;
    carList_t *repairHead = NULL;


    car_t car1 = newCar("AVA0001", 124000, 0);
    car_t car2 = newCar("AVA0002", 78000, 0);
    car_t car4 = newCar("AVA0003", 233000, 0);
    car_t car3 = newCar("AVA0004", 30000, 0);
    car_t car5 = newCar("AVA0005", 68000, 0);

    car_t carr1 = newCar("REN0001", 143000, 181018);
    car_t carr2 = newCar("REN0002", 133000, 181104);
    car_t carr3 = newCar("REN0003", 101010, 181002);
    car_t carr4 = newCar("REN0004", 200000, 181126);
    car_t carr5 = newCar("REN0005", 128000, 181103);

    car_t carre1 = newCar("REP0001", 10200, 0);
    car_t carre2 = newCar("REP0002", 345000, 0);
    car_t carre3 = newCar("REP0003", 212000, 0);
    car_t carre4 = newCar("REP0004", 121212, 0);
    car_t carre5 = newCar("REP0005", 202020, 0);

    pushAvailable(&availableHead, car1);
    pushAvailable(&availableHead,car2);
    pushAvailable(&availableHead,car3);
    pushAvailable(&availableHead,car4);
    pushAvailable(&availableHead, car5);

    pushRented(&rentedHead, carr1);
    pushRented(&rentedHead, carr2);
    pushRented(&rentedHead, carr3);
    pushRented(&rentedHead, carr4);
    pushRented(&rentedHead, carr5);

    pushRepair(&repairHead, carre1);
    pushRepair(&repairHead, carre2);
    pushRepair(&repairHead, carre3);
    pushRepair(&repairHead, carre4);
    pushRepair(&repairHead, carre5);


    toFile(&availableHead, "available.bin");
    toFile(&rentedHead, "rented.bin");
    toFile(&repairHead, "repair.bin");

    printList(availableHead);
    printList(rentedHead);
    printList(repairHead);


    printf("Finished\n");
    return 0;
}

