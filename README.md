# 🛍️ RETAIL_REFORM - Smart Shop Finder System

**RETAIL_REFORM** is a C++ Object-Oriented Programming (OOP) based project that simulates a smart shop-finder and product-booking system. It helps users discover nearby shops, search for products, view product availability, and make bookings—all in a structured, modular, and efficient way.

---

## 📌 Features

- 👤 User registration and login
- 🏪 Shop registration with product catalog
- 🔍 Search for products across shops
- ✅ Check product availability
- 📦 Book products from selected shops
- 🧾 Generate booking receipt for users
- 📜 LRU cache to store recently searched products
- 📊 Well-structured code using C++ OOP concepts

---

## 💡 Motivation

In local markets, it can be time-consuming to find a shop that has the desired product in stock. **RETAIL_REFORM** was built to solve this by allowing users to:

- Search and book products easily.
- Discover which nearby shops offer what.
- Help shopkeepers reach customers efficiently.

---

## 🛠️ Tech Stack

- **Language:** C++
- **Concepts Used:**
  - Classes & Objects
  - Inheritance & Polymorphism
  - STL Containers (`map`, `list`, `unordered_map`)
  - File I/O (if added later)
  - Modular code with header and implementation files

---

## 🧩 Modules Breakdown

| Module          | Description |
|----------------|-------------|
| `User`          | Handles user information, login, and registration. |
| `Shop`          | Manages shop details and available product inventory. |
| `Booking`       | Manages the booking process and receipt generation. |
| `LRUCache`      | Stores recently searched products to speed up user experience. |
| `Main` (Testing.cpp) | Entry point of the program and interaction logic. |

---

## ⚙️ How to Compile & Run

1. **Clone the project** or download all `.cpp` and `.h` files.
2. **Open terminal** in the project directory.
3. **Compile the project:**
   ```bash
   g++ Testing.cpp User.cpp Shop.cpp Booking.cpp LRUCache.cpp -o RetailReform
