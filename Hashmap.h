#ifndef HASHMAP_H
#define HASHMAP_H

#include "HashmapInterface.h"
#include <vector>
#include <stdexcept>

class Hashmap : public HashmapInterface {
public:
    Hashmap();
    virtual ~Hashmap();

    void insert(std::string key, int value) override;
    bool contains(const std::string &key) const override;
    int get(const std::string &key) const override;
    int &operator[](const std::string &key) override;
    bool remove(const std::string &key) override;
    void clear() override;
    int numBuckets() const override;
    int size() const override;

private:
    struct Node {
        std::string key;
        int value;
        bool isDeleted;

        Node(const std::string &key, int value)
                : key(key), value(value), isDeleted(false) {}
    };

    std::vector<Node *> table;
    size_t numElements;

    size_t hash(const std::string &key) const;
    void rehash();
    float loadFactor() const;
    };


#endif // HASHMAP_H
