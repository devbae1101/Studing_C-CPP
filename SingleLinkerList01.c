#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct USERDATA // 2. 데이터 구조 만들기
{
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pNext;

} USERDATA;

USERDATA* g_pHeadNode = NULL;


typedef enum MY_MENU {EXIT, NEW, SEARCH, PRINT, REMOVE} MY_MENU; // 1. 콘솔창에 띄울 메뉴 UI 만들기

void addNewNode(int nAge, char* pszName, char* pszPhone) // 3. 각 메뉴들의 기능 구현하기
{
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	pNewNode->age = nAge;
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pszName);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pszPhone);
	pNewNode->pNext = NULL;

	if (g_pHeadNode == NULL)
		g_pHeadNode = pNewNode;
	else // 마지막 노드.pNext에 pNewNode 대입 
	{
		USERDATA* pTmp = g_pHeadNode;
		while (pTmp->pNext != NULL)
			pTmp = pTmp->pNext;

		pTmp->pNext = pNewNode;
	}
}

void AddNewUser(void) // 3. 각 메뉴들의 기능 구현하기
{
	int nAge = 0;
	char szName[32] = { 0 };
	char szPhone[32] = { 0 };

	printf("Age: ");
	scanf_s("%d%*c", &nAge);
	printf("Name: ");
	gets_s(szName, sizeof(szName));
	printf("Phone: ");
	gets_s(szPhone, sizeof(szPhone));

	addNewNode(nAge, szName, szPhone);
}

void PrintList(void) // 3. 각 메뉴들의 기능 구현하기
{
	USERDATA* pTmp = g_pHeadNode;
	while (pTmp != NULL)
	{
		printf("[%p], %d, %s, %s, [Next: %p]\n", pTmp, pTmp->age, pTmp->name, pTmp->phone, pTmp->pNext);
		pTmp = pTmp->pNext;
	}
	printf("\n");
	_getch();
}

void ReleaseList(void) // 3. 각 메뉴들의 기능 구현하기
{
	USERDATA* pTmp = g_pHeadNode;
	USERDATA* pDelete = NULL;
	while (pTmp != NULL)
	{
		pDelete = pTmp;
		pTmp = pTmp->pNext;
		free(pDelete);
	}
	g_pHeadNode = NULL;
}


MY_MENU PrintMenu(void) // 3. 각 메뉴들의 기능 구현하기 (중요)기능 중 제일 먼저 구현합니다.
{
	MY_MENU input = 0;

	system("cls");
	printf("[1]NEW\t [2]SEARCH\t [3]PRINT\t [4]REMOVE\t [0]EXIT\n");
	scanf_s("%d%*c", &input);
	return input;

}

int SearchListByName(USERDATA* pUser, char* pszName) // 3. 각 메뉴들의 기능 구현하기
{
	USERDATA* pTmp = g_pHeadNode;
	while (pTmp != NULL)
	{
		if (strcmp(pszName, pTmp->name) == 0)
		{
			memcpy(pUser, pTmp, sizeof(USERDATA));
			return 1;
		}
		
		pTmp = pTmp->pNext;
	}
	return 0;
}

void SearchByName(void) // 3. 각 메뉴들의 기능 구현하기, Phone동일
{
	char szName[32] = { 0 };
	USERDATA pUser = { 0 };

	printf("Type Searching Name: ");
	gets_s(szName, sizeof(szName));
	if (SearchListByName(&pUser, szName) > 0)
		printf("[%p], %d, %s, %s, [Next: %p]\n", &pUser, pUser.age, pUser.name, pUser.phone, pUser.pNext);
	else
		puts("Not found.");

	_getch();
}

int SearchListByNameToRemove(USERDATA* pUser, char* pszName) // 3. 각 메뉴들의 기능 구현하기
{
	USERDATA* pDelete = g_pHeadNode;
	USERDATA* pPrev = NULL;

	while (pDelete != NULL)
	{
		if (strcmp(pszName, pDelete->name) == 0)
		{
			memcpy(pUser, pDelete, sizeof(USERDATA));
			if (pDelete == g_pHeadNode)
			{
				g_pHeadNode = pDelete->pNext;
				free(pDelete);
			}
			else
			{
				pPrev->pNext = pDelete->pNext;
			}
			return 1;
		}
		pPrev = pDelete;
		pDelete = pDelete->pNext;
	}
	return 0;
}

void RemoveByName(void) // 3. 각 메뉴들의 기능 구현하기, Phone 동일
{
	char szName[32] = { 0 };
	USERDATA pUser = { 0 };

	printf("Type Removing Name: ");
	gets_s(szName, sizeof(szName));
	if (SearchListByNameToRemove(&pUser, szName) > 0)
		printf("DELETE: [%p], %d, %s, %s, [Next: %p]\n", &pUser, pUser.age, pUser.name, pUser.phone, pUser.pNext);
	else
		puts("Not found.");

	_getch();
}


void EventLoopRun(void) // 1. 콘솔창에 띄울 메뉴 UI 만들기
{
	MY_MENU menu = 0;

	while ((menu = PrintMenu()) != 0 )
	{
		switch (menu)
		{

		case NEW:
			AddNewUser();
			break;
		
		case SEARCH:
			SearchByName();
			break;
		
		case PRINT:
			PrintList();
			break;
		
		case REMOVE:
			RemoveByName();
			break;

		default:
			break;
		}
		
	}
	puts("Bye~!");
}

void InitDummyData(void) // 4. 테스트 하기
{
	addNewNode(31, "Bae", "010-8306-0324");
	addNewNode(32, "Kim", "010-7306-0324");
	addNewNode(33, "Lee", "010-6306-0324");

}


int main(void) 
{
	InitDummyData();
	//PrintList();
	EventLoopRun();
	ReleaseList();

	return 0;

}