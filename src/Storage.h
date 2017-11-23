//
// Created by william on 11/22/17.
//

#ifndef BOOKY_SQLITE_H
#define BOOKY_SQLITE_H

#include <string>
#include <memory>
#include <vector>

#include "SQLiteCpp/SQLiteCpp.h"

#include "maybe.h"

class Storage {
    SQLite::Database db;

public:
    explicit Storage(const char *filename);
    virtual ~Storage() = default;

    maybe<std::string> getPath(const char *key);

    std::vector<std::string> listBookmarks();

    bool putBookmark(const char *key, const char *path, bool overwrite);

    bool deleteBookmark(const char *key);

};


#endif //BOOKY_SQLITE_H
