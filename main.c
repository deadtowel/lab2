#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_lab10.h"

int main(){
    FILE *pFile = GetFileFromUser();
    stList *pHead = CreateStudentList(pFile);
    fclose(pFile);
    puts("\nYour list:");
    PrintList(pHead);
    int iChoice;
    while (1){
        iChoice = ShowMenuAndGetChoice();
        if (iChoice < 1 || iChoice > 6){
            puts("Wrong number!");
            continue;
        }
        switch (iChoice){
            case 1:
       	SortListReversedToAlphabeticalOrder(&pHead);
                puts("Done!");
                break;
            case 2:
                puts("What mark?");
                scanf("%d", &iChoice);
                DeleteStudentsWithMarkN(&pHead,
iChoice);
                puts("Done!");
                break;
            case 3:
                puts("How many worst students?");
                scanf("%d", &iChoice);
                PrintNWorCStudents(pHead, iChoice);
                puts("Done!");
                break;
            case 4:
                ChangeStudentInfo(pHead);
                break;
            case 5:
                SaveListToFile(pHead);
                puts("Saved successfully!");
                break;
            case 6:
                puts("Write the number of student to delete:");
                scanf("%d", &iChoice);
                DeleteStudent(&pHead, iChoice);
                break;
            case 7:
                puts("Good Bye!");
                FreeList(&pHead);
                exit(EXIT_SUCCESS);
        }
    putchar('\n');
    PrintList(pHead);
    }
}
