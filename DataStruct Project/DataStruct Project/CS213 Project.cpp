#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Product {

public:
    int Pid;
    string Pname;
    int stock;
    int price;
    int exp_month;
    int exp_year;
    Product* pNext;
};

class CListProduct {
public:
    Product* pHead;
    Product* pTail;

    CListProduct()
    {
        pHead = NULL;
        pTail = NULL;
    }

    void Attach(Product* pnn)
    {
        if (pHead == NULL) {
            pHead = pnn;
            pTail = pnn;
        }
        else {
            pTail->pNext = pnn;
            pTail = pnn;
        }
    }

    void Add()
    {
        string name;
        int stock, price, expm, expy;

        Product* pnn = new Product;

        pnn->Pid = pTail->Pid + 1;

        cout << "Enter product name: ";
        cin >> name;
        pnn->Pname = name;
        cout << endl;

        cout << "Enter product stock quantity: ";
        cin >> stock;
        pnn->stock = stock;
        cout << endl;

        cout << "Enter product price: ";
        cin >> price;
        pnn->price = price;
        cout << endl;

        cout << "Enter product expiry month: ";
        cin >> expm;
        pnn->exp_month = expm;
        cout << endl;

        cout << "Enter product expiry year: ";
        cin >> expy;
        pnn->exp_year = expy;
        cout << endl;


        pnn->pNext = NULL;

        Attach(pnn);

    }

    void Buy(int productId, int quantity, int& tot)
    {
        Product* pTrav = pHead;

        while (pTrav != NULL)
        {
            if (pTrav->Pid == productId)
            {
                if (pTrav->stock >= quantity)
                {
                    pTrav->stock -= quantity;
                    cout << "Purchase successful!" << endl;
                    tot += pTrav->price * quantity;
                }
                else
                {
                    cout << "Insufficient stock." << endl;
                }

                return;
            }

            pTrav = pTrav->pNext;
        }

        cout << "Product not found." << endl;
    }

    void Return(int productId, int& tot)
    {
        Product* pTrav = pHead;

        while (pTrav != NULL)
        {
            if (pTrav->Pid == productId)
            {
                // Increase the stock
                pTrav->stock++;
                cout << "returned successfully" << endl;
                tot -= pTrav->price;
                break;
            }

            pTrav = pTrav->pNext;
        }
    }

    void Remove(int id)
    {
        Product* pTrav = pHead;
        Product* pB = NULL;

        while (pTrav != NULL)
        {
            if (pTrav->Pid == id)
            {
                if (pTrav != pHead) // Not the first node
                {
                    if (pTrav != pTail) // Not the last node
                    {
                        pB->pNext = pTrav->pNext;
                        pTrav->pNext = NULL;
                        delete pTrav;
                    }
                    else // Last node
                    {
                        pTail = pB;
                        pB->pNext = NULL;
                        delete pTrav;
                    }
                }
                else // First node
                {
                    pHead = pTrav->pNext;
                    pTrav->pNext = NULL;
                    delete pTrav;
                }

                break; // Exit the loop after removing the node
            }
            else
            {
                pB = pTrav;
                pTrav = pTrav->pNext;
            }
        }
    }

    void Adjust(int id)
    {
        char change;
        string name;
        int value = 0, again = 1;

        while (again == 1)
        {
            cout << "What do you want to adjust?\nn:Product Name\ns:Stock Quantity\np:Product Price\nm:Expiry Month\ny:Expiry Year\n";
            cin >> change;

            Product* pTrav = pHead;

            while (pTrav != NULL)
            {
                if (pTrav->Pid == id)
                {
                    if (change == 'n')
                    {
                        cout << "Enter new name: ";
                        cin >> name;
                        pTrav->Pname = name;
                        break;

                    }
                    if (change == 's')
                    {
                        cout << "Enter new stock quantity: ";
                        cin >> value;
                        pTrav->stock = value;
                        break;


                    }
                    if (change == 'p')
                    {
                        cout << "Enter new price: ";
                        cin >> value;
                        pTrav->price = value;
                        break;

                    }
                    if (change == 'm')
                    {
                        cout << "Enter new expiry month: ";
                        cin >> value;
                        pTrav->exp_month = value;
                        break;
                    }
                    if (change == 'y')
                    {
                        cout << "Enter new expiry year: ";
                        cin >> value;
                        pTrav->exp_year = value;
                        break;
                    }
                }

                pTrav = pTrav->pNext;


            }

            cout << "\nDo you want to adjust anything else in the SAME product? \n1.Yes\n2.No\n";
            cin >> again;

            name.clear();
            value = 0;
        }

    }

