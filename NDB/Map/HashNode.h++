/*
    NDB: Fastest HashTable Map + Remote In-Memory DataBase
    Copyright (C) 2021  AMIRMNOOHI

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#pragma optimize("", on)

#ifndef NDB_HASH_NODE_H
#define NDB_HASH_NODE_H

#include <cstdlib>
#include <cstdio>

namespace NDB {
    template<typename K, typename V>
    class HashNode {
    public:
        bool _isSet{};
        K _key;
        V _value;

        HashNode() = default;

        explicit HashNode(const bool isSet, const K& key, const V& value) {
            this->_isSet = isSet;
            this->_key = _key;
            this->_value = _value;
        }

        HashNode(const HashNode& source) {
            this->_isSet = source._isSet;
            this->_key = source._key;
            this->_value = source._value;
        };
    };
}
#endif //NDB_HASH_NODE_H
