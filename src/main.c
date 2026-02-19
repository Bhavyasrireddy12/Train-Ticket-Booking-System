#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/structures.h"

void registerUser() {
    struct User u;
    FILE *fp = fopen("data/users.txt", "a");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n--- User Registration ---\n");
    printf("Enter User ID: ");
    scanf("%d", &u.user_id);

    printf("Enter Username: ");
    scanf("%s", u.username);

    printf("Enter Password: ");
    scanf("%s", u.password);

    fprintf(fp, "%d %s %s\n", u.user_id, u.username, u.password);
    fclose(fp);

    printf("✅ Registration successful!\n");
}

void loginUser() {
    struct User u;
    char uname[30], pass[30];
    int found = 0;

    FILE *fp = fopen("data/users.txt", "r");
    if (fp == NULL) {
        printf("No users found. Please register first.\n");
        return;
    }

    printf("\n--- User Login ---\n");
    printf("Enter Username: ");
    scanf("%s", uname);

    printf("Enter Password: ");
    scanf("%s", pass);

    while (fscanf(fp, "%d %s %s", &u.user_id, u.username, u.password) != EOF) {
        if (strcmp(u.username, uname) == 0 &&
            strcmp(u.password, pass) == 0) {
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found)
        printf("✅ Login successful! Welcome %s\n", uname);
    else
        printf("❌ Invalid username or password\n");
}

void showMenu() {
    printf("\n===== Train Ticket Booking System =====\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Add Train\n");
    printf("4. view Trains\n");
    printf("5.Exit\n");
 printf("Enter your choice: ");
}
struct Train *trainHead = NULL;

void addTrain() {
    struct Train *newTrain = (struct Train *)malloc(sizeof(struct Train));

    printf("Enter Train ID: ");
    scanf("%d", &newTrain->train_id);

    printf("Enter Train Name: ");
    scanf("%s", newTrain->train_name);

    printf("Enter Available Seats: ");
    scanf("%d", &newTrain->available_seats);

    newTrain->next = trainHead;
    trainHead = newTrain;

    printf("✅ Train added successfully\n");
}

void viewTrains() {
    struct Train *temp = trainHead;

    if (temp == NULL) {
        printf("No trains available\n");
        return;
    }

    printf("\nTrain List:\n");
    while (temp != NULL) {
        printf("ID: %d | Name: %s | Seats: %d\n",
               temp->train_id, temp->train_name, temp->available_seats);
        temp = temp->next;
    }
}
struct Passenger *bookingHead = NULL;

void bookTicket() {
    int trainID;
    struct Train *t = trainHead;

    printf("Enter Train ID to book: ");
    scanf("%d", &trainID);

    while (t != NULL && t->train_id != trainID)
        t = t->next;

    if (t == NULL || t->available_seats <= 0) {
        printf("❌ Booking failed\n");
        return;
    }

    struct Passenger *p = (struct Passenger *)malloc(sizeof(struct Passenger));
    printf("Enter Passenger Name: ");
    scanf("%s", p->passenger_name);

    p->train_id = trainID;
    p->booking_id = rand() % 1000;
    p->next = bookingHead;
    bookingHead = p;

    t->available_seats--;

    printf("✅ Ticket Booked. Booking ID: %d\n", p->booking_id);
}
void cancelTicket() {
    int bid;
    struct Passenger *temp = bookingHead, *prev = NULL;

    printf("Enter Booking ID to cancel: ");
    scanf("%d", &bid);

    while (temp != NULL && temp->booking_id != bid) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("❌ Booking not found\n");
        return;
    }

    if (prev == NULL)
        bookingHead = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("✅ Ticket cancelled\n");
}
void bookingHistory() {
    struct Passenger *p = bookingHead;

    if (p == NULL) {
        printf("No bookings found\n");
        return;
    }

    printf("\nBooking History:\n");
    while (p != NULL) {
        printf("Booking ID: %d | Train ID: %d | Name: %s\n",
               p->booking_id, p->train_id, p->passenger_name);
        p = p->next;
    }
}

int main() {
    int choice;

    while (1) {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                break;

            case 3:
                addTrain();
                break;
            case 4:
                viewTrains();
                break; 
            case 5:
                printf("Thank you for using the system.\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