    void DisplayAllProducts()
    {
        Product* pTrav = pHead;

        cout << "Products" << endl;

        while (pTrav != NULL)
        {
            cout << "Product ID: " << pTrav->Pid << endl;
            cout << "Name: " << pTrav->Pname << endl;
            cout << "Stock: " << pTrav->stock << endl;
            cout << "Price: " << pTrav->price << endl;
            cout << "Expiry Month: " << pTrav->exp_month << endl;
            cout << "Expiry Year: " << pTrav->exp_year << endl;

            cout << endl;

            pTrav = pTrav->pNext;
        }
    }

    void DisplayLessStock()
    {
        int quantity;
        Product* pTrav = pHead;

        cout << "Enter quantity: ";
        cin >> quantity;
        cout << "\nProducts with stock less than " << quantity << endl;
        cout << endl;
        while (pTrav != NULL)
        {
            if (pTrav->stock < quantity)
            {
                cout << "Product ID: " << pTrav->Pid << endl;
                cout << "Name: " << pTrav->Pname << endl;
                cout << "Stock: " << pTrav->stock << endl;
                cout << "Price: " << pTrav->price << endl;
                cout << "Expiry Month: " << pTrav->exp_month << endl;
                cout << "Expiry Year: " << pTrav->exp_year << endl;

                cout << endl;
            }

            pTrav = pTrav->pNext;

        }
    }

    void DisplayAvaliable()
    {
        Product* pTrav = pHead;

        cout << "Avaliable Products" << endl;

        while (pTrav != NULL)
        {
            if (pTrav->stock > 0)
            {
                cout << "Product ID: " << pTrav->Pid << endl;
                cout << "Name: " << pTrav->Pname << endl;
                cout << "Stock: " << pTrav->stock << endl;
                cout << "Price: " << pTrav->price << endl;
                cout << "Expiry Month: " << pTrav->exp_month << endl;
                cout << "Expiry Year: " << pTrav->exp_year << endl;

                cout << endl;
            }

            pTrav = pTrav->pNext;

        }
    }

    void writeToFile()
    {
        ofstream ProductsFile;
        ProductsFile.open("C:/Users/ASUS/OneDrive/Desktop/semester 3/CS213 DataStructure/CS213 Project/Product.txt");

        if (ProductsFile.is_open())
        {
            Product* pTrav = pHead;

            ProductsFile << "ID" << ",";
            ProductsFile << "Name" << ",";
            ProductsFile << "Stock" << ",";
            ProductsFile << "Price" << ",";
            ProductsFile << "Exp Month" << ",";
            ProductsFile << "Exp Year" << endl;

            while (pTrav != NULL)
            {
                ProductsFile << pTrav->Pid << ",";
                ProductsFile << pTrav->Pname << ",";
                ProductsFile << pTrav->stock << ",";
                ProductsFile << pTrav->price << ",";
                ProductsFile << pTrav->exp_month << ",";
                ProductsFile << pTrav->exp_year << endl;

                pTrav = pTrav->pNext;
            }

            ProductsFile.close();
        }
    }


    ~CListProduct()
    {
        Product* pTrav;
        pTrav = pHead;
        while (pHead != NULL) {
            pHead = pTrav->pNext;
            pTrav->pNext = NULL;
            delete[] pTrav;
            pTrav = pHead;
        }
    }

};

class Customer {
public:
    int Cid;
    string cname;
    string pass;
    Customer* pNext;
};

class CListCustomer {
public:
    Customer* pHead;
    Customer* pTail;

