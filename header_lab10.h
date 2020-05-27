#ifndef HEADER_LAB10_H
#define HEADER_LAB10_H
///The max length of the char array that contains ///some name
#define NAME_LENGTH 12
///The number of exam marks
#define EXAM_NUM 7
///The maximal length of address
#define ADDRESS_LENGTH 30
///Puts the line to the screen
#define PRINT_MINUSES puts("-----------------------------------------------------------------------------")

typedef struct st{
    char szLastName[NAME_LENGTH], szFirstName[NAME_LENGTH];
    struct {
        int iDay, iMonth, iYear;
    } CBirthDate;
    int iExamResults[EXAM_NUM];
} st;

typedef struct lt{
    st CStudent;
    struct lt *pPrev, *pNext;
} stList;
///Returns the pointer to file, that is opened in "r" ///mode by the address, written by the user
FILE* GetFileFromUser (void);
///Mallocs the memory for the two-sided list and ///assumes the info from the file, pFile points to, ///to the list. Returns the pointer to the head of ///the new list
stList* CreateStudentList(FILE *pFile);
///Shows the menu to the user and returns the number, ///entered by the user
int ShowMenuAndGetChoice(void);
///Free the memory of the member of ppHead list and ///binds the pointers
void DeleteStudent(stList **ppHead, int iNum);
///Scans the info about student from a file, pFile ///points to, and assigns it to the node, pNode ///points to
int SetStudentInfoFromFile(FILE *pFile, stList *pNode);
///Adds the node, pNewNode points to, to the end of ///the list, that ppHead points to
void AddStudentToEndOfList(const stList *pHead,
stList *pNewNode);
///Sorts the list, ppHead points to, in the opposite ///alphabetical order
void SortListReversedToAlphabeticalOrder
(stList **ppHead);
///Finds the average value of the iArr, that has size ///iSize
double FindAverageValue(const int iArr[], int iSize);
///Prints the list, pHead points to, on the screen
void PrintList(const stList *pHead);
///Prints the list, pHead points to, to the file, ///pFile points to
void SaveListToFile(const stList *pHead);
///Prints information of n students that have the ///worst average exam result
void PrintNWorCStudents(const stList *pHead,
int iN);
///Cuts the nodes, that contain information about ///students that have mark 2 for any of exams, out of ///the list, ppHead points to
void DeleteStudentsWithMarkN (stList **ppHead, int iN);
///Returns the pointer to the node, that contains ///info about student on position number iNum
stList* GetStudentByNumber(const stList *pHead,
int iNum);
///Assigns the new info to the node, pNode points to
void ChangeStudentInfo(stList *pHead);
///Free the memory of the list ppHead points to
void FreeList(stList **ppHead);
///Swaps two nodes of the list, ppHead points to
void SwapStudents (stList **ppHead, int iNodeNum1,
int iNodeNum2);
#endif
