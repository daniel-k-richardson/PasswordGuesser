/**
 *  main.c: version 1.1
 *  Author: Daniel Richardson
 *  Date: 29/6/2016
 *
 *  Purpose: This is the basic logic of the password guesser program that I'm
 *  creating during in-between semester break. In very early development and 
 *  idea is for learning purposes only.
 *
 *  General idea: 
 *  1. The user will collect data on a target.
 *  2. The target data will be put into a text file.
 *  3. That text file will be read in by the program.
 *  4. The program will attempt to create the most likely
 *      password the target is using based on the input file.
 *
 *  5. Possible passwords will be consider using the logic:
 *      . The password has to be within a size range
 *      . Must contain at least one capital letter and one numeric value
 *      . Makes the assumption people will use name of pets, kids, family,
 *          sports teams etc and that many use dates associated with them.
 *
 *      . And that they won't 'exceed' the minimum password requirement by
 *          much or barely satisfy password requirements.
 *
 *      . Following the password logic above, manipulate data supplied to meet
 *          those basic password logic.
 *
 *  6. Then create a priority stack to display the most likely passwords.
 */

#include <stdio.h>
#include "linked_list.h"


/**
 *  print_list: This is used as a function pointer to be passed to traverse in
 *  order to deal with the void *data type so that it can be cast back to its
 *  original data type.
 *
 *  Params: void *data, is the value in which to print to the console.
 *
 *  Returns: void.
 */
void print_list(void *data)
{
    puts((char *) data);
}

bool search_match(void *target, void *data)
{
    if (strcmp((char *) target, (char *) data) == 0) {
        return true;
    }
    return false;
}

/**
 *  extracted_text_data: opens a text file. Reads each line, adding those words
 *  to the linked list as new nodes.
 *
 *  Params: List self, this is the list to append items from the text doc to.
 *
 *  Returns: the new list with all items added back to the caller!
 */
List extracted_text_data(List self)
{
    const unsigned buffer_size = 31;
    size_t size_of_input_string = 0;
    char buffer[buffer_size];
    FILE *fp = NULL;

    // TODO: prompt user for text location.
    if ((fp = fopen("./input.text", "r")) == NULL) {
        perror("File error");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_of_input_string = strlen(buffer) - 1;
        // need to remove newline characters at the end, otherwise
        // causes issues when traversing through the data in the linked list.
        if(buffer[size_of_input_string] == '\n') {
            buffer[size_of_input_string] = '\0';
        }
        self = insert(self, (void *) buffer, size_of_input_string);
    }
    fclose(fp);

    return self;
}


int main(void)
{
    List new_list = linked_list_init();

    //new_list = string_format()
    new_list = extracted_text_data(new_list);

    char *name = "Happy Bunny";

    traverse(new_list, &print_list);
    printf("DEBUG NUMBER OF NODES: %d\n", number_of_nodes(new_list));

    new_list = delete_item(new_list, (void *) name, &search_match);
    traverse(new_list, &print_list);
    printf("DEBUG NUMBER OF NODES: %d\n", number_of_nodes(new_list));

    return EXIT_SUCCESS;
}























