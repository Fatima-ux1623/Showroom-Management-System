# 🚗 Car Showroom Management System (C++)

A console-based **Car Showroom Management System** developed in **C++** that manages car inventory, customers, sales, and reports using **Object-Oriented Programming (OOP)** and **file handling**.  
The system supports **role-based login (Admin/User)** and provides advanced search, comparison, sorting, and sales reporting features.
---
## 📌 Features

### 🔐 User Authentication
- Secure login system
- Role-based access:
  - **Admin**
  - **User**
- Default admin is auto-created if no user exists

### 🚘 Car Inventory Management (Admin)
- Add new cars with complete details:
  - Make, Model, Year, Price
  - Stock, Color, Transmission, Body Type
- Persistent storage using file handling
- Display complete car inventory

### 👥 Customer Management (Admin)
- Add customer details
- View customer list
- Data saved in files for future use

### 🔍 Advanced Car Search
Search cars using:
- Car ID
- Make & Model
- Manufacturing Year
- Price Range
- Color
- Transmission type
- Body type

### ⚖️ Car Comparison
- Compare two cars side-by-side
- Comparison based on:
  - Year
  - Price
  - Color
  - Transmission
  - Body Type

### 🛒 Sales Management (Admin)
- Create sales for customers
- Multiple cars per sale
- Automatic stock update
- Total bill calculation

### 📊 Sales Report (Admin)
- Total revenue calculation
- Best-selling car analysis

### 🔃 Sorting Options (Admin)
- Sort cars by:
  - Price
  - Year
  - Make

### 🎨 User-Friendly Console UI
- Colored console output
- Menu-driven interface
- Clear and structured navigation

---

## 🛠️ Technologies Used
- **C++**
- Object-Oriented Programming (OOP)
- STL (`vector`, `map`, `algorithm`)
- File Handling (`fstream`)
- Console-based UI

---

## 📂 Data Storage
The system stores data in text files:
- `inventory.txt` → Car data
- `customers.txt` → Customer records
- `users.txt` → User login data

---

## ▶️ How to Run the Project

1. Clone the repository or download the source code
2. Open the project in any C++ compiler (Code::Blocks / Dev-C++ / VS Code)
3. Compile the code:
   ```bash

## 🔑 Default Admin Credentials
(Automatically created if no user exists)

- Username: admin
- Password: 123

   g++ main.cpp -o showroom

