#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define DATABASE_SIZE 100 // Define your desired size for the database
#define WAREHOUSE_SIZE 20
#define IPHONE_SIZE 4
#define MACBOOK_SIZE 3

typedef struct upgrade {
    int price;
    char upgradeType[20];
} Upgrade, *UpgradePTR;

typedef struct {
    int price;
    char version[10];
    char deviceName[20];
    UpgradePTR deviceUpgrades; // Assuming each device can have up to 3 upgrades
} Device;

typedef struct {
    char fName[16];
    char lName[16];
} Personal;

typedef struct {
    Personal name;
    int devicesCount;
    int totalPaid;
    Device ownedDevices[10]; // Assuming a customer can own up to 10 devices
} Customer;

typedef struct {
    int stockIphone;
    int stockMacbook;
    Device iphones[IPHONE_SIZE];
    Device macbooks[MACBOOK_SIZE];
} Warehouse;

typedef struct {
    int phonesSold;
    int laptopsSold;
    int grossSales;
} Profits;

typedef struct store {
    Profits income;
    Warehouse items;
} Store;

typedef struct heap {
	Customer heapCustomers[3];
	int lastNdx;
} Heap;

void initStore(Store* main);
void displayStore(Store main);

void buyDevice(Customer* customer, char device[], int quantity, Store* apple);
void displayCustomers(Customer customers[]);
void initHeap(Heap* main);
void minHeapify(Customer customer[], Heap* main);
void displayPOT(Heap main);

int main() {
	// Creating the store
    Store AppleStore;
    initStore(&AppleStore);
    displayStore(AppleStore);
    Heap CustomerHeap;
    initHeap(&CustomerHeap);
    
    // Customers
	Customer customers[3] = {
		{{"John", "Citizen"}, 0, 0, 0},
		{{"Joker", "The Thief"}, 0, 0, 0},
		{{"Achille", "Lanutan"}, 0, 0, 0},
	};
	
	displayCustomers(customers);
	
	// Customer[0] buys M1 and iPhone 12. 
	buyDevice(&customers[0], "M1", 1, &AppleStore);
    buyDevice(&customers[0], "M2", 1, &AppleStore);
	buyDevice(&customers[2], "12", 1, &AppleStore);
    buyDevice(&customers[1], "13", 1, &AppleStore);
    buyDevice(&customers[1], "M1", 1, &AppleStore);
    buyDevice(&customers[2], "14", 1, &AppleStore);
    buyDevice(&customers[1], "M3", 2, &AppleStore);
    buyDevice(&customers[0], "M3", 1, &AppleStore);
    
    displayCustomers(customers);
    displayCustomerDevices(&customers[0]);
	displayCustomerDevices(&customers[2]);
	
	displayStore(AppleStore);
	
	minHeapify(customers, &CustomerHeap);
	
	displayPOT(CustomerHeap);
	
    return 0;
}

void initStore(Store* main){
	// Initialize profits
    main->income.phonesSold = 0;
    main->income.laptopsSold = 0;
    main->income.grossSales = 0;
    
    // Initialize iPhone data
    Device iphone12 = {1000, "12", "iPhone"};
    Device iphone13 = {1100, "13", "iPhone"};
    Device iphone14 = {1200, "14", "iPhone"};
    Device iphone15 = {1300, "15", "iPhone"};

    main->items.stockIphone = 5;
    main->items.iphones[0] = iphone12;
    main->items.iphones[1] = iphone13;
    main->items.iphones[2] = iphone14;
    main->items.iphones[3] = iphone15;

    // Initialize MacBook data
    Device macbookM1 = {2000, "M1", "MacBook"};
    Device macbookM2 = {2200, "M2", "MacBook"};
    Device macbookM3 = {2400, "M3", "MacBook"};

    main->items.stockMacbook = 10;
    main->items.macbooks[0] = macbookM1;
    main->items.macbooks[1] = macbookM2;
    main->items.macbooks[2] = macbookM3;
    
    printf("\nInitialized Apple store. We're now open for business!");
}
void displayStore(Store main){
	int x;
	printf("\n\nApple Store Gross Sales :: %d", main.income.grossSales);
	printf("\nTotal iPhones sold :: %d", main.income.phonesSold);
	printf("\nTotal laptops sold :: %d", main.income.laptopsSold);
	
	// Display iPhones first
	printf("\n\nDisplaying iPhones...");
	printf("\nCurrent stock available :: %d", main.items.stockIphone);
	printf("\n%-8s", 	"PRICE");
	printf("%-12s", 	"DEVICE");
	printf("%-6s", 		"VERSION");
	if (main.items.iphones > 0){
		for (x = 0 ; x < IPHONE_SIZE ; x++){
			printf("\n%-8d%-12s%-6s%",
				main.items.iphones[x].price,
				main.items.iphones[x].deviceName,
				main.items.iphones[x].version
			);
		}
	} else {
		printf("\niPhone is currently out of stock. Come again another time!");
	}
	
	// Display Macbooks next
	printf("\n\nDisplaying Macbooks...");
	printf("\nCurrent stock available :: %d", main.items.stockMacbook);
	printf("\n%-8s", 	"PRICE");
	printf("%-12s", 	"DEVICE");
	printf("%-6s", 		"VERSION");
	if (main.items.macbooks > 0){
		for (x = 0 ; x < MACBOOK_SIZE ; x++){
			printf("\n%-8d%-12s%-6s%",
				main.items.macbooks[x].price,
				main.items.macbooks[x].deviceName,
				main.items.macbooks[x].version
			);
		}
	} else {
		printf("\nMacbooks are currently out of stock. Come again another time!");
	}
}

