//
// Created by william on 11/22/17.
//

#ifndef BOOKY_SQLITE_H
#define BOOKY_SQLITE_H

#include <string>
#include <memory>

#include "sqlite3.h"

class Storage {
    sqlite3 *db;

public:
    explicit Storage(const char *filename);
    virtual ~Storage();



};


#endif //BOOKY_SQLITE_H
