#include <iostream>
#include <vector>
#include <string>
#include <functional>

template <typename Key, typename Value>
class RobinHoodHashMap {
private:
    struct Entry {
        Key key;
        Value value;
        bool occupied = false;
        size_t dist = 0; // Distance from desired position
    };

    static constexpr size_t DEFAULT_SIZE = 1024;
    std::vector<Entry> m_table;
    size_t m_size = 0;

    // A placeholder to represent an empty entry
    static Entry EMPTY_ENTRY;

    size_t hash_func(const Key& key) const {
        return std::hash<Key>{}(key) % m_table.size();
    }

public:
    RobinHoodHashMap() : m_table(DEFAULT_SIZE) {}

    void insert(const Key& key, const Value& value) {
        if (m_size >= m_table.size() / 2) {
            rehash();
        }

        size_t index = hash_func(key);
        size_t distance = 0;
        Entry new_entry = {key, value, true, 0};

        while (true) {
            if (!m_table[index].occupied) {
                m_table[index] = new_entry;
                m_size++;
                return;
            }
            // Swap if new element has higher distance
            if (new_entry.dist > m_table[index].dist) {
                std::swap(m_table[index], new_entry);
            }
            index = (index + 1) % m_table.size();
            new_entry.dist++;
        }
    }

    bool find(const Key& key, Value& value) const {
        size_t index = hash_func(key);
        size_t distance = 0;
        while (m_table[index].occupied && distance <= m_table[index].dist) {
            if (m_table[index].key == key) {
                value = m_table[index].value;
                return true;
            }
            index = (index + 1) % m_table.size();
            distance++;
        }
        return false;
    }

private:
    void rehash() {
        std::vector<Entry> old_table = std::move(m_table);
        m_table.assign(old_table.size() * 2, EMPTY_ENTRY);
        m_size = 0;

        for (const auto& entry : old_table) {
            if (entry.occupied) {
                insert(entry.key, entry.value);
            }
        }
    }
};

template <typename Key, typename Value>
typename RobinHoodHashMap<Key, Value>::Entry RobinHoodHashMap<Key, Value>::EMPTY_ENTRY;

int main() {
    RobinHoodHashMap<std::string, double> price_map;
    price_map.insert("AAPL", 185.50);
    price_map.insert("GOOG", 135.25);
    price_map.insert("MSFT", 250.75);

    double price;
    if (price_map.find("MSFT", price)) {
        std::cout << "MSFT price: " << price << std::endl;
    }
    return 0;
}
