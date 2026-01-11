#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;

// =====================================================
//                     COLORS
// =====================================================
#define RESET   "\033[0m"
#define CYAN    "\033[96m"
#define GREEN   "\033[92m"
#define YELLOW  "\033[93m"
#define BLUE    "\033[94m"
#define ORANGE  "\033[33m"
#define RED     "\033[91m"

// =====================================================
//                     STRUCTS
// =====================================================
struct Car
{
    int id;
    string make;
    string model;
    int year;
    double price;
    int stock;
    string picture;
    string color;
    string transmission;
    string bodyType;
};

struct Customer
{
    int id;
    string name;
    string phone;
    string email;
};

struct SaleItem {
    int carId;
    int quantity;
    double unitPrice;
};

struct Sale {
    int id;
    int customerId;
    vector<SaleItem> items;
    double total = 0.0;
};

struct User {
    string username;
    string password;
    string role; // admin or user
};

// =====================================================
//                     GLOBALS
// =====================================================
vector<Car> inventory;
vector<Customer> customers;
vector<Sale> sales;
vector<User> users;
User currentUser;

// =====================================================
//                UTILITY / HELPER FUNCTIONS
// =====================================================
void banner() {
    cout << CYAN << "\n========================================\n" << RESET;
    cout << CYAN << "     CAR SHOWROOM MANAGEMENT SYSTEM     \n" << RESET;
    cout << CYAN << "========================================\n" << RESET;
}

void line() { cout << YELLOW << "----------------------------------------\n" << RESET; }

bool isAdmin() {
    return currentUser.role == "admin";
}

Car* findCarById(int id) {
    for (auto& c : inventory)
        if (c.id == id) return &c;
    return nullptr;
}

Customer* findCustomerById(int id) {
    for (auto& c : customers)
        if (c.id == id) return &c;
    return nullptr;
}

// =====================================================
//                FILE SAVE / LOAD
// =====================================================
void saveInventory() {
    ofstream myfile("inventory.txt");
    for (auto& c : inventory) {
        myfile << c.id << "|" << c.make << "|" << c.model << "|"
            << c.year << "|" << c.price << "|" << c.stock << "|"
            << c.picture << "|" << c.color << "|" << c.transmission << "|"
            << c.bodyType << "\n";
    }
}

