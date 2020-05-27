#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header_lab10.h"
///---------------------------------------------------------------------------
FILE* GetFileFromUser(){
    FILE *pFile = NULL;
    char szAddress[ADDRESS_LENGTH];
    while (!pFile){
        	   puts("Write the address of file with students			info:");
        gets(szAddress);
        pFile = fopen(szAddress, "r");
        if (!pFile)
            puts("Wrong address!");
    }
    return pFile;
}
///---------------------------------------------------------------------------
stList* CreateStudentList(FILE *pFile){
    stList *pHead = (stList*)malloc(sizeof(stList));
    pHead->pNext = NULL;
    pHead->pPrev = NULL;
    stList* pTemp = pHead;
    int iSetResult = 0;
    while (!feof(pFile)){
       if ((iSetResul = SetStudentInfoFromFile(
pFile, pTemp)) < 5 + EXAM_NUM){
            if (iSetResult == -2){
                puts("Unacceptable file pointer was given to 'SetStudentInfoFromFile' function.");
                exit(EXIT_FAILURE);
            }
            if (iSetResult == -1){
                puts("Unacceptable node pointer was given to 'SetStudentInfoFromFile' function.");
                exit(EXIT_FAILURE);
            }
            puts("Not enough info in the file.");
            exit(EXIT_FAILURE);
        }
        AddStudentToEndOfList(pHead, pTemp);
        if (!feof(pFile))
            pTemp = (stList*)malloc(sizeof(stList));
    }
    return pHead;
}
///---------------------------------------------------------------------------
int SetStudentInfoFromFile(FILE *pFile, stList *pNode){
    if (!pFile) return -2;
    if (!pNode) return -1;

    int iScanResult = fscanf(pFile, "%s %s %d %d %d",		pNode->CStudent.szLastName,
pNode->CStudent.szFirstName, 
&pNode->CStudent.CBirthDate.iDay,
     &pNode->CStudent.CBirthDate.iMonth,
&pNode->CStudent.CBirthDate.iYear);
    for (int i = 0; i < EXAM_NUM; ++i)
        iScanResult += fscanf(pFile, "%d",
&pNode->CStudent.iExamResults[i]);

    return iScanResult;
}
///---------------------------------------------------------------------------
void AddStudentToEndOfList(const stList *pHead, stList *pNewNode){
    if (!pHead || !pNewNode) return;
    if (pHead == pNewNode) return;

    stList *pLastNode = pHead;
    while (pLastNode->pNext){
        pLastNode = pLastNode->pNext;
    }
    pLastNode->pNext = pNewNode;
    pNewNode->pPrev = pLastNode;
    pNewNode->pNext = NULL;
}
///---------------------------------------------------------------------------
void PrintList(const stList *pHead){
    if (!pHead) return;
    PRINT_MINUSES;
    puts("|            NAME              |DATE OF BIRTH|  EXAM RESULTS |AVARAGE RESULT|");
    PRINT_MINUSES;
    stList* pTemp = pHead;
    int i = 1;
    while (pTemp) {
        printf("|%2d. %-*s %-*s |  %2d.%2d.%4d | ",
i, NAME_LENGTH, pTemp->CStudent.szLastName,
NAME_LENGTH, pTemp->CStudent.szFirstName, pTemp->CStudent.CBirthDate.iDay,
         pTemp->CStudent.CBirthDate.iMonth,
pTemp->CStudent.CBirthDate.iYear);
        for (int i = 0; i < EXAM_NUM; ++i)
            printf("%d ",
pTemp->CStudent.iExamResults[i]);
        printf("|   %lf   |\n", 
FindAverageValue(
pTemp->CStudent.iExamResults, EXAM_NUM));
        if (pTemp->pNext)
            pTemp = pTemp->pNext;
        else break;
        ++i;
    }
    PRINT_MINUSES;
}
///---------------------------------------------------------------------------
double FindAverage(const int iArr[], int iSize){
    if (!iArr) return 0;

    double iSum = 0;
    for (int i = 0; i < iSize; ++i)
        iSum += iArr[i];
    return iSum / iSize;
}
///---------------------------------------------------------------------------
void PrintNWorCStudents(const stList *pHead, int iN){
    if (!pHead) return;

    stList* pTemp = pHead;
    int iListSize = 1;
    while (pTemp->pNext){
        pTemp = pTemp->pNext;
        ++iListSize;
    }

    pTemp = pHead;
    double* pAvgArr = (double*)malloc(
iListSize * sizeof(double));
    for (int i = 0; i < iListSize; ++i){
        pAvgArr[i] = FindAverageValue(
pTemp->CStudent.iExamResults, EXAM_NUM);
        if (pTemp->pNext)
            pTemp = pTemp->pNext;
        else break;
    }

    int* pIndexes = (int*)malloc(
iListSize * sizeof(int));
    for (int i = 0; i < iListSize; ++i)
        pIndexes[i] = i;
    double dTempVal;
    int iTempInd;
    for (int i = 0; i < iListSize; ++i) {
        for (int j = 1; j < iListSize; ++j) {
            if (pAvgArr[j - 1] > pAvgArr[j]) {
                dTempVal = pAvgArr[j - 1];
                pAvgArr[j - 1] = pAvgArr[j];
                pAvgArr[j] = dTempVal;

                iTempInd = pIndexes[j - 1];
                pIndexes[j - 1] = pIndexes[j];
                pIndexes[j] = iTempInd;
            }
        }
    }

    printf("\n%d worst students:\n", iN);
    for (int i = 0; i < iN; ++i){
        pTemp = pHead;
        for (int j = 0; j < pIndexes[i]; ++j)
            pTemp = pTemp->pNext;
        printf("%s %s - %lf\n",
pTemp->CStudent.szLastName,
         pTemp->CStudent.szFirstName,
pAvgArr[i]);
    }

    free(pAvgArr);
}
///---------------------------------------------------------------------------
void DeleteStudentsWithMarkN (stList **ppHead,
int iN){
    if (!ppHead) return;

    stList* pTemp = *ppHead;
    int iCheck;
    while (pTemp){
        iCheck = 0;
        for (int i = 0; i < EXAM_NUM; ++i){
            if (pTemp->CStudent.iExamResults[i]
 == iN)
                ++iCheck;
        }
        if (iCheck > 0){
            if (pTemp == *ppHead){
                (*ppHead)->pNext->pPrev = NULL;
                free(pTemp);
                *ppHead = (*ppHead)->pNext;
            } else {
                if (pTemp->pNext){
                    pTemp->pPrev->pNext = 
pTemp->pNext;
                    pTemp->pNext->pPrev = 
pTemp->pPrev;
                    free(pTemp);
                } else {
                    pTemp->pPrev->pNext = NULL;
                    free(pTemp);
                    return;
                }
            }
        }
        if (pTemp->pNext)
            pTemp = pTemp->pNext;
        else break;
    }
}
///---------------------------------------------------------------------------
void FreeList(stList **ppHead){
    if (!*ppHead) return;

    stList *pTemp = *ppHead, *pT = pTemp;
    while (pTemp->pNext)
        pTemp = pTemp->pNext;
    while (pT){
        pT = pTemp->pPrev;
        free(pTemp);
        pTemp = pT;
    }
    *ppHead = NULL;
}
///---------------------------------------------------------------------------
void SwapStudents (stList **ppHead, int iNodeNum1,
int iNodeNum2){
    if (!*ppHead) return;

    stList* pNode1 = *ppHead;
    for (int i = 1; i < iNodeNum1; ++i)
        pNode1 = pNode1->pNext;
    stList* pNode2 = *ppHead;
    for (int i = 1; i < iNodeNum2; ++i)
        pNode2 = pNode2->pNext;

    stList *pNode1Next = pNode1->pNext,
*pNode2Next = pNode2->pNext,
*pNode1Prev = pNode1->pPrev,
     *pNode2Prev = pNode2->pPrev;

    if (pNode1 == *ppHead || pNode2 == *ppHead){
        if (pNode1 == *ppHead){
            if (pNode1->pNext == pNode2 && 
pNode2->pNext){
                pNode2->pNext->pPrev = pNode1;
                pNode1->pNext = pNode2Next;
                pNode1->pPrev = pNode2;
                pNode2->pNext = pNode1;
                pNode2->pPrev = NULL;
                *ppHead = pNode2;
                return;
            }
            if (pNode1->pNext == pNode2 &&
!pNode2->pNext){
                pNode1->pNext = NULL;
                pNode1->pPrev = pNode2;
                pNode2->pPrev = NULL;
                pNode2->pNext = pNode1;
                *ppHead = pNode1;
                return;
            }
            if (pNode1->pNext != pNode2 &&
pNode2->pNext){
                pNode2->pNext->pPrev = pNode1;
                pNode2->pPrev->pNext = pNode1;
                pNode1->pNext->pPrev = pNode2;
                pNode1->pNext = pNode2Next;
                pNode1->pPrev = pNode2Prev;
                pNode2->pNext = pNode1Next;
                pNode2->pPrev = NULL;
                *ppHead = pNode2;
                return;
            }
            if (pNode1->pNext != pNode2 &&
!pNode2->pNext){
                pNode2->pPrev->pNext = pNode1;
                pNode1->pNext->pPrev = pNode2;
                pNode1->pNext = NULL;
                pNode1->pPrev = pNode2Prev;
                pNode2->pNext = pNode1Next;
                pNode2->pPrev = NULL;
                *ppHead = pNode2;
                return;
            }

            if (pNode2 == *ppHead){
                	   if (pNode2->pNext == pNode1 &&
pNode1->pNext){
                    pNode1->pNext->pPrev = pNode1;
                    pNode2->pNext = pNode1Next;
                    pNode2->pPrev = pNode1;
                    pNode1->pNext = pNode2;
                    pNode1->pPrev = NULL;
                    *ppHead = pNode1;
                    return;
                }
                if (pNode2->pNext == pNode2 &&
!pNode1->pNext){
                    pNode2->pNext = NULL;
                    pNode2->pPrev = pNode1;
                    pNode1->pPrev = NULL;
                    pNode1->pNext = pNode2;
                    *ppHead = pNode2;
                    return;
                }
                if (pNode2->pNext != pNode1 &&
pNode1->pNext){
                    pNode1->pNext->pPrev = pNode2;
                    pNode1->pPrev->pNext = pNode2;
                    pNode2->pNext->pPrev = pNode1;
                    pNode2->pNext = pNode1Next;
                    pNode2->pPrev = pNode1Prev;
                    pNode1->pNext = pNode2Next;
                    pNode1->pPrev = NULL;
                    *ppHead = pNode1;
                    return;
                }
                if (pNode2->pNext != pNode1 &&
!pNode1->pNext){
                    pNode1->pPrev->pNext = pNode2;
                    pNode2->pNext->pPrev = pNode1;
                    pNode2->pNext = NULL;
                    pNode2->pPrev = pNode1Prev;
                    pNode1->pNext = pNode2Next;
                    pNode1->pPrev = NULL;
                    *ppHead = pNode1;
                    return;
                }
            }
        }
    }
    if (pNode1->pNext == pNode2 && pNode2->pNext){
        pNode2->pNext->pPrev = pNode1;
        pNode1->pPrev->pNext = pNode2;
        pNode2->pPrev = pNode1Prev;
        pNode2->pNext = pNode1;
        pNode1->pNext = pNode2Next;
        pNode1->pPrev = pNode2;
        return;
    }
    if (pNode1->pNext == pNode2 && !pNode2->pNext){
        pNode1->pPrev->pNext = pNode2;
        pNode2->pPrev = pNode1Prev;
        pNode2->pNext = pNode1;
        pNode1->pPrev = pNode2;
        pNode1->pNext = NULL;
        return;
    }
    if (pNode2->pNext == pNode1 && pNode1->pNext){
        pNode1->pNext->pPrev = pNode2;
        pNode2->pPrev->pNext = pNode1;
        pNode1->pPrev = pNode2Prev;
        pNode1->pNext = pNode2;
        pNode2->pNext = pNode1Next;
        pNode2->pPrev = pNode1;
        return;
    }
    if (pNode2->pNext == pNode1 && !pNode1->pNext){
        pNode2->pPrev->pNext = pNode1;
        pNode1->pPrev = pNode2Prev;
        pNode1->pNext = pNode2;
        pNode2->pPrev = pNode1;
        pNode2->pNext = NULL;
        return;
    }
    if (pNode1->pPrev && !pNode2->pNext){
        pNode1->pNext->pPrev = pNode2;
        pNode1->pPrev->pNext = pNode2;
        pNode2->pPrev->pNext = pNode1;
        pNode1->pPrev = pNode2Prev;
        pNode1->pNext = NULL;
        pNode2->pNext = pNode1Next;
        pNode2->pPrev = pNode1Prev;
        return;
    }
    if (pNode2->pPrev && !pNode1->pNext){
        pNode2->pNext->pPrev = pNode1;
        pNode2->pPrev->pNext = pNode1;
        pNode1->pPrev->pNext = pNode2;
        pNode2->pPrev = pNode1Prev;
        pNode2->pNext = NULL;
        pNode1->pNext = pNode2Next;
        pNode1->pPrev = pNode2Prev;
        return;
    }
    pNode2->pNext->pPrev = pNode1;
    pNode2->pPrev->pNext = pNode1;
    pNode1->pNext->pPrev = pNode2;
    pNode1->pPrev->pNext = pNode2;
    pNode1->pNext = pNode2Next;
    pNode1->pPrev = pNode2Prev;
    pNode2->pNext = pNode1Next;
    pNode2->pPrev = pNode1Prev;
}
///---------------------------------------------------------------------------
void SortListReversedToAlphabeticalOrder(
stList **ppHead){
    if (!*ppHead) return;

    int iListSize = 1;
    stList *pTemp = *ppHead;
    while (pTemp->pNext){
        ++iListSize;
        pTemp = pTemp->pNext;
    }
    int iCmpLastNameRes, iCmpFirstNameRes;
    pTemp = *ppHead;
    for (int i = 1; i <= iListSize; ++i){
        for (int j = 1; j < iListSize; ++j){
            for (int k = 1; k < j; ++k)
                pTemp = pTemp->pNext;
            iCmpLastNameRes = strcmp(
pTemp->CStudent.szLastName,
pTemp->pNext->CStudent.szLastName);
            if (iCmpLastNameRes < 0)
                SwapStudents(ppHead, j, j + 1);
            else if (iCmpLastNameRes == 0){
                iCmpFirstNameRes = strcmp(
pTemp->CStudent.szFirstName,
pTemp->pNext->
CStudent.szFirstName);
                if (iCmpFirstNameRes < 0)
                    SwapStudents(ppHead, j, j + 1);
            }
            pTemp = *ppHead;
        }
    }
}
///---------------------------------------------------------------------------
void SaveListToFile(const stList *pHead){
    if (!pHead) return;

    FILE *pFile = NULL;
    char szAddress[ADDRESS_LENGTH];
    while (!pFile){
        puts("Write the address:");
        gets(szAddress);
        pFile = freopen(szAddress, "w", stdout);
        if (!pFile)
            puts("Wrong address!");
        else break;
    }
    PrintList(pHead);
    freopen("CON", "w", stdout);
}
///---------------------------------------------------------------------------
stList* GetStudentByNumber(const stList *pHead,
int iNum){
    if (!pHead) return;

    stList *pTemp = pHead;
    for (int i = 1; i < iNum; ++i){
        pTemp = pTemp->pNext;
        if (!pTemp) return NULL;
    }
    return pTemp;
}
///---------------------------------------------------------------------------
void ChangeStudentInfo(stList *pHead){
    if (!pHead) return;

    int iStudentNum, iChoice;
    char cName[NAME_LENGTH];
    stList *pNode;

    while (1){
        puts("Enter the number of student you want to change info about:");
        scanf("%d", &iStudentNum);
        pNode = GetStudentByNumber(pHead, iStudentNum);
        if (!pNode)
            puts("Wrong number! Try again:");
        else break;
    }
    puts("What do you want to change?");
    puts("1. Last Name       2. First Name");
    puts("3. Date of birth   4. Exam results");
    scanf("%d", &iChoice);
    switch (iChoice){
        case 1:
            puts("Enter the new last name:");
            scanf("%s", cName);
            strcpy(pNode->CStudent.szLastName,
cName);
            puts("Saved!");
            break;
        case 2:
            puts("Enter the new first name:");
            scanf("%s", cName);
            strcpy(pNode->CStudent.szLastName,
cName);
            puts("Saved!");
            break;
        case 3:
            puts("Enter the new date of birth:");
            scanf("%d.%d.%d",
&pNode->CStudent.CBirthDate.iDay, &pNode->CStudent.CBirthDate.iMonth,
             	&pNode->CStudent.CBirthDate.iYear);
            puts("Saved!");
            break;
        case 4:
            puts("Enter the new exam results:");
            for (int i = 0; i < EXAM_NUM; ++i)
                scanf("%d",
&pNode->CStudent.iExamResults[i]);
            puts("Saved!");
            break;
        default:
            puts("Wrong number! Try again!");
    }
}
///---------------------------------------------------------------------------
int ShowMenuAndGetChoice(void){
    puts("What to do?");
    puts("1. Sort list                2. Delete students with mark N");
    puts("3. Print N worst students   4. Change info");
    puts("5. Save list to file        6. Delete student");
    puts("7. End");
    int iChoice;
    scanf("%d", &iChoice);
    return iChoice;
}
///---------------------------------------------------------------------------
void DeleteStudent(stList **ppHead, int iNum){
    if (!*ppHead || iNum < 1) return;

    stList *pTemp;
    if (iNum == 1){
        pTemp = (*ppHead)->pNext;
        pTemp->pPrev = NULL;
        free(*ppHead);
        *ppHead = pTemp;
        return;
    }
    pTemp = *ppHead;
    for (int i = 1; i < iNum; ++i)
        pTemp = pTemp->pNext;
    if (pTemp->pNext){
        pTemp->pPrev->pNext = pTemp->pNext;
        pTemp->pNext->pPrev = pTemp->pPrev;
    } else pTemp->pPrev->pNext = NULL;
    free(pTemp);
}
