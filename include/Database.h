#ifndef DATABASE_H
#define DATABASE_H


#include <windows.h>
#include "framework.h"
#include "CPQSoftware.h"
#include <random>
#include <vector>
#include <string>
#include "../sqlite/sqlite3.h"




class DbHandler
{
public:

    sqlite3* DB;
    static int selectedQuoteIndex;

    struct Quote {
        std::wstring quoteName;
        std::wstring customerName;
        std::wstring material;
        std::wstring size;
        int price;
    };
    std::vector<Quote> quotes;

    void ExecuteSQL(const char* sql);
    void InitializeDatabase();
    void LoadQuotesFromDatabase();
    void AddQuoteToDatabase(const WCHAR* quoteName, const WCHAR* customerName, const WCHAR* material, const WCHAR* size, int price);
    void DeleteQuoteFromDatabase(int quoteNumber);
    void UpdateQuoteInDatabase(int quoteNumber, const WCHAR* newQuoteName, const WCHAR* newCustomerName, const WCHAR* newMaterial, const WCHAR* newSize, int newPrice);

};

#endif // DATABASE_H