void loadInventory() {
    ifstream myfile("inventory.txt");
    if (!myfile) return;

    string line;
    while (getline(myfile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Car c; string temp;

        getline(ss, temp, '|'); c.id = stoi(temp);
        getline(ss, c.make, '|');
        getline(ss, c.model, '|');
        getline(ss, temp, '|'); c.year = stoi(temp);
        getline(ss, temp, '|'); c.price = stod(temp);
        getline(ss, temp, '|'); c.stock = stoi(temp);
        getline(ss, c.picture, '|');
        getline(ss, c.color, '|');
        getline(ss, c.transmission, '|');
        getline(ss, c.bodyType, '|');

        inventory.push_back(c);
    }
}

void saveCustomers() {
    ofstream f("customers.txt");
    for (auto& c : customers)
        f << c.id << "|" << c.name << "|" << c.phone << "|" << c.email << "\n";
}

void loadCustomers() {
    ifstream f("customers.txt");
    if (!f) return;

    string line;
    while (getline(f, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Customer c; string temp;

        getline(ss, temp, '|'); c.id = stoi(temp);
        getline(ss, c.name, '|');
        getline(ss, c.phone, '|');
        getline(ss, c.email, '|');
        customers.push_back(c);
    }
}

void saveUsers() {
    ofstream f("users.txt");
    for (auto& u : users)
        f << u.username << "|" << u.password << "|" << u.role << "\n";
}

void loadUsers() {
    ifstream f("users.txt");
    if (!f) return;

    string line;
    while (getline(f, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        User u;

        getline(ss, u.username, '|');
        getline(ss, u.password, '|');
        getline(ss, u.role, '|');

        users.push_back(u);
    }
}

// =====================================================
//                     LOGIN
// =====================================================
bool login() {
    string uname, pass;
    cout << BLUE << "Enter Username: " << RESET;
    cin >> uname;
    cout << BLUE << "Enter Password: " << RESET;
    cin >> pass;

    for (auto& u : users) {
        if (u.username == uname && u.password == pass) {
            currentUser = u;
            cout << GREEN << "Login Successful (" << u.role << ")\n" << RESET;
            return true;
        }
    }
    cout << RED << "Invalid username or password.\n" << RESET;
    return false;
}

// =====================================================
//                     DISPLAY
// =====================================================
void displayCars() {
    banner();
    cout << ORANGE << "CAR INVENTORY\n" << RESET;
    line();

    if (inventory.empty()) {
        cout << RED << "No cars available.\n" << RESET;
        return;
    }

    for (auto& c : inventory)
    {
        cout << CYAN << "ID: " << c.id
            << " | " << c.make << " " << c.model
            << " | Year: " << c.year
            << " | Price: " << c.price
            << " | Stock: " << c.stock
            << " | Color: " << c.color
            << " | Trans: " << c.transmission
            << " | Body: " << c.bodyType << RESET << "\n";
    }
    line();
}

void displayCustomers() {
    banner();
    cout << ORANGE << "CUSTOMERS\n" << RESET;
    line();

    if (customers.empty()) {
        cout << RED << "No customers found.\n" << RESET;
        return;
    }

    for (auto& c : customers) {
        cout << CYAN << "ID: " << c.id << " | Name: " << c.name
            << " | Phone: " << c.phone
            << " | Email: " << c.email << RESET << "\n";
    }
    line();
}

// =====================================================
//                     ADD DATA
// =====================================================
void addCar() {
    if (!isAdmin()) { cout << RED << "Admins only.\n" << RESET; return; }

    Car c;
    cout << BLUE << "Enter Car ID: " << RESET; cin >> c.id;
    cout << BLUE << "Make: " << RESET; cin >> c.make;
    cout << BLUE << "Model: " << RESET; cin >> c.model;
    cout << BLUE << "Year: " << RESET; cin >> c.year;
    cout << BLUE << "Price: " << RESET; cin >> c.price;
    cout << BLUE << "Stock: " << RESET; cin >> c.stock;
    cout << BLUE << "Color: " << RESET; cin >> c.color;
    cout << BLUE << "Transmission: " << RESET; cin >> c.transmission;
    cout << BLUE << "Body Type: " << RESET; cin >> c.bodyType;
    cout << BLUE << "Picture Path: " << RESET; cin >> c.picture;

    inventory.push_back(c);
    saveInventory();
    cout << GREEN << "Car Added.\n" << RESET;
}

void addCustomer() {
    if (!isAdmin()) { cout << RED << "Admins only.\n" << RESET; return; }

    Customer c;
    cout << BLUE << "Customer ID: " << RESET; cin >> c.id;
    cin.ignore();
    cout << BLUE << "Name: " << RESET; getline(cin, c.name);
    cout << BLUE << "Phone: " << RESET; getline(cin, c.phone);
    cout << BLUE << "Email: " << RESET; getline(cin, c.email);

    customers.push_back(c);
    saveCustomers();
    cout << GREEN << "Customer Added.\n" << RESET;
}

// =====================================================
//                    SEARCH / COMPARE
// =====================================================
void searchCar() {
    int choice;
    cout << ORANGE << "\n=== ADVANCED SEARCH ===\n" << RESET;
    cout << BLUE
        << "1. Search by ID\n"
        << "2. Search by Make & Model\n"
        << "3. Search by Year\n"
        << "4. Search by Price Range\n"
        << "5. Search by Color\n"
        << "6. Search by Transmission\n"
        << "7. Search by Body Type\n"
        << "Enter choice: " << RESET;
    cin >> choice;

    bool found = false;

    if (choice == 1) {
        int id;
        cout << BLUE << "Enter Car ID: " << RESET;
        cin >> id;

        for (auto& c : inventory) {
            if (c.id == id) {
                cout << GREEN << "Found: " << c.make << " " << c.model
                    << " | Price: " << c.price << "\n" << RESET;
                found = true;
            }
        }
    }
    else if (choice == 2) {
        string make, model;
        cout << BLUE << "Enter Make: " << RESET; cin >> make;
        cout << BLUE << "Enter Model: " << RESET; cin >> model;
        for (auto& c : inventory) {
            if (c.make == make && c.model == model) {
                cout << GREEN << "Found ? ID: " << c.id
                    << " | Year: " << c.year
                    << " | Price: " << c.price << "\n" << RESET;
                found = true;
            }
        }
    }
    else if (choice == 3) {
        int year;
        cout << BLUE << "Enter Year: " << RESET; cin >> year;
        for (auto& c : inventory) {
            if (c.year == year) {
                cout << GREEN << "Found ? " << c.make << " " << c.model
                    << " | Price: " << c.price << "\n" << RESET;
                found = true;
            }
        }
    }
    else if (choice == 4) {
        double minP, maxP;
        cout << BLUE << "Enter Min Price: " << RESET; cin >> minP;
        cout << BLUE << "Enter Max Price: " << RESET; cin >> maxP;
        for (auto& c : inventory) {
            if (c.price >= minP && c.price <= maxP) {
                cout << GREEN << "Found ? " << c.make << " " << c.model
                    << " | Price: " << c.price << "\n" << RESET;
                found = true;
            }
        }
    }
    else if (choice == 5) {
        string color;
        cout << BLUE << "Enter Color: " << RESET; cin >> color;
        for (auto& c : inventory) {
            if (c.color == color) {
                cout << GREEN << "Found ? " << c.make << " " << c.model
                    << " | Price: " << c.price << "\n" << RESET;
                found = true;
            }
        }
    }
    else if (choice == 6) {
        string trans;
        cout << BLUE << "Enter Transmission: " << RESET; cin >> trans;
        for (auto& c : inventory) {
            if (c.transmission == trans) {
                cout << GREEN << "Found ? " << c.make << " " << c.model
                    << " | Year: " << c.year << "\n" << RESET;
                found = true;
            }
        }
    }
    else if (choice == 7) {
        string body;
        cout << BLUE << "Enter Body Type: " << RESET; cin >> body;
        for (auto& c : inventory) {
            if (c.bodyType == body) {
                cout << GREEN << "Found ? " << c.make << " " << c.model
                    << " | Price: " << c.price << "\n" << RESET;
                found = true;
            }
        }
    }
    else {
        cout << RED << "Invalid option.\n" << RESET;
    }

    if (!found)
        cout << RED << "No matching car found.\n" << RESET;
}

// =====================================================
//                   COMPARE / SALES / SORT
// =====================================================
void compareCars() {
    int id1, id2;
    cout << BLUE << "First Car ID: " << RESET; cin >> id1;
    cout << BLUE << "Second Car ID: " << RESET; cin >> id2;

    Car* c1 = findCarById(id1);
    Car* c2 = findCarById(id2);

    if (!c1 || !c2) {
        cout << RED << "Car not found.\n" << RESET;
        return;
    }

    cout << ORANGE << "\n=== Comparison ===\n" << RESET;
    cout << GREEN << c1->make << " " << c1->model
        << " VS " << c2->make << " " << c2->model << "\n" << RESET;
    cout << CYAN << "Year: " << c1->year << " vs " << c2->year << "\n" << RESET;
    cout << CYAN << "Price: " << c1->price << " vs " << c2->price << "\n" << RESET;
    cout << CYAN << "Color: " << c1->color << " vs " << c2->color << "\n" << RESET;
    cout << CYAN << "Transmission: " << c1->transmission << " vs " << c2->transmission << "\n" << RESET;
    cout << CYAN << "Body: " << c1->bodyType << " vs " << c2->bodyType << "\n" << RESET;
}

void createSale() {
    if (!isAdmin()) { cout << RED << "Admins only.\n" << RESET; return; }

    if (inventory.empty()) {
        cout << RED << "No cars in inventory.\n" << RESET;
        return;
    }

    Sale s;
    cout << BLUE << "Sale ID: " << RESET; cin >> s.id;
    cout << BLUE << "Customer ID: " << RESET; cin >> s.customerId;
    cout << BLUE << "Number of different cars: " << RESET;
    int count; cin >> count;

    for (int i = 0; i < count; i++) {
        int carId, qty;
        cout << BLUE << "Car ID and Quantity: " << RESET;
        cin >> carId >> qty;

        Car* car = findCarById(carId);
        if (!car) {
            cout << RED << "Car not found.\n" << RESET;
            return;
        }

        if (qty > car->stock) {
            cout << RED << "Not enough stock.\n" << RESET;
            return;
        }

        car->stock -= qty;
        s.items.push_back({ carId, qty, car->price });
        s.total += qty * car->price;
    }

    sales.push_back(s);
    saveInventory();

    cout << GREEN << "Sale Created. Total = " << s.total << "\n" << RESET;
}

void salesReport() {
    if (!isAdmin()) { cout << RED << "Admins only.\n" << RESET; return; }

    double revenue = 0;
    map<int, int> countSold;

    for (auto& s : sales) {
        revenue += s.total;
        for (auto& item : s.items)
            countSold[item.carId] += item.quantity;
    }

    cout << ORANGE << "Total Revenue: " << GREEN << revenue << "\n" << RESET;

    int bestId = -1, maxSold = 0;
    for (auto& p : countSold) {
        if (p.second > maxSold) {
            maxSold = p.second;
            bestId = p.first;
        }
    }

    if (bestId != -1) {
        Car* c = findCarById(bestId);
        if (c)
            cout << ORANGE << "Best-selling: " << GREEN << c->make << " " << c->model
            << ORANGE << " (" << maxSold << " units)\n" << RESET;
    }
}

void sortCars() {
    if (!isAdmin()) { cout << RED << "Admins only.\n" << RESET; return; }

    int ch;
    cout << BLUE << "Sort by: 1.Price  2.Year  3.Make\nChoice: " << RESET;
    cin >> ch;

    if (ch == 1)
        sort(inventory.begin(), inventory.end(), [](Car a, Car b) { return a.price < b.price; });
    else if (ch == 2)
        sort(inventory.begin(), inventory.end(), [](Car a, Car b) { return a.year < b.year; });
    else if (ch == 3)
        sort(inventory.begin(), inventory.end(), [](Car a, Car b) { return a.make < b.make; });
    else {
        cout << RED << "Invalid choice.\n" << RESET;
        return;
    }

    cout << GREEN << "Cars sorted.\n" << RESET;
}

void showMenu() {
    banner();
    cout << YELLOW
        << "1. Add Car (Admin)\n"
        << "2. Display Cars\n"
        << "3. Add Customer (Admin)\n"
        << "4. Display Customers\n"
        << "5. Search Car\n"
        << "6. Compare Cars\n"
        << "7. Create Sale (Admin)\n"
        << "8. Sales Report (Admin)\n"
        << "9. Sort Cars (Admin)\n"
        << "10. Exit\n" << RESET;
    line();
    cout << BLUE << "Enter choice: " << RESET;
}

int main() {
    loadUsers();
    loadInventory();
    loadCustomers();

    if (users.empty()) {
        User defaultAdmin;
        defaultAdmin.username = "admin";
        defaultAdmin.password = "123";
        defaultAdmin.role = "admin";

        users.push_back(defaultAdmin);
        saveUsers();

        cout << GREEN << "\nNo users detected. Default admin created:\n" << RESET;
        cout << CYAN << "Username: admin\nPassword: 123\n\n" << RESET;
    }

    cout << ORANGE << "=== Welcome ===\n" << RESET;
    if (!login()) return 0;

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: addCar(); break;
        case 2: displayCars(); break;
        case 3: addCustomer(); break;
        case 4: displayCustomers(); break;
        case 5: searchCar(); break;
        case 6: compareCars(); break;
        case 7: createSale(); break;
        case 8: salesReport(); break;
        case 9: sortCars(); break;
        case 10: cout << GREEN << "Goodbye!\n" << RESET; break;
        default: cout << RED << "Invalid choice.\n" << RESET;
        }
    } while (choice != 10);

    return 0;
}