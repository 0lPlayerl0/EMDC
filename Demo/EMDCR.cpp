#include "EMDC.Hpp"


int main() {
    Table table1({"id", "name", "age"});
    table1.insert({"1", "Alice", "25"});
    table1.insert({"2", "Bob", "30"});
    table1.insert({"3", "Charlie", "35"});

    Table table2({"id", "job"});
    table2.insert({"1", "teacher"});
    table2.insert({"2", "engineer"});
    table2.insert({"3", "doctor"});

    table1.select_all();
    table1.select_where([](const Row& row) { return row.columns.at("name") == "Bob"; });

    table1.update_where([](const Row& row) { return row.columns.at("name") == "Bob"; }, [](Row& row) { row.columns["age"] = "40"; });
    table1.select_all();

    table1.delete_where([](const Row& row) { return row.columns.at("name") == "Bob"; });
    table1.select_all();

    auto result = table1.join(table2, [](const Row& row1, const Row& row2) { return row1.columns.at("id") == row2.columns.at("id"); });
    for (const auto& row : result) {
        for (const auto& column : row.columns) {
            std::cout << column.first << ": " << column.second << ", ";
        }
        std::cout << '\n';
    }

    fs::path folder = "database";
    std::string key = "secret";
    table1.save_to_file(folder, "table1.csv", key);
    table2.save_to_file(folder, "table2.csv", key);

    Table table3({"id", "name", "age"});
    table3.load_from_file(folder, "table1.csv", key);
    table3.select_all();

    return 0;
}


