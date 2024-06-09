// CPQ Software.cpp : Defines the entry point for the application.
//

#include "../include/CPQSoftware.h"

// Define the global variables
#define MAX_LOADSTRING 1000
HINSTANCE hInst = nullptr;
wchar_t szTitle[MAX_LOADSTRING];
wchar_t szWindowClass[MAX_LOADSTRING];
DbHandler CPQDbAdapter;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    if (!LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING) ||
        !LoadStringW(hInstance, IDC_CPQSOFTWARE, szWindowClass, MAX_LOADSTRING))
    {
        MessageBox(NULL, L"Failed to load strings", L"Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    if (!MyRegisterClass(hInstance))
    {
        MessageBox(NULL, L"Failed to register class", L"Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    // Perform application initialization
    if (!InitInstance(hInstance, nCmdShow))
    {
        MessageBox(NULL, L"Failed to initialize instance", L"Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    CPQDbAdapter.InitializeDatabase();
    CPQDbAdapter.LoadQuotesFromDatabase();

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CPQSOFTWARE));

    MSG msg;
    // Main message loop
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CPQSOFTWARE));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CPQSOFTWARE);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    ATOM result = RegisterClassExW(&wcex);
    if (!result) {
        MessageBox(NULL, L"RegisterClassExW failed", L"Error", MB_OK | MB_ICONERROR);
    }
    return result;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 500, 400, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        MessageBox(NULL, L"CreateWindowW failed", L"Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hStaticText, hCreateButton, hViewButton, hEditButton, hDeleteButton, hExitButton;

    switch (message)
    {
    case WM_CREATE:
    {
        // Create static text
        hStaticText = CreateWindowW(L"STATIC", L"WindowQuotePro [ CPQ software platform]", WS_VISIBLE | WS_CHILD,
            90, 0, 300, 20, hWnd, NULL, hInst, NULL);
        hStaticText = CreateWindowW(L"STATIC", L"Please select an option:", WS_VISIBLE | WS_CHILD,
            0, 0, 300, 20, hWnd, NULL, hInst, NULL);

        // Create buttons
        hCreateButton = CreateWindowW(L"BUTTON", L"Create Quote", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            0, 0, 150, 30, hWnd, (HMENU)IDM_CREATE_QUOTE, hInst, nullptr);
        hViewButton = CreateWindowW(L"BUTTON", L"View All Quotes", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            0, 0, 150, 30, hWnd, (HMENU)IDM_VIEW_QUOTES, hInst, nullptr);
        hEditButton = CreateWindowW(L"BUTTON", L"Edit Quote", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            0, 0, 150, 30, hWnd, (HMENU)IDM_EDIT_QUOTE, hInst, nullptr);
        hDeleteButton = CreateWindowW(L"BUTTON", L"Delete Quote", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            0, 0, 150, 30, hWnd, (HMENU)IDM_DELETE_QUOTE, hInst, nullptr);
        hExitButton = CreateWindowW(L"BUTTON", L"Exit", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            0, 0, 150, 30, hWnd, (HMENU)IDM_EXIT, hInst, nullptr);
    }
    break;

    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);

        // Center positions
        int xCenter = (width - 150) / 2;
        int yStart = (height - 250) / 2;

        // Set positions
        SetWindowPos(hStaticText, NULL, xCenter - 75, yStart - 30, 300, 20, SWP_NOZORDER);
        SetWindowPos(hCreateButton, NULL, xCenter, yStart, 150, 30, SWP_NOZORDER);
        SetWindowPos(hViewButton, NULL, xCenter, yStart + 40, 150, 30, SWP_NOZORDER);
        SetWindowPos(hEditButton, NULL, xCenter, yStart + 80, 150, 30, SWP_NOZORDER);
        SetWindowPos(hDeleteButton, NULL, xCenter, yStart + 120, 150, 30, SWP_NOZORDER);
        SetWindowPos(hExitButton, NULL, xCenter, yStart + 160, 150, 30, SWP_NOZORDER);
    }
    break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections
        switch (wmId)
        {
        case IDM_CREATE_QUOTE:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_CREATE_QUOTE), hWnd, CreateQuoteDialog);
            break;
        case IDM_VIEW_QUOTES:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_VIEW_QUOTES), hWnd, ViewQuotesDialog);
            break;
        case IDM_EDIT_QUOTE:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_SELECT_QUOTE), hWnd, SelectQuoteDialog);
            break;
        case IDM_DELETE_QUOTE:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DELETE_QUOTE), hWnd, DeleteQuoteDialog);
            break;
        case IDM_EXIT:
            CPQDbAdapter.LoadQuotesFromDatabase();
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
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

