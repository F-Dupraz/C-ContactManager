/* I'm learninng C and practicing data structures and algorithms */
/* And now I'm learning GUI develompent in windows */

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#include "AVLNode.h"
#include "File.h"

#define CUSTOM_COLOR_CONTACTS_S RGB(33, 33, 33)
#define CUSTOM_COLOR_IDKY_S RGB(45, 45, 81)

AVLNode* root = NULL;
Contact new_contact;
const char* filename = "contacts.txt";

char complete_name[50], name[25], last_name[25], phone_number[15], address[50], email[50], birthday[15];

static TCHAR szWindowClass[] = _T("C-ContactManager");

static TCHAR szTitle[] = _T("Contact Manager - My Personal Agenda");

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

LOGFONTA createFont(LONG size, BYTE wh) {
    LOGFONTA logFont;

    memset(&logFont, 0, sizeof(LOGFONTA));

    logFont.lfHeight = size;
    logFont.lfWidth = 0;
    logFont.lfEscapement = 0;
    logFont.lfOrientation = 0;
    logFont.lfWeight = wh;
    logFont.lfItalic = FALSE;
    logFont.lfUnderline = FALSE;
    logFont.lfStrikeOut = FALSE;
    logFont.lfCharSet = ANSI_CHARSET;
    logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
    logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    logFont.lfQuality = DEFAULT_QUALITY;
    logFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    strcpy_s(logFont.lfFaceName, 16, "Times New Roman");

    return logFont;
}

void PreOrder(AVLNode* root, HDC hdc, int cc)
{
    if (root != NULL)
    {
        char full_name[50] = "";
        int s = 0;
        for (int i = 0; i < 50; ++i) {
            if (root->contact.name[i] == '\0') {
                break;
            }

            if (root->contact.name[i] == ' ' && s <= 1) {
                full_name[strlen(full_name)] = root->contact.name[i];
                full_name[strlen(full_name) + 1] = '\0';
                ++s;
            }
            else if (root->contact.name[i] != ' ' && s <= 1) {
                full_name[strlen(full_name)] = root->contact.name[i];
                full_name[strlen(full_name) + 1] = '\0';
            }
            else if (s == 2) {
                TextOutA(hdc, 25, (80 + cc), full_name, strlen(full_name));
                break;
            }
        }

        if (root->left != NULL && root->right != NULL)
        {
            cc += 31;
            PreOrder(root->left, hdc, cc);
            cc += 31;
            PreOrder(root->right, hdc, cc);
        }
        else if (root->left != NULL && root->right == NULL)
        {
            cc += 31;
            PreOrder(root->left, hdc, cc);
        }
        else if (root->left == NULL && root->right != NULL)
        {
            cc += 31;
            PreOrder(root->right, hdc, cc);
        }
        else
            return;
    }
}

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
    LoadContacts(&root, filename);

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
    static HFONT hFont;
    static HBRUSH hBrush;
    char contact_title[] = "Your contacts:";
    char add_contact_title[] = "Add a new contact";

    int contact_counter = 0;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        LOGFONTA logFontT = createFont(36L, FW_BOLD);

        HFONT hNewFontT = CreateFontIndirectA(&logFontT);

        FillRect(hdc, &ps_contacts_side.rcPaint, CreateSolidBrush(CUSTOM_COLOR_CONTACTS_S));
        FillRect(hdc, &ps_isky_size.rcPaint, CreateSolidBrush(CUSTOM_COLOR_IDKY_S));

        SelectObject(hdc, hNewFontT);
        SetTextColor(hdc, RGB(250, 250, 250));
        SetBkColor(hdc, CUSTOM_COLOR_CONTACTS_S);
        TextOutA(hdc,
            20, 20,
            contact_title, sizeof(contact_title));

        LOGFONTA logFontN = createFont(24L, FW_NORMAL);

        HFONT hNewFontN = CreateFontIndirectA(&logFontN);

        SelectObject(hdc, hNewFontN);

        PreOrder(root, hdc, contact_counter);

        SelectObject(hdc, hNewFontT);

        SetBkColor(hdc, CUSTOM_COLOR_IDKY_S);
        TextOutA(hdc,
            320, 20,
            add_contact_title, sizeof(add_contact_title));

        SelectObject(hdc, hNewFontN);

        TextOutA(hdc,
            325, 85,
            "Name and last name:", 20);
        TextOutA(hdc,
            325, 166,
            "Phone number:", 14);
        TextOutA(hdc,
            325, 247,
            "Address:", 9);
        TextOutA(hdc,
            325, 328,
            "Email:", 7);
        TextOutA(hdc,
            325, 410,
            "Birthday:", 11);

        contact_counter = 0;

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
