#include <stdlib.h>

struct person
{
    int id;
    char name[25];
    int age;
};

typedef struct person person;

struct node
{
    struct person data;
    struct node *next;
};

typedef struct node node;

node* head = NULL;
/*
    head ostaje NULL sve dok se ne doda prvi element u listu!
    node* new_node = (struct node *)malloc(sizeof(struct node));
    funkcija za dodavanje treba da bude univerzalna u odnosu na trenutni broj elemenata liste,
    tj. da prvo nadje zadnji element pa na njega da dodaje
*/

int main(int argc, char* argv[])
{
    /*
        Zadaci:
            zadatak (a): Napisati funkcije za dodavanje elemenata na pocetak, kraj i iza
                         zadanog (pomocu pokazivaca) elementa liste
            zadatak (b): Napisati funkcije find_element i for_each za istu listu

            Sve istestirati u okviru ove main funkcije  
    */
    return 0;
}
