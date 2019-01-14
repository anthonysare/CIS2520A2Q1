//
// Created by Anthony on 10/13/2018.
//
#include <ctype.h>
#include "helper.h"

/**
 * Fills a car struct with the given parameters
 * @param plate License plate number with 7 chars
 * @param mileage  Mileage of car
 * @param expectedReturn Expected return date in yymmdd format
 * @return the filled car struct
 */
car_t newCar(char plate[7], int mileage, int expectedReturn) {
    car_t toCreate;
    strcpy(toCreate.plate, plate);
    toCreate.mileage = mileage;
    toCreate.expectedReturn = expectedReturn;
    toCreate.list = 0;
    return toCreate;
}
/**
 * Prints the car specified by the parameter
 * @param car Car struct to be printed
 */
void printCar(car_t car) {
    printf("Plate no: %s - Mileage: %d - ExpectedReturn: %d List: %d\n",
           car.plate, car.mileage, car.expectedReturn, car.list);
}

/**
 * Pushes the given car to the available-for-rent list in order of descending mileage
 * @param head pointer to head of list
 * @param toAdd car to add to list
 */
void pushAvailable(carList_t **head, car_t toAdd) {
    //Making node of car to add
    carList_t *addCar;
    addCar = malloc(sizeof(carList_t));
    addCar->data = toAdd;
    addCar->next = NULL;
    addCar->data.list = 0;

    //Making node to iterate through list
    carList_t *current;
    current = *head;

    //If list is empty make head equal to given car
    if (*head == NULL) {
        *head = addCar;
    //If the head mileage is greater than the new car mileage, make new car the head
    } else if ((*head)->data.mileage >= addCar->data.mileage) {
        addCar->next = *head;
        *head = addCar;
    //Iterate through list until ordered spot is found and push new car
    } else {
        while (current->next != NULL && current->next->data.mileage <= addCar->data.mileage) {
            current = current->next;
        }
        addCar->next = current->next;
        current->next = addCar;
    }
}

/**
 * Push car to rented list in descending order of the date
 * @param head pointer to head of rented list
 * @param toAdd car to add to rented list
 */
void pushRented(carList_t **head, car_t toAdd) {
    //Making node of car to add
    carList_t *addCar;
    addCar = malloc(sizeof(carList_t));
    addCar->data = toAdd;
    addCar->next = NULL;
    addCar->data.list = 1;

    //Making node to iterate through list
    carList_t *current;
    current = *head;

    //If list is empty make new car the head
    if (*head == NULL) {
        *head = addCar;
    //If the head date is greater than the new date make new car the head
    } else if ((*head)->data.expectedReturn >= addCar->data.expectedReturn) {
        addCar->next = *head;
        *head = addCar;
    //Iterate through the list until ordred spot is found and push new car
    } else {
        while (current->next != NULL && current->next->data.expectedReturn <= addCar->data.expectedReturn) {
            current = current->next;
        }
        addCar->next = current->next;
        current->next = addCar;
    }
}

/**
 * Add the given car to the repair list
 * @param head pointer to head of repair list
 * @param toAdd car to add to repair list
 */
void pushRepair(carList_t **head, car_t toAdd) {
    //Making node of car to add
    carList_t *addCar;
    addCar = malloc(sizeof(carList_t));
    addCar->data = toAdd;
    addCar->next = NULL;
    addCar->data.list = 2;

    //If head is empty make new car the head
    if (*head == NULL) {
        *head = addCar;
    //Push to list
    } else {
        addCar->next = *head;
        *head = addCar;
    }
}

/**
 * Removes the given car from the given list
 * @param head pointer to head of list with car to remove
 * @param toPop car to remove from the list
 * @return returns the mileage of the car or -1 if not found
 */
int popCar(carList_t **head, car_t toPop){
    //Making Car, temp and current nodes
    carList_t *temp;
    carList_t *current;
    current = *head;
    car_t toReturn;
    toReturn.mileage=-1;
    temp = NULL;
    //If given car is at head pop from list
    if(strcmp((*head)->data.plate, toPop.plate)== 0){

        toReturn = (*head)->data;
        temp= (*head)->next;
        free(*head);
        *head = temp;
        return toReturn.mileage;
    }
    //Iterate through linked list comparing plates
    while(current->next!=NULL){
        //If current node's plate is equal to given cars plate remove from list
        if (strcmp(current->next->data.plate, toPop.plate) == 0){
            temp = current->next;
            toReturn = temp->data;
            current->next = temp->next;
            free(temp);
            return toReturn.mileage;
        }
        current = current->next;
    }
//    while(strcmp(current->next->data.plate, toPop.plate) != 0){
//        if(current->next == NULL){
//            return -1;
//        }
//
//        current = current->next;
//    }
    return -1;
}

/**
 * Calculate the service charge
 * @param km Kilometre difference of mileage
 * @return Service charge
 */
double calcCharge(int km){
    double charge =40;
    km -=100;
    if(km>0){
        charge += km*0.15;
    }
    return charge;
}

/**
 * Prints the given linked list
 * @param head pointer to head of linked list to print
 */
void printList(carList_t *head) {
    carList_t *current = head;
    while (current != NULL) {
        printCar(current->data);
        current = current->next;
    }
}

/**
 * Prints all three linked lists with formatting
 * @param availableHead Pointer to head of available-to-rent list
 * @param rentedHead  Pointer to head of rented list
 * @param repairHead  Pointer to head of repair list
 */
void printAll(carList_t *availableHead, carList_t *rentedHead, carList_t *repairHead){
    carList_t *current;
    printf("Available: \n");
    current = availableHead;
    while (current != NULL) {
        printf("Plate: %s - Mileage: %d\n", current->data.plate, current->data.mileage);
        current = current->next;
    }
    printf("Rented: \n");
    current = rentedHead;
    while (current != NULL) {
        printf("Plate: %s - Mileage: %d - Expected Return: %d\n", current->data.plate, current->data.mileage, current->data.expectedReturn);
        current = current->next;
    }
    printf("In for repair: \n");
    current = repairHead;
    while (current != NULL) {
        printf("Plate: %s - Mileage: %d\n", current->data.plate, current->data.mileage);
        current = current->next;
    }
}

/**
 * Stores the given list in the given file
 * @param listHead Pointer to head of linked list of the list to store
 * @param file name of file to store list
 */
void toFile(carList_t **listHead, char file[]) {
    //File pointer
    FILE *fptr;
    fptr = fopen(file, "wb");

    //Current node to iterate through linked list
    carList_t *current;
    current = *listHead;

    //Iterate through linked list and add values
    while (current != NULL) {
        fwrite(&current->data, sizeof(struct car), 1, fptr);
        current = current->next;
    }
    fclose(fptr);
}

/**
 * Stores the given linked list from the given file
 * @param listHead Pointer to head of linked list to store from file
 * @param file name of file to store list
 */
void fromFile(carList_t **listHead, char file[]) {
    //Making temp node for cars to add
    car_t addCar;

    //Making File Pointer
    FILE *fptr;
    fptr = fopen(file, "rb");

    //Checking if file exists
    if (fptr == NULL) {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }
    //Iterate through list pushing to respective linked list
    while (fread(&addCar, sizeof(struct car), 1, fptr)) {
        switch (addCar.list) {

            case 0:
                pushAvailable(listHead, addCar);
                break;
            case 1:
                pushRented(listHead, addCar);
                break;
            case 2:
                pushRepair(listHead, addCar);
                break;
            default:
                printf("List not found for car: ");
                printCar(addCar);
                break;

        }
    }
    fclose(fptr);
}