    CListCustomer()
    {
        pHead = NULL;
        pTail = NULL;
    }

    void Attach(Customer* pnn)
    {
        if (pHead == NULL) {
            pHead = pnn;
            pTail = pnn;
        }
        else {
            pTail->pNext = pnn;
            pTail = pnn;
        }
    }

    void RegisterNewCustomer(CListCustomer& Customers, const string& username, const string& password, int& found)
    {
        Customer* pnn = new Customer;
        pnn->Cid = Customers.pTail->Cid + 1;
        pnn->cname = username;
        pnn->pass = password;
        pnn->pNext = NULL;

        Attach(pnn);

        cout << "Registration successful! Your Customer ID is: " << pnn->Cid << endl;
        found = pnn->Cid;
    }

    void DisplayAllCustomers()
    {
        Customer* pTrav = pHead;

        cout << "Customers" << endl;

        while (pTrav != NULL)
        {
            cout << "Customer ID: " << pTrav->Cid << endl;
            cout << "Name: " << pTrav->cname << endl;
            cout << "Pass: " << pTrav->pass << endl;

            cout << endl;

            pTrav = pTrav->pNext;
        }
    }

    void writeToFile()
    {
        ofstream CustomersFile;
        CustomersFile.open("C:/Users/ASUS/OneDrive/Desktop/semester 3/CS213 DataStructure/CS213 Project/Customer.txt");

        if (CustomersFile.is_open())
        {
            Customer* pTrav = pHead;

            CustomersFile << "ID" << ",";
            CustomersFile << "Name" << ",";
            CustomersFile << "Password" << endl;

            while (pTrav != NULL)
            {
                CustomersFile << pTrav->Cid << ",";
                CustomersFile << pTrav->cname << ",";
                CustomersFile << pTrav->pass << endl;

                pTrav = pTrav->pNext;
            }

            CustomersFile.close();
        }
    }


    ~CListCustomer()
    {
        Customer* pTrav;
        pTrav = pHead;
        while (pHead != NULL) {
            pHead = pTrav->pNext;
            pTrav->pNext = NULL;
            delete[] pTrav;
            pTrav = pHead;
        }
    }

};

class Order {
public:
    int Pid;
    int Cid;
    Order* pNext;
};

class CListOrders {
public:
    Order* pHead;
    Order* pTail;

    CListOrders()
    {
        pHead = NULL;
        pTail = NULL;
    }

    void Attach(Order* pnn)
    {
        if (pHead == NULL) {
            pHead = pnn;
            pTail = pnn;
        }
        else {
            pTail->pNext = pnn;
            pTail = pnn;
        }
    }

    void Remove(int id)
    {
        Order* pTrav = pHead;
        Order* pB = NULL;

        while (pTrav != NULL)
        {
            if (pTrav->Pid == id)
            {
                if (pTrav != pHead) // Not the first node
                {
                    if (pTrav != pTail) // Not the last node
                    {
                        pB->pNext = pTrav->pNext;
                        pTrav->pNext = NULL;
                        delete pTrav;
                    }
                    else // Last node
                    {
                        pTail = pB;
                        pB->pNext = NULL;
                        delete pTrav;
                    }
                }
                else // First node
                {
                    pHead = pTrav->pNext;
                    pTrav->pNext = NULL;
                    delete pTrav;
                }

                break; // Exit the loop after removing the node
            }
            else
            {
                pB = pTrav;
                pTrav = pTrav->pNext;
            }
        }

    }


    void DisplayAllOrders()
    {
        Order* pTrav = pHead;

        cout << "Orders" << endl;

        while (pTrav != NULL)
        {
            cout << "Customer ID: " << pTrav->Cid << endl;
            cout << "Product ID: " << pTrav->Pid << endl;
            cout << endl;

            pTrav = pTrav->pNext;
        }
    }

