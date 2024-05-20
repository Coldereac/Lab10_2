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
            getchar();
            gets(temp);
            strcpy(result->details.art_novel_details.genre = Mem(strlen(temp)) + 1, temp);
            puts("Input illustrator's lastname");
            gets(temp);
            strcpy(result->details.art_novel_details.illustratorLastName = Mem(strlen(temp)) + 1, temp);
            break;
        case DICTIONARY:
            puts("Input number of words");
            scanf("%d", &result->details.dictionaryWordCount);
            break;
        case TEXTBOOK:
            puts("Input subject");
            getchar();
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
        getchar();
        gets(temp);
        strcpy(result.title = Mem(strlen(temp)) + 1, temp);
        puts("Input Author(first name and last name)");
        scanf("%s", temp);
        strcpy(result.author.firstName = Mem(strlen(temp)) + 1, temp);
        scanf("%s", temp);
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
    for (int i = 0; i < result.size; ++i) {
        result.catalog[i] = input_book();
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
            printf("Genre: %s\nLast name of the illustator: %s\n", _book.details.art_novel_details.genre,
                   _book.details.art_novel_details.illustratorLastName);
            break;
        case DICTIONARY:
            printf("Number of words: %d\n", _book.details.dictionaryWordCount);
            break;
        case TEXTBOOK:
            printf("Subject: %s\nGrade: %d\n", _book.details.textbook_details.subject,
                   _book.details.textbook_details.grade);
            break;
    }
}

void output_book(book _book) {
    printf("Title: %s\n", _book.title);
    printf("Author: %s %s\n", _book.author.firstName, _book.author.lastName);
    printf("Year of release: %d\n", _book.year);
    printf("Price: %.2f\n", _book.price);
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

array find_by_detail_artNovel(array books, int detail, char *searchedDetail) {
    array result;
    result.size = 0;
    result.catalog = (book *) malloc(books.size * sizeof(book));
    switch (detail) {
        case 1:
            for (int i = 0; i < books.size; ++i) {
                if (strcasecmp(books.catalog[i].details.art_novel_details.genre, searchedDetail) == 0) {
                    result.catalog[result.size++] = books.catalog[i];
                }
            }
            break;
        case 2:
            for (int i = 0; i < books.size; ++i) {
                if (strcasecmp(books.catalog[i].details.art_novel_details.illustratorLastName, searchedDetail) == 0) {
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
    int searchedWordCountMin = atoi(strtok(searchedDetail, "-"));
    int searchedWordCountMax = atoi(strtok(NULL, "-"));
    for (int i = 0; i < books.size; ++i) {
        if (books.catalog[i].details.dictionaryWordCount >= searchedWordCountMin && books.catalog[i].details.
            dictionaryWordCount <= searchedWordCountMax) {
            result.catalog[result.size++] = books.catalog[i];
        }
    }
    result.catalog = (book *) realloc(result.catalog, result.size * sizeof(book));
    return result;
}

array find_by_detail_textbook(array books, int detail, char *searchedDetail) {
    array result;
    result.size = 0;
    result.catalog = (book *) malloc(books.size * sizeof(book));
    switch (detail) {
        case 1:
            for (int i = 0; i < books.size; ++i) {
                if (strcasecmp(books.catalog[i].details.textbook_details.subject, searchedDetail) == 0) {
                    result.catalog[result.size++] = books.catalog[i];
                }
            }
            break;
        case 2:
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
        if (books.catalog[i].price <= max && books.catalog[i].price >= min) {
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

array find_by_detail(array books, category searchedCategory, int detail, char *searchedDetail) {
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
                result = find_by_detail_textbook(filtered, detail, searchedDetail);
                break;
            case DICTIONARY:
                result = find_by_detail_dictionary(filtered, searchedDetail);
                break;
        }
        return result;
    }
}

void output_finded(book finded) {
    printf("Title: %s\n", finded.title);
    printf("Author: %s\n", finded.author.lastName);
    printf("Price: %.2f\n", finded.price);
}

void output_finded_array(array finded) {
    for (int i = 0; i < finded.size; ++i) {
        output_finded(finded.catalog[i]);
    }
}
