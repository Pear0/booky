#include <iostream>

#include "sqlite3.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    sqlite3 *db;
    int rc;
    char *zErrMsg = nullptr;

    rc = sqlite3_open("test.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    rc = sqlite3_exec(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, key TEXT UNIQUE NOT NULL, value TEXT)", callback, nullptr, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL Error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);

    return 0;
}