    void writeToFile()
    {
        ofstream OrdersFile;
        OrdersFile.open("C:/Users/ASUS/OneDrive/Desktop/semester 3/CS213 DataStructure/CS213 Project/Orders.txt");

        if (OrdersFile.is_open())
        {
            Order* pTrav = pHead;

            OrdersFile << "Customer ID" << ",";
            OrdersFile << "Product ID" << endl;

            while (pTrav != NULL)
            {
                OrdersFile << pTrav->Cid << ",";
                OrdersFile << pTrav->Pid << endl;

                pTrav = pTrav->pNext;
            }

            OrdersFile.close();
        }
        else
        {
            cout << "Error opening Orders.txt file" << endl;
        }
    }

    ~CListOrders()
    {
        Order* pTrav;
        pTrav = pHead;
        while (pHead != NULL) {
            pHead = pTrav->pNext;
            pTrav->pNext = NULL;
            delete[] pTrav;
            pTrav = pHead;
        }
    }
};

class Admin {
public:
    int Aid;
    string aname;
    string pass;
    Admin* pNext;
};

class CListAdmin {
public:
    Admin* pHead;
    Admin* pTail;

    CListAdmin()
    {
        pHead = NULL;
        pTail = NULL;
    }

    void Attach(Admin* pnn)
    {
        if (pHead == NULL) {
            pHead = pnn;
            pTail = pnn;
        }
        else {
            pTail->pNext = pnn;
            pTail = pnn;
        }
    }

    void DisplayAllAdmins()
    {
        Admin* pTrav = pHead;

        cout << "Admins" << endl;

        while (pTrav != NULL)
        {
            cout << "Admin ID: " << pTrav->Aid << endl;
            cout << "Name: " << pTrav->aname << endl;
            cout << "Pass: " << pTrav->pass << endl;

            cout << endl;

            pTrav = pTrav->pNext;
        }
    }

    void writeToFile()
    {
        ofstream AdminsFile;
        AdminsFile.open("C:/Users/ASUS/OneDrive/Desktop/semester 3/CS213 DataStructure/CS213 Project/Admin.txt");

        if (AdminsFile.is_open())
        {
            Admin* pTrav = pHead;

            AdminsFile << "ID" << ",";
            AdminsFile << "Name" << ",";
            AdminsFile << "Password" << endl;

            while (pTrav != NULL)
            {
                AdminsFile << pTrav->Aid << ",";
                AdminsFile << pTrav->aname << ",";
                AdminsFile << pTrav->pass << endl;

                pTrav = pTrav->pNext;
            }

            AdminsFile.close();
        }
    }

    ~CListAdmin()
    {
        Admin* pTrav;
        pTrav = pHead;
        while (pHead != NULL) {
            pHead = pTrav->pNext;
            pTrav->pNext = NULL;
            delete[] pTrav;
            pTrav = pHead;
        }
    }
};

void readProductsintoList(CListProduct& Products)
{
    string ProductsText;
    ifstream ProductsFile;
    ProductsFile.open("C:/Users/ASUS/OneDrive/Desktop/semester 3/CS213 DataStructure/CS213 Project/Product.txt");
    if (ProductsFile.is_open())
    {
        string temp[6];
        int k = 0;
        int ct = 0;
        //cout << "File is Open" << endl;

        while (getline(ProductsFile, ProductsText))
        {

            if (ct > 0)
            {
                for (int i = 0; i < ProductsText.length(); i++)
                {
                    if (ProductsText[i] == ',')
                    {
                        k++;
                    }
                    else
                    {
                        temp[k] += ProductsText[i];
                    }

                }
                k = 0;
                Product* pnn = new Product;
                pnn->Pid = stoi(temp[0]);
                pnn->Pname = temp[1];
                pnn->stock = stoi(temp[2]);
                pnn->price = stoi(temp[3]);
                pnn->exp_month = stoi(temp[4]);
                pnn->exp_year = stoi(temp[5]);
                pnn->pNext = NULL;
                Products.Attach(pnn);

                for (int h = 0; h < 6; h++)
                {
                    temp[h].clear();
                }
            }
            ct++;

        }
    }
    ProductsFile.close();
    //cout << "-----LIST----" << endl;
    //Products.DisplayAllProducts();

}

