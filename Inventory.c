#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_PRODUCTS 100
#define MAX_BRANCHES 100

typedef enum{True,False}bool;

int linecheck();

int part1();
int part2();
int add_product();
int delete_product();
int update_product();
//int add_feature();
int add_stock_entry();
int delete_stock_entry();
int update_stock_entry();

int part3();
int list_all_products();
int filter_print_products();
int part4();

void query_product_stock();

void list_branch_stock();

void list_out_of_stock();


void part5();

void part6();
bool program_isRunning=True;
int main(){
printf("Welcome operator, please select an option to continue:\n");
part1();

}

int part1(){

    while(program_isRunning==True){
        
        int menu_choice;
        printf("1- File operations\n");
        printf("2- Query products\n");
        printf("3- Check stock status\n");
        printf("4- Stock control by brand\n");
        printf("5- Export report\n");
        scanf("%d",&menu_choice);
        switch(menu_choice){
            case 1:
                part2();
                break;
            case 2:
                part3();
                break;
            case 3:
                part4();
                break;
            case 4:
                part5();
                break;
            case 5:
                part6();
                program_isRunning=False;
                break;
            default:
                printf("Invalid input, try again.\n");
                break;
        }

    }

}

int part2(){
    int menu_choice;
    bool menu_isRunning=True;
    while(menu_isRunning==True){
        printf("1- Add product\n");
        printf("2- Delete product\n");
        printf("3- Update product\n");
        printf("4- Add feature to products\n");
        printf("5- Add a new stock entry\n");
        printf("6- Delete a stock entry\n");
        printf("7- Update a stock entry\n");
        printf("8- Back to main menu.\n");
        scanf("%d",&menu_choice);
        switch(menu_choice){
            case 1:
                add_product();
                break;
            case 2:
                delete_product();
                break;
            case 3:
                update_product();
                break;
            case 4:
                //add feature to products
                break;
            case 5:
                add_stock_entry();
                break;
            case 6:
                delete_stock_entry();
                break;
            case 7:
                update_stock_entry();
                break;
            case 8:
                menu_isRunning=False;
                break;
            default:
                printf("Invalid input, try again.\n");
                break;
    }

    }

}


