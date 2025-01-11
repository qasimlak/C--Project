#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

struct Product {
    int id;
    string name;
    double price;
    int quantity;
};

struct Customer {
    int id;
    string name;
    string contact;
};

struct Sale {
    int saleId;
    int productId;
    int customerId;
    int quantitySold;
    double totalPrice;
};

void displayMenu();
void addProduct(vector<Product>& products);
void displayProducts(const vector<Product>& products);
void addCustomer(vector<Customer>& customers);
void displayCustomers(const vector<Customer>& customers);
void recordSale(vector<Product>& products, vector<Customer>& customers, vector<Sale>& sales);
void displaySales(const vector<Sale>& sales);

void loadProducts(const string& filename, vector<Product>& products);
void saveProducts(const string& filename, const vector<Product>& products);
void loadCustomers(const string& filename, vector<Customer>& customers);
void saveCustomers(const string& filename, const vector<Customer>& customers);
void loadSales(const string& filename, vector<Sale>& sales);
void saveSales(const string& filename, const vector<Sale>& sales);

int main() {
    vector<Product> products;
    vector<Customer> customers;
    vector<Sale> sales;
    int choice;

    try {
        loadProducts("products.txt", products);
        loadCustomers("customers.txt", customers);
        loadSales("sales.txt", sales);
    }
    catch (const exception& e) {
        cerr << "Error during file loading: " << e.what() << endl;
    }

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            addProduct(products);
            break;
        case 2:
            displayProducts(products);
            break;
        case 3:
            addCustomer(customers);
            break;
        case 4:
            displayCustomers(customers);
            break;
        case 5:
            recordSale(products, customers, sales);
            break;
        case 6:
            displaySales(sales);
            break;
        case 0:
            try {
                saveProducts("products.txt", products);
                saveCustomers("customers.txt", customers);
                saveSales("sales.txt", sales);
            }
            catch (const exception& e) {
                cerr << "Error during file saving: " << e.what() << endl;
            }
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

void displayMenu() {
    cout << "\n1. Add Product\n2. Display Products\n3. Add Customer\n4. Display Customers\n5. Record Sale\n6. Display Sales\n0. Exit\nEnter your choice: ";
}

void loadProducts(const string& filename, vector<Product>& products) {
    ifstream file(filename);
    if (!file) throw runtime_error("Unable to open " + filename);
    Product temp;
    while (file >> temp.id >> temp.name >> temp.price >> temp.quantity) {
        products.push_back(temp);
    }
    cout << "Products loaded successfully from " << filename << endl;
}

void saveProducts(const string& filename, const vector<Product>& products) {
    ofstream file(filename);
    if (!file) throw runtime_error("Unable to open " + filename + " for writing");
    for (const auto& product : products) {
        file << product.id << " " << product.name << " " << product.price << " " << product.quantity << "\n";
    }
    file.flush();
    cout << "Products saved successfully to " << filename << endl;
}

void loadCustomers(const string& filename, vector<Customer>& customers) {
    ifstream file(filename);
    if (!file) throw runtime_error("Unable to open " + filename);
    Customer temp;
    while (file >> temp.id >> temp.name >> temp.contact) {
        customers.push_back(temp);
    }
    cout << "Customers loaded successfully from " << filename << endl;
}

void saveCustomers(const string& filename, const vector<Customer>& customers) {
    ofstream file(filename);
    if (!file) throw runtime_error("Unable to open " + filename + " for writing");
    for (const auto& customer : customers) {
        file << customer.id << " " << customer.name << " " << customer.contact << "\n";
    }
    file.flush();
    cout << "Customers saved successfully to " << filename << endl;
}

void loadSales(const string& filename, vector<Sale>& sales) {
    ifstream file(filename);
    if (!file) throw runtime_error("Unable to open " + filename);
    Sale temp;
    while (file >> temp.saleId >> temp.productId >> temp.customerId >> temp.quantitySold >> temp.totalPrice) {
        sales.push_back(temp);
    }
    cout << "Sales loaded successfully from " << filename << endl;
}

void saveSales(const string& filename, const vector<Sale>& sales) {
    ofstream file(filename);
    if (!file) throw runtime_error("Unable to open " + filename + " for writing");
    for (const auto& sale : sales) {
        file << sale.saleId << " " << sale.productId << " " << sale.customerId << " " << sale.quantitySold << " " << sale.totalPrice << "\n";
    }
    file.flush();
    cout << "Sales saved successfully to " << filename << endl;
}

void addProduct(vector<Product>& products) {
    Product newProduct;
    cout << "Enter Product ID: ";
    cin >> newProduct.id;
    cin.ignore();
    cout << "Enter Product Name: ";
    getline(cin, newProduct.name);
    cout << "Enter Product Price: ";
    cin >> newProduct.price;
    cout << "Enter Product Quantity: ";
    cin >> newProduct.quantity;
    products.push_back(newProduct);
}

void displayProducts(const vector<Product>& products) {
    for (const auto& product : products) {
        cout << "ID: " << product.id << " Name: " << product.name << " Price: " << product.price << " Quantity: " << product.quantity << "\n";
    }
}

void addCustomer(vector<Customer>& customers) {
    Customer newCustomer;
    cout << "Enter Customer ID: ";
    cin >> newCustomer.id;
    cin.ignore();
    cout << "Enter Customer Name: ";
    getline(cin, newCustomer.name);
    cout << "Enter Customer Contact: ";
    getline(cin, newCustomer.contact);
    customers.push_back(newCustomer);
}

void displayCustomers(const vector<Customer>& customers) {
    for (const auto& customer : customers) {
        cout << "ID: " << customer.id << " Name: " << customer.name << " Contact: " << customer.contact << "\n";
    }
}

void recordSale(vector<Product>& products, vector<Customer>& customers, vector<Sale>& sales) {
    Sale newSale;
    cout << "Enter Sale ID: ";
    cin >> newSale.saleId;
    cout << "Enter Product ID: ";
    cin >> newSale.productId;
    cout << "Enter Customer ID: ";
    cin >> newSale.customerId;
    cout << "Enter Quantity Sold: ";
    cin >> newSale.quantitySold;

    for (auto& product : products) 
    {
        if (product.id == newSale.productId) {
            if (product.quantity >= newSale.quantitySold) {
                newSale.totalPrice = newSale.quantitySold * product.price;
                product.quantity -= newSale.quantitySold;
                sales.push_back(newSale);
                cout << "Sale recorded. Total Price: " << newSale.totalPrice << "\n";
                return;
            }
            else {
                cout << "Not enough stock available.\n";
                return;
            }
        }
    }
    cout << "Product not found.\n";
}

void displaySales(const vector<Sale>& sales) {
    for (const auto& sale : sales) {
        cout << "Sale ID: " << sale.saleId << " Product ID: " << sale.productId << " Customer ID: " << sale.customerId
            << " Quantity Sold: " << sale.quantitySold << " Total Price: " << sale.totalPrice << "\n";
    }
}
