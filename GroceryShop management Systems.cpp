#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define MAX_SIZE 100
struct item *getAddress(char name[]);
struct item
{
    int id;
    char pName[MAX_SIZE];
    double price;
    int quantity;
    struct item *next;
}*head = NULL;
void menuForAdmin() // add products, log in
{
    system("color 70");
    int n;
    logIn();
    while(1)
    {
        system("cls");
        system("COLOR 02");
        printf("\n =================================================================================================================\n");
        printf("\n\t\t\t\t\t ----------MENU----------\n\n");
        printf(" =================================================================================================================\n");
        printf("\n\t1.ADD PRODUCTS.");
        printf("\n\t2.DISPLAY PRODUCT LIST.");
        printf("\n\t3.FOR BACK.\n");
        printf("\n\tENTER-->> ");
        scanf("%d", &n);
        if(n == 1)
        {
            addProduct();
        }
        else if(n == 2)
        {
            displayProducts();
        }
        else if(n == 3)
            return;
        else
        {
            printf("\nPlease enter correct option!\n");
            system("pause");
        }
    }
}
void CustomerLogIn()
{
    system("cls");
    system("COLOR 0E");
    char email[MAX_SIZE];
    char pass[MAX_SIZE];
    printf("\n\t\t\t\t\t :::::::::::::::: LOGIN :::::::::::::::::\n");
    printf("\n\t\t\t\t\t Enter Your mail: ");
//getchar();
    gets(email);
    printf("\n\t\t\t\t\t Enter Password: ");
    gets(pass);
    strcat(email, ".txt");
    FILE *fp = fopen(email, "r");
    if(fp == NULL)
    {
        printf("\nYou have not any account !\n");
        system("pause");
        return;
    }
    char temp[MAX_SIZE], ch;
    int i = 0;
    ch = fgetc(fp);
    temp[i] = ch;
    while(ch != EOF)
    {
        ch = fgetc(fp);
        temp[++i] = ch;
    }
    temp[i] = '\0';
    if(strcmp(temp, pass) == 0)
    {
        menuForCustomer();
    }
    else
    {
        system("cls");
        system("COLOR 04");
        printf("\n\n\n\n\n\n\t\t\t\t\t Email/Password is wrong! Try again\n\n");
        system("pause");
        CustomerLogIn(); // You can delete this line
    }
}
void buyProducts()
{
    system("cls");
    displayProducts();
    if(head == NULL)
        return ;
    char name[MAX_SIZE];
    int q;
    printf("\nEnter product name and quantity to buy\n\n");
    printf("Name: ");
    getchar();
    gets(name);
    printf("Quantity: ");
    scanf("%d", &q);
    struct item *current = getAddress(name);
    if(current == NULL)
    {
        printf("\nEnter Correct Name!\n");
        return;
    }
    else if(current->quantity < q)
    {
        printf("\nStock Limited\n");
        return;
    }
    current->quantity-=q;
    FILE *fp = fopen("product.txt", "r");
    if(fp == NULL)
    {
        fclose(fp);
        fp = fopen("product.txt", "w");
        fprintf(fp, "ID: %d\n", current->id);
        fprintf(fp, "Name: %s\n", current->pName);
        fprintf(fp, "Price: %lf\n", current->price);
        fprintf(fp, "Quantity: %d\n", q);
        fprintf(fp, "Total Price: %d\n", (int)(current->price*q));
    }
    else
    {
        fclose(fp);
        fp = fopen("product.txt", "a");
        fprintf(fp, "\nID: %d\n", current->id);
        fprintf(fp, "Name: %s\n", current->pName);
        fprintf(fp, "Price: %lf\n", current->price);
        fprintf(fp, "Quantity: %d\n", q);
        fprintf(fp, "Total Price: %d\n", (int)(current->price*q));
    }
    fclose(fp);
    printf("\nPurchased Successfully!\n\n");
    system("pause");
}
void showProducts()
{
    printf("\n\t\t:::::: Your Product and Price List ::::::\n\n");
    FILE *fp = fopen("product.txt", "r");
    if(fp == NULL)
    {
        printf("\nYou haven't order yet!\n");
        system("pause");
        return;
    }
    char ch = fgetc(fp);
    while(ch != EOF)
    {
        printf("%c", ch);
        ch = fgetc(fp);
    }
    system("pause");
}
void menuForCustomer()
{
    system("cls");
    printf("\n\t\t\t\t\t***************LOGIN SUCCESSFUL********************\n\n");
    system("pause");
    int n, a;
    while(1)
    {
        printf("\nEnter\n\n1 for buy a product\n2 for show products which u have bought\n3 for
               back\n\n");
               scanf("%d", &a);
               if(a == 1)
    {
        buyProducts();
        }
        else if(a == 2)
    {
        showProducts();
        }
        else if(a == 3)
    {
        break;
    }
    else printf("\nChoose a correct option!\n");
    }
}
void signUp()
{
    char name[MAX_SIZE], email[MAX_SIZE], pass[MAX_SIZE];
    char ext[] = ".txt";
    FILE *fp;
    system("cls");
    system("COLOR 74");
    printf("\n\t\t\t\t\t :::::::::::::::: SIGN UP ::::::::::::::::\n");
    printf("\n\t\t\t\t\t Enter Your Name: ");
    getchar(); // For Buffer Character
    gets(name);
    printf("\n\t\t\t\t\t Enter Your Email: ");
    gets(email);
    strcat(email, ext);
    fp = fopen(email, "w");
    printf("\n\t\t\t\t\t Enter Password: ");
    fprintf(fp, gets(pass));
    fclose(fp);
    CustomerLogIn();
}
void gateWay()
{
    char ch;
    system("cls");
    printf("\n =================================================================================================================");
    printf("\n\t\t\t\t\t:::::::DO YOU HAVE ANY ACCOUNT?::::::::::");
    printf("\n =================================================================================================================\n");
    printf("\n\tPlease Enter Y or N-->> ");
    getchar();
    scanf("%c", &ch);
    if(ch == 'y' || ch == 'Y')
    {
        getchar();
        CustomerLogIn();
    }
    else if(ch == 'n' || ch == 'N')
    {
        signUp();
    }
    else return;
}
int searchProduct(char name[])
{
    struct item *current;
    current = head;
    while(current != NULL)
    {
        if(strcmp(current->pName, name) == 0)
            return 1;
        current = current->next;
    }
    return 0;
}
struct item *getAddress(char name[])
{
    struct item *current;
    current = head;
    while(current != NULL)
    {
        if(strcmp(current->pName, name) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}
//Admin menu
void addProduct()
{
    int idd, q, n;
    double prc;
    char pr[MAX_SIZE];
    struct item *new_node, *current;
    while(1)
    {
        system("cls");
        printf("\n\tEnter\n\t1. FOR ADD NEW PRODUCT.\n\t2. FOR ADD EXSITING
               PRODUCT.\n\t3. BACK\n");
               printf("\tEnter your choice-->> ");
               scanf("%d", &n);
               if(n == 1)
    {
        system("cls");
            system("COLOR 09");
            printf("\n\t\t\t\t======= Current Selection: Addition of new stock========\n\n");
            printf("\nEnter product Name: ");
            getchar();
            gets(pr);
            printf("Enter product ID: ");
            scanf("%d", &idd);
            printf("Enter Price: ");
            scanf("%lf", &prc);
            printf("Enter quantity: ");
            scanf("%d", &q);
            if(searchProduct(pr))
            {
                printf("\nSorry, This product is already existed!\n");
                continue;
            }
            new_node = (struct item*)malloc(sizeof(struct item));
            new_node->id = idd;
            strcpy(new_node->pName, pr);
            new_node->price = prc;
            new_node->quantity = q;
            new_node->next = NULL;
            if(head == NULL)
            {
                head = new_node;
                current = new_node;
            }
            else
            {
                current->next = new_node;
                current = new_node;
            }
            printf("\nProduct added successfully !\n\n");
            system("pause");
        }
        else if(n==2)
    {
        system("cls");
            system("COLOR 09");
            printf("\n\t\t\t\t======= Current Selection: Addition of existing stock ========");
            printf("\n\nEnter product Name : ");
            getchar();
            gets(pr);
            printf("How much quantity wanna add : ");
            scanf("%d", &q);
            if(!searchProduct(pr))
            {
                system("cls");
                printf("\nSorry Product not found!\n");
                system("pause");
                continue;
            }
            struct item *temp = getAddress(pr);
            temp->quantity = (temp->quantity)+q;
            printf("\nProduct added successfully !\n\n");
            system("pause");
        }
        else if(n == 3)
        break;
        else printf("\nChoose a correct option!\n");
        }
}
//Admin Menu
void displayProducts()
{
    system("cls");
    printf("\n\t\t==========================================================================================\n");
    printf("\n\t\t\t\t\t :::::::::::Product List::::::::::::::\n");
    printf("\n\t\t==========================================================================================\n");
    struct item *current;
    current = head;
    if(head == NULL)
    {
        system("cls");
        system("COLOR 04");
        printf("\n\n\n\t\t\t\t\t SORRY NO PRODUCT AVAILABLE !\n\n\n");
        system("pause");
        return;
    }
    int c = 0;
    while(current != NULL)
    {
        printf(" %d\n", ++c);
        printf(" ---\n");
        printf("ID : %d\n", current->id);
        printf("Name : %s\n", current->pName);
        printf("Price : %lf\n", current->price);
        printf("Available : %d\n\n", current->quantity);
        current = current->next;
    }
    system("pause");
}
void logIn()
{
    int a=0,i=0;
    char uname[10],c=' ';
    char pword[10],code[10];
    char user[10]="vintage";
    char pass[10]="12345";
    do
    {
        system("cls");
        printf("\n\t\t\t\t\t\t ALLAH IS ALMIGHTY");
        printf("\n\n\t\t\t\t\t
               \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
               printf("\t\t\t\t\t WELCOME TO VINTAGE GROCERY SHOP. \n");
               printf("\t\t\t\t\t
                      \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n\n");
                      printf("\n\t\t\t\t\t \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd LOGIN FORM
                             \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd ");
                             printf("\n\n\t\t\t\t\t ENTER USERNAME: ");
                             scanf("%s", &uname);
                             printf(" \n\n\t\t\t\t\t ENTER PASSWORD: ");
                             while(i<10)
    {
        pword[i]=getch();
            c=pword[i];
            if(c==13) break;
            else printf("*");
            i++;
        }
        pword[i]='\0';
//char code=pword;
                 i=0;
//scanf("%s",&pword);
                 if(strcmp(uname,"vintage")==0 && strcmp(pword,"12345")==0)
    {
        system("color 0A");
            printf("\n\t\t\t\t\t
                   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd");
                   printf(" \n\n\t\t\t\t\t\t !!!! WELCOME ADMIN !!!!");
                   printf("\n\n\n\t\t\t\t\t Press any key to continue...");
                   getch();//holds the screen
                   break;
        }
        else
        {
            system("COLOR 04");
            printf("\n\t\t\t\t\t
                   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd");
                   printf("\n\n\t\t\t\t\t LOGIN IS UNSUCESSFUL...PLEASE TRY AGAIN...");
                   a++;
                   getch();//holds the screen
        }
    }
    while(a<=2);
    if (a>2)
    {
        printf("\nSorry you have entered the wrong username and password for four times!!!");
        getch();
    }
    system("cls");
}
int choice()
{
    int a;
    system("cls");
    printf("\n =================================================================================================================\n");
    printf("\n\t\t\t\t\t ***WELCOME TO VINTAGE GROCERY SHOP.*** \n");
    printf("\t\t\t\t\t \"WE BELIEVE IN QUALITY\" \t\t\t\t\t\t\n");
    printf("\n =================================================================================================================\n");
    printf("\tWhat would you like to do?");
    printf("\n\t1. ADMIN SECTION..");
    printf("\n\t2. CUSTOMER SECTION.");
    printf("\n\t3. EXIT.");
    printf("\n\tENTER YOUR CHOICE--> ");
    scanf("%d", &a);
    return a;
}
int main()
{
    int a;
    TITLE();
    while(1)
    {
        a = choice();
        if(a == 1)
        {
            menuForAdmin();
        }
        else if(a == 2)
        {
            gateWay();
        }
        else if(a == 3)
        {
            system("CLS");
            system("COLOR 02");
            printf("\n\n\n\n\n\n\n\n\n\t\t\t\t
                   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
                   printf("\t\t\t\t\t\tTHANK YOU FOR VISITING US");
                   printf("\n\t\t\t\t
                          \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
                          printf("\n\t\t\t\t\t :::: HAVE A GOOD DAY ::::");
                          getch();
                          remove("product.txt");
                          break;
        }
               else printf("\nSorry you enter wrong choice!\nTry again\n\n");
    }
    return 0;
}
void TITLE()
{
    system("cls");
    system("color 06");
    time_t t;
    time(&t);
    printf("\t---------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t%s",ctime(&t));
    printf("\t---------------------------------------------------------------------------------------------------------\n");
    printf("\n\t\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
    printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
    printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
    printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
    printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
    printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
    printf("\n\t\t\t\t\t****WELCOME TO VINTAGE GROCERY SHOP.**** \n");
    printf("\n\t\t\t\t\t\t \"WE BELIEVE IN QUALITY\" \t\t\t\t\t\t\n");
    printf("\n\t\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
    printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
    printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
    printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
    printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
    printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\n");
    printf("\n\n\n\t\t\t\t \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD
           *Presented By- ORPA & RUPA* \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD");
           puts("\nPress any key to continue...");
           getch();
}
