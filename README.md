<p align="center">
  <img src="(https://github.com/0lPlayerl0/EMDC/assets/84262516/c0eac0f8-ce58-4794-a9c3-3943ec59952e" alt="Banner" style="display: block; margin: auto;">
</p>


# **EMDC: A Simple SQL-like Database in C++**

_________________

## Overview
EMDC is a simple SQL-like database program written in C++. It allows users to create and manipulate tables of data using a familiar SQL-like syntax. EMDC includes support for defining the table schema, inserting rows at the beginning or end of the table, and performing basic queries such as selecting, updating, and deleting rows. It also includes support for joining multiple tables based on a given condition.

One of the advanced features of EMDC is its support for multi-threading. This allows the program to perform database operations in parallel, potentially improving performance on multi-core systems. EMDC uses a mutex to synchronize access to the table data and ensure that multiple threads can safely perform operations on the table at the same time.

Another advanced feature of EMDC is its support for saving and loading the database to/from a file. This allows users to persist their data and continue working with it even after the program has been closed. EMDC uses a simple encryption algorithm to protect the data when saving it to a file, adding an extra layer of security.

## Usage
To use EMDC, you can create instances of the Table class and use its methods to manipulate data in your tables. Here is an example that demonstrates how to create two tables, insert data into them, perform some basic queries, and save and load data from files:
```cpp
#include "EMDC.hpp"

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
```
This code creates two tables named table1 and table2, inserts some data into them, performs some basic queries using methods such as select_all, select_where, and join, and then saves and loads data from files using methods such as save_to_file and load_from_file.

When using EMDC, it is recommended to follow best practices for working with databases, such as normalizing your data, using appropriate data types and constraints, and properly indexing your tables for efficient querying.

## API Reference
The following is a brief reference of the main classes and methods in EMDC:

Table: The Table class represents a table in the database. It has a constructor that accepts a list of column names, allowing you to define the schema of the table when creating it.

insert: The insert method of the Table class allows you to insert rows into the table. It accepts a list of values and an optional at_end argument that specifies whether to insert the new row at the beginning or end of the table.

select_all: The select_all method of the Table class allows you to select all rows from the table and print them to the console.

select_where: The select_where method of the Table class allows you to select rows from the table that meet a given condition. It accepts a predicate function that specifies the condition and prints the matching rows to the console.

update_where: The update_where method of the Table class allows you to update rows in the table that meet a given condition. It accepts a predicate function that specifies the condition and an updater function that specifies how to update the matching rows.

delete_where: The delete_where method of the Table class allows you to delete rows from the table that meet a given condition. It accepts a predicate function that specifies the condition.

join: The join method of the Table class allows you to join two tables based on a given condition. It accepts another Table object and a predicate function that specifies the condition, and returns a new table containing the joined rows.

save_to_file: The save_to_file method of the Table class allows you to save the contents of a table to a file. It accepts a folder path, a filename, and an encryption key as arguments.

load_from_file: The load_from_file method of the Table class allows you to load data into a table from a file. It accepts a folder path, a filename, and an encryption key as arguments.

## Conclusion
EMDC is a powerful and flexible tool for working with tabular data in C++. Its familiar SQL-like syntax and advanced features make it an attractive option for users who need to manipulate and analyze data in a simple and efficient manner. With its support for multi-threading and file-based persistence, EMDC is well-suited for a wide range of data processing tasks.