int count_lines() {
    FILE* fp=fopen("products.txt","r");
    int count = 0;
    char c;

    if (fp == NULL) {
        printf("Unable to open file\n");
        return -1;
    }

    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }

    fclose(fp);

    return count;
}
int add_product() {
    int pID=count_lines();
    char type, name[8],brand[8];
    double price;
    FILE *file = fopen("products.txt", "a");  // open file in append mode
    if(file == NULL){  // check if file was opened successfully{
        printf("Failed to open file %s\n", "products.txt");
        return -1;
    }
    printf("Enter product type: ");
    scanf(" %c",&type);
    printf("Enter product name: ");
    scanf("%s",&name);
    printf("Enter product brand: ");
    scanf("%s",&brand);
    printf("Enter product price: ");
    scanf("%.2lf",&price);
    fprintf(file,"%d,%c,%s,%s,%.2lf\n",pID,type,name,brand,price);
    fclose(file);
}
int delete_product() {
    printf("Enter product ID to delete: ");
    int pIDtodel;
    int pID;
    int newpID=1;
    char name[8],brand[8],type;
    double price;
    scanf("%d",&pIDtodel);

    FILE *file = fopen("products.txt", "r+");
    FILE *temp_file = fopen("temp.txt", "w+");
    char c;
    while((c=fgetc(file))!='\n'){
    fputc(c,temp_file);
    }
    fputc('\n',temp_file);

    while(fscanf(file,"%d,%c,%[^,],%[^,],%.2lf\n",&pID,&type,&name,&brand,&price)==5){
        if(pID!=pIDtodel){
            fprintf(temp_file,"%d,%c,%s,%s,%.2lf\n",newpID,type,name,brand,price);
            newpID++;
        }
    }
    fclose(file);
    fclose(temp_file);
    remove("products.txt");
    rename("temp.txt","products.txt");
    
}
int update_product(){
    printf("Enter product ID to update: ");
    int pIDtoupdate, pID, feature, comma_count = 0;
    char name[8], brand[8], new_data[8], type;
    double price;
    
    scanf("%d",&pIDtoupdate);

    FILE *file = fopen("products.txt", "r");
    FILE *temp_file = fopen("temp.txt", "w");

    char c;
    while ((c = fgetc(file)) != EOF) {
        fputc(c, temp_file);
        if (c == '\n') {
            break; // found the first line, exit loop
        }
    }

    while(fscanf(file, "%d,%c,%[^,],%[^,],%.2lf\n", &pID, &type, name, brand, &price) == 5){
        if(pID == pIDtoupdate){
            printf("Please enter the rank of the feature to be updated:");
            printf("E.g. 2 for type, 3 for name...\n");
            scanf("%d",&feature);
            int n = feature - 1;
            switch(feature) {
    case 1:
        printf("Cannot update product ID!\n");
        fprintf(temp_file, "%d,%c,%s,%s,%.2lf\n", pID, type, name, brand, price);
        break;
    case 2:
        printf("Enter new type: ");
        scanf(" %c",&type);
        fprintf(temp_file,"%d,%c,%s,%s,%.2lf\n",pID,type,name,brand,price);
        break;
    case 3:
        printf("Enter new name: ");
        scanf("%s",new_data);
        fprintf(temp_file,"%d,%c,%s,%s,%.2lf\n",pID,type,new_data,brand,price);
        break;
    case 4:
        printf("Enter new brand: ");
        scanf("%s",new_data);
        fprintf(temp_file,"%d,%c,%s,%s,%.2lf\n",pID,type,name,new_data,price);
        break;
    case 5:
        printf("Enter new price: ");
        scanf("%.2lf",&price);
        fprintf(temp_file,"%d,%c,%s,%s,%.2lf\n",pID,type,name,brand,price);
        break;
    default:
        printf("Invalid input, try again.\n");
        fprintf(temp_file, "%d,%c,%s,%s,%.2lf\n", pID, type, name, brand, price);
        break;
}


   
}
        else if(pID!=pIDtoupdate){
            fprintf(temp_file,"%d,%c,%s,%s,%.2lf\n",pID,type,name,brand,price);
        }
    }
    fclose(file);
    fclose(temp_file);

    remove("products.txt");
    rename("temp.txt","products.txt");

    return 0;
    }
int add_stock_entry(){
    
    int sID=count_lines();
    int pID,current_stock;
    char Branch[8];
    FILE *file = fopen("stocks.txt", "a");  // open file in append mode
    if(file == NULL){  // check if file was opened successfully{
        printf("Failed to open file %s\n", "stocks.txt");
        return -1;
    }
    printf("Enter product pID: ");
    scanf("%d",&pID);
    printf("Enter stock branch: ");
    scanf("%s",&Branch);
    printf("Enter current stock: ");
    scanf("%d",&current_stock);

    fprintf(file,"\n%d,%d,%s,%d",sID,pID,Branch,current_stock);
    fclose(file);

}
int delete_stock_entry(){
     printf("Enter stock ID to delete: ");
    int sIDtodel;
    int sID;
    int newsID=1;
    char Branch[8];
    int pID,current_stock;
    scanf("%d",&sIDtodel);

    FILE *file = fopen("stocks.txt", "r+");
    FILE *temp_file = fopen("temp.txt", "w+");
    char c;
    while((c=fgetc(file))!='\n'){
    fputc(c,temp_file);
    }
    fputc('\n',temp_file);

    while(fscanf(file,"%d,%d,%[^,],%d\n",&sID,&pID,&Branch,&current_stock)==4){
        if(sID!=sIDtodel){
            fprintf(temp_file,"%d,%d,%s,%d\n",newsID,pID,Branch,current_stock);
            newsID++;
        }
    }
    fclose(file);
    fclose(temp_file);
    remove("stocks.txt");
    rename("temp.txt","stocks.txt");
    
}

