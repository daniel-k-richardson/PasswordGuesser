//
//  Linked_List.h
//  PasswordGuesser
//
//  Created by Daniel Richardson on 28/06/2016.
//  Copyright © 2016 edu.utas.Daniel. All rights reserved.
//

#ifndef Linked_List_h
#define Linked_List_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node *List;

List insert(List self, void *data, size_t size);
List delete_item(List self, void *target, bool (*search)(void *target, void *data));
void traverse(List self, void (*print)(void *));
int number_of_nodes(List self);

#endif /* Linked_List_h */
