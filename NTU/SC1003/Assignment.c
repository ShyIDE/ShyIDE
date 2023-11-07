#include <stdio.h>
#include <string.h>
#define MAX 5

//structure goes here
typedef struct {
    int bookID;
    char title[40];
    char author[40];
    double price;
    int quantity;
} Book;

//function declaration goes here
//choice 01
void listBooks(Book *name_Book, int size);
//choice 02
int addBook(Book *name_Book, int size);
//choice 03
int removeBook(Book *name_Book, int size);
//choice 04
void findBook(Book *name_Book, int size);
//choice 05
void updateBook(Book *name_Book, int size);
//sorting algo
void sortAsc(Book *name_Book, int size);

int main() {

    Book name_Book[MAX];
    char *p;
    char dummy;
    int size = 0, choice;

    //menu goes here
    printf("NTU BOOKSHOP MANAGEMENT PROGRAM: \n");
    printf("1: listBooks() \n");
    printf("2: addBook() \n");
    printf("3: removeBook() \n");
    printf("4: findBook() \n");
    printf("5: updateBook() \n");
    printf("6: quit \n");

    do{
        printf("Enter your choice: \n");
        scanf("%d", &choice);
        scanf("%c", &dummy);

        switch (choice){
            case 1:
                listBooks(name_Book, size);
                break;
            case 2:
                size = addBook(name_Book, size);
                break;
            case 3:
                size = removeBook(name_Book, size);
                break;
            case 4:
                findBook(name_Book, size);
                break;
            case 5:
                updateBook(name_Book, size);
                break;
        }
    } while (choice < 6);

    return 0;
}

//function goes here

//choice 01
void listBooks(Book *name_Book, int size){
    printf("listBooks(): \n");

    if (size > 0){

        int i;
        for (i = 0; i < size; i++){
            printf("BookID: %d \n", name_Book[i].bookID);
            printf("Book title: %s \n", name_Book[i].title);
            printf("Author name: %s \n", name_Book[i].author);
            printf("Book price: %.2lf\n", name_Book[i].price);
            printf("Quantity: %d\n", name_Book[i].quantity);
        }
    }
    else{
        printf("The bookshop is empty \n");
    }
}

//choice 02
int addBook(Book *name_Book, int size){
    printf("addBook(): \n");

    int i,quantity, book_ID;
    double price;
    char title[40], author[40], dummy[40], *p;

    printf("Enter bookID: \n");
    scanf("%d", &book_ID);
    //fgets(dummy, 40, stdin);
    //scanf("%c", &dummy);
    getchar();

    printf("Enter book title: \n");
    fgets(title, 40, stdin);
    if (p = strchr(title, '\n')){
        *p = '\0';
    }

    printf("Enter author name: \n");
    fgets(author, 40, stdin);
    if (p = strchr(author, '\n')){
        *p = '\0';
    }

    printf("Enter price: \n");
    scanf("%lf", &price);

    printf("Enter quantity: \n");
    scanf("%d", &quantity);

    if (size == MAX){
        printf("The bookshop is full! Unable to addBook() \n");
        return size;
    }

    for (i = 0; i < size; i++){
        if (book_ID == name_Book[i].bookID){
            printf("The bookID has already existed! Unable to addBook() \n");
            return size;
        }
    }

    name_Book[size].bookID = book_ID;
    strcpy(name_Book[size].title, title);
    strcpy(name_Book[size].author, author);
    name_Book[size].price = price;
    name_Book[size].quantity = quantity;

    printf("The book has been added successfully \n");

    size++;
    sortAsc(name_Book, size);
    return size;
}
//choice 03
int removeBook(Book *name_Book, int size) {
    printf("removeBook(): \n");

    char searchTitle[40], searchAuthor[40], *p;

    printf("Enter the target book title: \n");
    fgets(searchTitle, 40, stdin);

    printf("Enter the target author name: \n");
    fgets(searchAuthor, 40, stdin);

    if (p = strchr(searchTitle, '\n')){
        *p = '\0';
    }

    if (p = strchr(searchAuthor, '\n')){
        *p = '\0';
    }

    int i;

    if (size == 0){
        printf("The bookshop is empty \n");
        return size;
    }

    for (i = 0; i < size; i++){
        if (strcasecmp(searchTitle, name_Book[i].title) == 0 &&
            strcasecmp(searchAuthor, name_Book[i].author) == 0) {

            printf("The target book is removed \n");
            printf("BookID: %d \n", name_Book[i].bookID);
            printf("Book title: %s \n", name_Book[i].title);
            printf("Author name: %s \n", name_Book[i].author);
            printf("Book price: %.2lf\n", name_Book[i].price);
            printf("Quantity: %d\n", name_Book[i].quantity);

            for (int j = i; j < size - 1; j++) {
                name_Book[j] = name_Book[j + 1];
            }
            name_Book[size - 1].bookID = 0;
            strcpy(name_Book[size - 1].title, "");
            strcpy(name_Book[size - 1].author, "");
            name_Book[size - 1].price = 0.0;
            name_Book[size - 1].quantity = 0;


            size--;
            sortAsc(name_Book, size);
            return size;
        }
    }

    printf("The target book is not in the bookshop \n");
    return size;
}

