#ifndef STRUCTURES_H
#define STRUCTURES_H

struct User {
    int user_id;
    char username[30];
    char password[30];
};

struct Train {
    int train_id;
    char train_name[50];
    int available_seats;
    struct Train *next;    
};

struct Passenger {
    int booking_id;
    int user_id;
    int train_id;
    char passenger_name[50];
    struct Passenger *next;
};

#endif
