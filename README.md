# EMDC
EMDC (Stands for Effective Multithereded Database Creating ToolKit) is a simple opensourse SQL-like database program written in C++. It allows users to create and manipulate tables of data using a familiar SQL-like syntax.
EMDC includes support for defining the table schema, inserting rows at the beginning or end of the table, and performing basic queries such as selecting, updating, and deleting rows. It also includes support for joining multiple tables based on a given condition.

One of the advanced features of EMDC is its support for multi-threading. This allows the program to perform database operations in parallel, potentially improving performance on multi-core systems. EMDC uses a mutex to synchronize access to the table data and ensure that multiple threads can safely perform operations on the table at the same time.

Another advanced feature of EMDC is its support for saving and loading the database to/from a file. This allows users to persist their data and continue working with it even after the program has been closed. EMDC uses a simple encryption algorithm to protect the data when saving it to a file, adding an extra layer of security.

Overall, EMDC is a powerful and flexible tool for working with tabular data in C++. Its familiar SQL-like syntax and advanced features make it an attractive option for users who need to manipulate and analyze data in a simple and efficient manner.

Compileing: 
To compile the code for the EMDC program, you will need a C++ compiler that supports at least the C++11 standard. Popular C++ compilers include GCC, Clang, and Microsoft Visual C++. You can download and install one of these compilers from their respective websites.

Once you have a C++ compiler installed, you can compile the code using the command line. Open a command prompt or terminal window and navigate to the directory where you saved the EMDC.cpp file. Then, enter the following command to compile the code:

g++ EMDC.cpp -o EMDC.exe -lstdc++fs

This command uses the GCC compiler to compile the code in the EMDC.cpp file and produce an executable file named EMDC.exe. The -lstdc++fs flag is used to link against the stdc++fs library, which is required to use the std::experimental::filesystem or std::filesystem library.

If you are using a different compiler or if your system requires different flags or options, you may need to adjust this command accordingly. Consult the documentation for your compiler for more information on how to compile C++ code.

Once the code has been compiled successfully, you can run the EMDC.exe executable file to start the program.
