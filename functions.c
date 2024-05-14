//
// Created by malinka on 29.04.24.
//

#include "functions.h"

category input_category(int choice) {
    category result;
    switch (choice) {
        case 1:
            result = ART_NOVEL;
            break;
        case 2:
            result = DICTIONARY;
            break;
        case 3:
            result = TEXTBOOK;
            break;
        default:
            puts("Error");
            result = ERROR;
    }
    return result;
}

void input_union(book *result) {
    char temp[100];
    switch (result->category) {
        case ART_NOVEL:
            puts("Input genre");
            gets(temp);
            strcpy(result->details.art_novel_details.genre = Mem(strlen(temp)) + 1, temp);
            puts("Input illustrator's lastname");
            gets(temp);
            strcpy(result->details.art_novel_details.illustrator = Mem(strlen(temp)) + 1, temp);
            break;
        case DICTIONARY:
            puts("Input number of words");
            scanf("%d", result->details.dictionaryWordCount);
            break;
        case TEXTBOOK:
            puts("Input subject");
            gets(temp);
            strcpy(result->details.text_textbook_details.subject = Mem(strlen(temp)) + 1, temp);
            puts("Input grade");
            scanf("%d", &result->details.text_textbook_details.grade);
            break;
    }
}

book input_book() {
    puts("Input category:\n1) Art Novel\n2) Dictionary\n3) Textbook");
    int choice;
    scanf("%d", &choice);
    book result;
    result.category = input_category(choice);
    if (result.category != ERROR) {
        char temp[100];
        puts("Input title");
        gets(temp);
        strcpy(result.title = Mem(strlen(temp)) + 1, temp);
        puts("Input Author(first name and last name");
        gets(temp);
        strcpy(result.author.firstName = Mem(strlen(temp)) + 1, temp);
        gets(temp);
        strcpy(result.author.lastName = Mem(strlen(temp)) + 1, temp);
        puts("Input price");
        scanf("%f", &result.price);
        puts("Input release year");
        scanf("%d", &result.year);
        input_union(&result);
    } else {
        puts("Wrong input");
    }
    return result;
}

array input_array(int size) {
    array result;
    result.catalog = (book *) malloc(size * sizeof(book));
    result.size = size;
    int i = 0;
    int inputing = 1;
    while (i < result.size && inputing) {
        result.catalog[i] = input_book();
        if (result.catalog[i].category == ERROR) {
            puts("You want to continue input and try again?[y/n]");
            char choice = getchar();
            if (choice == 'y' || choice == 'Y') {
                i--;
            }
            else {
                inputing = 0;
            }
        }
        i++;
    }
    return result;
}
