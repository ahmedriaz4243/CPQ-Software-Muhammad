#include "../include/Database.h"
#include <codecvt>


// Convert UTF-8 string to wide string
std::wstring Utf8ToWString(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}
void DbHandler::ExecuteSQL(const char* sql) {
    char* errorMessage = 0;
    int rc = sqlite3_exec(DB, sql, 0, 0, &errorMessage);

    if (rc != SQLITE_OK) {
        MessageBoxA(NULL, errorMessage, "SQL Error", MB_OK | MB_ICONERROR);
        sqlite3_free(errorMessage);
    }
}

void DbHandler::InitializeDatabase() {
    int rc = sqlite3_open("quotes.db", &DB);

    if (rc) {
        MessageBoxA(NULL, "Can't open database", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS QUOTES ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "QUOTENAME TEXT NOT NULL, "
        "CUSTOMERNAME TEXT NOT NULL, "
        "MATERIAL TEXT NOT NULL, "
        "SIZE TEXT NOT NULL, "
        "PRICE INT NOT NULL);";
    ExecuteSQL(createTableSQL);
}
// Load quotes from the database
void DbHandler::LoadQuotesFromDatabase() {
    const char* sql = "SELECT * FROM QUOTES;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(DB, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(DB));
        return;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::wstring quoteName = Utf8ToWString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::wstring customerName = Utf8ToWString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        std::wstring material = Utf8ToWString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        std::wstring size = Utf8ToWString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        int price = sqlite3_column_int(stmt, 5);

        quotes.push_back({ quoteName, customerName, material, size, price });
    }

    sqlite3_finalize(stmt);
}

// Add a quote to the database
void DbHandler::AddQuoteToDatabase(const WCHAR* quoteName, const WCHAR* customerName, const WCHAR* material, const WCHAR* size, int price) {
    char sql[1024];
    sprintf_s(sql, sizeof(sql), "INSERT INTO QUOTES (QUOTENAME, CUSTOMERNAME, MATERIAL, SIZE, PRICE) VALUES ('%ws', '%ws', '%ws', '%ws', %d);",
        quoteName, customerName, material, size, price);
    ExecuteSQL(sql);
}

void DbHandler::DeleteQuoteFromDatabase(int quoteNumber) {
    char sql[1024];
    sprintf_s(sql, sizeof(sql), "DELETE FROM QUOTES WHERE ID = %d;", quoteNumber);
    ExecuteSQL(sql);
}

// Update a quote in the database
void DbHandler::UpdateQuoteInDatabase(int quoteNumber, const WCHAR* newQuoteName, const WCHAR* newCustomerName, const WCHAR* newMaterial, const WCHAR* newSize, int newPrice) {
    char sql[1024];
    sprintf_s(sql, sizeof(sql), "UPDATE QUOTES SET QUOTENAME = '%ws', CUSTOMERNAME = '%ws', MATERIAL = '%ws', SIZE = '%ws', PRICE = %d WHERE ID = %d;",
        newQuoteName, newCustomerName, newMaterial, newSize, newPrice, quoteNumber);
    ExecuteSQL(sql);
}

int DbHandler::selectedQuoteIndex = -1;