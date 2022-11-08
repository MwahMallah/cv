#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//number of characters in one line
int MAX_NUMBER_IN_LINE = 100;

//two-dimensional array, which represents number to charachter relationship 
//2 -> ('a','b','c'), 3 -> ('d','e','f') and so on 
char number_to_letter[10][4] = {{'+'},{},{'a', 'b', 'c'}, {'d','e','f'}, {'g','h','i'}, {'j','k','l'},{'m','n','o'},{'p','q','r','s'},
{'t','u','v'},{'w','x','y','z'}};


void print_all_contacts(char*);
int check_name(char*, int, char*, int);
int check_phone_number(char*, int, char*, int);

int main(int argc, char* argv[])
{
    //arrays of characters which stores one line from contact list
    char name[MAX_NUMBER_IN_LINE];
    char phone_number[MAX_NUMBER_IN_LINE];

    //indicator of standard behavior of the program
    int flag = 0;
    //stores phone input in a phone_input variable
    char* phone_input = argv[1];

    // checks if there is no phone input
    if (argc == 1)
    {
        // prints all contacts from the list
        print_all_contacts(name);
        return 0;
    }

    //checks if there is only one argument to programm
    else if (argc == 2)
    {
        int length_input = strlen(argv[1]);

        //checks if input is a number and returns error if it is not
        for (int i = 0; i < length_input; i++)
        {
            if (isdigit(argv[1][i]) == 0)
            {
                fprintf(stderr, "argument is not a number\n");
                return 1;
            }
        }
    }

    //checks if there are phone input and one additional argument
    else if (argc == 3)
    {
        //checks if first argument is "-s"
        if (strcmp(argv[1], "-s") == 0)
        {
            //switches behaviour to searching for cuted sequences of characters
            flag = 1;

            int length_input = strlen(argv[2]); 

            //checks if input is a number and returns error if it is not
            for (int i = 0; i < length_input; i++)
            {
                if (isdigit(argv[2][i]) == 0)
                {
                    fprintf( stderr, "argument is not a number\n");
                    return 1;
                }
            }
            phone_input = argv[2];
        }
        //checks if second argument is "-s"
        else if(strcmp(argv[2], "-s") == 0)
        {
            //switches behaviour to searching for cuted sequences of characters
            flag = 1;

            int length_input = strlen(argv[1]);

            //checks if input is a number and returns error if it is not
            for (int i = 0; i < length_input; i++)
            {
                if (isdigit(argv[1][i]) == 0)
                {
                    fprintf( stderr, "argument is not a number\n");
                    return 1;
                }
            }
        }
    }

    //if there is more than 3 arguments returns error
    else 
    {
        fprintf( stderr, "too many arguments\n");
        return 1;
    }


    //finds length of phone input
    int length_of_input = strlen(phone_input);
    int person_counter = 0;

    //reads every name from contact list and stores it at name array, untill contact list is not empty
    while (fgets(name, MAX_NUMBER_IN_LINE, stdin))
    {
        //stores phone number of person to phone_number array
        fgets(phone_number, MAX_NUMBER_IN_LINE, stdin);

        //checks if phone input is equal to sequence in name or in phone number
        if ((check_name(phone_input, length_of_input, name, flag) == 0) || (check_phone_number(phone_input, length_of_input, phone_number, flag) == 0))
        {
            //removes newline character from name and prints person's name and phone number
            name[strlen(name)-1] = '\0';
            printf("%s, %s", name, phone_number);

            //increases counter of found persons
            person_counter++;
        } 
    }

    //if noone was found prints "Not found"
    if (person_counter == 0)
    {
        printf("Not found\n");
        return 0;
    }

    return 0;
}


void print_all_contacts(char str[])
{
    //reads every line of contact list and stores it at str array, untill contact list is not empty
    while (fgets(str, MAX_NUMBER_IN_LINE, stdin) != NULL)
    {
        //removes newline character from str variable and prints name of person
        str[strlen(str) - 1] = '\0';
        printf("%s, ", str);

        //reads phone number of person, stores it in str array and prints it 
        fgets(str, 100, stdin);
        printf("%s", str);
    }
}


int check_phone_number(char* phone_input, int input_length, char* phone_number, int flag)
{
    int number_length = strlen(phone_number);
    int j = -1;

    //iterate over every digit in phone input
    for (int i = 0; i < input_length; i++)
    {
        //iterate over every digit in phone number, starting from the next digit, where was last equality
        for ( ; j < number_length; j++)
        {
            //checks if digit from the phone input was equal to digit in phone number and sets pass variable to successfull state
            if (phone_input[i] == phone_number[j])
            {
                j++;                
                break;
            }

            if (flag == 0)
            {
                j -= i;
                i = 0;
            }
        }

        //checks pass variable to check if this iteration of cycle was successfull 
        if (j == number_length)
        {
            return 1;
        }
    }
    return 0;
}

 int check_name(char* phone_input, int input_length, char* name, int flag)
{
    int name_length = strlen(name);
    int pass;
    int j = 0;

    //iterate over every digit in phone input
    for (int i = 0; i < input_length; i++)
    {
        pass = 1;

        //iterate over every character in name, starting from the next character, where was last equality
        for ( ; j < name_length; j++)
        {
            int index_to_letter = phone_input[i] - '0';
            //iterate over every character in two-dimensional array
            for (int k = 0; k < 4; k++)
            {
                //checks if letter from two-dimensional array is equal to lowercased character from name and sets pass variable to successfull state
                if (number_to_letter[index_to_letter][k] == tolower(name[j]))
                {
                    pass = 0;
                    j++;
                    break;
                }
            }

            if (pass == 0)
            {
                break;
            }
            
            if (flag == 0)
            {
                j -= i;
                i = 0;
            }
        }

        //checks pass variable to check if this iteration of cycle was successfull 
        if (pass == 1)
        {
            return 1;
        }
    }

    return 0;
} 

