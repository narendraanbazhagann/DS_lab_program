#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Book{
    char isbn[20];  
    char title[100];
    char author[100];
    float price;
}Book;

typedef struct Node{
    Book book;
    struct Node *left;
    struct Node *right;
}Node;

Node* createNode(Book book){
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->book=book;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

Node* insert(Node* root,Book book){
    if(root==NULL){
        return createNode(book);
    }
    if(strcmp(book.isbn,root->book.isbn)<0){
        root->left=insert(root->left,book);
    }else if(strcmp(book.isbn,root->book.isbn)>0){
        root->right=insert(root->right,book);
    }
    return root;
}

Book* search(Node* root,const char* isbn){
    if(root==NULL){
        return NULL;
    }
    if(strcmp(isbn,root->book.isbn)==0){
        return &root->book;
    }else if(strcmp(isbn,root->book.isbn)< 0){
        return search(root->left,isbn);
    }else{
        return search(root->right,isbn);
    }
}

void displaySorted(Node* root){
    if(root != NULL){
        displaySorted(root->left);
        printf("ISBN: %s,Title: %s,Author: %s,Price: %.2f\n",
               root->book.isbn,root->book.title,root->book.author,root->book.price);
        displaySorted(root->right);
    }
}

int main(){
    Node* root=NULL;
    int choice;
    
    do{
        printf("\nMenu:\n");
        printf("1. Insert a new book\n");
        printf("2. Search for a book by ISBN\n");
        printf("3. Display all books\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        getchar(); 
        switch(choice){
            case 1:{
                Book newBook;
                printf("Enter ISBN: ");
                fgets(newBook.isbn,sizeof(newBook.isbn),stdin);
                newBook.isbn[strcspn(newBook.isbn,"\n")]=0; 
                
                printf("Enter Title: ");
                fgets(newBook.title,sizeof(newBook.title),stdin);
                newBook.title[strcspn(newBook.title,"\n")]=0; 

                printf("Enter Author: ");
                fgets(newBook.author,sizeof(newBook.author),stdin);
                newBook.author[strcspn(newBook.author,"\n")]=0; 
                printf("Enter Price: ");
                scanf("%f",&newBook.price);
                getchar(); 
                
                root=insert(root,newBook);
                printf("Book inserted successfully!\n");
                break;
            }
            case 2:{
                char isbn[20];
                printf("Enter ISBN to search: ");
                fgets(isbn,sizeof(isbn),stdin);
                isbn[strcspn(isbn,"\n")]=0; 

                Book* foundBook=search(root,isbn);
                if(foundBook != NULL){
                    printf("Found: ISBN: %s,Title: %s,Author: %s,Price: %.2f\n",
                           foundBook->isbn,foundBook->title,foundBook->author,foundBook->price);
                }else{
                    printf("Book with ISBN %s not found.\n",isbn);
                }
                break;
            }
            case 3:
                printf("Books in sorted order:\n");
                displaySorted(root);
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }while(choice != 4);
 return 0;
}
