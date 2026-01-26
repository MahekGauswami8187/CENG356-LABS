// Mahek Gauswami
// N01668187

#include <stdio.h>                           // For printf

// Define the struct exactly as in the lab sheet
struct Account {                              // Account struct definition
    unsigned int account_number;              // Unsigned int field
    char account_type;                        // Char field
    char *last_name;                          // Pointer to char (string)
    char *first_name;                         // Pointer to char (string)
    float balance;                            // Float field
    char reserved[6];                         // Reserved bytes
};

// Function to display all sizes
void displaySizes(void) {                     // Function header
    char alpaca = 'A';                        // char variable
    short bison = 10;                         // short variable
    int cougar = 100;                         // int variable
    long dolphin = 1000L;                     // long variable
    float falcon = 1.23f;                     // float variable
    double giraffe = 3.14159;                 // double variable

    int *hyena = &cougar;                     // pointer to int
    long *ibex = &dolphin;                    // pointer to long
    float *jellyfish = &falcon;               // pointer to float
    double *kangaroo = &giraffe;              // pointer to double

    struct Account llama;                     // struct Account variable
    struct Account *meerkat = &llama;         // pointer to struct Account

    printf("Sizes in bytes (using sizeof):\n");
    printf("char: %zu\n", sizeof(alpaca));
    printf("short: %zu\n", sizeof(bison));
    printf("int: %zu\n", sizeof(cougar));
    printf("long: %zu\n", sizeof(dolphin));
    printf("float: %zu\n", sizeof(falcon));
    printf("double: %zu\n", sizeof(giraffe));

    printf("pointer to int: %zu\n", sizeof(hyena));
    printf("pointer to long: %zu\n", sizeof(ibex));
    printf("pointer to float: %zu\n", sizeof(jellyfish));
    printf("pointer to double: %zu\n", sizeof(kangaroo));

    printf("struct Account: %zu\n", sizeof(llama));
    printf("pointer to struct Account: %zu\n", sizeof(meerkat));
}

int main(void) {                              // Main function
    displaySizes();                           // Call the function
    return 0;                                 // Exit successfully
}
