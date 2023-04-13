#include "Hashmap.h"

size_t Hashmap::hash(const std::string &key) const {
    size_t hashValue = 0;
    for (char c : key) {
        hashValue = 31 * hashValue + c;
    }
    return hashValue % numBuckets();
}

void Hashmap::rehash() {
    std::vector<Node *> oldTable = table;
    table.clear();
    table.resize(numBuckets() * GROW_FACTOR, nullptr);
    numElements = 0;

    for (Node *node : oldTable) {
        if (node && !node->isDeleted) {
            insert(node->key, node->value);
            delete node;
        }
    }
}

Hashmap::Hashmap() : table(INITIAL_BUCKETS, nullptr), numElements(0) {}

Hashmap::~Hashmap() {
    for (Node *node : table) {
        delete node;
    }
}

void Hashmap::insert(std::string key, int value) {
    if (loadFactor() > MAX_LOAD_FACTOR) {
        rehash();
    }

    size_t index = hash(key);
    while (table[index] && !table[index]->isDeleted && table[index]->key != key) {
        index = (index + 1) % numBuckets();
    }

    if (!table[index] || table[index]->isDeleted) {
        delete table[index];
        table[index] = new Node(key, value);
        numElements++;
    } else {
        table[index]->value = value;
    }
}

bool Hashmap::contains(const std::string &key) const {
    size_t index = hash(key);
    while (table[index]) {
        if (!table[index]->isDeleted && table[index]->key == key) {
            return true;
        }
        index = (index + 1) % numBuckets();
    }
    return false;
}

int Hashmap::get(const std::string &key) const {
    size_t index = hash(key);
    while (table[index]) {
        if (!table[index]->isDeleted && table[index]->key == key) {
            return table[index]->value;
        }
        index = (index + 1) % numBuckets();
    }
    throw std::invalid_argument("Key not found");
}

int &Hashmap::operator[](const std::string &key) {
    size_t index = hash(key);
    while (table[index] && !table[index]->isDeleted && table[index]->key != key) {
        index = (index + 1) % numBuckets();
    }

    if (!table[index] || table[index]->isDeleted) {
        insert(key, 0);
        index = hash(key);
    }

    return table[index]->value;
}

bool Hashmap::remove(const std::string &key) {
    size_t index = hash(key);
    while (table[index]) {
        if (!table[index]->isDeleted && table[index]->key == key) {
            table[index]->isDeleted = true;
            numElements--;
            return true;
        }
        index = (index + 1) % numBuckets();
    }
    return false;
}

void Hashmap::clear() {
    for (Node *node : table) {
        delete node;
    }
    table.clear();
    table.resize(INITIAL_BUCKETS, nullptr);
    numElements = 0;
}

int Hashmap::numBuckets() const {
    return table.size();
}

int Hashmap::size() const {
    return numElements;
}

float Hashmap::loadFactor() const {
    return static_cast<float>(numElements) / static_cast<float>(table.size());
}