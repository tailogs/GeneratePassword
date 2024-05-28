// main.c
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "resources.h"

// ��������� ��� ������������� ��������� ����������
#define ID_GENERATE_BTN 1
#define ID_COPY_BTN 2
#define ID_LOWERCASE_CHK 3
#define ID_UPPERCASE_CHK 4
#define ID_DIGITS_CHK 5
#define ID_SYMBOLS_CHK 6
#define ID_LENGTH_EDIT 7
#define ID_PASSWORD_TEXT 8

// ������� ��� ��������� ������
const char LOWERCASE_CHARS[] = "abcdefghijklmnopqrstuvwxyz";
const char UPPERCASE_CHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char DIGIT_CHARS[] = "0123456789";
const char SYMBOL_CHARS[] = "!@#$%^&*()_+~`|\\}{[\":?><,./;'";

// ��������� �������
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void GeneratePassword(HWND);
void CopyPassword(HWND);

// ���������� ����������
HWND hLengthEdit, hLowercaseChk, hUppercaseChk, hDigitsChk, hSymbolsChk, hPasswordText, hCopyBtn;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // �������������� ��������� ��������� �����
    srand((unsigned int)time(NULL));

    // ������������ ����� ����
    WNDCLASSEX wcex = { 0 };
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(30, 30, 30)); // �����-������ ���� ����
    wcex.lpszClassName = "PasswordGenerator";
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(ICON1));  // ��������� ������ �� ��������
    RegisterClassEx(&wcex);

    // ������� ������� ����
    HWND hWnd = CreateWindow("PasswordGenerator", "��������� �������",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT,
        405, 255, NULL, NULL, hInstance, NULL);

    if (!hWnd)
        return FALSE;

    // ������� �������� ����������
    CreateWindow("BUTTON", "�������������", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
        10, 10, 140, 30, hWnd, (HMENU)ID_GENERATE_BTN, hInstance, NULL);

    hLowercaseChk = CreateWindow("BUTTON", "�������� �����", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
        10, 50, 140, 30, hWnd, (HMENU)ID_LOWERCASE_CHK, hInstance, NULL);

    hUppercaseChk = CreateWindow("BUTTON", "��������� �����", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
        10, 80, 140, 30, hWnd, (HMENU)ID_UPPERCASE_CHK, hInstance, NULL);

    hDigitsChk = CreateWindow("BUTTON", "�����", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
        10, 110, 140, 30, hWnd, (HMENU)ID_DIGITS_CHK, hInstance, NULL);

    hSymbolsChk = CreateWindow("BUTTON", "�������", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
        10, 140, 140, 30, hWnd, (HMENU)ID_SYMBOLS_CHK, hInstance, NULL);

    hLengthEdit = CreateWindow("EDIT", "8", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
        160, 50, 40, 25, hWnd, (HMENU)ID_LENGTH_EDIT, hInstance, NULL);

    CreateWindow("STATIC", "�����", WS_CHILD | WS_VISIBLE,
        160, 80, 47, 25, hWnd, NULL, hInstance, NULL);

    hPasswordText = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY,
        10, 180, 275, 25, hWnd, (HMENU)ID_PASSWORD_TEXT, hInstance, NULL);

    hCopyBtn = CreateWindow("BUTTON", "�����������", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        290, 180, 90, 25, hWnd, (HMENU)ID_COPY_BTN, hInstance, NULL);
    ShowWindow(hCopyBtn, SW_HIDE); // �������� �������� ������ "�����������"

    // ������������� ��������� �������� ��������� ����������
    SendMessage(hLowercaseChk, BM_SETCHECK, BST_CHECKED, 0);
    SendMessage(hUppercaseChk, BM_SETCHECK, BST_CHECKED, 0);
    SendMessage(hDigitsChk, BM_SETCHECK, BST_CHECKED, 0);

    ShowWindow(hCopyBtn, SW_SHOW);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // ���� ��������� ���������
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// ���������� ��������� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_GENERATE_BTN:
            GeneratePassword(hWnd);
            break;
        case ID_COPY_BTN:
            CopyPassword(hWnd);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ������� ��������� ������
void GeneratePassword(HWND hWnd)
{
    // �������� ��������� �� ��������� ����������
    BOOL useLowercase = SendMessage(hLowercaseChk, BM_GETCHECK, 0, 0) == BST_CHECKED;
    BOOL useUppercase = SendMessage(hUppercaseChk, BM_GETCHECK, 0, 0) == BST_CHECKED;
    BOOL useDigits = SendMessage(hDigitsChk, BM_GETCHECK, 0, 0) == BST_CHECKED;
    BOOL useSymbols = SendMessage(hSymbolsChk, BM_GETCHECK, 0, 0) == BST_CHECKED;

    // ���������, ��� ���� �� ���� ��� �������� ������
    if (!useLowercase && !useUppercase && !useDigits && !useSymbols)
    {
        MessageBox(hWnd, "�������� ���� �� ���� ��� �������� ��� ��������� ������.", "������", MB_OK | MB_ICONERROR);
        return;
    }

    // �������� ����� ������ �� ���� �����
    char lengthStr[4];
    GetWindowText(hLengthEdit, lengthStr, 4);
    int length = atoi(lengthStr);

    // ���������, ��� ����� ������ ��������� � ���������� ���������
    if (length < 4 || length > 32)
    {
        MessageBox(hWnd, "����� ������ ������ ���� �� 4 �� 32 ��������.", "������", MB_OK | MB_ICONERROR);
        return;
    }

    // ������� ������ ��� ��������� ������
    char charset[128] = { 0 };
    int charsetLen = 0;

    if (useLowercase)
    {
        strcat(charset, LOWERCASE_CHARS);
        charsetLen += sizeof(LOWERCASE_CHARS) - 1;
    }

    if (useUppercase)
    {
        strcat(charset, UPPERCASE_CHARS);
        charsetLen += sizeof(UPPERCASE_CHARS) - 1;
    }

    if (useDigits)
    {
        strcat(charset, DIGIT_CHARS);
        charsetLen += sizeof(DIGIT_CHARS) - 1;
    }

    if (useSymbols)
    {
        strcat(charset, SYMBOL_CHARS);
        charsetLen += sizeof(SYMBOL_CHARS) - 1;
    }

    // ���������� ������
    char password[33] = { 0 };
    for (int i = 0; i < length; i++)
    {
        int randomIndex = rand() % charsetLen;
        password[i] = charset[randomIndex];
    }

    // ������� ��������������� ������ � ��������� ����
    SetWindowText(hPasswordText, password);
}

// ������� ����������� ������ � ����� ������
void CopyPassword(HWND hWnd)
{
    // �������� ����� �� ���������� ���� ������
    char password[33];
    GetWindowText(hPasswordText, password, sizeof(password));

    // ��������� ����� ������
    if (OpenClipboard(hWnd))
    {
        // ������� ������� ���������� ������ ������
        EmptyClipboard();

        // �������� ������ ��� ������ ������
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, strlen(password) + 1);
        if (hMem != NULL)
        {
            // �������� ��������� �� ���������� ������
            char *memPtr = (char *)GlobalLock(hMem);
            if (memPtr != NULL)
            {
                // �������� ������ � ���������� ������
                strcpy(memPtr, password);

                // ������������ ������
                GlobalUnlock(hMem);

                // ������������� ������ � ����� ������
                SetClipboardData(CF_TEXT, hMem);
            }
        }

        // ��������� ����� ������
        CloseClipboard();
    }
}
