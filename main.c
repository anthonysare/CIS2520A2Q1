#include "helper.h"

int main() {
    int input = 0;
    int kmUsed;
    double serviceCharge;
    double totalCharge = 0;
    car_t userCar;
    car_t tempCar;

    carList_t *availableHead = NULL;
    carList_t *rentedHead = NULL;
    carList_t *repairHead = NULL;

    fromFile(&availableHead, "available.bin");
    fromFile(&rentedHead, "rented.bin");
    fromFile(&repairHead, "repair.bin");

    do {
        printf("1. Add a new car to the available-for-rent list\n2. Add a returned car to the available-for-rent list\n"
               "3. Add a returned car to the available-for-rent list\n4. Transfer a car from the repair list to the available-for-rent list"
               "\n5. Rent the first available car\n6. Print all the lists\n7. Quit\n");
        printf("Please enter a transaction code(0-7): ");
        scanf(" %d", &input);
        switch (input) {
            case 1:
                printf("Please enter license plate: ");
                scanf(" %s", userCar.plate);
                printf("Please enter mileage: ");
                scanf(" %d", &userCar.mileage);
                userCar.expectedReturn = 0;
                pushAvailable(&availableHead, userCar);
                printf("Car: %s added to available car list\n", userCar.plate);
                break;
            case 2:
                printf("Please enter license plate: ");
                scanf(" %s", userCar.plate);
                tempCar.mileage = popCar(&rentedHead, userCar);
                if (tempCar.mileage == -1) {
                    printf("Car not found!\n");
                    break;
                }

                do {
                    printf("Please enter mileage: ");
                    scanf(" %d", &userCar.mileage);
                    if (userCar.mileage < tempCar.mileage) {
                        printf("Please enter valid mileage.\n");
                    }
                } while (userCar.mileage < tempCar.mileage);
                kmUsed = userCar.mileage - tempCar.mileage;
                serviceCharge += calcCharge(kmUsed);
                userCar.list = 0;
                pushAvailable(&availableHead, userCar);
                printf("Car %s returned to available list from rented list\n", userCar.plate);
                printf("Service charge: $%.2lf\n", serviceCharge);
                break;
            case 3:
                printf("Please enter license plate: ");
                scanf(" %s", userCar.plate);
                tempCar.mileage = popCar(&rentedHead, userCar);
                if (tempCar.mileage == -1) {
                    printf("Car not found!\n");
                    break;
                }
                do {
                    printf("Please enter mileage: ");
                    scanf(" %d", &userCar.mileage);
                    if (userCar.mileage < tempCar.mileage) {
                        printf("Please enter valid mileage.\n");
                    }
                } while (userCar.mileage < tempCar.mileage);
                kmUsed = userCar.mileage - tempCar.mileage;
                serviceCharge += calcCharge(kmUsed);
                userCar.list = 2;
                pushRepair(&repairHead, userCar);
                printf("Car %s sent to repair list from rented list\n", userCar.plate);
                printf("Service charge: $%.2lf", serviceCharge);
                break;
            case 4:
                printf("Please enter license plate: ");
                scanf(" %s", userCar.plate);
                tempCar.mileage = popCar(&repairHead, userCar);
                if (tempCar.mileage == -1) {
                    printf("Car not found!\n");
                    break;
                }
                userCar.list = 2;
                userCar.mileage = tempCar.mileage;
                pushAvailable(&availableHead, userCar);
                printf("Car %s added to available list from rented list\n", userCar.plate);
                break;
            case 5:
                userCar = (*availableHead).data;
                printf("Car available: ");
                printCar(userCar);
                printf("Please enter expected return date (yymmdd)\n");
                scanf(" %d", &userCar.expectedReturn);
                tempCar.mileage = popCar(&availableHead, userCar);
                if (tempCar.mileage == -1) {
                    printf("Car not found!\n");
                    break;
                }
                userCar.list = 1;
                pushRented(&rentedHead, userCar);
                printf("Car %s transferred from available list to rented list\n", userCar.plate);
                break;
            case 6:
                printAll(availableHead, rentedHead, repairHead);
                break;
            case 7:
                break;
            default:
                printf("Please enter a valid transaction code\n");
                break;
        }
        kmUsed = 0;
        totalCharge += serviceCharge;
        serviceCharge = 0;
    } while (input != 7);
    printf("Total Income: $%.2lf", totalCharge);
    toFile(&availableHead, "available.bin");
    toFile(&rentedHead, "rented.bin");
    toFile(&repairHead, "repair.bin");

}
