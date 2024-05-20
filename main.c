#include "functions.h"

int main(void) {
    array books;

    int number;
    puts("Input number of books you want to input");
    scanf("%d", &number);
    if (number > 0) {
        books = input_array(number);
        output_array(books);
        puts("Input a category you want to find\n1)Art Novel\n2)Dictionary\n3)Textbook");
        scanf("%d", &number);
        switch (number) {
            case 1:
                output_finded_array(find_by_category(books, ART_NOVEL));
            break;
            case 2:
                output_finded_array(find_by_category(books, DICTIONARY));
            break;
            case 3:
                output_finded_array(find_by_category(books, TEXTBOOK));
            break;
            default:
                puts("Wrong input");
        }
        puts("Input a category where you want to sirch\n1)Art Novel\n2)Dictionary\n3)Textbook");
        scanf("%d", &number);
        char detail[50];
        int typeOfDetail;
        switch (number) {
            case 1:
                puts("Input the type of detail you want to find and detail\n1)Genre\n2)Illustrator");
            scanf("%d", &typeOfDetail);
            scanf("%s", detail);
            output_finded_array(find_by_detail(books, ART_NOVEL, typeOfDetail, detail));
            break;
            case 2:
                puts("Input min and max number of words in dictionary through minus. Example: 20-100");
            scanf("%s", detail);
            output_finded_array(find_by_detail(books, DICTIONARY, "", detail));
            break;
            case 3:
                puts("Input the type of detail you want to find and detail\n1)Subject\n2)Grade");
            scanf("%d", &typeOfDetail);
            scanf("%s", detail);
            output_finded_array(find_by_detail(books, TEXTBOOK, typeOfDetail, detail));
            break;
            default:
                puts("Wrong input");
        }
        puts("Input min and max price for books to find:");
        int max, min;
        scanf("%d %d", &min, &max);
        output_finded_array(find_by_price(books, max, min));
    }
    return 0;
}
