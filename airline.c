#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Flight {
    int flightID;
    char source[20];
    char destination[20];
    char time[10];
    int economySeats;
    int businessSeats;
};

struct Passenger {
    int passengerID;
    char name[50];
    char category[10]; // "Adult" or "Child"
};

struct Booking {
    int bookingID;
    int flightID;
    char seatClass[10];
    int numPassengers;
    struct Passenger passengers[10]; // Max 10 per booking
};

int passengerCounter = 1; // Unique ID for passengers

void viewFlights(struct Flight flights[], int count) {
    printf("\nAvailable Flights:\n");
    printf("ID\tFrom\tTo\tTime\tEconomy\tBusiness\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%s\t%s\t%d\t%d\n",
               flights[i].flightID,
               flights[i].source,
               flights[i].destination,
               flights[i].time,
               flights[i].economySeats,
               flights[i].businessSeats);
    }
}

void bookTicket(struct Flight flights[], int flightCount, struct Booking bookings[], int *bookingCount) {
    int flightID, found = 0;
    char seatClass[10];
    int numPassengers;

    printf("\nEnter Flight ID to book: ");
    scanf("%d", &flightID);
    printf("Choose Class (Economy/Business): ");
    scanf(" %s", seatClass);
    printf("Enter number of passengers (max 10): ");
    scanf("%d", &numPassengers);

    if (numPassengers <= 0 || numPassengers > 10) {
        printf("Invalid number of passengers.\n");
        return;
    }

    for (int i = 0; i < flightCount; i++) {
        if (flights[i].flightID == flightID) {
            int *seats = NULL;

            if ((strcmp(seatClass, "Economy") == 0 || strcmp(seatClass, "economy") == 0))
                seats = &flights[i].economySeats;
            else if ((strcmp(seatClass, "Business") == 0 || strcmp(seatClass, "business") == 0))
                seats = &flights[i].businessSeats;

            if (seats != NULL && *seats >= numPassengers) {
                *seats -= numPassengers;
                struct Booking *b = &bookings[*bookingCount];
                b->bookingID = *bookingCount + 1;
                b->flightID = flightID;
                strcpy(b->seatClass, seatClass);
                b->numPassengers = numPassengers;

                for (int j = 0; j < numPassengers; j++) {
                    printf("Enter name for passenger %d: ", j + 1);
                    scanf(" %[^\n]", b->passengers[j].name);
                    printf("Is this passenger an Adult or Child? ");
                    scanf(" %s", b->passengers[j].category);
                    b->passengers[j].passengerID = passengerCounter++;
                }

                printf("Booking confirmed! Booking ID: %d\n", b->bookingID);
                (*bookingCount)++;
                return;
            } else {
                printf("Not enough seats available in %s class.\n", seatClass);
                return;
            }
        }
    }

    printf("Invalid flight ID.\n");
}

void viewBookings(struct Booking bookings[], int count) {
    printf("\nAll Bookings:\n");
    for (int i = 0; i < count; i++) {
        printf("\nBooking ID: %d | Flight ID: %d | Class: %s\n",
               bookings[i].bookingID,
               bookings[i].flightID,
               bookings[i].seatClass);
        for (int j = 0; j < bookings[i].numPassengers; j++) {
            printf("Passenger %d: ID: %d | %s (%s)\n",
                   j + 1,
                   bookings[i].passengers[j].passengerID,
                   bookings[i].passengers[j].name,
                   bookings[i].passengers[j].category);
        }
    }
}

int main() {
    struct Flight flights[3] = {
        {101, "NYC", "LA", "10:00", 5, 2},
        {102, "Boston", "Chicago", "12:30", 4, 2},
        {103, "Dallas", "Miami", "15:00", 6, 3}
    };

    struct Booking bookings[100];
    int bookingCount = 0;

    int choice;
    do {
        printf("\n--- Airline Ticket Booking System ---\n");
        printf("1. View Flights\n");
        printf("2. Book Ticket\n");
        printf("3. View Bookings\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: viewFlights(flights, 3); break;
            case 2: bookTicket(flights, 3, bookings, &bookingCount); break;
            case 3: viewBookings(bookings, bookingCount); break;
            case 4: printf("Thank you for using the system!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