int update_stock_entry(){
     printf("Enter stock ID to update: ");
    int sIDtoupdate, sID, feature;
    char Branch[8];
    int pID,current_stock;
    
    scanf("%d",&sIDtoupdate);

    FILE *file = fopen("stocks.txt", "r");
    FILE *temp_file = fopen("temp.txt", "w");

    char c;
    while ((c = fgetc(file)) != EOF) {
        fputc(c, temp_file);
        if (c == '\n') {
            break; // found the first line, exit loop
        }
    }

    while(fscanf(file, "%d,%d,%[^,],%d\n", &sID, &pID, &Branch, &current_stock) == 4){
        if(sID == sIDtoupdate){
            printf("Please enter the rank of the feature to be updated:");
            printf("E.g. 2 for pID, 3 for branch...\n");
            scanf("%d",&feature);
            switch(feature) {
    case 1:
        printf("Cannot update stock ID!\n");
        fprintf(temp_file, "%d,%d,%s,%d\n", sID,pID,Branch,current_stock);
        break;
    case 2:
        printf("Enter new pID: ");
        scanf("%d",&pID);
        fprintf(temp_file, "%d,%d,%s,%d\n", sID,pID,Branch,current_stock);
        break;
    case 3:
        printf("Enter new Branch: ");
        scanf("%s",Branch);
        fprintf(temp_file, "%d,%d,%s,%d\n", sID,pID,Branch,current_stock);
        break;
    case 4:
        printf("Enter new current stock value: ");
        scanf("%d",current_stock);
        fprintf(temp_file, "%d,%d,%s,%d\n", sID,pID,Branch,current_stock);
        break;
    default:
        printf("Invalid input, try again.\n");
        fprintf(temp_file, "%d,%d,%s,%d\n", sID,pID,Branch,current_stock);
        break;
}


   
}
        else if(sID!=sIDtoupdate){
            fprintf(temp_file, "%d,%d,%s,%d\n", sID,pID,Branch,current_stock);        }
    }
    fclose(file);
    fclose(temp_file);

    remove("stocks.txt");
    rename("temp.txt","stocks.txt");

    return 0;

}
int part3(){
    int choice;
    bool searchmenu_isRunning = True;
    printf("1-List all products\n");
    printf("2-Filter products\n");
    printf("3-Back to main menu\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);
    while(searchmenu_isRunning==True){
        switch (choice)
    {
    case 1:
        list_all_products();
        searchmenu_isRunning = False;
        break;
    case 2:
        filter_print_products();
        searchmenu_isRunning = False;
        break;
    case 3:
        searchmenu_isRunning = False;
        break;
    
    default:
        printf("Invalid input, try again.\n");
        break;
    }
    }



}
int list_all_products(){
    FILE *file = fopen("products.txt", "r");
    printf("\n");
    char c;
    while((c=fgetc(file))!=EOF){
        printf("%c",c);
    }
    printf("\n");
    fclose(file);

}

int filter_print_products() {
    
    typedef struct {
    int pID;
    char Type;
    char Name[50];
    char Brand[50];
    double Price;
} Product;
    
    
    
    char filter_type[50];
    char filter_values[100];
    printf("Enter filter type (brand, type, price, or feature): ");
    scanf("%s", filter_type);
    printf("Enter filter value(s), separated by commas: ");
    scanf("%s", filter_values);
    char *token;
    char *values[10];
    int count = 0;
    token = strtok(filter_values, ",");
    while (token != NULL) {
        values[count++] = token;
        token = strtok(NULL, ",");
    }
    int matches = 0;
    Product products[20];
    FILE *fp = fopen("products.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    char line[100];
    fgets(line, sizeof(line), fp); // skip header line
    while (fgets(line, sizeof(line), fp) != NULL) {
        Product product;
        sscanf(line, "%d,%c,%[^,],%[^,],%lf", &product.pID, &product.Type, product.Name, product.Brand, &product.Price);
        int match = 0;
        if (strcmp(filter_type, "brand") == 0) {
            for (int i = 0; i < count; i++) {
                if (strcmp(product.Brand, values[i]) == 0) {
                    match = 1;
                    break;
                }
            }
        } else if (strcmp(filter_type, "type") == 0) {
            for (int i = 0; i < count; i++) {
                if (product.Type == values[i][0]) {
                    match = 1;
                    break;
                }
            }
        } else if (strcmp(filter_type, "price") == 0) {
            double min_price = atof(values[0]);
            double max_price = atof(values[1]);
            if (product.Price >= min_price && product.Price <= max_price) {
                match = 1;
            }
        } else {
            for (int i = 0; i < count; i++) {
                if (strcmp(product.Name, values[i]) == 0) {
                    match = 1;
                    break;
                }
            }
        }
        if (match) {
            products[matches++] = product;
        }
    }
    fclose(fp);
    if (matches > 0) {
        printf("%d product(s) found:\n", matches);
        for (int i = 0; i < matches; i++) {
            printf("%d,%c,%s,%s,%.2lf\n", products[i].pID, products[i].Type, products[i].Name, products[i].Brand, products[i].Price);
        }
    } else {
        printf("No products found.\n");
    }
}

int part4(){

    int choice;
    do {
        printf("\n--- Stock Query Menu ---\n");
        printf("1. Query product stock in a branch\n");
        printf("2. List stock of all products in a branch\n");
        printf("3. List out-of-stock products in a branch\n");
        printf("4. Return to main menu\n");
        printf("Enter option: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                query_product_stock();
                break;
            case 2:
                list_branch_stock();
                break;
            case 3:
                list_out_of_stock();
                break;
            case 4:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    } while(choice != 4);
    return 0;

}

void query_product_stock() {

    typedef struct {
    int sid;
    int pid;
    char branch[20];
    int stock;
} Stock;


    int pid, stock;
    char branch[20];
    printf("Enter product ID: ");
    scanf("%d", &pid);
    printf("Enter branch name: ");
    scanf("%s", branch);
    FILE *fp = fopen("stocks.txt", "r");
    if (fp == NULL) {
        printf("Error: stocks.txt not found\n");
        return;
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp)) {
        Stock s;
        sscanf(line, "%d,%d,%[^,],%d", &s.sid, &s.pid, s.branch, &s.stock);
        if (s.pid == pid && strcmp(s.branch, branch) == 0) {
            printf("Current stock: %d\n", s.stock);
            fclose(fp);
            return;
        }
    }
    printf("Product not found in branch\n");
    fclose(fp);
}

void list_branch_stock() {

    typedef struct {
    int sid;
    int pid;
    char branch[20];
    int stock;
} Stock;


    char branch[20];
    printf("Enter branch name: ");
    scanf("%s", branch);
    FILE *fp = fopen("stocks.txt", "r");
    if (fp == NULL) {
        printf("Error: stocks.txt not found\n");
        return;
    }
    char line[MAX_LINE_LENGTH];
    printf("Stocks in branch %s:\n", branch);
    while (fgets(line, MAX_LINE_LENGTH, fp)) {
        Stock s;
        sscanf(line, "%d,%d,%[^,],%d", &s.sid, &s.pid, s.branch, &s.stock);
        if (strcmp(s.branch, branch) == 0) {
            printf("Product ID: %d, Current stock: %d\n", s.pid, s.stock);
        }
    }
    fclose(fp);
}

void list_out_of_stock() {

    typedef struct {
    int sid;
    int pid;
    char branch[20];
    int stock;
} Stock;

    char branch[20];
    printf("Enter branch name: ");
    scanf("%s", branch);
    FILE *fp = fopen("stocks.txt", "r");
    if (fp == NULL) {
        printf("Error: stocks.txt not found\n");
        return;
    }
    char line[MAX_LINE_LENGTH];
    printf("Out-of-stock products in branch %s:\n", branch);
    int out_of_stock = 1;
    while (fgets(line, MAX_LINE_LENGTH, fp)) {
        Stock s;
        sscanf(line, "%d,%d,%[^,],%d", &s.sid, &s.pid, s.branch, &s.stock);
        if (strcmp(s.branch, branch) == 0 && s.stock > 0) {
            out_of_stock = 0;
        } else if (strcmp(s.branch, branch) == 0 && s.stock == 0) {
            out_of_stock = 1;
            printf("Product ID: %d\n", s.pid);
        }
    }
    if (!out_of_stock) {
        printf("No out-of-stock products found in branch\n");
    }
    fclose(fp);
}

void part5() {
    char brand[20];
    printf("Enter the brand: ");
    scanf("%s", brand);

    FILE *productsFile = fopen("products.txt", "r");
    if (productsFile == NULL) {
        printf("Error opening products.txt\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, productsFile); // skip header line

    int products[MAX_PRODUCTS][3];
    int productCount = 0;

    while (fgets(line, MAX_LINE_LENGTH, productsFile) != NULL) {
        char *pID = strtok(line, ",");
        strtok(NULL, ","); // skip Type
        strtok(NULL, ","); // skip Name
        char *productBrand = strtok(NULL, ",");
        char *price = strtok(NULL, ",");

        if (strcmp(brand, productBrand) == 0) {
            products[productCount][0] = atoi(pID);
            products[productCount][1] = atof(price);
            products[productCount][2] = 0;
            productCount++;
        }
    }

    fclose(productsFile);

    FILE *stocksFile = fopen("stocks.txt", "r");
    if (stocksFile == NULL) {
        printf("Error opening stocks.txt\n");
        exit(1);
    }

    fgets(line, MAX_LINE_LENGTH, stocksFile); // skip header line

    while (fgets(line, MAX_LINE_LENGTH, stocksFile) != NULL) {
        strtok(NULL, ","); // skip sID
        char *pID = strtok(NULL, ",");
        strtok(NULL, ","); // skip Branch
        char *currentStock = strtok(NULL, ",");

        for (int i = 0; i < productCount; i++) {
            if (products[i][0] == atoi(pID)) {
                products[i][2] += atoi(currentStock);
                break;
            }
        }
    }

    fclose(stocksFile);

    printf("pID\tPrice\tCurrent Stock\n");
    for (int i = 0; i < productCount; i++) {
        printf("%d\t%.2f\t%d\n", products[i][0], (float)products[i][1], products[i][2]);
    }
}

void part6() {
    char brand[20];
    printf("Enter the brand: ");
    scanf("%s", brand);

    FILE *productsFile = fopen("products.txt", "r");
    if (productsFile == NULL) {
        printf("Error opening products.txt\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, productsFile); // skip header line

    int products[MAX_PRODUCTS][3];
    int productCount = 0;

    while (fgets(line, MAX_LINE_LENGTH, productsFile) != NULL) {
        char *pID = strtok(line, ",");
        strtok(NULL, ","); // skip Type
        strtok(NULL, ","); // skip Name
        char *productBrand = strtok(NULL, ",");
        char *price = strtok(NULL, ",");

        if (strcmp(brand, productBrand) == 0) {
            products[productCount][0] = atoi(pID);
            products[productCount][1] = atof(price);
            products[productCount][2] = 0;
            productCount++;
        }
    }

    fclose(productsFile);

    int stocks[MAX_PRODUCTS][MAX_PRODUCTS];
    int stockCounts[MAX_PRODUCTS] = {0};

    FILE *stocksFile = fopen("stocks.txt", "r");
    if (stocksFile == NULL) {
        printf("Error opening stocks.txt\n");
        exit(1);
    }

    fgets(line, MAX_LINE_LENGTH, stocksFile); // skip header line

    while (fgets(line, MAX_LINE_LENGTH, stocksFile) != NULL) {
        strtok(NULL, ","); // skip sID
        char *pID = strtok(NULL, ",");
        strtok(NULL, ","); // skip Branch
        char *currentStock = strtok(NULL, ",");

        for (int i = 0; i < productCount; i++) {
            if (products[i][0] == atoi(pID)) {
                stocks[i][stockCounts[i]] = atoi(currentStock);
                stockCounts[i]++;
                break;
            }
        }
    }

    fclose(stocksFile);

    FILE *reportFile = fopen("report.txt", "w");
    if (reportFile == NULL) {
        printf("Error opening report.txt\n");
        exit(1);
    }

    fprintf(reportFile, "pID,Min Stock Value,Max Stock Value,Median Stock Value\n");

    for (int i = 0; i < productCount; i++) {
        int minStockValue = stocks[i][0];
        int maxStockValue = stocks[i][0];
        int medianStockValue;

        for (int j = 1; j < stockCounts[i]; j++) {
            if (stocks[i][j] < minStockValue) minStockValue = stocks[i][j];
            if (stocks[i][j] > maxStockValue) maxStockValue = stocks[i][j];
        }

        if (stockCounts[i] % 2 == 0) {
            medianStockValue = (stocks[i][stockCounts[i]/2 - 1] + stocks[i][stockCounts[i]/2]) / 2;
        } else {
            medianStockValue = stocks[i][stockCounts[i]/2];
        }

        fprintf(reportFile, "%d,%d,%d,%d\n", products[i][0], minStockValue, maxStockValue, medianStockValue);
    }

    fclose(reportFile);
}