//choice 04
void findBook(Book *name_Book, int size){
    printf("findBook(): \n");

    int i;
    char searchTitle[40], searchAuthor[40], *p;

    printf("Enter the target book title: \n");
    fgets(searchTitle, 40, stdin);

    printf("Enter the target author name: \n");
    fgets(searchAuthor, 40, stdin);

    if (p = strchr(searchTitle, '\n')){
        *p = '\0';
    }

    if (p = strchr(searchAuthor, '\n')){
        *p = '\0';
    }

    for (i = 0; i < size; i++){
        if (strcasecmp(searchTitle, name_Book[i].title) == 0 &&
            strcasecmp(searchAuthor, name_Book[i].author) == 0) {

            printf("The target book is found \n");
            printf("BookID: %d \n", name_Book[i].bookID);
            printf("Book title: %s \n", name_Book[i].title);
            printf("Author name: %s \n", name_Book[i].author);
            printf("Book price: %.2lf\n", name_Book[i].price);
            printf("Quantity: %d\n", name_Book[i].quantity);
            return;
        }
    }
    printf("The target book is not found \n");

}

//choice 05
void updateBook(Book *name_Book, int size) {
    printf("updateBook():\n");

    char searchTitle[40], searchAuthor[40], *p;

    printf("Enter the target book title: \n");
    fgets(searchTitle, 40, stdin);

    printf("Enter the target author name: \n");
    fgets(searchAuthor, 40, stdin);

    if (p = strchr(searchTitle, '\n')) {
        *p = '\0';
    }

    if (p = strchr(searchAuthor, '\n')) {
        *p = '\0';
    }

    int i;

    if (size == 0) {
        printf("The bookshop is empty.\n");
        return;
    }

    for (i = 0; i < size; i++) {
        if (strcasecmp(searchTitle, name_Book[i].title) == 0 &&
            strcasecmp(searchAuthor, name_Book[i].author) == 0) {
            printf("Enter updated book price: \n");
            scanf("%lf", &name_Book[i].price);
            printf("Enter updated quantity: \n");
            scanf("%d", &name_Book[i].quantity);

            printf("The target book is updated\n");
            printf("BookID: %d\n", name_Book[i].bookID);
            printf("Book title: %s\n", name_Book[i].title);
            printf("Author name: %s\n", name_Book[i].author);
            printf("Book price: %.2lf\n", name_Book[i].price);
            printf("Quantity: %d\n", name_Book[i].quantity);

            return;
        }
    }

    printf("The target book is not in the bookshop\n");
}

//sorting algo
void sortAsc(Book *name_Book, int size){

    Book temp;
    int i, j;
    for (i = 0; i < (size - 1); i++){
        for (j = 0; j < (size - 1 - i); j++){
            if (name_Book[j].bookID > name_Book[j + 1].bookID){
                temp = name_Book[j];
                name_Book[j] = name_Book[j + 1];
                name_Book[j + 1] = temp;
            }
        }
    }
}
