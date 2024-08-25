#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Note to TF: Hello! I didn't use abstraction in this code because I found the flow/algorithm easier to make when it was kept together, and
// I thought it'd kinda defeat the purpose of efficiency if I had to go back and purposefully abstract my code when that wasn't the way I wrote it.
// I talked to my section leader, Carter, who said it was okay to keep it like this for PSET 1 and wouldn't impact my Design score,
// but I understand the usefulness of abstraction after section and will begin implementing it in my future psets as part of my process. Thank you!

int main(void)
{
    // prompt user for credit card number
    long id = get_long("Number: ");

    // CHECK IF NUMBER OF DIGITS IS VALID
    int j = 0;
    long copy = id;
    // get number of digits
    while (copy > 0)
    {
        copy = copy / 10;
        j++;
    }

    // CHECK IF STARTING TWO DIGITS OF ID IS VALID
    string type = "INVALID";
    // set flag to prevent inefficiently checking Luho's alg later card isn't even valid
    bool flag = 1;
    long digi = id;
    digi = id / (pow(10, j - 2));
    if ((digi == 34 || digi == 37) && j == 15)
    {
        type = "AMEX";
    }
    else if ((digi == 51 || digi == 52 || digi == 53 || digi == 54 || digi == 55) && j == 16)
    {
        type = "MASTERCARD";
    }
    else if ((digi / 10 == 4) && (j == 13 || j == 16))
    {
        type = "VISA";
    }
    else
    {
        // set flag to 0, do not proceed
        flag = 0;
        printf("INVALID\n");
    }

    // CHECK LUHO'S ALGORITHM - do not proceed if card isn't valid
    if (flag)
    {
        // int variable that gets multiplied by 2
        int mult_two = 0;
        // int variable that is not multiplied by 2
        int no_mult = 0;

        // traverse through all digits, starting from last
        for (int i = 0; i < j; i++)
        {
            // sum every other digit, starting from last digit
            if (i % 2 == 0)
            {
                no_mult += id % 10;
            }
            // if loop is in every odd (other) digit
            else
            {
                int d_digit = 2 * (id % 10);
                // if value of d_digit exceeds ten, take sum of digits
                if (d_digit >= 10)
                {
                    mult_two += d_digit % 10 + d_digit / 10;
                }
                else
                {
                    mult_two += d_digit;
                }
            }
            // remove last digit in each traversal of loop
            id = id / 10;
        }
        // check if sum of the digits by Luho's alg is divisble by 10
        int sum_digits = no_mult + mult_two;
        if (sum_digits % 10 == 0)
        {
            printf("%s\n", type);
        }
        else
        {
            printf("INVALID\n");
        }
    }
}
