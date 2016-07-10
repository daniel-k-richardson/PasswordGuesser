/**
 *  Author: Daniel Richardson
 *  Date: 28/6/2016
 *  Version: 1.1
 *  Purpose: This is a generic link-list that uses a void pointer in order to store
 *  data. It is a minimalistic version of a linked-list data structure for the sole
 *  purposes of the current project and is its the first iterations.
 */

#include "linked_list.h"

// DTA for the linked-list.
struct Node {
    void *data;
    struct Node *next;
};

typedef struct Node *Node;

struct Linked_List {
    Node head;
    Node tail;
};


void free_node_memory(Node self);

/**
 *  //TODO ADD SOME COMMENTS.
 */
List linked_list_init()
{
    List new_list = NULL;

    if ((new_list = malloc(sizeof(*new_list))) == NULL) {
        perror("Error: allocating memory for List\n");
        exit(EXIT_FAILURE);
    }
    new_list->head = NULL;
    new_list->tail = NULL;

    return new_list;
}

/**
 *  node_init: creates a new_node in memory then creates memory for the data
 *  then returns to newly created node back to the caller.
 *
 *  Params: void *data is the data that will be stored in the node.
 *          size_t is the size of the memory needed to store the data.
 *
 *  Returns: A new_node that has been initialised back to the caller.
 */
Node node_init(void *data, size_t size)
{
    Node new_node = NULL;

    if ((new_node = malloc(sizeof(*new_node))) == NULL) {
        perror("Error: allocating memory for node\n");
        exit(EXIT_FAILURE);
    }

    if ((new_node->data = malloc(sizeof(size))) == NULL){
        perror("Error: allocating memory for data\n");
        exit(EXIT_FAILURE);
    }

    memcpy(new_node->data, data, size);
    new_node->next = NULL;

    return new_node;
}

/**
 *  insert: Creates a new node and inserts at front.
 *
 *  Params: List self, the list to add a node to.
 *          void *data, the data to be stored inside the node.
 *          size_t size, the size of the data to be created in memory.
 *
 *  Returns: This returns a new linked list with the new node at the front.
 */
List insert(List self, void *data, size_t size)
{
    Node node_to_add = node_init(data, size);

    if (self->head == NULL) {
        self->head = node_to_add;
        self->tail = self->head;
    } else {
        self->tail->next = node_to_add;
        self->tail = self->tail->next;
    }
    return self;
}

/**
 *  delete_item: searches for the target data to remove from the linked list and
 *  returns a new list with the item removed.
 *
 *  Params: List self, the linked_list to remove item from,
 *          void *target, the target data to search and remove if found.
 *          bool (*search) (void *target, void *data), a function pointer for
            handling the matching process by casting back to original data type.
 *
 *  Return: The list after the deletetion has been done, or the orgional list if
 *  the target to find and remove doesn't exisit in the list.
 */
List delete_item(List self, void *target, bool (*search)(void *target, void *data))
{
    Node current = self->head;
    Node previous = NULL;

    while (current != NULL) {
        if (search(target, current->data)) {
            if (previous == NULL) {
                self->head = current->next;
                free_node_memory(current);
            } else {
                previous = current->next;
                free_node_memory(current);
                current = previous->next;
            }
        } else {
            previous = current;
            current = current->next;
        }
    }
    return self;
}

/**
 *  free_node_memory: a convenience way to free a nodes memory while deleting items.
 *
 *  Params: List self, this is the target to be freed.
 *
 *  Returns: void.
 */
void free_node_memory(Node self)
{
    free(self->data);
    free(self);
    self->data = NULL;
    self = NULL;
}

/**
 *  traverse: prints all elements within the linked-list nodes.
 *
 *  Params: List self, the list that we want to traverse through.
 *          void (*print)(void *data), a function pointer that takes
 *          a void pointer type to cast back to original data type and
 *          print it to the console.
 *
 *  Returns: void.
 */
void traverse(List self, void (*print)(void *data))
{
    Node current = self->head;

    while (current != NULL) {
        print(current->data);
        current = current->next;
    }
}

/**
 *  number_of_nodes: this counts the total number of nodes inside the linked-list.
 *
 *  Params: List self, the linked-list to count the number of nodes from.
 *
 *  Returns: int, the number of nodes found inside the list.
 */
int number_of_nodes(List self)
{
    int counter = 0;

    Node current = self->head;
    while (current != NULL) {
        counter++;
        current = current->next;
    }
    return counter;
}