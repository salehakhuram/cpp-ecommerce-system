Multi-Role E-Commerce Management System in C++

 Project Description

This is a console-based e-commerce management system written in C++. It simulates the core features of an online store and supports three roles: Admin, Employee, and User. Each role has specific permissions and functionalities. Data is managed using text files for storage and retrieval.

Features

Authentication System

* Sign up, log in, and reset passwords
* Password input is hidden using getch()

User Role

* Browse products and categories
* Add items to cart and place orders
* Cancel orders and make payments
* Review products

Employee Role

* Add, update, and delete products
* Add and update categories
* Update stock and check low inventory
* View and manage orders
* Access sales report

Admin Role

* View and delete users and employees
* View product reviews
* Search products by ID

File-Based Storage

* All data (users, products, orders, cart, etc.) is stored in text files

Skills Used

C++ Programming
Object-Oriented Programming (OOP)
File Handling (ifstream, ofstream)
Input Validation
Console UI Design

How to Run the Code

1. Install a C++ compiler (e.g., g++, Code::Blocks, Dev C++, or Visual Studio).
2. Place the `.cpp` file and required `.txt` files (such as `products.txt`, `users.txt`) in the same folder.
3. Open a terminal or command prompt.
4. Compile the file:
   g++ final.cpp -o ecommerce
5. Run the program:
   ./ecommerce   (or ecommerce.exe on Windows)

If you're using an IDE like Code::Blocks or Visual Studio, just create a new project and add the `Ecommerce System.cpp` file, then build and run it from there.
 C++ Console-Based E-Commerce System with multi-role support
