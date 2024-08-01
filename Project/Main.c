/* I'm learninng C and practicing data structures and algorithms */
/* And now I'm learning GUI develompent in windows */

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

//#include "Display.h"
//#include "AVLNode.h"
//#include "File.h"

#define CUSTOM_COLOR_CONTACTS_S RGB(33, 33, 33)
#define CUSTOM_COLOR_IDKY_S RGB(45, 45, 81)

static TCHAR szWindowClass[] = _T("C-ContactManager");

static TCHAR szTitle[] = _T("Contact Manager - My Personal Agenda");

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Contact Manager - My Personal Agenda"),
            NULL);

        return 1;
    }

    hInst = hInstance;

    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Contact Manager - My Personal Agenda"),
            NULL);

        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;

    PAINTSTRUCT ps_contacts_side;
    ps_contacts_side.rcPaint.left = 0L;
    ps_contacts_side.rcPaint.top = 0L;
    ps_contacts_side.rcPaint.right = 300L;
    ps_contacts_side.rcPaint.bottom = 2000L;

    PAINTSTRUCT ps_isky_size;
    ps_isky_size.rcPaint.left = 300L;
    ps_isky_size.rcPaint.top = 0L;
    ps_isky_size.rcPaint.right = 3000L;
    ps_isky_size.rcPaint.bottom = 2000L;

    HDC hdc;
    //TCHAR greeting[] = _T("Hello, Windows desktop!\nYour favorite agenda.\n");

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        FillRect(hdc, &ps_contacts_side.rcPaint, CreateSolidBrush(CUSTOM_COLOR_CONTACTS_S));
        FillRect(hdc, &ps_isky_size.rcPaint, CreateSolidBrush(CUSTOM_COLOR_IDKY_S));

        /*TextOut(hdc,
            25, 25,
            greeting, _tcslen(greeting));*/

        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}

//AVLNode* root = NULL;
//Contact new_contact;
//const char* filename = "contacts.txt";
//char complete_name[50], name[25], last_name[25], phone_number[15], address[50], email[50], birthday[15];
//
//LoadContacts(&root, filename);
//
//while (1)
//{
//	int choise = ShowDisplay();
//
//	switch (choise)
//	{
//	case 1:
//		printf("\n Estos son todos tus contactos: \n\n");
//		PreOrder(root);
//
//		break;
//	case 2:
//		printf("\n Input the name and last name only: ");
//		scanf_s("%s %s", name, (unsigned int)sizeof(name), last_name, (unsigned int)sizeof(last_name));
//		printf("\n Input the phone number: ");
//		scanf_s("%s", phone_number, (unsigned int)sizeof(phone_number));
//		printf("\n Input the address: ");
//		scanf_s("%s", address, (unsigned int)sizeof(address));
//		printf("\n Input the email: ");
//		scanf_s("%s", email, (unsigned int)sizeof(email));
//		printf("\n Input the birthday: ");
//		scanf_s("%s", birthday, (unsigned int)sizeof(birthday));
//
//		strcpy_s(complete_name, 50, name);
//		strcat_s(complete_name, 50, " ");
//		strcat_s(complete_name, 50, last_name);
//		strcpy_s(new_contact.name, sizeof(new_contact.name), complete_name);
//		strcpy_s(new_contact.phone_number, sizeof(new_contact.phone_number), phone_number);
//		strcpy_s(new_contact.address, sizeof(new_contact.address), address);
//		strcpy_s(new_contact.email, sizeof(new_contact.email), email);
//		strcpy_s(new_contact.birthday, sizeof(new_contact.birthday), birthday);
//
//		root = Insert(root, new_contact);
//
//		break;
//	case 3:
//		printf("\n Input the name and last name only: ");
//		scanf_s("%s %s", name, (unsigned int)sizeof(name), last_name, (unsigned int)sizeof(last_name));
//
//		strcpy_s(complete_name, 50, name);
//		strcat_s(complete_name, 50, " ");
//		strcat_s(complete_name, 50, last_name);
//
//		root = Delete(root, complete_name);
//
//		printf("\n Contact deleted succesflly!\n\n");
//
//		break;
//	case 4:
//		printf("\n Input the name and last name only: ");
//		scanf_s("%s %s", name, (unsigned int)sizeof(name), last_name, (unsigned int)sizeof(last_name));
//		printf("\n Change the phone number: ");
//		scanf_s("%s", phone_number, (unsigned int)sizeof(phone_number));
//		printf("\n Change the address: ");
//		scanf_s("%s", address, (unsigned int)sizeof(address));
//		printf("\n Change the email: ");
//		scanf_s("%s", email, (unsigned int)sizeof(email));
//		printf("\n Change the birthday: ");
//		scanf_s("%s", birthday, (unsigned int)sizeof(birthday));
//
//		strcpy_s(complete_name, 50, name);
//		strcat_s(complete_name, 50, " ");
//		strcat_s(complete_name, 50, last_name);
//		strcpy_s(new_contact.name, sizeof(new_contact.name), complete_name);
//		strcpy_s(new_contact.phone_number, sizeof(new_contact.phone_number), phone_number);
//		strcpy_s(new_contact.address, sizeof(new_contact.address), address);
//		strcpy_s(new_contact.email, sizeof(new_contact.email), email);
//		strcpy_s(new_contact.birthday, sizeof(new_contact.birthday), birthday);
//
//		root = Delete(root, complete_name);
//
//		root = Insert(root, new_contact);
//
//		printf("\n Your contact was updated succesfully!.\n");
//
//		break;
//	case 5:
//		printf(" Insert de name and last name: ");
//		scanf_s("%s %s", name, (unsigned int)sizeof(name), last_name, (unsigned int)sizeof(last_name));
//
//		strcpy_s(complete_name, 50, name);
//		strcat_s(complete_name, 50, " ");
//		strcat_s(complete_name, 50, last_name);
//
//		AVLNode* found = Search(root, complete_name);
//
//		if (found != NULL)
//			printf("  %s:\n  Phone number: %s.\n  Address: %s.\n  Email: %s.\n  Birthday: %s.\n\n", found->contact.name, found->contact.phone_number, found->contact.address, found->contact.email, found->contact.birthday);
//		else
//			printf("  Contacto no encontrado.\n");
//
//		break;
//	case 6:
//		SaveContacts(root, filename);
//		printf("\n Contactos guardados en el archivo: %s.\n", filename);
//		exit(0);
//	default:
//		printf("\n Invalid option.\n");
//
//		break;
//	}
//}
//
//return 0;
