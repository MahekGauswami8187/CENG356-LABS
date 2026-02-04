/*
 ============================================================================
 Name        : Lab2.c
 Author      : Mahek Hastapuri Gauswami
 Student id  : N01668187
 Description : Lab 2 - Signed (8-bit two's complement) + IEEE-754 (32-bit) conversion
 ============================================================================
*/

#include <stdio.h>   // standard input/output functions (printf, scanf)
#include <stdlib.h>  // EXIT_SUCCESS, general utilities
#include <string.h>  // string handling (strlen)
#include <math.h>    // pow() for floating point calculations

// Maximum binary string size (32 bits)
#define SIZE 32

// Example predefined numbers (not used directly in program flow)
#define number1 "11000001010010000000000000000000"
#define number2 "01000001010101000000000000000000"

// Function prototypes (declarations)
void convert_binary_to_signed(const char *binary);
void convert_binary_to_float(const char *binary);

/*
 * Checks if the string is a valid binary string
 * - Must be required length
 * - Must contain only 0 or 1
 */
static int is_binary_string(const char *s, int required_len) {
    if (!s) return 0;  // if pointer is null → invalid
    if ((int)strlen(s) != required_len) return 0;  // wrong length

    // loop through characters and verify only 0 or 1
    for (int i = 0; i < required_len; i++) {
        if (s[i] != '0' && s[i] != '1') return 0;
    }
    return 1;  // valid binary string
}

/*
 * Converts binary string → unsigned integer
 * Example: "1011" → 11
 * Uses bit shifting
 */
static unsigned int bin_to_uint(const char *s, int len) {
    unsigned int v = 0;

    for (int i = 0; i < len; i++) {
        // shift left by 1 bit and add next digit
        v = (v << 1) | (unsigned int)(s[i] - '0');
    }

    return v;
}

/*
 * Menu text displayed to the user
 */
char *menu =
        "\n"
        "===================================================================\n"
        "************Please select the following options********************\n"
        " *    1. Binary number to signed decimal number conversion.(Lab 2) *\n"
        " *    2. Binary number to Floating number conversion (Lab 2)       *\n"
        " *******************************************************************\n"
        " *    e. To Exit, Type 'e'                                         *\n"
        " *******************************************************************\n";

int main(void) {
    char options;          // stores menu option
    char inputs[33] = {0}; // holds binary string (32 bits + null terminator)

    // infinite loop until user exits
    while (1) {
        puts(menu);  // print menu

        // read single character option (ignores whitespace)
        scanf(" %c", &options);

        switch (options) {

            case '1':
                puts("Please input your 8-bit BINARY number (example: 11111111):");
                scanf("%32s", inputs);  // safely read string
                convert_binary_to_signed(inputs);
                break;

            case '2':
                puts("Please input your 32-bit floating point number in binary:");
                scanf("%32s", inputs);
                convert_binary_to_float(inputs);
                break;

            case 'e':
                puts("Code finished, exit now");
                return EXIT_SUCCESS;

            default:
                puts("Not a valid entry. Try again.");
                break;
        }
    }
}

/*
 * Option 1
 * Converts 8-bit two’s complement → signed decimal
 */
void convert_binary_to_signed(const char *binary) {

    // validate input
    if (!is_binary_string(binary, 8)) {
        printf("Error: Option 1 requires EXACTLY 8 bits (only 0/1).\n");
        return;
    }

    // convert to unsigned value
    unsigned int u = bin_to_uint(binary, 8);

    int signed_val;

    // check sign bit (MSB = bit 7)
    if (u & 0x80u) {
        // negative number → subtract 256
        signed_val = (int)u - 256;
    } else {
        signed_val = (int)u;
    }

    // display result
    printf("Binary (8-bit): %s\n", binary);
    printf("Signed decimal: %d\n", signed_val);
}

/*
 * Option 2
 * Converts 32-bit IEEE-754 binary → float
 */
void convert_binary_to_float(const char *binary) {

    // validate input
    if (!is_binary_string(binary, 32)) {
        printf("Error: Option 2 requires EXACTLY 32 bits (only 0/1).\n");
        return;
    }

    // sign bit (first bit)
    int sign = (binary[0] == '1') ? -1 : 1;

    // exponent bits (next 8 bits)
    unsigned int exp_bits  = bin_to_uint(binary + 1, 8);

    // fraction/mantissa bits (last 23 bits)
    unsigned int frac_bits = bin_to_uint(binary + 9, 23);

    const int bias = 127;  // IEEE-754 bias

    // special case: infinity or NaN
    if (exp_bits == 255) {
        printf("Binary (32-bit): %s\n", binary);

        if (frac_bits == 0)
            printf("Float value: %sInfinity\n", (sign < 0) ? "-" : "+");
        else
            printf("Float value: NaN\n");

        return;
    }

    double frac = 0.0;

    // subnormal numbers
    if (exp_bits == 0) {

        // fraction only (no leading 1)
        for (int i = 0; i < 23; i++) {
            if (binary[9 + i] == '1')
                frac += pow(2.0, -(i + 1));
        }

        double value = sign * frac * pow(2.0, 1 - bias);

        printf("Binary (32-bit): %s\n", binary);
        printf("Float value: %.10g\n", value);

    } else {

        // normalized number → implicit leading 1
        frac = 1.0;

        for (int i = 0; i < 23; i++) {
            if (binary[9 + i] == '1')
                frac += pow(2.0, -(i + 1));
        }

        int exp = (int)exp_bits - bias;
        double value = sign * frac * pow(2.0, exp);

        printf("Binary (32-bit): %s\n", binary);
        printf("Float value: %.10g\n", value);
    }
}
