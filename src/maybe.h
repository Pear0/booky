//
// Created by william on 11/22/17.
//

#ifndef BOOKY_MAYBE_H
#define BOOKY_MAYBE_H

#include <utility>

template <typename Type>
class maybe {
    Type value;
    bool is_value;

public:
    explicit maybe(Type &value) : value(value), is_value(true) {}
    explicit maybe(Type &&value) : value(std::move(value)), is_value(true) {}

    explicit maybe() : is_value(false) {}

    virtual ~maybe() = default;

    explicit operator bool() const {
        return is_value;
    }

    const Type &operator*() const {
        if (!is_value) {
            throw std::runtime_error("Cannot unwrap maybe with no value");
        }

        return value;
    }

};


#endif //BOOKY_MAYBE_H