void readCustomersintoList(CListCustomer& Customers)
{
    string CustomersText;
    ifstream CustomersFile;

    CustomersFile.open("C:/Users/ASUS/OneDrive/Desktop/semester 3/CS213 DataStructure/CS213 Project/Customer.txt");
    if (CustomersFile.is_open())
    {
        string temp[3];
        int k = 0;
        int ct = 0;
        //cout << "File is Open" << endl;

        while (getline(CustomersFile, CustomersText))
        {
            if (ct > 0)
            {
                for (int i = 0; i < CustomersText.length(); i++)
                {
                    if (CustomersText[i] == ',')
                    {
                        k++;
                    }
                    else
                    {
                        temp[k] += CustomersText[i];
                    }

                }
                k = 0;
                Customer* pnn = new Customer;
                pnn->Cid = stoi(temp[0]);
                pnn->cname = temp[1];
                pnn->pass = temp[2];
                pnn->pNext = NULL;
                Customers.Attach(pnn);

                for (int h = 0; h < 3; h++)
                {
                    temp[h].clear();
                }
            }
            ct++;

        }
    }
    CustomersFile.close();
    //cout << "-----LIST----" << endl;
    //Customers.DisplayAllCustomers();

}

void readOrdersintoList(CListOrders& Orders)
{
    string OrdersText;
    ifstream OrdersFile;

    OrdersFile.open("C:/Users/ASUS/OneDrive/Desktop/semester 3/CS213 DataStructure/CS213 Project/Orders.txt");
    if (OrdersFile.is_open())
    {
        string temp[2];
        int k = 0;
        int ct = 0;
        //cout << "File is Open" << endl;

        while (getline(OrdersFile, OrdersText))
        {
            if (ct > 0)
            {
                for (int i = 0; i < OrdersText.length(); i++)
                {
                    if (OrdersText[i] == ',')
                    {
                        k++;
                    }
                    else
                    {
                        temp[k] += OrdersText[i];
                    }

                }
                k = 0;
                Order* pnn = new Order;
                pnn->Cid = stoi(temp[0]);
                pnn->Pid = stoi(temp[1]);
                pnn->pNext = NULL;
                Orders.Attach(pnn);

                for (int h = 0; h < 2; h++)
                {
                    temp[h].clear();
                }
            }
            ct++;

        }
    }
    OrdersFile.close();
    //cout << "----- Orders LIST----" << endl;
    //Orders.DisplayAllOrders();

}

void readAdminsintoList(CListAdmin& Admins)
{
    string AdminsText;
    ifstream AdminsFile;

    AdminsFile.open("C:/Users/ASUS/OneDrive/Desktop/semester 3/CS213 DataStructure/CS213 Project/Admin.txt");
    if (AdminsFile.is_open())
    {
        string temp[3];
        int k = 0;
        int ct = 0;
        //cout << "File is Open" << endl;

        while (getline(AdminsFile, AdminsText))
        {
            if (ct > 0)
            {
                for (int i = 0; i < AdminsText.length(); i++)
                {
                    if (AdminsText[i] == ',')
                    {
                        k++;
                    }
                    else
                    {
                        temp[k] += AdminsText[i];
                    }

                }
                k = 0;
                Admin* pnn = new Admin;
                pnn->Aid = stoi(temp[0]);
                pnn->aname = temp[1];
                pnn->pass = temp[2];
                pnn->pNext = NULL;
                Admins.Attach(pnn);

                for (int h = 0; h < 3; h++)
                {
                    temp[h].clear();
                }
            }
            ct++;

        }
    }
    AdminsFile.close();
    //cout << "----- Admins LIST----" << endl;
    //Admins.DisplayAllAdmins();
}

int SignInCustomer(CListCustomer& Customers, string& username, string& password)
{
    Customer* pTrav = Customers.pHead;
    int found = 0;

    while (pTrav != NULL)
    {
        if (pTrav->cname == username && pTrav->pass == password)
        {
            cout << "Sign-in successful! Your Customer ID is: " << pTrav->Cid << endl;
            found = pTrav->Cid;
            break;
        }

        pTrav = pTrav->pNext;
    }

    return found;
}