int GetPriceBasedOnSelection(const WCHAR* material, const WCHAR* size) {
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::time(0)));

    // Generate a random price between 1 and 100
    return std::rand() % 100 + 1;
}

INT_PTR CALLBACK CreateQuoteDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);

    switch (message) {
    case WM_INITDIALOG:
        SendDlgItemMessage(hDlg, IDC_DOOR_MATERIAL, CB_ADDSTRING, 0, (LPARAM)L"Wood");
        SendDlgItemMessage(hDlg, IDC_DOOR_MATERIAL, CB_ADDSTRING, 0, (LPARAM)L"Metal");
        SendDlgItemMessage(hDlg, IDC_DOOR_SIZE, CB_ADDSTRING, 0, (LPARAM)L"S");
        SendDlgItemMessage(hDlg, IDC_DOOR_SIZE, CB_ADDSTRING, 0, (LPARAM)L"M");
        SendDlgItemMessage(hDlg, IDC_DOOR_SIZE, CB_ADDSTRING, 0, (LPARAM)L"L");
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            WCHAR quoteName[100], customerName[100], material[100], size[100];
            GetDlgItemText(hDlg, IDC_QUOTE_NAME, quoteName, 100);
            GetDlgItemText(hDlg, IDC_CUSTOMER_NAME, customerName, 100);
            GetDlgItemText(hDlg, IDC_DOOR_MATERIAL, material, 100);
            GetDlgItemText(hDlg, IDC_DOOR_SIZE, size, 100);

            // Validate input fields
            if (wcslen(quoteName) == 0 || wcslen(customerName) == 0 || wcslen(material) == 0 || wcslen(size) == 0) {
                MessageBox(hDlg, L"All fields must be filled out.", L"Error", MB_OK | MB_ICONERROR);
                return (INT_PTR)TRUE;
            }

            // Simulating price fetch based on selected material and size
            int price = GetPriceBasedOnSelection(material, size);

            // Set the price in the dialog box
            WCHAR priceStr[100];
            swprintf_s(priceStr, 100, L"%d", price);
            SetDlgItemText(hDlg, IDC_PRICE, priceStr);

            // Add the new quote to the database and list
            CPQDbAdapter.AddQuoteToDatabase(quoteName, customerName, material, size, price);
            CPQDbAdapter.quotes.push_back({ quoteName, customerName, material, size, price });

            MessageBox(hDlg, L"Quote created successfully!", L"Success", MB_OK);
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ViewQuotesDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);

    switch (message) {
    case WM_INITDIALOG: {
        const int yPosStart = 30; // Initial y position for the first quote
        const int height = 20; // Height of each text box
        const int margin = 5; // Margin between text boxes
        int yPos = yPosStart;

        if (CPQDbAdapter.quotes.empty()) {
            MessageBox(hDlg, L"No Quote Available!", L"Error", MB_OK | MB_ICONERROR);
            EndDialog(hDlg, 0);
            return (INT_PTR)FALSE;
        }

        // Create header labels
        CreateWindowW(L"STATIC", L"Number", WS_VISIBLE | WS_CHILD, 10, 10, 50, height, hDlg, NULL, hInst, NULL);
        CreateWindowW(L"STATIC", L"Quote Name", WS_VISIBLE | WS_CHILD, 70, 10, 100, height, hDlg, NULL, hInst, NULL);
        CreateWindowW(L"STATIC", L"Customer Name", WS_VISIBLE | WS_CHILD, 180, 10, 100, height, hDlg, NULL, hInst, NULL);
        CreateWindowW(L"STATIC", L"Material", WS_VISIBLE | WS_CHILD, 290, 10, 100, height, hDlg, NULL, hInst, NULL);
        CreateWindowW(L"STATIC", L"Size", WS_VISIBLE | WS_CHILD, 400, 10, 50, height, hDlg, NULL, hInst, NULL);
        CreateWindowW(L"STATIC", L"Price", WS_VISIBLE | WS_CHILD, 460, 10, 50, height, hDlg, NULL, hInst, NULL);

        // Create text boxes for each quote
        for (size_t i = 0; i < CPQDbAdapter.quotes.size(); ++i) {
            CreateWindowW(L"STATIC", std::to_wstring(i + 1).c_str(), WS_VISIBLE | WS_CHILD, 10, yPos, 50, height, hDlg, NULL, hInst, NULL);
            CreateWindowW(L"STATIC", CPQDbAdapter.quotes[i].quoteName.c_str(), WS_VISIBLE | WS_CHILD, 70, yPos, 100, height, hDlg, NULL, hInst, NULL);
            CreateWindowW(L"STATIC", CPQDbAdapter.quotes[i].customerName.c_str(), WS_VISIBLE | WS_CHILD, 180, yPos, 100, height, hDlg, NULL, hInst, NULL);
            CreateWindowW(L"STATIC", CPQDbAdapter.quotes[i].material.c_str(), WS_VISIBLE | WS_CHILD, 290, yPos, 100, height, hDlg, NULL, hInst, NULL);
            CreateWindowW(L"STATIC", CPQDbAdapter.quotes[i].size.c_str(), WS_VISIBLE | WS_CHILD, 400, yPos, 50, height, hDlg, NULL, hInst, NULL);
            CreateWindowW(L"STATIC", (L"$" + std::to_wstring(CPQDbAdapter.quotes[i].price)).c_str(), WS_VISIBLE | WS_CHILD, 460, yPos, 50, height, hDlg, NULL, hInst, NULL);

            yPos += height + margin; // Update y position for the next quote
        }
        return (INT_PTR)TRUE;
    }

    case WM_COMMAND:
        if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


INT_PTR CALLBACK DeleteQuoteDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            WCHAR quoteNumberStr[10];
            GetDlgItemText(hDlg, IDC_DELETE_QUOTE_NUMBER, quoteNumberStr, 10);
            int quoteNumber = _wtoi(quoteNumberStr);

            if (quoteNumber > 0 && quoteNumber <= CPQDbAdapter.quotes.size()) {
                CPQDbAdapter.DeleteQuoteFromDatabase(quoteNumber);
                CPQDbAdapter.quotes.erase(CPQDbAdapter.quotes.begin() + quoteNumber - 1);
                MessageBox(hDlg, L"Quote deleted successfully!", L"Success", MB_OK);
            }
            else {
                MessageBox(hDlg, L"Invalid quote number!", L"Error", MB_OK | MB_ICONERROR);
            }

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK EditQuoteDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
    case WM_INITDIALOG:
    {
        DbHandler::Quote quote = CPQDbAdapter.quotes[DbHandler::selectedQuoteIndex];

        std::wstring currentQuoteText = L"Editing Quote: " + std::to_wstring(DbHandler::selectedQuoteIndex + 1);
        SetDlgItemText(hDlg, IDC_CURRENT_QUOTE, currentQuoteText.c_str());

        std::wstring quoteNameText = L"Enter new quote name (current: " + quote.quoteName + L"):";
        SetDlgItemText(hDlg, IDC_NEW_QUOTE_NAME, quoteNameText.c_str());

        std::wstring customerNameText = L"Enter new customer name (current: " + quote.customerName + L"):";
        SetDlgItemText(hDlg, IDC_NEW_CUSTOMER_NAME, customerNameText.c_str());

        SendDlgItemMessage(hDlg, IDC_NEW_DOOR_MATERIAL, CB_ADDSTRING, 0, (LPARAM)L"Wood");
        SendDlgItemMessage(hDlg, IDC_NEW_DOOR_MATERIAL, CB_ADDSTRING, 0, (LPARAM)L"Metal");

        SendDlgItemMessage(hDlg, IDC_NEW_DOOR_SIZE, CB_ADDSTRING, 0, (LPARAM)L"S");
        SendDlgItemMessage(hDlg, IDC_NEW_DOOR_SIZE, CB_ADDSTRING, 0, (LPARAM)L"M");
        SendDlgItemMessage(hDlg, IDC_NEW_DOOR_SIZE, CB_ADDSTRING, 0, (LPARAM)L"L");

        // Set the current values
        SetDlgItemText(hDlg, IDC_NEW_QUOTE_NAME, quote.quoteName.c_str());
        SetDlgItemText(hDlg, IDC_NEW_CUSTOMER_NAME, quote.customerName.c_str());
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            WCHAR newQuoteName[100], newCustomerName[100], newMaterial[100], newSize[100];
            GetDlgItemText(hDlg, IDC_NEW_QUOTE_NAME, newQuoteName, 100);
            GetDlgItemText(hDlg, IDC_NEW_CUSTOMER_NAME, newCustomerName, 100);
            GetDlgItemText(hDlg, IDC_NEW_DOOR_MATERIAL, newMaterial, 100);
            GetDlgItemText(hDlg, IDC_NEW_DOOR_SIZE, newSize, 100);

            // Simulating price fetch based on selected material and size
            int newPrice = GetPriceBasedOnSelection(newMaterial, newSize);

            // Update the selected quote
            CPQDbAdapter.UpdateQuoteInDatabase(DbHandler::selectedQuoteIndex + 1, newQuoteName, newCustomerName, newMaterial, newSize, newPrice);
            CPQDbAdapter.quotes[DbHandler::selectedQuoteIndex] = { newQuoteName, newCustomerName, newMaterial, newSize, newPrice };

            MessageBox(hDlg, L"Quote updated successfully!", L"Success", MB_OK);
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK SelectQuoteDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
    case WM_INITDIALOG:
    {
        std::wstring allQuotes;
        for (size_t i = 0; i < CPQDbAdapter.quotes.size(); ++i) {
            allQuotes += std::to_wstring(i + 1) + L". " + CPQDbAdapter.quotes[i].quoteName + L", " + CPQDbAdapter.quotes[i].customerName + L", Price: $" + std::to_wstring(CPQDbAdapter.quotes[i].price) + L"\n";
        }
        SetDlgItemText(hDlg, IDC_QUOTES_TEXT, allQuotes.c_str());
    }
    return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            WCHAR quoteNumberStr[10];
            GetDlgItemText(hDlg, IDC_EDIT_QUOTE_NUMBER, quoteNumberStr, 10);
            int quoteNumber = _wtoi(quoteNumberStr);

            if (quoteNumber > 0 && quoteNumber <= CPQDbAdapter.quotes.size()) {
                DbHandler::selectedQuoteIndex = quoteNumber - 1;
                EndDialog(hDlg, LOWORD(wParam));
                DialogBox(hInst, MAKEINTRESOURCE(IDD_EDIT_QUOTE), GetParent(hDlg), EditQuoteDialog);
            }
            else {
                MessageBox(hDlg, L"Invalid quote number!", L"Error", MB_OK | MB_ICONERROR);
            }

            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
