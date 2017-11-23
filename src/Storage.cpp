//
// Created by william on 11/22/17.
//

#include "Storage.h"

Storage::Storage(const char *filename) : db(filename, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE) {

    SQLite::Transaction transaction(db);

    db.exec("CREATE TABLE IF NOT EXISTS meta (id INTEGER PRIMARY KEY, key TEXT UNIQUE NOT NULL, value TEXT)");

    int schema_version = 0;

    // pull the db's schema version
    {
        SQLite::Statement schema_query(db, "SELECT value FROM meta WHERE key = 'schema_version'");

        if (schema_query.executeStep()) {
            const char *value = schema_query.getColumn(0);
            schema_version = std::stoi(value);
        }else {
            db.exec("INSERT INTO meta (key, value) VALUES ('schema_version', '0')");
        }
    }

    // perform upgrades

    if (schema_version == 0) {
        db.exec("CREATE TABLE bookmarks (id INTEGER PRIMARY KEY, name TEXT UNIQUE NOT NULL, path TEXT NOT NULL)");
        schema_version++;
    }

    // set the new schema version
    {
        SQLite::Statement schema_update(db, "UPDATE meta SET value = ? WHERE key = 'schema_version'");
        schema_update.bind(1, std::to_string(schema_version));
        schema_update.exec();
    }

    transaction.commit();

}

maybe<std::string> Storage::getPath(const char *key) {

    SQLite::Statement query(db, "SELECT path FROM bookmarks WHERE name = ?");
    query.bind(1, key);

    if (query.executeStep()) {
        std::string value = query.getColumn(0);
        return maybe<std::string>(value);
    }else {
        return maybe<std::string>();
    }
}

std::vector<std::string> Storage::listBookmarks() {

    std::vector<std::string> bookmarks;

    SQLite::Statement query(db, "SELECT name FROM bookmarks");

    while (query.executeStep()) {
        bookmarks.push_back(query.getColumn(0));
    }

    return bookmarks;
}

bool Storage::putBookmark(const char *key, const char *path, bool overwrite) {
    SQLite::Transaction transaction(db);

    auto oldValue = getPath(key);
    if (oldValue && !overwrite) {
        return false;
    }

    int rowsAffected = 0;

    if (oldValue) {
        SQLite::Statement query(db, "UPDATE bookmarks SET path = ? WHERE name = ?");
        query.bind(1, path);
        query.bind(2, key);
        rowsAffected = query.exec();
    }else {
        SQLite::Statement query(db, "INSERT INTO bookmarks (name, path) VALUES (?, ?)");
        query.bind(1, key);
        query.bind(2, path);
        rowsAffected = query.exec();
    };

    transaction.commit();
    return rowsAffected != 0;
}

bool Storage::deleteBookmark(const char *key) {
    SQLite::Transaction transaction(db);

    SQLite::Statement query(db, "DELETE FROM bookmarks WHERE name = ?");
    query.bind(1, key);
    int rowsAffected = query.exec();

    transaction.commit();
    return rowsAffected != 0;
}

