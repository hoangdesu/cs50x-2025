#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    struct Student {
        int id;
        char name[20];
    }; // semi-colon required

    // Must use the `struct` keyword, followed by the name of the structure, then the name of the structure variable
    // struct + StructName + structVar
    struct Student s1;
    s1.id = 1;

    // Error: array type 'char[20]' is not assignable
    // s1.name = "Brian";

    // Cannot assign a value to array. Must use strcpy
    strcpy(s1.name, "Brian");

    printf("Student 1: id=%d, name=%s\n", s1.id, s1.name);

    // Shorter syntax. No need strcpy. Order matters
    // - C89-style initializers
    // - contiguous members 
    struct Student s2 = {2, "Hoang Nguyen"};
    printf("Student 2: id=%d, name=%s\n", s2.id, s2.name);
    

    // For non contiguous or out of order members list, 'designated initializer' style may be used.
    struct Student s3 = { .name = "Lewis", .id = 4 };
    printf("Student 3: id=%d, name=%s\n", s3.id, s3.name);


    // Declare an new struct with values init to 0. Clear garbage values from previous programs
    struct Student s4 = {0};
    printf("Student 4: id=%d, name=%s\n", s4.id, s4.name);


    // Copy structs
    // - values are copied, not referenced. No values are not affected
    struct Student copied_s2 = s2;
    copied_s2.id = 3;
    strcpy(copied_s2.name, "Nguyen Quoc Hoang");

    printf("Copied Student 2: id=%d, name=%s\n", copied_s2.id, copied_s2.name);
    printf("Student 2: id=%d, name=%s\n", s2.id, s2.name);


    // Named Structures (Tagged Structures) vs Unnamed Structures (Anonymous Structures)
    // - above struct has a tag 'Student'
    // - An unnamed structure is declared without a tag. 
    // - It can only be used IMMEDIATELY to declare variables 
    // - or as part of a typedef declaration to create an alias for the structure type.

    struct {
        char name[10];
        int price;
    } ferrari;

    strcpy(ferrari.name, "SF90");
    ferrari.price = 600000;
    printf("%s: $%d\n", ferrari.name, ferrari.price);


    // Declare and assign values in 1 go
    struct {
        char name[20];
        int price;
    } porsche = {"Porsche 911", 100000};

    printf("%s: $%d\n", porsche.name, porsche.price);


    // Cannot do sth like this. Must define a struct first
    // struct merc = {"Merc", 100};
    

    // Using `typedef` with an unnamed structure
    // calling this whole struct "Car"
    typedef struct {
        char brand[20];
        int price;
    } Car;

    // no need to use the `struct` keyword when declaring variables
    // use `Car` as a type
    Car lambo = {"Lamborghini", 1234567};
    printf("%s: $%d\n", lambo.brand, lambo.price);

    Car mclaren = {"McLaren", 1999999};
    printf("%s: $%d\n", mclaren.brand, mclaren.price);
    
    printf("sizeof(mclaren): %lu\n", sizeof(mclaren)); // 24 bytes = char 1 byte * 20 + int 4 bytes

    // A struct occupies a contiguous block of memory
    printf("%p - %p\n", &mclaren.brand[19], &mclaren.price);
    

    // Using struct with pointer: must dynamically allocate size for the struct
    Car *my_car = malloc(sizeof(Car));
    if (my_car == NULL)
    {
        return 1;
    }
    strcpy(my_car->brand, "Mercedes AMG GT One");
    my_car->price = 1000000;
    printf("My car is a %s: $%d\n", my_car->brand, (*my_car).price);


    // Can also have tagged struct with typedef, but redundant and not necessary
    typedef struct City_Struct {
        int num;
        char name[20];
    } City;

    City saigon = { .name = "Saigon", .num = 50 };
    City hanoi = {30, "Hanoi"};

    printf("%s: %d\n", saigon.name, saigon.num);
    printf("%s: %d\n", hanoi.name, hanoi.num); 

    // also valid, but redundant
    struct City_Struct vinh = {37, "Vinh"};
    printf("%s: %d\n", vinh.name, vinh.num);


    // Note: my_node is NOT a nickname to node, but an actual record created from node structure
    struct node {
        int id;
        char name;
    } my_node;

    struct node a = {0};
    struct node b;

    printf("a.id: %d - b.name: %c\n", a.id, b.name);
    printf("my_node.id: %d\n", my_node.id);


    return 0;
}