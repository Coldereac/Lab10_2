//
// Created by malinka on 29.04.24.
//

#include "functions.h"

#include <ctype.h>

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
            strcpy(result->details.art_novel_details.illustratorLastName = Mem(strlen(temp)) + 1, temp);
            break;
        case DICTIONARY:
            puts("Input number of words");
            scanf("%d", result->details.dictionaryWordCount);
            break;
        case TEXTBOOK:
            puts("Input subject");
            gets(temp);
            strcpy(result->details.textbook_details.subject = Mem(strlen(temp)) + 1, temp);
            puts("Input grade");
            scanf("%d", &result->details.textbook_details.grade);
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
            } else {
                inputing = 0;
            }
        }
        i++;
    }
    return result;
}

void output_catagory(book _book) {
    switch (_book.category) {
        case ART_NOVEL:
            puts("Category: Art Novel");
            break;
        case DICTIONARY:
            puts("Category: Dictionary");
            break;
        case TEXTBOOK:
            puts("Category: Textbook");
            break;
    }
}

void output_union(book _book) {
    switch (_book.category) {
        case ART_NOVEL:
            printf("Genre: %s\n Last name of the illustator: %s\n", _book.details.art_novel_details.genre,
                   _book.details.art_novel_details.illustratorLastName);
            break;
        case DICTIONARY:
            printf("Number of words: %d\n", _book.details.dictionaryWordCount);
            break;
        case TEXTBOOK:
            printf("Subject: %s\n Grade: %d\n", _book.details.textbook_details.subject,
                   _book.details.textbook_details.grade);
            break;
    }
}

void output_book(book _book) {
    printf("Title: %s\n", _book.title);
    printf("Author: %s %s\n", _book.author.firstName, _book.author.lastName);
    printf("Year of release: %d\n", _book.year);
    printf("Price: %f\n", _book.price);
    output_catagory(_book);
    output_union(_book);
}

void output_array(array books) {
    for (int i = 0; i < books.size; ++i) {
        output_book(books.catalog[i]);
    }
}

array find_by_category(array books, category searched) {
    array result;
    result.size = 0;
    result.catalog = (book *) malloc(books.size * sizeof(book));
    for (int i = 0; i < books.size; ++i) {
        if (books.catalog[i].category == searched) {
            result.catalog[result.size++] = books.catalog[i];
        }
    }
    result.catalog = (book *) realloc(result.catalog, result.size * sizeof(book));
    return result;
}

char *lowering(const char *str) {
    char *result = Mem(strlen(str)+1);
    while (*str != '\0') {
        *result++ = tolower(*str);
    }
    return result;
}

array find_by_detail_artNovel(array books, char *detail, char *searchedDetail) {
    array result;
    result.size = 0;
    result.catalog = (book *) malloc(books.size * sizeof(book));
    switch (lowering(detail)) {
        case "genre":
            for (int i = 0; i < books.size; ++i) {
                    if (strcasecmp(books.catalog[i].details.art_novel_details.genre, searchedDetail)) {
                        result.catalog[result.size++] = books.catalog[i];
                    }
            }
            break;
        case "illustrator":
            for (int i = 0; i < books.size; ++i) {
                    if (strcasecmp(books.catalog[i].details.art_novel_details.illustratorLastName, searchedDetail)) {
                        result.catalog[result.size++] = books.catalog[i];
                    }
            }
    }
    result.catalog = (book *) realloc(result.catalog, result.size * sizeof(book));
    return result;
}

array find_by_detail_dictionary(array books, char *searchedDetail) {
    array result;
    result.size = 0;
    result.catalog = (book *) malloc(books.size * sizeof(book));
    int searchedWordCount = atoi(searchedDetail);
    for (int i = 0; i < books.size; ++i) {
        if (books.catalog[i].details.dictionaryWordCount == searchedWordCount) {
            result.catalog[result.size++] = books.catalog[i];
        }
    }
    result.catalog = (book *) realloc(result.catalog, result.size * sizeof(book));
    return result;
}

array find_by_detail_textBook(array books, char *detail, char *searchedDetail) {
    array result;
    result.size = 0;
    result.catalog = (book *) malloc(books.size * sizeof(book));
    switch (lowering(detail)) {
        case "subject":
            for (int i = 0; i < books.size; ++i) {
                if (strcasecmp(books.catalog[i].details.textbook_details.subject, searchedDetail)) {
                    result.catalog[result.size++] = books.catalog[i];
                }
            }
            break;
        case "grade":
            int grade = atoi(searchedDetail);
            for (int i = 0; i < books.size; ++i) {
                if (books.catalog[i].details.textbook_details.grade == grade) {
                    result.catalog[result.size++] = books.catalog[i];
                }
            }
            break;
    }
    result.catalog = (book *) realloc(result.catalog, result.size * sizeof(book));
    return result;
}


array find_by_price(array books, int max, int min) {
    array result;
    result.size = 0;
    result.catalog = (book *) malloc(books.size * sizeof(book));
    for (int i = 0; i < books.size; ++i) {
        if (books.catalog[i].price <= max && books.catalog[i].price <= min) {
            result.catalog[result.size++] = books.catalog[i];
        }
    }
    result.catalog = (book *) realloc(result.catalog, result.size * sizeof(book));
    return result;
}

void freeBook(book _book) {
    free(_book.title);
    free(_book.author.firstName);
    free(_book.author.lastName);
    switch (_book.category) {
        case ART_NOVEL:
            free(_book.details.art_novel_details.genre);
            free(_book.details.art_novel_details.illustratorLastName);
            break;
        case TEXTBOOK:
            free(_book.details.textbook_details.subject);
            break;
    }
}

void freeArray(array books) {
    for (int i = 0; i < books.size; ++i) {
        freeBook(books.catalog[i]);
    }
    free(books.catalog);
}

array find_by_detail(array books, category searchedCategory, char *detail, char *searchedDetail) {
    array result;
    result.size = 0;
    result.catalog = NULL;
    array filtered = find_by_category(books, searchedCategory);
    if (filtered.size != 0) {
        switch (searchedCategory) {
            case ART_NOVEL:
                result = find_by_detail_artNovel(filtered, detail, searchedDetail);
            break;
            case TEXTBOOK:
                result = find_by_detail_textBook(filtered, detail, searchedDetail);
            break;
            case DICTIONARY:
                result = find_by_detail_dictionary(filtered, searchedDetail);
            break;
        }
    }
    freeArray(filtered);
    return result;
}
