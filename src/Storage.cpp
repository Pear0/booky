//
// Created by william on 11/22/17.
//

#include "Storage.h"

#include <exception>
#include <stdexcept>

void sql_exec(sqlite3 *db, const char *sql, int (*callback)(void* arg, int num_columns, char** row_values, char** row_names), void *callback_arg) {
    char *errMsg = nullptr;

    int rc = sqlite3_exec(db, sql, callback, callback_arg, &errMsg);

    if (rc != SQLITE_OK) {
        throw std::runtime_error(errMsg); // we leak the error message here
    }
}

static void init_db(sqlite3 *db) {

    // select 1 from sqlite_master where type='table' and name='TABLE_NAME_TO_CHECK'

    sql_exec(db, "CREATE TABLE IF NOT EXISTS meta (id INTEGER PRIMARY KEY, key TEXT UNIQUE NOT NULL, value TEXT)", nullptr, nullptr);





}

Storage::Storage(const char *filename) {
    int rc = sqlite3_open(filename, &db);
    if (rc != 0) {
        sqlite3_close(db);
        throw std::runtime_error("Failed to open database");
    }
}

Storage::~Storage() {
    sqlite3_close(db);
}
