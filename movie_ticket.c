
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Ticket {
    int bookingID;
    char customer[50];
    char movie[50];
    int seat;
    char date[20];
    char time[20];
    float price;
    struct Ticket *next;
} Ticket;

Ticket *head = NULL;
int nextID = 1001;

Ticket* createTicket() {
    Ticket *t = (Ticket*)malloc(sizeof(Ticket));
    if(!t){
        printf("Memory allocation failed!\n");
        exit(1);
    }
    t->bookingID = nextID++;

    printf("Customer Name : ");
    scanf(" %[^\n]", t->customer);

    printf("Movie Name    : ");
    scanf(" %[^\n]", t->movie);

    printf("Seat Number(1-100): ");
    scanf("%d",&t->seat);

    printf("Date (DD/MM/YYYY): ");
    scanf("%s",t->date);

    printf("Time (HH:MM): ");
    scanf("%s",t->time);

    printf("Ticket Price: ");
    scanf("%f",&t->price);

    t->next=NULL;
    return t;
}

int seatExists(int seat){
    Ticket *temp=head;
    while(temp){
        if(temp->seat==seat) return 1;
        temp=temp->next;
    }
    return 0;
}

void bookTicket(){
    Ticket *t=createTicket();

    if(t->seat<1 || t->seat>100){
        printf("Invalid seat.\n");
        free(t);
        return;
    }

    if(seatExists(t->seat)){
        printf("Seat already booked!\n");
        free(t);
        return;
    }

    if(head==NULL){
        head=t;
    }else{
        Ticket *temp=head;
        while(temp->next)
            temp=temp->next;
        temp->next=t;
    }

    printf("\nBooking Successful!\n");
    printf("Booking ID : %d\n",t->bookingID);
}

void displayTickets(){
    Ticket *temp=head;

    if(temp==NULL){
        printf("\nNo bookings available.\n");
        return;
    }

    printf("\n---------------------------------------------------------------\n");

    while(temp){
        printf("Booking ID : %d\n",temp->bookingID);
        printf("Customer   : %s\n",temp->customer);
        printf("Movie      : %s\n",temp->movie);
        printf("Seat       : %d\n",temp->seat);
        printf("Date       : %s\n",temp->date);
        printf("Time       : %s\n",temp->time);
        printf("Price      : %.2f\n",temp->price);
        printf("---------------------------------------------------------------\n");
        temp=temp->next;
    }
}

void searchBookingID(){
    int id;
    printf("Enter Booking ID : ");
    scanf("%d",&id);

    Ticket *temp=head;

    while(temp){
        if(temp->bookingID==id){
            printf("\nBooking Found\n");
            printf("Customer : %s\n",temp->customer);
            printf("Movie    : %s\n",temp->movie);
            printf("Seat     : %d\n",temp->seat);
            printf("Date     : %s\n",temp->date);
            printf("Time     : %s\n",temp->time);
            printf("Price    : %.2f\n",temp->price);
            return;
        }
        temp=temp->next;
    }

    printf("Booking not found.\n");
}

void searchCustomer(){
    char name[50];
    int found=0;

    printf("Enter Customer Name : ");
    scanf(" %[^\n]",name);

    Ticket *temp=head;

    while(temp){
        if(strcmp(temp->customer,name)==0){
            found=1;
            printf("\nBooking ID : %d\n",temp->bookingID);
            printf("Movie      : %s\n",temp->movie);
            printf("Seat       : %d\n",temp->seat);
            printf("Date       : %s\n",temp->date);
            printf("Time       : %s\n",temp->time);
            printf("Price      : %.2f\n\n",temp->price);
        }
        temp=temp->next;
    }

    if(!found)
        printf("No bookings found.\n");
}

void updateTicket(){
    int id,newSeat;

    printf("Enter Booking ID : ");
    scanf("%d",&id);

    Ticket *temp=head;

    while(temp){
        if(temp->bookingID==id){

            printf("New Movie : ");
            scanf(" %[^\n]",temp->movie);

            printf("New Seat : ");
            scanf("%d",&newSeat);

            if(newSeat!=temp->seat && seatExists(newSeat)){
                printf("Seat already booked.\n");
                return;
            }

            temp->seat=newSeat;

            printf("New Date : ");
            scanf("%s",temp->date);

            printf("New Time : ");
            scanf("%s",temp->time);

            printf("Updated Successfully.\n");
            return;
        }
        temp=temp->next;
    }

    printf("Booking not found.\n");
}

void cancelTicket(){
    int id;

    printf("Enter Booking ID : ");
    scanf("%d",&id);

    Ticket *temp=head,*prev=NULL;

    while(temp){

        if(temp->bookingID==id){

            if(prev==NULL)
                head=temp->next;
            else
                prev->next=temp->next;

            printf("Ticket Cancelled.\n");
            printf("Refund Amount : %.2f\n",temp->price);

            free(temp);
            return;
        }

        prev=temp;
        temp=temp->next;
    }

    printf("Booking not found.\n");
}

void customerHistory(){
    searchCustomer();
}

void freeList(){
    Ticket *temp;
    while(head){
        temp=head;
        head=head->next;
        free(temp);
    }
}

int main(){

    int choice;

    while(1){

        printf("\n========== MOVIE TICKET BOOKING ==========\n");
        printf("1. Book Ticket\n");
        printf("2. Display Tickets\n");
        printf("3. Search by Booking ID\n");
        printf("4. Search by Customer Name\n");
        printf("5. Update Ticket\n");
        printf("6. Cancel Ticket\n");
        printf("7. Customer History\n");
        printf("8. Exit\n");

        printf("Enter Choice : ");
        if(scanf("%d",&choice)!=1){
            break;
        }

        switch(choice){

            case 1:
                bookTicket();
                break;

            case 2:
                displayTickets();
                break;

            case 3:
                searchBookingID();
                break;

            case 4:
                searchCustomer();
                break;

            case 5:
                updateTicket();
                break;

            case 6:
                cancelTicket();
                break;

            case 7:
                customerHistory();
                break;

            case 8:
                freeList();
                printf("Thank You!\n");
                return 0;

            default:
                printf("Invalid Choice.\n");
        }
    }

    freeList();
    return 0;
}
