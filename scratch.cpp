#include "HashmapInterface.h"
#include "Hashmap.h"
#include <iostream>

int main() {
    Hashmap map;

    // Inserting values
    map.insert("apple", 5);
    map.insert("banana", 10);
    map.insert("orange", 15);

    // Testing contains
    std::cout << "map contains 'apple': " << std::boolalpha << map.contains("apple") << std::endl;
    std::cout << "map contains 'grape': " << std::boolalpha << map.contains("grape") << std::endl;

    // Testing get and operator[]
    std::cout << "map['apple']: " << map.get("apple") << std::endl;
    std::cout << "map['banana']: " << map["banana"] << std::endl;

    // Updating value using operator[]
    map["orange"] = 20;
    std::cout << "map['orange']: " << map["orange"] << std::endl;

    // Testing remove
    std::cout << "Removing 'apple': " << std::boolalpha << map.remove("apple") << std::endl;
    std::cout << "map contains 'apple': " << std::boolalpha << map.contains("apple") << std::endl;

    // Testing size
    std::cout << "Map size: " << map.size() << std::endl;

    // Testing clear
    map.clear();
    std::cout << "Map size after clear: " << map.size() << std::endl;

    return 0;
}
