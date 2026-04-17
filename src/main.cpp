// tradebridge - C++ backend with SQLite storage
#include <iostream>
#include <string>
#include <sqlite3.h>

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("app.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }
    const char *sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, email TEXT UNIQUE, full_name TEXT, hashed_password TEXT);"
                      "CREATE TABLE IF NOT EXISTS items (id INTEGER PRIMARY KEY, title TEXT, description TEXT, owner_id INTEGER, created_at TEXT);";
    char *err_msg = nullptr;
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    std::cout << "tradebridge backend initialized successfully." << std::endl;
    sqlite3_close(db);
    return 0;
}
