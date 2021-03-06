#include "library_header.h"


error_t searchBooks(const char *FILE_NAME)
{
    error_t found_status = SUCCESS;
    char bookName[MAX_BOOK_NAME] = {0};
    s_BooksInfo Book = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\nFile is not opened\n");
        return FILE_NOT_FOUND;
    }
   

    //put the control on books detail
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\nFacing issue while reading file\n");
        return FAILURE;
    }
    printf("\nEnter Book Name to search:");
    fflush(stdin);
    fgets(bookName,MAX_BOOK_NAME,stdin);
    while (fread(&Book, sizeof(Book), 1, fp))
    {
        if(!strcmp(bookName,Book.bookName))
        {
            found_status = SUCCESS;
            break;
        }
    }
    if(found_status)
    {
        printf("\nBook id = %u\n",Book.books_id);
        printf("\nBook name = %s",Book.bookName);
        printf("\nBook authorName = %s",Book.authorName);
        printf("\nBook issued by student = %s",Book.studentName);
        printf("\nBook issue date(day/month/year) =  (%d/%d/%d)",Book.bookIssueDate.dd,
               Book.bookIssueDate.mm, Book.bookIssueDate.yyyy);
        printf("\nBook return date(day/month/year) =  (%d/%d/%d)",Book.returnDate.dd,
               Book.returnDate.mm, Book.returnDate.yyyy);
               
        //return SUCCESS;
    }
    else
    {
        printf("\nNo Book by this name");
        found_status= NOT_FOUND;
    }
    fclose(fp);
    printf("\nPress any key to go to main menu.....");
    getchar();
    return found_status;
}