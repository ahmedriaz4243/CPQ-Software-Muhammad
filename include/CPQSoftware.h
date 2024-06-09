#ifndef CPQSOFTWARE_H
#define CPQSOFTWARE_H

#include <windows.h>
#include <ctime>
#include "../include/framework.h"
#include "../include/resource.h"
#include "../include/Database.h"



	// Dseclarations of functions included in this code module:
	ATOM                MyRegisterClass(HINSTANCE hInstance);
	BOOL                InitInstance(HINSTANCE, int);
	LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
	INT_PTR CALLBACK    CreateQuoteDialog(HWND, UINT, WPARAM, LPARAM);
	INT_PTR CALLBACK    ViewQuotesDialog(HWND, UINT, WPARAM, LPARAM);
	INT_PTR CALLBACK    DeleteQuoteDialog(HWND, UINT, WPARAM, LPARAM);
	INT_PTR CALLBACK    EditQuoteDialog(HWND, UINT, WPARAM, LPARAM);
	INT_PTR CALLBACK    SelectQuoteDialog(HWND, UINT, WPARAM, LPARAM);
	int                 GetPriceBasedOnSelection(const WCHAR* material, const WCHAR* size);


	

#endif // CPQSOFTWARE_H