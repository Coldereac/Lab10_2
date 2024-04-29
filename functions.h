//
// Created by malinka on 29.04.24.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef enum Category {
    ART_NOVEL, // Художня література
    DICTIONARY, // Словник
    TEXTBOOK // Підручник
} Category;

 typedef struct ArtNovelDetails {
    char genre[30]; // Жанр
    char illustrator[30]; // Прізвище художника-ілюстратора
} artNovelDetails;

typedef struct TextbookDetails {
    char subject[30]; // Предметна галузь
    int grade; // Клас
} textbookDetails;

typedef union BookDetails {
    artNovelDetails art_novel_details;
    int dictionaryWordCount; // Кількість слів у словнику
    textbookDetails text_textbook_details;
} BookDetails;

typedef struct Book {
    char *title; // Назва
    struct Author {
        char *firstName; // Ім'я автора
        char *lastName; // Прізвище автора
    } author;
    float price; // Ціна
    int year; // Рік видання
    Category category; // Категорія
    BookDetails details; // Деталі книги
} Book;

#endif //FUNCTIONS_H
