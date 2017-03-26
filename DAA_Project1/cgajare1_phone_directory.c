/*
 ============================================================================
 Name        : cgajare1_phone_directory.c
 Author      : Chetan
 Email       : cgajare1@binghamton.edu
 Created on  : Feb 9, 2017
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct records
{
    char fname[50];
    char lname[50];
    char number[50];
} directory[50];

int totalRecords =0;

void create(char *);
void sort_contact();
void randomizedQuickSort(struct records *, int, int );
void swapRecords(struct records *, struct records *);
int compareTwoRecords(const struct records*,const struct records* );
void search(char *,char *);
void delete(char *,char *,char *);
void insert(char *,char *,char *);
void printRecords();

int main( int argc, char *argv[] )
{
    int choice;
    char consoleFirstName[50];
    char consoleLastName[50];
    char consoleNumber[50];
    char file_name[50] ;
    strcpy(file_name,argv[1]);
    create(file_name);

    do
    {
        printf("\n\nPlease enter your choice :  ");
        printf("\n1:Sort Contacts");
        printf("\n2:Search");
        printf("\n3:Delete");
        printf("\n4:Insert\n");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            printf("\n");
            sort_contact();
                printRecords();

            break;
        case 2:
            printf("\nEnter the name to search : ");
            scanf("%s",consoleFirstName);
            scanf("%s",consoleLastName);
            strcat(consoleLastName,",");
            search(consoleFirstName,consoleLastName);
            break;
        case 3:
            printf("\nEnter the name to Delete : ");
            scanf("%s",consoleFirstName);
            scanf("%s",consoleLastName);
            scanf("%s",consoleNumber);
            //strcat(consoleLastName,",");
            delete(consoleFirstName,consoleLastName,consoleNumber);
            break;
        case 4:
            printf("\nEnter the details to Insert : ");
            //First Name
            scanf("%s",consoleFirstName);
            //Last Name
            scanf("%s",consoleLastName);
            //Number
            scanf("%s",consoleNumber);
            //strcat(consoleLastName,",");
            insert(consoleFirstName,consoleLastName,consoleNumber);
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("\nPlease re-enter your choice");
            break;
        }
    }
    while (choice!=5);
    return 0;
}

void create(char *file_name)
{
    FILE *fp;
    int i=0;
    //Open file in read mode
    fp = fopen(file_name, "r");
    char fname[50],lname[50],number[50];
    if (fp == NULL)
    {
        perror("Error while opening the input file");
        exit(0);
    }
    else
    {
        //Take and store 3 parameters from File tokenized with space
        while (fscanf(fp, "%s %s %s",fname,lname,number) == 3)
        {
            fflush(stdout);
            strcpy(directory[i].fname,fname);
            strcpy(directory[i].lname,lname);
            strcpy(directory[i].number,number);
            i++;
            totalRecords++;
        }
    }
    fclose(fp);
}

void sort_contact()
{
    randomizedQuickSort(directory, 0, totalRecords-1);
}

void randomizedQuickSort(struct records *divided_Dictionary, int left, int right)
{
    //Generate random number for pivot index
    int pivotIndex = left + rand() % (right - left + 1);
    //Select random record as Pivot
    struct records pivotRecord = divided_Dictionary[pivotIndex];
    int l = left;
    int r = right;
    while (l <= r)
    {
        while (compareTwoRecords(divided_Dictionary+l, &pivotRecord) < 0)
            l++;
        while (compareTwoRecords(divided_Dictionary+r, &pivotRecord) > 0)
            r--;
        if (l <= r)
        {
            swapRecords(divided_Dictionary+l, divided_Dictionary+r);
            r--;
            l++;
        }
    }
    if (left < r)
        randomizedQuickSort(divided_Dictionary, left, r);
    if (l < right)
        randomizedQuickSort(divided_Dictionary, l, right);
}


void swapRecords(struct records *left, struct records *right)
{
    struct records temp;
    temp =  *right;
    *right = *left;
    *left = temp;
}

int compareTwoRecords(const struct records* left,const struct records* right)
{
    int first = strcmp(left->fname, right->fname);
    int second;
    if(first==0)  //If program found first name match.
    {
        second =  strcmp(left->lname,right->lname);
        if(second ==0)  //If program found last name match.
        {
            int third = strcmp(left->number, right->number);
            return(third);  //If program found number match.
        }
        return (second);
    }
    return (first);
}


void printRecords()
{
    int i;
    //printf("\n--------------------------------------------");
    for (i=0; i<totalRecords; i++)
    {
        printf("\n%s %s %s",directory[i].fname,directory[i].lname,directory[i].number);
    }
    //printf("\n--------------------------------------------");
}


void search(char *consoleFirstName,char *consoleLastName)
{
    int start = 0;
    int end = totalRecords - 1;
    int middle = (start+end)/2;
    sort_contact();
    struct records *divided_Dictionary = directory;
    while (start <= end)
    {
        int first = strcmp((divided_Dictionary+middle)->fname, consoleFirstName);
        int second =strcmp((divided_Dictionary+middle)->lname, consoleLastName);
        if (first<0)
            start = middle + 1; //If the input record from user is greater than record in middle
        else if (first==0 && second==0)
        {
            //If the input record from user is matched with record in middle
            printf("\n%s %s %s",(divided_Dictionary+middle)->fname,(divided_Dictionary+middle)->lname,(divided_Dictionary+middle)->number);
            break;
        }
        else
            end = middle - 1;  //If the input record from user is smaller than record in middle
        middle = (start + end)/2;
    }
    if (start > end)
        printf("\nName not Found\n");
}

void delete(char *consoleFirstName,char *consoleLastName,char *consoleNumber)
{
    int start = 0;
    int end = totalRecords - 1;
    int middle = (start+end)/2;
    struct records *divided_Dictionary = directory;
    //Flag is est when program found the record in dictionary.
    int flag = 0;
    int i;
    for (i=0; i<totalRecords; i++)
    {
        int first = strcmp((divided_Dictionary+i)->fname, consoleFirstName);
        int second =strcmp((divided_Dictionary+i)->lname, consoleLastName);
        int third =strcmp((divided_Dictionary+i)->number, consoleNumber);

        if (first==0 && second==0 && third==0 && flag==0)
        {
            //Record Found
            flag = 1;
            totalRecords--;
        }
        if(flag==1)
        {
            //Record YET not found
            *(divided_Dictionary+i) = *(divided_Dictionary+i+1);
        }
    }
    if(flag==0)
    {
        printf("\nName not Found\n");
    }
    else
    {
        printRecords();
    }
}

void insert(char *consoleFirstName,char *consoleLastName,char *consoleNumber)
{
    strcpy(directory[totalRecords].fname,consoleFirstName);
    strcpy(directory[totalRecords].lname,consoleLastName);
    strcpy(directory[totalRecords].number,consoleNumber);
    totalRecords++;
    sort_contact();
        printRecords();

}


