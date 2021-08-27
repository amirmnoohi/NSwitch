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

#ifndef NDB_HASHMAP_H
#define NDB_HASHMAP_H

#include "HashNode.h++"
#include <vector>

namespace NDB {
    enum class STATUS {
        ADDED,
        UPDATED
    };

    uint_fast64_t loadFactor, startDepth;
    template<typename K>
    std::hash<K> hashFunction;

    template<typename K, typename V>
    class HashMap {
    public:

        std::vector<std::vector<NDB::HashNode<K, V>>> table;
        int *usage = nullptr;

        explicit HashMap(uint_fast64_t load_factor = 100000, uint_fast64_t start_depth = 100) {
            NDB::loadFactor = load_factor;
            NDB::startDepth = start_depth;

            this->usage = new int[loadFactor]{0};

            this->table.resize(loadFactor);

            for (int i = 0; i < loadFactor; ++i) {
                this->table[i].resize(startDepth);
                this->table[i].reserve(startDepth * 2);
            }
        }

        [[maybe_unused]] STATUS put(K &key, V &value) {
            auto hashKey = hashFunction<K>(key) % loadFactor;

            // check if exist to update value
            for (long long i = 0; i < table[hashKey].size() && i < usage[hashKey]; ++i) {
                if (table[hashKey][i]._isSet && table[hashKey][i]._key == key) {
                    table[hashKey][i]._value = value;
                    return STATUS::UPDATED;
                }
            }

            // add new key_value
            if (usage[hashKey] == table[hashKey].size()) {
                HashNode<K, V> temp(true, key, value);
                table[hashKey].push_back(temp);
            } else {
                table[hashKey][usage[hashKey]]._isSet = true;
                table[hashKey][usage[hashKey]]._key = key;
                table[hashKey][usage[hashKey]]._value = value;
            }

            usage[hashKey]++;

            return STATUS::ADDED;
        }

        [[maybe_unused]] V &get(K &key) {
            auto hashKey = hashFunction<K>(key) % loadFactor;
            for (int i = 0; i < table[hashKey].size(); ++i) {
                if (table[hashKey][i]._isSet && table[hashKey][i]._key == key)
                    return table[hashKey][i]._value;
            }
            throw std::runtime_error("Object Not Found");
        }

        [[maybe_unused]] V &operator[](const K &key) {
            auto hashKey = hashFunction<K>(key) % loadFactor;
            for (int i = 0; i < table[hashKey].size(); ++i) {
                if (table[hashKey][i]._isSet && table[hashKey][i]._key == key)
                    return table[hashKey][i]._value;
            }

            // add new HashNode  to end of vector
            if (usage[hashKey] == table[hashKey].size()) {
                HashNode<K, V> temp(true, key, V());
                table[hashKey].push_back(temp);
            }

            // set _isSet to true for indicating that data will be assigned

            usage[hashKey]++;

            table[hashKey][usage[hashKey] - 1]._isSet = true;
            table[hashKey][usage[hashKey] - 1]._key = key;

            return table[hashKey][usage[hashKey] - 1]._value;

        }
    };
}
#endif //LEARNING_HASHTABLE_H