void buyDevice(Customer* customer, char device[], int quantity, Store* apple){
	int x, y;
	for (x = 0 ; x < IPHONE_SIZE && strcmp(device, apple->items.iphones[x].version) != 0 ; x++){};
	if (x < IPHONE_SIZE){
		printf("\n%s wishes to buy iPhone %s", customer->name.fName, apple->items.iphones[x].version);
		if (apple->items.stockIphone > 0){
			for (y = 0 ; y < quantity ; y++){
				customer->ownedDevices[customer->devicesCount] = apple->items.iphones[x];
				customer->devicesCount++;
				customer->totalPaid += apple->items.iphones[x].price;
				apple->items.stockIphone--;
				apple->income.phonesSold++;
				apple->income.grossSales += apple->items.iphones[x].price;
				printf("\niPhone purchase successful.");
			}
		}
	} else {
		for (x = 0 ; x < MACBOOK_SIZE && strcmp(device, apple->items.macbooks[x].version) != 0 ; x++){};
		if (x < MACBOOK_SIZE){
			printf("\n%s wishes to buy Macbook %s", customer->name.fName, apple->items.macbooks[x].version);
			if (apple->items.stockMacbook > 0){
				for (y = 0 ; y < quantity ; y++){
					customer->ownedDevices[customer->devicesCount] = apple->items.macbooks[x];
					customer->devicesCount += quantity;
					customer->totalPaid += apple->items.macbooks[x].price;
					apple->items.stockMacbook--;
					apple->income.laptopsSold++;
					apple->income.grossSales += apple->items.macbooks[x].price;
					printf("\nMacbook purchase successful.");
				}
			} else {
				printf("\nCannot proceed purchase of Macbook. No stock available.");
			}
		}
	}
	
}
void displayCustomers(Customer customers[]){
	int x;
	printf("\n\nDisplaying all customers...");
	printf("\n%-12s", 		"First name");
	printf("%-12s", 		"Last name");
	printf("%-16s", 		"Total devices");
	printf("%-12s", 		"Total spent");
	for (x = 0 ; x < 3 ; x++){
		printf("\n%-12s%-12s%-16d%-12d",
				customers[x].name.fName,
				customers[x].name.lName,
				customers[x].devicesCount,
				customers[x].totalPaid
			);
	}
	printf("\n");
}
void displayCustomerDevices(Customer customer){
	int x;
	if (customer.devicesCount > 0){
		printf("\n\nDisplaying %s's devices...", customer.name.fName);
		printf("\nTotal devices   :: %d", customer.devicesCount);
		printf("\nTotal paid 	:: %d", customer.totalPaid);
		printf("\n%-8s", 	"DEVICE");
		printf("%-8s", 		"VERSION");
		printf("%-8s", "PRICE");
		printf("\n%-24s", "------------------------");
		for (x = 0 ; x < customer.devicesCount  ; x++){
			printf("\n%-8s%-8s%-8d",
				customer.ownedDevices[x].deviceName,
				customer.ownedDevices[x].version,
				customer.ownedDevices[x].price
			);
		}
	} else {
		printf("\n%s doesn't have any Apple devices yet.", customer.name.fName);
	}
}
void initHeap(Heap* main){
	main->lastNdx = -1;
	printf("\nInitialized heap.");
}
void minHeapify(Customer customer[], Heap* main){
	int x;
	for (x = 0 ; x < 3 ; x++){
		int currNdx;
		main->lastNdx++;
		currNdx = main->lastNdx;
		main->heapCustomers[currNdx] = customer[x];
		while (currNdx > 0 && main->heapCustomers[(currNdx - 1)/2].totalPaid < customer[x].totalPaid){
			main->heapCustomers[currNdx] = main->heapCustomers[(currNdx - 1)/2];
			currNdx = (currNdx - 1)/2;
			printf("Swapped");
		}
		main->heapCustomers[currNdx] = customer[x];
		printf("\nInserted [%s] into POT.", main->heapCustomers[main->lastNdx].name.fName);
	}
}
void displayPOT(Heap main){
	int x;
	printf("\nDisplaying POT...");
	for (x = 0 ; x < 3 ; x++){
		printf("%d -> ", main.heapCustomers[x].totalPaid);
	}
	printf("NULL\n");
}



