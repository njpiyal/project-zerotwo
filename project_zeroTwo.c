#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_ROW 100
#define MAX_COL 5

typedef struct {
    char productName[20];
    char productDate[20];
    char transId[20];
    int soldProduct;
    int revenue;
} TranscationStructure;

void createFile(TranscationStructure userData[][MAX_COL], int loopCount)
{
    FILE *file;

    file = fopen("user_transaction.csv", "w+");
    fprintf(file,"Product name, Transaction Id, Date, Sold amount, Revenue\n");

    for(int i=0; i <= loopCount-1; i++)
    {
        fprintf(file,"%s, %s, %s, %d, %d\n", userData[i][0].productName, userData[i][1].transId,userData[i][2].productDate, userData[i][3].soldProduct, userData[i][4].revenue);
    }

    fclose(file);
}

int analysisResult(TranscationStructure userData[][MAX_COL], int loopCount)
{
    int highest = 0;
    char product_name[20];
    double total_revenue = 0;
    double avg_revenue = 0.0;

    for(int i=0; i <= loopCount-1; i++)
    {
       total_revenue += (userData[i][3].soldProduct * userData[i][4].revenue);
    }
    avg_revenue = total_revenue/loopCount;

    for(int i=0; i <= loopCount-1; i++)
    {
        double each_revenue = (userData[i][3].soldProduct * userData[i][4].revenue);
        if (each_revenue > highest) {
            highest = each_revenue;
            strcpy(product_name, userData[i][0].productName);
        }
    }

    FILE *file;
    file = fopen("analysis_transaction.csv", "w+");

    fprintf(file,"Total revenue, Avg revenue, Top selling product\n");
    fprintf(file,"%0.2f, %0.2f, %s\n", total_revenue, avg_revenue, product_name);

    fclose(file);
}

int main()
{
     TranscationStructure ts[MAX_ROW][MAX_COL]; // ts is TranscationStructure

    int loopSwitch, loopCount=0;
    while(1)
    {
        printf("Enter the product name: ");
        fgets(ts[loopCount][0].productName,sizeof ts[loopCount][0].productName, stdin);
        ts[loopCount][0].productName[strcspn(ts[loopCount][0].productName, "\n")] = '\0';

        printf("Enter the Transaction Id: ");
        fgets(ts[loopCount][1].transId,sizeof ts[loopCount][1].transId, stdin);
        ts[loopCount][1].transId[strcspn(ts[loopCount][1].transId, "\n")] = '\0';

        printf("Enter the Transaction Date: ");
        fgets(ts[loopCount][2].productDate,sizeof ts[loopCount][2].productDate, stdin);
        ts[loopCount][2].productDate[strcspn(ts[loopCount][2].productDate, "\n")] = '\0';

        printf("Enter the amount of sold product: ");
        scanf("%d",&ts[loopCount][3].soldProduct);

        printf("Enter the product Revenue: ");
        scanf("%d",&ts[loopCount][4].revenue);


        printf("\nProduct name: %s\nTransaction Id : %s\tTransaction Date: %s\nSold Product: %d\tRevenue: %d\n\n",ts[loopCount][0].productName,ts[loopCount][1].transId,ts[loopCount][2].productDate,ts[loopCount][3].soldProduct,ts[loopCount][4].revenue);

        printf("Continue input or create file?\nPress 0 to continue input\nPress 1 to create file\n");
        printf("Action: ");
        scanf("%d",&loopSwitch);

        loopCount++;
        if(loopSwitch == 1)
        {
            printf("\nPress 0 to create a transaction CSV file\nPress 1 to create a analysis file of the transaction\n");
            printf("Action: ");
            scanf("%d",&loopSwitch);

            switch(loopSwitch)
            {
                case 0:
                    createFile(ts, loopCount);
                    printf("Transaction data stored in a CSV file");
                    break;

                case 1:
                    analysisResult(ts, loopCount);
                    printf("Analysis data stored in a CSV file");
                    break;
            }

            break;
        }
        getchar();
    }
}