int SignInAdmin(CListAdmin& Admins, string& username, string& password)
{
    Admin* pTrav = Admins.pHead;
    int found = 0;

    while (pTrav != NULL)
    {
        if (pTrav->aname == username && pTrav->pass == password)
        {
            cout << "Sign-in successful! Your Admin ID is: " << pTrav->Aid << endl;
            found = pTrav->Aid;
            break;
        }

        pTrav = pTrav->pNext;
    }

    return found;
}

void DisplayOrdersByCustomer(CListOrders& Orders)
{
    int customerId;
    cout << "\nEnter Customer ID: ";
    cin >> customerId;
    cout << endl;

    Order* pOrderTrav = Orders.pHead;
    int ct = 0;

    while (pOrderTrav != NULL)
    {
        if (pOrderTrav->Cid == customerId)
        {
            ct++;
        }

        pOrderTrav = pOrderTrav->pNext;
    }

    if (ct == 0)
    {
        cout << "No orders found for this customer" << endl;
    }
    else
    {
        cout << "Customer with ID " << customerId << " has placed " << ct << " orders" << endl;
    }


}


void main()
{
    int choice, found, id, q, N, tot = 0, okay;
    CListProduct Products;
    CListCustomer Customers;
    CListOrders Orders;
    CListAdmin Admins;
    string un, pass;

    readProductsintoList(Products);
    readCustomersintoList(Customers);
    readOrdersintoList(Orders);
    readAdminsintoList(Admins);

    do {
        cout << "1. Customer\n2. Admin\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter username: ";
            cin >> un;
            cout << endl << "Enter password: ";
            cin >> pass;

            found = SignInCustomer(Customers, un, pass); //if zero, no id found else found carries the id


            if (found == 0)
            {
                cout << "User not found" << endl;
                cout << "Registration" << endl;
                cout << "Enter new username: ";
                cin >> un;
                cout << endl << "Enter new password: ";
                cin >> pass;

                Customers.RegisterNewCustomer(Customers, un, pass, found);
                //Customers.DisplayAllCustomers();

            }

            Products.DisplayAvaliable();

            cout << "Purchase Section" << endl;
            cout << "How many types of products do you want to buy?" << endl;
            cin >> N;
            for (int i = 0; i < N; i++)
            {
                cout << "Enter product id: ";
                cin >> id;
                cout << endl;
                cout << "Enter the quantity wanted: ";
                cin >> q;
                Products.Buy(id, q, tot);

                Order* pnn = new Order;
                pnn->Cid = found;
                pnn->Pid = id;
                pnn->pNext = NULL;
                Orders.Attach(pnn);

            }
            cout << "Your receipt total is: " << tot << " EGP" << endl;

            okay = 0;
            cout << "Do you want to logout?\n 1. Yes\n 2. No" << endl;
            cin >> okay;
            if (okay == 1)
            {
                choice = 3;
                Products.writeToFile();
                Customers.writeToFile();
                Orders.writeToFile();
                Admins.writeToFile();
                break;
            }

            okay = 0;
            cout << "Return Section" << endl;
            cout << "Do you want to return product/s?\n 1. Yes\n 2. No" << endl;
            cin >> okay;
            if (okay == 1)
            {
                cout << "How many types of products do you want to return?" << endl;
                cin >> N;

                for (int i = 0; i < N; i++)
                {
                    cout << "Enter product id: ";
                    cin >> id;
                    cout << endl;
                    Products.Return(id, tot);
                    Orders.Remove(id);
                }

                cout << "Your receipt total is: " << tot << " EGP" << endl;

            }

            okay = 0;
            cout << "Do you want to logout?\n 1. Yes\n 2. No" << endl;
            cin >> okay;
            if (okay == 1)
            {
                choice = 3;
                Products.writeToFile();
                Customers.writeToFile();
                Orders.writeToFile();
                Admins.writeToFile();
                break;
            }

        }
        else if (choice == 2)
        {
            cout << "Enter username: ";
            cin >> un;
            cout << endl << "Enter password: ";
            cin >> pass;

            found = SignInAdmin(Admins, un, pass); //if zero, no id found else found carries the id

            if (found == 0)
            {
                cout << "Admin not found" << endl;
            }
            else
            {
                cout << "Products" << endl;
                Products.DisplayAllProducts();
                cout << endl;

                okay = 0;
                cout << "Do you want to adjust a product/s?\n 1. Yes\n 2. No" << endl;
                cin >> okay;
                if (okay == 1)
                {
                    cout << "How many types of products do you want to adjust?" << endl;
                    cin >> N;
                    for (int i = 0; i < N; i++)
                    {
                        cout << "Enter id of product you want to adjust\n";
                        cout << "Enter product id: ";
                        cin >> id;
                        cout << endl;
                        Products.Adjust(id);

                    }
                }

                okay = 0;
                cout << "Do you want to logout?\n 1. Yes\n 2. No" << endl;
                cin >> okay;
                if (okay == 1)
                {
                    choice = 3;
                    Products.writeToFile();
                    Customers.writeToFile();
                    Orders.writeToFile();
                    Admins.writeToFile();
                    break;
                }

                okay = 0;
                cout << "Do you want to delete a product/s?\n 1. Yes\n 2. No\n" << endl;
                cin >> okay;
                if (okay == 1)
                {
                    cout << "How many types of products do you want to delete?" << endl;
                    cin >> N;
                    for (int i = 0; i < N; i++)
                    {
                        cout << "Enter id of product you want to delete\n";
                        cout << "Enter product id: ";
                        cin >> id;
                        cout << endl;
                        Products.Remove(id);
                    }
                }

                okay = 0;
                cout << "Do you want to logout?\n 1. Yes\n 2. No" << endl;
                cin >> okay;
                if (okay == 1)
                {
                    choice = 3;
                    Products.writeToFile();
                    Customers.writeToFile();
                    Orders.writeToFile();
                    Admins.writeToFile();
                    break;
                }

                okay = 0;
                cout << "Do you want to add a product/s?\n 1. Yes\n 2. No\n" << endl;
                cin >> okay;
                if (okay == 1)
                {
                    cout << "How many types of products do you want to add?" << endl;
                    cin >> N;
                    for (int i = 0; i < N; i++)
                    {
                        Products.Add();
                    }
                }

                okay = 0;
                cout << "Do you want to logout?\n 1. Yes\n 2. No" << endl;
                cin >> okay;
                if (okay == 1)
                {
                    choice = 3;
                    Products.writeToFile();
                    Customers.writeToFile();
                    Orders.writeToFile();
                    Admins.writeToFile();
                    break;
                }

                okay = 0;
                cout << "Do you want to display products of a quantity less than a certain value?\n 1. Yes\n 2. No\n" << endl;
                cin >> okay;
                if (okay == 1)
                {
                    Products.DisplayLessStock();
                }

                okay = 0;
                cout << "Do you want to logout?\n 1. Yes\n 2. No" << endl;
                cin >> okay;
                if (okay == 1)
                {
                    choice = 3;
                    Products.writeToFile();
                    Customers.writeToFile();
                    Orders.writeToFile();
                    Admins.writeToFile();
                    break;
                }

                okay = 0;
                cout << "Do you want to display the number of orders for a certain customer?\n 1. Yes\n 2. No\n" << endl;
                cin >> okay;
                if (okay == 1)
                {
                    cout << "How many customers do you want to look for? " << endl;
                    cin >> N;
                    for (int i = 0; i < N; i++)
                    {
                        DisplayOrdersByCustomer(Orders);
                    }
                }

                okay = 0;
                cout << "Do you want to logout?\n 1. Yes\n 2. No" << endl;
                cin >> okay;
                if (okay == 1)
                {
                    choice = 3;
                    Products.writeToFile();
                    Customers.writeToFile();
                    Orders.writeToFile();
                    Admins.writeToFile();
                    break;
                }

            }

        }

    } while (choice != 3);
}
