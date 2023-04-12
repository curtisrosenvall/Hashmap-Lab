#pragma once

#include <string>
#include <vector>
#include "HashmapInterface.h"


struct Node {
    std::string key;
    int value;
    bool isDeleted;

    Node(const std::string &key, int value) : key(key), value(value), isDeleted(false) {}
};

class Hashmap : public HashmapInterface {
private:
    std::vector<Node *> table;
    size_t numElements;

    size_t hash(const std::string &key) const;
    void rehash();

public:
    Hashmap();
    ~Hashmap() override;

    void insert(std::string key, int value) override;
    bool contains(const std::string &key) const override;
    int get(const std::string &key) const override;
    int &operator[](const std::string &key) override;
    bool remove(const std::string &key) override;
    void clear() override;

    int numBuckets() const override;
    int size() const override;
};
