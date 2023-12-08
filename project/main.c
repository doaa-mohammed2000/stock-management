#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

#define normalcolor 15
#define highlightcolor 334

typedef struct products products;
typedef struct category category;

void gotoxy(int x, int y)
{
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct products
{
    char name[20];
    int quantity;
    float price;
    category *cat_name;
};
struct category
{
    char name[20];
    products *product;
    int num_products;
};
category *cat = NULL;
int cat_count = 0;

int IsCategoryExist(const char* categoryName)
{
    for (int i = 0; i < cat_count; i++)
    {
        if (strcmp(cat[i].name, categoryName) == 0)
        {
            return 1;
        }

        return 0;
    }
}

void add_category()
{
    int cat_num, pro_num;
    char c;

    printf("\nEnter The Number Of Categories That You Want To Add: ");
    scanf("%d", &cat_num);

    cat = realloc(cat, (cat_count + cat_num) * sizeof(category));

    for (int i = cat_count; i < cat_count + cat_num; i++)
    {
        char categoryName[50];
        int categoryExists;

        do
        {

            printf("\nPlease Enter The Category %d Name: ",i+1);
            scanf("%s", categoryName);
            categoryExists = IsCategoryExist(categoryName);
            if (categoryExists)
            {
                printf("Category with the same name already exists. Please enter a different name.\n");
            }
        }
        while (categoryExists);
        cat[i].num_products = 0;
        strcpy(cat[i].name, categoryName);
        printf("\nDo You Need To Add Products To This Category? (y/n) ");
        c = getch();
        if (c == 'y')
        {
            printf("\n\nPlease Enter The Number Of Products: ");
            scanf("%d", &pro_num);
            cat[i].product = malloc(pro_num * sizeof(products));
            for (int j = 0; j < pro_num; j++)
            {
                printf("\nPlease Enter The Name Of Product %d: ", j + 1);
                scanf("%s", cat[i].product[j].name);

                printf("\nPlease Enter The Quantity Of Product %d: ", j + 1);
                scanf("%d", &cat[i].product[j].quantity);

                printf("\nPlease Enter The Price Of Product %d: ", j + 1);
                scanf("%f", &cat[i].product[j].price);
            }
            printf("\n*******************************************************");
            cat[i].num_products += pro_num;
        }
        else
        {
            cat[i].product = NULL;
            cat[i].num_products = 0;
        }

        printf("\n\n\t\tCategory $$ %s $$ Added Successfully!!", cat[i].name);
    }

    cat_count += cat_num;
    clear();
}
void display()
{
    gotoxy(50, 3);
    if(cat_count!=0)
    {
        printf("!!! My Menu !!!\n");
        for (int i = 0; i < cat_count; i++)
        {
            printf("\n%d-%s", i + 1, cat[i].name);
            if (cat[i].product != NULL )
            {
                for (int j = 0; j < cat[i].num_products; j++)
                {
                    if (cat[i].product[j].quantity != NULL )
                    {
                        printf("\n  %d.%d Product Name: %s ", i + 1, j + 1, cat[i].product[j].name);
                        printf("\n      Product Quantity %d ",  cat[i].product[j].quantity);
                        printf("\n      Product Price %.2f\n",  cat[i].product[j].price);
                    }
                }
            }
        }
    }
    else
    {
        gotoxy(40, 5);
        printf("You Have Not Any Categories !!!");
    }
}
int IsProductExistInCategory(const char *productName)
{
    for (int i = 0; i < cat_count; i++)
    {
        for(int j=0; j<cat[i].num_products; j++)
        {
            if (strcmp(cat[i].product[j].name, productName) == 0)
            {
                return 1;
            }
        }

        return 0;
    }
}
void add_product()
{
    int index;
    char c;
    int pro_num;

    if (cat_count != 0)
    {
        for (int i = 0; i < cat_count; i++)
        {
            printf("\n%d-%s", i + 1, cat[i].name);

            if (cat[i].product != NULL)
            {
                for (int j = 0; j < cat[i].num_products; j++)
                {
                    printf("\n  %d.%d Product Name: %s ", i + 1, j + 1, cat[i].product[j].name);
                    printf("\n     Product Quantity %d ",  cat[i].product[j].quantity);
                    printf("\n     Product Price %.2f\n",  cat[i].product[j].price);
                }
            }
        }
    }
    else
    {
        printf("You Have Not Any Categories !!!");
        return;
    }
    printf("\nPlease Enter the Index Of The Category You Want To Add In: ");
    scanf(" %d", &index);
    index -= 1;

    if (index >= 0 && index < cat_count)
    {
        printf("\nPlease Enter The Number Of Products: ");
        scanf("%d", &pro_num);

        cat[index].product = realloc(cat[index].product, (cat[index].num_products + pro_num) * sizeof(products));

        for (int j = cat[index].num_products; j < cat[index].num_products + pro_num; j++)
        {
            char productName[50];
            int productExists;

            do
            {
                printf("\nPlease Enter The Name Of Product %d: ", j + 1);
                scanf("%s", productName);
                productExists = IsProductExistInCategory( productName);
                if (productExists)
                {
                    printf("Product with the same name already exists. Please enter a different name.\n");
                }
            }
            while (productExists);
            printf("\nPlease Enter The Quantity Of Product %d: ", j + 1);
            scanf("%d", &cat[index].product[j].quantity);

            printf("\nPlease Enter The Price Of Product %d: ", j + 1);
            scanf("%f", &cat[index].product[j].price);
            strcpy(cat[index].product[j].name, productName);
        }
        cat[index].num_products += pro_num;
        printf("\n\n\t\tProducts Added to Category $$ %s $$ Successfully!!", cat[index].name);
    }
    else
    {
        printf("\nInvalid Category Index!\n");
    }
    clear();
}
void remove_product()
{
    int cat_index, pro_index;
    char c;

    if (cat_count != 0)
    {
        for (int i = 0; i < cat_count; i++)
        {
            printf("\n%d-%s", i + 1, cat[i].name);

            if (cat[i].product != NULL)
            {
                for (int j = 0; j < cat[i].num_products; j++)
                {
                    printf("\n  %d.%d Product Name: %s ", i + 1, j + 1, cat[i].product[j].name);
                    printf("\n    Product Quantity %d ",  cat[i].product[j].quantity);
                    printf("\n    Product Price %.2f\n",  cat[i].product[j].price);
                }
            }
        }
    }
    else
    {
        printf("You Have Not Any Categories !!!");
        return;
    }
    printf("\nPlease Enter the Index Of The Category You Want To Remove From !! ");
    scanf(" %d", &cat_index);
    cat_index -= 1;

    if (cat_index >= 0 && cat_index < cat_count)
    {
        printf("\nPlease Enter The Index Of Product You Want To Remove !! ");
        scanf("%d", &pro_index);
        pro_index -= 1;

        if (pro_index >= 0 && pro_index < cat[cat_index].num_products)
        {
            for (int i = pro_index; i < cat[cat_index].num_products - 1; i++)
            {
                cat[cat_index].product[i] = cat[cat_index].product[i + 1];
            }
            cat[cat_index].num_products--;

            printf("\n\n\t\tProduct Removed From Category $$ %s $$ Successfully!!", cat[cat_index].name);
        }
        else
        {
            printf("\nInvalid Product Index!\n");
        }
    }
    else
    {
        printf("\nInvalid Category Index!\n");
    }
    clear();
}
void move_product()
{
    int cat1_index, cat2_index, pro_index;
    if (cat_count >= 2)
    {
        for (int i = 0; i < cat_count; i++)
        {
            printf("\n%d-%s", i + 1, cat[i].name);

            if (cat[i].product != NULL)
            {
                for (int j = 0; j < cat[i].num_products; j++)
                {
                    printf("\n  %d.%d Product Name: %s ", i + 1, j + 1, cat[i].product[j].name);
                    printf("\n      Product Quantity %d ",  cat[i].product[j].quantity);
                    printf("\n      Product Price %.2f\n",  cat[i].product[j].price);
                }
            }
        }
    }
    else
    {
        printf("You Must Have At Least Two Categories !!!");
        return;
    }
    printf("\nPlease Enter the Index Of The Category You Want To Move From !! ");
    scanf("%d", &cat1_index);
    cat1_index -= 1;

    if (cat1_index >= 0 && cat1_index < cat_count)
    {
        printf("\nPlease Enter The Index Of Product You Want To Move It!! ");
        scanf("%d", &pro_index);
        pro_index -= 1;

        if (pro_index >= 0 && pro_index < cat[cat1_index].num_products)
        {
            printf("\nPlease Enter the Index Of The Category You Want To Move To !! ");
            scanf("%d", &cat2_index);
            cat2_index -= 1;
            cat[cat2_index].product = realloc(cat[cat2_index].product, (cat[cat2_index].num_products + 1) * sizeof(products));
            strcpy(cat[cat2_index].product[cat[cat2_index].num_products].name, cat[cat1_index].product[pro_index].name);
            cat[cat2_index].product[cat[cat2_index].num_products].price = cat[cat1_index].product[pro_index].price;
            cat[cat2_index].product[cat[cat2_index].num_products].quantity = cat[cat1_index].product[pro_index].quantity;
            cat[cat2_index].num_products++;
            for (int i = pro_index; i < cat[cat1_index].num_products - 1; i++)
            {
                cat[cat1_index].product[i] = cat[cat1_index].product[i + 1];
            }
            cat[cat1_index].num_products--;

            printf("\n\n\t\tProduct Moved From Category $$ %s $$ To Category  $$ %s $$ Successfully!!", cat[cat1_index].name, cat[cat2_index].name);
        }
        else
        {
            printf("\nInvalid Product Index!\n");
        }
    }
    else
    {
        printf("\nInvalid Category Index!\n");
    }
    clear();
}
void sell_product()
{
    int cat_index, pro_index, sell_quantity, sell_prod;
    char c, cust_name[10];
    products sell_cat[10];

    if (cat_count > 0)
    {
        for (int i = 0; i < cat_count; i++)
        {
            printf("\n%d-%s", i + 1, cat[i].name);

            if (cat[i].product != NULL)
            {
                for (int j = 0; j < cat[i].num_products; j++)
                {
                    printf("\n  %d.%d Product Name: %s ", i + 1, j + 1, cat[i].product[j].name);
                    printf("\n      Product Quantity %d ", cat[i].product[j].quantity);
                    printf("\n      Product Price %.2f\n", cat[i].product[j].price);
                }
            }
        }
    }
    else
    {
        printf("\nYou Have Not Any Categories !!!");
        return;
    }

    printf("\nPlease Enter The Customer Name: ");
    scanf("%s", cust_name);

    printf("\nPlease Enter The Number Of Products You Will Sell: ");

    if (scanf("%d", &sell_prod) == 1 && sell_prod > 0)
    {
        float totalAmount = 0.0;

        for (int n = 0; n < sell_prod; n++)
        {
            printf("\nPlease Enter The Index Of Category: ");
            scanf("%d", &cat_index);
            cat_index -= 1;
            if (cat_index >= 0 && cat_index < cat_count)
            {
                printf("\nPlease Enter The Product Index: ");
                scanf("%d", &pro_index);
                pro_index -= 1;

                if (pro_index >= 0 && pro_index < cat[cat_index].num_products)
                {
                    printf("\nPlease Enter The Quantity You Want To Sell: ");
                    scanf("%d", &sell_quantity);
                    if (cat[cat_index].product[pro_index].quantity >= sell_quantity)
                    {
                        cat[cat_index].product[pro_index].quantity -= sell_quantity;
                        float productAmount = sell_quantity * cat[cat_index].product[pro_index].price;
                        totalAmount += productAmount;

                        strcpy(sell_cat[n].name, cat[cat_index].product[pro_index].name);
                        sell_cat[n].price = cat[cat_index].product[pro_index].price;
                        sell_cat[n].quantity = sell_quantity;
                    }

                    else if (sell_quantity == cat[cat_index].product[pro_index].quantity)
                    {
                        for (int i = pro_index; i < cat[cat_index].num_products - 1; i++)
                        {
                            cat[cat_index].product[i] = cat[cat_index].product[i + 1];
                        }
                        cat[cat_index].num_products--;
                    }
                    else
                    {
                        printf("Not enough quantity available for sale!\n");
                    }
                }
                else
                {
                    printf("Invalid Product Index !!");
                }
            }
            else
            {
                printf("Invalid Category Index !!");
            }
        }

        printf("\nPlease Press Enter To Display The Invoice!!");
        c = getch();

        if (c == 13)
        {
            system("cls");
            printf("\n\n********** Invoice **********\n");
            printf("Customer Name: %s\n", cust_name);

            for (int y = 0; y < sell_prod; y++)
            {
                printf("\nProduct $$ %s $$ - Quantity: %d - Price: %.2f - Amount: %.2f",
                       sell_cat[y].name, sell_cat[y].quantity,
                       sell_cat[y].price, sell_cat[y].price * sell_cat[y].quantity);
            }

            printf("\n\nTotal Amount: %.2f\n", totalAmount);
            printf("********** End of Invoice **********\n");
        }
    }
    else
    {
        printf("Please Enter A Valid Number!!");
    }

    clear();
}

void clear()
{
    int x;
    while(x=getchar()!='\n' && x!=EOF);
}
int main()
{
    char c;
    gotoxy(33, 10);
    printf("*-*-*-*-* Welcome To My Market *-*-*-*-* ");
    c = getch();

    if (c == 13)
    {
        do
        {
            system("cls");
            gotoxy(5, 5);
            printf(" 1 Display My Products ");
            gotoxy(5, 7);
            printf(" 2 Add Category \n\n");
            gotoxy(5, 9);
            printf(" 3 Add Product \n\n");
            gotoxy(45, 5);
            printf(" 4 Remove Product \n\n");
            gotoxy(45, 7);
            printf(" 5 Sell Product \n\n");
            gotoxy(45, 9);
            printf(" 6 Move Product \n\n");
            gotoxy(30, 11);
            printf(" 7 Exit?");
            gotoxy(0, 15);
            printf("\nEnter Your Choice!! ");
            c = getch();

            switch (c)
            {
            case '1':
                system("cls");
                gotoxy(44, 2);
                printf("***Displaying My Goods***\n");
                display();
                break;
            case '2':
                system("cls");
                gotoxy(44, 2);
                printf("***Adding Categories***\n");
                add_category();
                break;
            case '3':
                system("cls");
                gotoxy(44, 2);
                printf("***Adding Products***\n");
                add_product();
                break;
            case '4':
                system("cls");
                gotoxy(44, 2);
                printf("***Removing Products***\n");
                remove_product();
                break;
            case '5':
                system("cls");
                gotoxy(44, 2);
                printf("*** Selling ***\n");
                sell_product();
                break;
            case '6':
                system("cls");
                gotoxy(44, 2);
                printf("***Moving Products***\n");
                move_product();
                break;
            case '7':
                return 0;

            }
            printf("\nDo you want to continue? (y/n): ");
            c = getch();
        }
        while (c == 'y');

        for (int i = 0; i < cat_count; i++)
        {
            free(cat[i].product);
        }
        free(cat);
    }
    return 0;
}
