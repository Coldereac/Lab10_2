//
// Created by malinka on 29.04.24.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define Mem(n) (char*)malloc(n*sizeof(char))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*TODO:
 *main
 *debug
 */

typedef enum category {
    ART_NOVEL, // Художня література
    DICTIONARY, // Словник
    TEXTBOOK, // Підручник
    ERROR
} category;

typedef struct artNovelDetails {
    char *genre; // Жанр
    char *illustratorLastName; // Прізвище художника-ілюстратора
} artNovelDetails;

typedef struct textbookDetails {
    char *subject; // Предметна галузь
    int grade; // Клас
} textbookDetails;

typedef union bookDetails {
    artNovelDetails art_novel_details;
    int dictionaryWordCount; // Кількість слів у словнику
    textbookDetails textbook_details;
} bookDetails;

typedef struct book {
    char *title; // Назва
    struct Author {
        char *firstName; // Ім'я автора
        char *lastName; // Прізвище автора
    } author;

    float price; // Ціна
    int year; // Рік видання
    category category; // Категорія
    bookDetails details; // Деталі книги
} book;

typedef struct array {
    book *catalog;
    int size;
} array;

category input_category(int choice);

void input_union(book *);

book input_book();

array input_array(int);

void output_catagory(book);

void output_book(book);

void output_union(book);

void output_array(array);

void output_finded(book);

void output_finded_array(array);

array find_by_category(array, category);

array find_by_detail(array, category, int, char *);

array find_by_price(array, int max, int min);

array find_by_detail_artNovel(array books, int detail, char *searchedDetail);

array find_by_detail_dictionary(array books, char *searchedDetail);

array find_by_detail_textbook(array books, int detail, char *searchedDetail);


#endif //FUNCTIONS_H
