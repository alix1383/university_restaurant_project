#include <stdio.h>

#define taxRate 0.06      // 6%
#define discountRate 0.10 // 10%

typedef struct orderMenuItems
{
    char name[20];
    float price;
} orderMenuItems;

void print_menu_main(int *input);

void print_menu_order(int *input, orderMenuItems *orderMenuItems, int orderMenuItemsCount, int *orders, int *orderCount, float *total);
void print_menu_order_items(orderMenuItems *orderMenuItems, int orderMenuItemsCount);

void print_menu_billing(int *input, float *total);
float calc_tax(float *total);
float calc_discount(float *total);
void print_orders(orderMenuItems *orderMenuItems, int orderMenuItemsCount, int *orders, int orderCount);

int main()
{
    orderMenuItems orderMenuItems[] = {
        {"Burger", 4.99},
        {"Pizza", 4.49},
        {"Pasta", 8.99},
        {"Sandwich", 15.99},
        {"Salad", 1.49}};

    int orderMenuItemsCount = sizeof(orderMenuItems) / sizeof(orderMenuItems[0]);

    // save order ids in orders array
    //! order ids are the index of the orderMenuItems array
    int input = 0, orderCount = 0, orders[100];
    float total = 0.0;

    do
    {
        switch (input)
        {
        case 0:
            // main
            printf("--------------------\n");
            print_menu_main(&input);
            break;

        case 1:
            // order
            printf("--------------------\n");
            print_menu_order(&input, orderMenuItems, orderMenuItemsCount, orders, &orderCount, &total);
            break;
        case 2:
            // billing
            printf("--------------------\n");
            printf("--------------------\n");
            print_orders(orderMenuItems, orderMenuItemsCount, orders, orderCount);
            printf("--------------------\n");
            print_menu_billing(&input, &total);
            input = 0;
            break;
        case 3:
            // reset
            printf("--------------------\n");
            orderCount = 0;
            total = 0.0;
            input = 0;
            break;
        default:
            printf("Invalid Input\n");
            input = 0;
            break;
        }

    } while (input != 4);

    return 0;
}

void print_menu_main(int *input)
{
    printf("\tMain Menu:\n");
    printf("1. Order\n");
    printf("2. Billing Calculation\n");
    printf("3. Reset\n");
    printf("4. Exit\n");

    printf("Enter Number: ");

    scanf("%d", input);
}

void print_menu_order(int *input, orderMenuItems *orderMenuItems, int orderMenuItemsCount, int *orders, int *orderCount, float *total)
{
    int orderInput;
    do
    {
        printf("--------------------\n");
        print_menu_order_items(orderMenuItems, orderMenuItemsCount);
        printf("Enter Order Number: ");
        scanf("%d", &orderInput);

        if (orderInput < 1 || orderInput > orderMenuItemsCount + 1)
        {
            printf("Invalid input. Please try again.\n");
            continue;
        }

        orderInput--;

        if (orderInput == orderMenuItemsCount)
        {
            break;
        }

        // save order id in orders array
        orders[*orderCount] = orderInput;
        *orderCount += 1;
        *total += orderMenuItems[orderInput].price;

    } while (1);

    *input = 0;
}

void print_menu_order_items(orderMenuItems *orderMenuItems, int orderMenuItemsCount)
{
    printf("\tOrder Menu:\n");
    for (int i = 0; i < orderMenuItemsCount; i++)
    {
        printf("%d. %s - $%.2f\n", i + 1, orderMenuItems[i].name, orderMenuItems[i].price);
    }
    printf("%d. Exit\n", orderMenuItemsCount + 1);
}

void print_menu_billing(int *input, float *total)
{
    printf("total: %.2f$\n", *total);

    float tax = calc_tax(total);
    float discount = calc_discount(total);

    printf("Tax: %.2f$\n", tax);
    printf("Discount: %.2f$\n", discount);

    printf("Total Pay: %.2f$\n", (*total + tax) - discount);
    *input = 0;
}

void print_orders(orderMenuItems *orderMenuItems, int orderMenuItemsCount, int *orders, int orderCount)
{
    int count;

    for (int i = 0; i < orderMenuItemsCount; i++)
    {
        count = 0;

        for (int j = 0; j < orderCount; j++)
        {
            if (orders[j] == i)
            {
                count++;
            }
        }

        if (count != 0)
        {
            printf("%s: %d\n", orderMenuItems[i].name, count);
        }
    }
}

float calc_tax(float *total)
{
    return (*total * taxRate);
}

float calc_discount(float *total)
{
    return (*total * discountRate);
}