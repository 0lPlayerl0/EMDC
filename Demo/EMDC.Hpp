#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <fstream>
#include <experimental/filesystem>
#include <thread>
#include <mutex>

namespace fs = std::experimental::filesystem;

struct Row {
    std::unordered_map<std::string, std::string> columns;
};

class Table {
public:
    Table(const std::vector<std::string>& column_names) : column_names(column_names) {}

    void insert(const std::vector<std::string>& values, bool at_end = true) {
        if (values.size() != column_names.size()) {
            std::cerr << "Invalid number of values\n";
            return;
        }

        Row row;
        for (size_t i = 0; i < column_names.size(); i++) {
            row.columns[column_names[i]] = values[i];
        }

        std::lock_guard<std::mutex> lock(mutex);

        if (at_end) {
            rows.push_back(row);
        } else {
            rows.insert(rows.begin(), row);
        }
    }

    void select_all() {
        std::lock_guard<std::mutex> lock(mutex);

        if (rows.empty()) return;

        for (const auto& column_name : column_names) {
            std::cout << column_name << " | ";
        }
        std::cout << '\n';

        for (const auto& row : rows) {
            for (const auto& column : row.columns) {
                std::cout << column.second << " | ";
            }
            std::cout << '\n';
        }
    }

    void select_where(std::function<bool(const Row&)> predicate) {
        std::lock_guard<std::mutex> lock(mutex);

        if (rows.empty()) return;

        for (const auto& column_name : column_names) {
            std::cout << column_name << " | ";
        }
        std::cout << '\n';

        for (const auto& row : rows) {
            if (predicate(row)) {
                for (const auto& column : row.columns) {
                    std::cout << column.second << " | ";
                }
                std::cout << '\n';
            }
        }
    }

    void update_where(std::function<bool(const Row&)> predicate, std::function<void(Row&)> updater) {
        std::lock_guard<std::mutex> lock(mutex);

        for (auto& row : rows) {
            if (predicate(row)) {
                updater(row);
            }
        }
    }

    void delete_where(std::function<bool(const Row&)> predicate) {
        std::lock_guard<std::mutex> lock(mutex);

        rows.erase(std::remove_if(rows.begin(), rows.end(), predicate), rows.end());
    }

    std::vector<Row> join(Table& other, std::function<bool(const Row&, const Row&)> predicate) {
        std::lock_guard<std::mutex> lock1(mutex);
        std::lock_guard<std::mutex> lock2(other.mutex);

        std::vector<Row> result;

        for (const auto& row1 : rows) {
            for (const auto& row2 : other.rows) {
                if (predicate(row1, row2)) {
                    Row row;
                    row.columns.insert(row1.columns.begin(), row1.columns.end());
                    row.columns.insert(row2.columns.begin(), row2.columns.end());
                    result.push_back(row);
                }
            }
        }

        return result;
    }

    void save_to_file(const fs::path& folder, const std::string& filename, const std::string& key) {
        fs::create_directories(folder);

        fs::path filepath = folder / filename;


        std::ofstream file(filepath.string());

        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filepath << '\n';
            return;
        }

        if (rows.empty()) return;

        for (const auto& column_name : column_names) {
            file << encrypt(column_name, key) << ",";
        }
        file << '\n';

        for (const auto& row : rows) {
            for (const auto& column : row.columns) {
                file << encrypt(column.second, key) << ",";
            }
            file << '\n';
        }

        file.close();
    }

    void load_from_file(const fs::path& folder, const std::string& filename, const std::string& key) {
        fs::path filepath = folder / filename;
        std::ifstream file(filepath.string());

        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filepath << '\n';
            return;
        }

        rows.clear();

        std::string line;
        getline(file, line);

        size_t start = 0;
        size_t end = line.find(',');
        while (end != std::string::npos) {
            start = end + 1;
            end = line.find(',', start);
        }

        while (getline(file, line)) {
            Row row;

            start = 0;
            end = line.find(',');
            size_t i = 0;
            while (end != std::string::npos) {
                row.columns[column_names[i]] = decrypt(line.substr(start, end - start), key);
                start = end + 1;
                end = line.find(',', start);
                i++;
            }

            rows.push_back(row);
        }

        file.close();
    }

private:
    std::vector<std::string> column_names;
    std::vector<Row> rows;
    std::mutex mutex;

    std::string encrypt(const std::string& text, const std::string& key) {
        std::string result = text;

        for (size_t i = 0; i < result.size(); i++) {
            result[i] ^= key[i % key.size()];
        }

        return result;
    }

    std::string decrypt(const std::string& text, const std::string& key) {
        return encrypt(text, key);
    }
};
