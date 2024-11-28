#pragma once

#include <iostream>
#include <stdio.h>
#include <memory>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <functional>

using namespace std;

namespace fa
{
    // Type aliases for smart pointers
    template<typename T>
    using unique = unique_ptr<T>;

    template<typename T>
    using shared = shared_ptr<T>;

    template<typename T>
    using weak = weak_ptr<T>;

    // Type alias for vector
    template<typename T>
    using List = vector<T>;

    // Type alias for map (ordered)
    template<typename keyType, typename valType, typename Pr = less<keyType>>
    using Map = map<keyType, valType, Pr>;

    // Type alias for unordered_map (hash map)
    template<typename keyType, typename valType, typename hasher = hash<keyType>>
    using Dictionary = unordered_map<keyType, valType, hasher>;

    // Type alias for unordered_set (hash set)
    template<typename T>
    using Set = unordered_set<T>;

    // Logging macros for various log levels
#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
#define LOG_INFO(M, ...) printf("[INFO] " M "\n", ##__VA_ARGS__)
#define LOG_WARNING(M, ...) printf("[WARNING] " M "\n", ##__VA_ARGS__)
#define LOG_ERROR(M, ...) printf("[ERROR] " M "\n", ##__VA_ARGS__)
#define LOG_DEBUG(M, ...) printf("[DEBUG] " M "\n", ##__VA_ARGS__)

// Utility functions for logging
    inline void logError(const string& message)
    {
        LOG_ERROR("%s", message.c_str());
    }

    inline void logInfo(const string& message)
    {
        LOG_INFO("%s", message.c_str());
    }

    inline void logDebug(const string& message)
    {
        LOG_DEBUG("%s", message.c_str());
    }

    inline void logWarning(const string& message)
    {
        LOG_WARNING("%s", message.c_str());
    }
}
