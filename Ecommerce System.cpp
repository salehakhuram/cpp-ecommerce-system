#include <iostream>     // Standard input/output operations
#include <fstream>      // File handling for reading/writing user/product data
#include <string>       // String operations
#include <cstdlib>      // Utility functions (e.g., system("CLS"))
#include <conio.h>      // For _getch() and password masking
#include<iomanip>        // for setprecision in price
using namespace std;

class Masking {
public:
	// FUNCTION TO GET HIDDEN PASSWORD
	static string getHiddenPassword()
	{
		string pass;
		char ch;
		while (true)
		{
			ch = _getch();
			if (ch == 13)
			{ // Enter
				cout << endl;
				break;
			}
			else if (ch == 8)
			{ // Backspace
				if (!pass.empty())
				{
					pass.pop_back();
					cout << "\b \b";
				}
			}
			else
			{
				pass += ch;
				cout << '*';
			}
		}
		return pass;
	}
};
//----------------------------------Validation--------------------------------------------
class Validation {
public:
	static bool isEmptyOrWhitespace(const string& str)
	{
		if (str.empty()) 
		{
			cout << "Input cannot be empty or whitespace!" << endl;
			return true;
		}
		for (char ch : str)
		{
			if (ch != ' ' && ch != '\t' && ch != '\n')
			{
				return false;
			}
		}
		cout << "Input cannot be empty or whitespace!" << endl;
		return true;
	}

	//  FUNCTION FOR ORDER ID
	static int orderId()
	{
		int orderID = 101;

		ifstream idFile("order_id.txt");
		if (idFile) {
			idFile >> orderID;
		}
		idFile.close();


		orderID++;
		ofstream outFile("order_id.txt", ios :: app);
		outFile << orderID;
		outFile.close();
		return orderID;

	}
	//FUNCTION TO CHECK PRID
	static bool checkproID(string id)
	{
		string proid, name, category, subcategory;
		int stock;
		float price;
		ifstream read("products.txt");
		{
			if (read.is_open())
			{
				while (read >> proid)
				{
					if (proid == id)
					{
						return false;
					}
				}
			}

		}
		return true;
	}
	//FUNCTION FOR THE INPUT VALIDATION OF DIGITS 
	static bool containsDigit(string input)
	{
		for (int i = 0; i < input.length(); i++)
		{
			if (isdigit(input[i]))
			{
				return true;
			}
		}
		return false;
	}


	//FUNCTION FOR THE VALIDATION OF CORRECT USERNAME
	static bool validUsername(string username)
	{
		if (isEmptyOrWhitespace(username)) 
		{
			cout << "\nInvalid Username! Username cannot be empty or contain only whitespace.\n" << endl;
			return false;
		}

		if (username.length() >= 15) 
		{
			cout << "\nInvalid Username! Username should have at most 15 characters.\n" << endl;
			return false;
		}
		return true; 
	}
	// FUNCTION TO CHECK THERE IS NO SAME USERNAME
	static bool checkUser(string userN, string role)
	{
		string usern, passw;
		if (role == "1" || role == "User")
		{
			ifstream read("users.txt");
			if (read.is_open())
			{
				while (read >> usern >> passw)
				{
					if (usern == userN)
					{
						cout << "Username already exists! Enter a new one!" << endl;
						system("pause");
						return false;
					}
				}
			}
		}
		if (role == "2" || role == "Admin")
		{
			ifstream read("admin.txt");
			if (read.is_open())
			{
				while (read >> usern >> passw)
				{
					if (usern == userN)
					{
						cout << "Username already exists! Enter a new one!" << endl;
						system("pause");
						return false;
					}
				}
			}
		}
		if (role == "3" || role == "Employee")
		{
			ifstream read("employee.txt");
			if (read.is_open())
			{
				while (read >> usern >> passw)
				{
					if (usern == userN)
					{
						cout << "Username already exists! Enter a new one!" << endl;
						system("pause");
						return false;
					}
				}
			}
		}
		return true;
	}
	// FUNCTION FOR THE VALIDATION OF CORRECT PASSWORD 
	static bool validPass(string pass)
	{
		if (isEmptyOrWhitespace(pass)) 
		{
			cout << "\nInvalid Password! Password cannot be empty or contain only whitespace.\n" << endl;
			return false;
		}

		if (pass.length() < 8)
		 {
			cout << "\nInvalid Password! Password should be at least 8 characters long.\n" << endl;
			return false;
		}

		if (!containsDigit(pass)) 
		{
			cout << "\nInvalid Password! Password should contain at least one digit.\n" << endl;
			return false;
		}
		return true; 
	}

	// FUNCTION FOR THE VALIDATION OF INTEGER
	static bool validInteger(string temp)
	{
		for (char ch : temp) 
		{
			if (!isdigit(ch))
				return false;
		}
		return true;
	}

};
//----------------------------------PERSON CLASS--------------------------------------------
class Person 
{
public:
	//FUNCTION FOR FORGOTTEN PASSWORD
	static void forgotPass(string role)
	{
		string u, p, newpass, uname, input;
		bool found = false;

		if (role == "User" || role == "2") 
		{
			do 
			{
				cout << "Enter your username (No spaces allowed): " << endl;
				getline(cin, uname);
			} while (!Validation::validUsername(uname));


			ifstream read("users.txt");
			ofstream write("temp.txt");

			if (read.is_open() && write.is_open()) 
			{
				while (read >> u >> p) 
				{
					if (u == uname) 
					{
						found = true;
						do {
							cout << "Enter new Password: " << endl;
							newpass = Masking::getHiddenPassword();

						} while (!Validation::validPass(newpass));


						bool confirmed = false;
                      while (!confirmed) 
					  {
                     cout << "Are you sure you want to set this as your password? (yes/no): ";
                   getline(cin, input);
                   if (Validation::isEmptyOrWhitespace(input)) 
				   {
                  cout << "Invalid input.\n";
                     continue;
                      }

						if (input == "yes") 
						{
							cout << "Password reset successfully!" << endl;
							write << u << " " << newpass << endl;
							confirmed = true;
						}
						else
						{
							cout << "Password not changed. Keeping old password." << endl;
							write << u << " " << p << endl;
						}
					}
					}else
					{

						write << u << " " << p << endl;

					}
				}
				}
        
				read.close();
				write.close();

				if (remove("users.txt") != 0)
				{
					perror("Error deleting users.txt");
				}
				else
				{
					if (rename("temp.txt", "users.txt") != 0)
					{
						perror("Error renaming temp.txt to users.txt");
					}
				}

				if (!found)
				{
					cout << "Username not Found!" << endl;
				}
			else
			{
				cout << "File not opening.." << endl;
			}
			system("pause");
		}
		else if (role == "Admin" || role == "1")
		{
			do {
				cout << "Enter your username (No spaces allowed): " << endl;
				getline(cin, uname);

			} while (!Validation::validUsername(uname));
			ifstream read("admin.txt");
			ofstream write("tempc.txt");

			if (read.is_open() && write.is_open())
			{
				while (read >> u >> p)
				{
					if (u == uname)
					{
						found = true;
						do {
							cout << "Enter new Password: " << endl;
							newpass = Masking::getHiddenPassword();
						} while (!Validation::validPass(newpass));
                          bool confirmed = false;
						  while (!confirmed) {
                     cout << "Are you sure you want to set this as your password? (yes/no): ";
                   getline(cin, input);
                   if (Validation::isEmptyOrWhitespace(input)) 
				   {
                  cout << "Invalid input.\n";
                     continue;
                      }}

						if (input == "yes")
						{
							cout << "Password reset successfully!" << endl;
							write << u << " " << newpass << endl;
							confirmed = true;
						}
						else
						{
							cout << "Password not changed. Keeping old password." << endl;
							write << u << " " << p << endl;
						}
					}
					else
					{

						write << u << " " << p << endl;
					}
				}
			}

				read.close();
				write.close();

				if (remove("admin.txt") != 0) 
				{
					perror("Error deleting admin.txt");
				}
				else 
				{
					if (rename("tempc.txt", "admin.txt") != 0) 
					{
						perror("Error renaming tempc.txt to admin.txt");
					}
				}

				if (!found) 
				{
					cout << "Username not Found!" << endl;
				}
	
			else 
			{
				cout << "File not opening.." << endl;
			}
			system("pause");
		}
	
		else if (role == "Employee" || role == "3")
		{
			do {
				cout << "Enter your username (No spaces allowed): " << endl;
				getline(cin, uname);
			} while (!Validation::validUsername(uname));;

			ifstream read("employee.txt");
			ofstream write("tempe.txt");

			if (read.is_open() && write.is_open())
			{
				while (read >> u >> p)
				{
					if (u == uname)
					{
						found = true;
						do {
							cout << "Enter new Password: " << endl;
							newpass = Masking::getHiddenPassword();
						} while (!Validation::validPass(newpass));
                         bool confirmed = false;
						  while (!confirmed) {
                     cout << "Are you sure you want to set this as your password? (yes/no): ";
                   getline(cin, input);
                   if (Validation::isEmptyOrWhitespace(input)) {
                  cout << "Invalid input.\n";
                     continue;
                      }

						if (input == "yes")
						{
							cout << "Password reset successfully!" << endl;
							write << u << " " << newpass << endl;
							confirmed = true;
						}
						else
						{
							cout << "Password not changed. Keeping old password." << endl;
							write << u << " " << p << endl;

						}
					}
				}
					else
					{

						write << u << " " << p << endl;

					}
			}

				system("pause");
				read.close();
				write.close();

				if (remove("employee.txt") != 0)
				{
					perror("Error deleting employee.txt");
				}
				else {
					if (rename("tempe.txt", "employee.txt") != 0)
					{
						perror("Error renaming tempe.txt to employee.txt");
					}
				}

				if (!found)
				{
					cout << "Username not Found!" << endl;
				}
			}
			else
			{
				cout << "File not opening.." << endl;
			}
			system("pause");
		}
	}
	static void signup(string role)
	{
		string username, password;
		system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|               SIGN UP PAGE               |\n";
		cout << "-------------------------------------------\n";
		do{
			cout << "Enter your Username (max 15 chars & no spaces allowed): ";
			getline(cin, username);
		} while (!Validation::isEmptyOrWhitespace(username) && !Validation::checkUser(username , role ));

		while (true) 
		{
			cout << "\nEnter your Password(min 8 chars and should contain at least one digit && no spaces allowed): ";
			password = Masking::getHiddenPassword();
			if (Validation::validPass(password))
			{
				break;
			}
		}
		if (Validation::validUsername(username) && Validation::checkUser(username, role) && (Validation::validPass(password)))
		{
			if (role == "User" || role == "2")
			{
				ofstream fuser("users.txt", ios::app);
				if (fuser.is_open()) 
				{
					fuser << username << " " << password << endl;
					fuser.close();
					cout << "The sign up has been successful!" << endl;
				}
				else {
					cout << "Error: Unable to open users.txt for writing.\n";

				}
			}
			else if (role == "Employee" || role == "3")
			{
				ofstream femp("employee.txt", ios::app);
				if (femp.is_open()) {
					femp << username << " " << password << endl;
					femp.close();
					cout << "The sign up has been successful!\n";
				}
				else {
					cout << "Error: Unable to open users.txt for writing.\n";
				}
			}

			else if (role == "Admin" || role == "1")
			{
				ofstream fadmin("admin.txt", ios::app);
				if (fadmin.is_open())
				{
					fadmin << username << " " << password << endl;
					fadmin.close();
					cout << "The sign up has been successful!\n";
				}
				else {
					cout << "Error: Unable to open users.txt for writing.\n";
				}

			}
		}
		else
		{
			cout << " \nSignup Failed. Check input. \n";
			system("cls");
		}
		system("pause");

	}

	// LOGIN FUNCTION
	static bool login(string role)
	{
		string username, password;

		bool outfound = false;
		system("cls");
		cout << "\n-----------------------------------------\n";
		cout << "|               LOGIN PAGE               |\n";
		cout << "-----------------------------------------\n";
		while (true)
		{
			cout << "\nEnter your Username (max 15 chars & no spaces allowed): ";
			getline(cin,username);
			if (Validation::validUsername(username))
			{
				break;
			}
		}
		while (true)
		{
			cout << "\nEnter your Password(min 8 chars and should contain at least one digit && no spaces allowed): ";
			password = Masking::getHiddenPassword();
			if (Validation::validPass(password))
			{
				break;
			}
		}
		if (Validation::validUsername(username) && (Validation::validPass(password)))
		{
			if (role == "User" || role == "2")
			{

				ifstream in("users.txt");
				if (in.is_open())
				{
					string name, pass;
					bool found = false;

					while (in >> name >> pass)
					{
						if (name == username && pass == password) 
						{
							found = true;
							break;
						}
					}
					in.close();
					if (found)
					{
						cout << "\nLogin has been successful!!\n";
						outfound = true;
						system("pause");
					}
					else
					{
						cout << "\nLogin has been unsuccessful!!Try Again!\n";
						outfound = false;
						system("pause");
						system("cls");
					}
				}
			}
			else if (role == "Employee" || role == "3")
			{

				ifstream emp("employee.txt");
				if (emp.is_open()) 
				{
					string name, pass;
					bool found = false;

					while (emp >> name >> pass) 
					{
						if (username == name && password == pass) 
						{
							found = true;
							break;
						}
					}
					emp.close();
					if (found)
					{
						cout << "\nLogin has been successful!!\n";
						outfound = true;
						system("pause");
					}
					else
					{
						cout << "\nLogin has been unsuccessful!!Try Again!\n";
						outfound = false;
						system("pause");
						system("cls");
					}
				}
			}
			else if (role == "Admin" || role == "1")
			{
				ifstream ad("admin.txt");
				if (ad.is_open()) 
				{
					string name, pass;
					bool found = false;

					while (ad >> name >> pass) 
					{
						if (name == username && pass == password) 
						{
							found = true;
							break;
						}
					}
					ad.close();
					if (found)
					{
						cout << "\nLogin has been successful!!\n";
						outfound = true;
						system("pause");
					}
					else
					{
						cout << "\nLogin has been unsuccessful!!Try Again!\n";
						outfound = false;
						system("pause");
						system("cls");
					}
				}
			}
		}
		else
		{
			cout << "\n Wrong username or password!!\n";
			outfound = false;
			system("pause");
		}
		if (outfound)
			system("cls");

		return outfound;
	}

};

//----------------------------------PRODUCT CLASS--------------------------------------------
class Product {
private:
	string proID;
	string name;
	float price;
	int stock;
	string category;
	string subcategory;
public:
	Product() {
		proID = "";
		name = "";
		price = 0.0;
		stock = 0;
		category = "";
		subcategory = "";
	}

	//SETTERS AND GETTERS
	void setproID(string id)
	{
		proID = id;
	}
	string getproID()
	{
		return proID;
	}
	void setname(string n)
	{
		name = n;
	}
	string getname()
	{
		return name;
	}
	void setstock(int s)
	{
		stock = s;
	}
	int getstock()
	{
		return stock;
	}
	void setprice(float p)
	{
		price = p;
	}
	float getprice()
	{
		return price;
	}
	void setcategory(string cat)
	{
		category = cat;
	}
	string getcategory()
	{
		return category;
	}
	void setsubcat(string subc)
	{
		subcategory = subc;
	}
	string getsubcat()
	{
		return subcategory;
	}
	void displayProducts()
	{
		system("cls");
		cout << "\n---------------------------------------------\n";
		cout << "|           PRODUCT LIST                   |\n";
		cout << "----------------------------------------------\n";
		string proID, name, category, subcategory;
		float price;
		int stock;
		ifstream fin("products.txt");
		if (fin.is_open())
		{
			cout << "File opened successfully." << endl;
			while (fin >> proID >> name >> category >> subcategory >> price >> stock)
			{

				cout << "Product Id :" << proID << endl;
				cout << "Product Name :" << name << endl;
				cout << "Category:" << category << endl;
				cout << "Subcategory: " << subcategory << endl;
				cout << "Price : Rs." << price << endl;
				cout << "Stock:" << stock << endl;
				cout << "---------------------------------------------" << endl;
			}
		}
		else {
			cout << "Error: Could not open products.txt file." << endl;
		}
		fin.close();
		system("pause");
	}


	// FUNCTION TO DISPLAY CATEGORIES
	void displayCategories()
	{
		system("cls");

		cout << "\n-------------------------------------------\n";
		cout << "|           DISPLAY CATEGORIES             |\n";
		cout << "--------------------------------------------\n";

		string cat, sub1, sub2;
		ifstream display;
		display.open("cat.txt");
		if (!(display.is_open()))
		{
			cout << "Error! File can't be opened!\n";
		}
		while (display >> cat >> sub1 >> sub2)
		{
			cout << "Category:" << cat << endl;
			cout << "Subcategory:" << sub1 << endl;
			cout << "Subcategory:" << sub2 << endl;
		}
		display.close();

		system("pause");
	}
	//FUNCTION TO REVIEW PRODUCTS
	void reviewProducts() 
	{	
		system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|           REVIEW A PRODUCT              |\n";
		cout << "-------------------------------------------\n";
		string ID;
		do {
			cout << " Enter the Product ID of product you want to review" << endl;
			getline(cin, ID);
		} while (Validation :: isEmptyOrWhitespace(ID));
		string proId, review, name;
		ifstream pro("products.txt");
		ofstream rev("review.txt", ios :: app);
		{
			if (pro.is_open()) {
				while (pro >> proId >> name)
				{
					if (proId == ID)
					{
						do {
							cout << " Write Your Review :" << endl;
							getline(cin, review);
							if (Validation::isEmptyOrWhitespace(review)) {
								cout << "Input is empty or just whitespace!\n";
							}
						} while (Validation::isEmptyOrWhitespace(review));
						if (rev.is_open())
						{
							rev << proId << " " << name << " " << review << endl;
						}

					}
				}
			}
		}
		system("pause");
	}
	void viewReviews()
	{  
	    system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|           VIEW REVIEWS              |\n";
		cout << "-------------------------------------------\n";
		string id, name, review;
		ifstream read("review.txt");
		if (read.is_open())
		{
			while (read >> id >> name)
			{
				read.ignore(); // Ignore the whitespace before getline
				getline(read, review);
				cout << "-----Reviews------\n";
				cout << "Product ID :" << id << endl;
				cout << "Name :" << name << endl;
				cout << "Reviews :" << review << endl;
				cout << "-----------------\n" << endl;

			}
		}
		else {
			cout << "Unable to open review file.\n";
			return;
		}
		system("pause");
	}

};
//----------------------------------CART CLASS--------------------------------------------
class CartOrder {
private:

	string orderStatus;
	int orderID;
	string payStatus;
	int quantity;

public:
	CartOrder()
	{
		orderStatus = "Pending";
		orderID = 0;
		payStatus = "Unpaid";
		int quantity = 0;
	}

	void setQuantity(int qty) {
		quantity = qty;
	}
	int getQuantity() {
		return quantity;
	}


	void addItem()
	{	
		system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|              ADD TO CART                |\n";
		cout << "-------------------------------------------\n";
		Product p;
		p.displayProducts();
		string proID;
		do {
			cout << "Write the product ID of the item you want to add in Cart :" << endl;
			getline(cin, proID);
		} while (Validation::isEmptyOrWhitespace(proID));
		cout << "You entered: [" << proID << "]\n";
		bool found = false;
		int quantity = 0;
		// Variables for product info from products.txt
		string prodID, name, category, subcategory;
		float price = 0.0;
		int stock = 0;

		ifstream pro("products.txt");
		if (pro.is_open())
		{
			// Find product in products.txt
			while (pro >> prodID >> name >> category >> subcategory >> price >> stock) {
				if (prodID == proID) 
				{
					found = true;
					break;
				}
			}
			pro.close();

			if (!found) 
			{
				cout << "Product not found!" << endl;
				return;
			}
				cout << "Quantity of Product " << proID << ":" << endl;
				cin >> quantity;
			if (quantity <= 0) 
			{
				cout << "Invalid quantity.\n";
				return;
			}
			setQuantity(quantity);

			// Variables for reading cart.txt
			string cartID, cartName;
			float cartPrice;
			int cartQty;

			bool productExists = false;
			ifstream inFile("cart.txt");
			ofstream tempFile("tempc.txt");

			if (!inFile.is_open()) 
			{
				// If cart.txt does not exist, create it and add the product directly
				ofstream write("cart.txt", ios::app);
				if (write.is_open())
				 {
					write << prodID << " " << name << " " << price << " " << quantity << endl;
					cout << "Product added to cart successfully.\n";
					write.close();
				}
				else 
				{
					cout << "Unable to open cart.txt for writing.\n";
				}
				return;
			}

			// Read current cart, update quantity if product exists
			while (inFile >> cartID >> cartName >> cartPrice >> cartQty) 
			{
				if (cartID == proID) 
				{
					cartQty += quantity;
					productExists = true;
				}
				tempFile << cartID << " " << cartName << " " << cartPrice << " " << cartQty << endl;
			}

			inFile.close();
			tempFile.close();

			if (productExists) 
			{
				if (remove("cart.txt") != 0) 
				{
					cout << "Error deleting old cart file.\n";
					return;
				}
				if (rename("tempc.txt", "cart.txt") != 0) 
				{
					cout << "Error renaming temporary file.\n";
					return;
				}
				cout << "Quantity updated for product " << proID << endl;
			}
			else {

				remove("tempc.txt");
				ofstream write("cart.txt", ios::app);
				if (write.is_open()) {
					write << prodID << " " << name << " " << price << " " << quantity << endl;
					cout << "Product added to cart successfully.\n";
					write.close();
				}
				else 
				{
					cout << "Unable to open cart.txt for writing.\n";
				}
			}
		}
		else 
		{
			cout << "Unable to open products.txt\n";
		}
		system("pause");
	}


	void viewCart()
	{
		system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|               VIEW CART                 |\n";
		cout << "-------------------------------------------\n";
		string id, name;
		float price;
		int quantity;
		ifstream read("cart.txt");
		if (read.is_open()) {
			cout << "\nYour Cart:\n";
			cout << "--------------------------\n";
			bool isEmpty = true;
			while (read >> id >> name >> price >> quantity) 
			{   isEmpty = false;
				cout << "Product ID: " << id << endl;
				cout << "Name: " << name << endl;
				cout << "Quantity: " << quantity << endl;
				cout << "Price: Rs. " << price << endl;
				cout << "--------------------------\n";
				
             return;
			}
			if (isEmpty) {
				cout << "Your cart is empty.\n";
			}
			read.close();
		}
		else {
			cerr << "Error: Unable to open cart.txt\n";
		}
		system("pause");
	}
	void removeItem()
	{  
		system("cls");
		 cout << "\n-------------------------------------------\n";
		cout << "|               REMOVE ITEM                |\n";
		cout << "-------------------------------------------\n";
		string itemproID;
		do {
			cout << "Enter Product ID to remove the item: ";
			cin >> itemproID;
		} while (Validation::isEmptyOrWhitespace(itemproID));

		ifstream read("cart.txt");
		ofstream write("tempt.txt");

		bool found = false;
		string name, proID;
		double price;
		int quantity;

		while (read >> proID >> name >> price >> quantity)
		{
			if (itemproID == proID)
			{
				found = true;
				continue;

			}
			write << proID << " " << name << " " << price << " " << quantity << endl;
		}

		read.close();
		write.close();
		if (remove("cart.txt") != 0) {
			cout << "Error deleting old cart file.\n";
			return;
		}
		if (rename("tempt.txt", "cart.txt") != 0)
		{
			perror("Error renaming files!");
		}
		if (found)
			cout << "Item was removed successfully.\n";
		else
			cout << "Item was not removed.\n";
		system("pause");

	}
	void updateQuantity()
	{
		system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|           UPDATE QUANTITY             |\n";
		cout << "-------------------------------------------\n";
		string qproID;
		int quan;
		
		do {
			cout << "Enter Product ID to update the quantity : ";
			cin >> qproID;
		} while (Validation::isEmptyOrWhitespace(qproID));
	
		cout << "Enter the new quantity of the product : ";
		cin >> quan;
		if (quan <= 0) {
			cout << "Invalid quantity.\n";
			return;
		}
		ifstream read("cart.txt");
		ofstream write("templ.txt");

		bool found = false;
		string name, proID;
		double price;
		int quantity;
		setQuantity(quan);
		while (read >> proID >> name >> price >> quantity)
		{
			if (qproID == proID)
			{
				found = true;
				write << proID << " " << name << " " << price << " " << getQuantity() << endl;
			}
			else
			{
				write << proID << " " << name << " " << price << " " << quantity << endl;
			}
		}

		read.close();
		write.close();
		if (remove("cart.txt") != 0) 
		{
			cout << "Error deleting old orders file.\n";
			return;
		}
		if (rename("templ.txt", "cart.txt") != 0)
		{
			perror("Error renaming files!");
		}
		if (found)
			cout << "Quantity was updated successfully.\n";
		else
			cout << "Quantity was not updated.\n";
		system("pause");
	}

	void setStatus(string st)
	{
		orderStatus = st;
	}
	string getStatus()
	{
		return orderStatus;
	}
	void updateOrderStatus() 
	{	
	system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|         UPDATE ORDER STATUS              |\n";
		cout << "-------------------------------------------\n";
		ifstream inFile("orders.txt");
		ofstream tempFile("tempo.txt");
		bool found = false;

		if (!inFile || !tempFile) {
			cout << "Error opening files.\n";
			return;
		}
		int orderID;
		cout << " Enter the order ID of the order you want to update order Status :" << endl;
		cin >> orderID;
		if (orderID <= 0) {
			cout << "Invalid orderID.\n";
			return;
		}
		string productID, name, status, payStatus;
		int id, quantity;
		float price;

		while (inFile >> id >> productID >> name >> price >> quantity >> status >> payStatus) {
			if (orderID == id) {
				status = orderStatus;
				found = true;
				cout << "Order status updated.\n";
			}
			tempFile << id << " " << productID << " " << name << " "
				<< price << " " << quantity << " " << status << " " << payStatus << endl;
		}

		inFile.close();
		tempFile.close();

		if (remove("orders.txt") != 0) {
			cout << "Error deleting old orders file.\n";
			return;
		}
		if (rename("tempo.txt", "orders.txt") != 0) {
			cout << "Error renaming temporary file.\n";
			return;
		}


		if (!found) {
			cout << "Order ID not found.\n";
		}
		system("pause");
	}

	void selectItems() 
	{	
		system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|        SELECT ITEMS FROM CART             |\n";
		cout << "-------------------------------------------\n";
		viewCart();
		int num;
		cout << "How many products from cart you want to order: ";
		cin >> num;

		if (num <= 0 || num > 100)
		 {
			cout << "Invalid number of items.\n";
			return;
		}

		string selproID[100];
		for (int i = 0; i < num; i++) 
		{
			cout << "Enter Product ID to order from your cart (" << i + 1 << "): ";
			cin >> selproID[i];
		}

		ifstream read("cart.txt");
		if (!read.is_open()) 
		{
			cout << "Unable to open cart.txt\n";
			return;
		}

		string id, name;
		float price;
		int quantity;
		bool found = false;
		string payStatus = "Unpaid";

		ofstream write("orders.txt", ios::app);
		if (!write.is_open()) {
			cout << "Unable to open orders.txt\n";
			return;
		}
		orderID = Validation::orderId();
		cout << "Order ID: " << orderID << endl;
		while (read >> id >> name >> price >> quantity) 
		{
			for (int i = 0; i < num; i++) 
			{
				if (id == selproID[i]) 
				{
					write << orderID << " " << id << " " << name << " " << price << " " << quantity << " " << getStatus() << " " << payStatus << endl;
					cout << "Item " << id << " added to your order.\n";
					found = true;
				}
			}
		}
		orderID++;

		if (!found) 
		{
			cout << "None of the entered Product IDs were found in the cart.\n";
		}

		read.close();
		write.close();
		system("pause");
	}

	void viewOrder()
	{ 
	    system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|               VIEWS ORDERS                |\n";
		cout << "-------------------------------------------\n";
		string proID, name, status, payStatus;
		int quantity, id;
		float price;
		ifstream read("orders.txt");
		if (read.is_open())
		{
			cout << "----- Orders -----\n";
			while (read >> id >> proID >> name >> price >> quantity >> status >> payStatus)
			{
				cout << "Order ID: " << id << endl;
				cout << "Product ID: " << proID << endl;
				cout << "Product Name: " << name << endl;
				cout << "Price: " << price << endl;
				cout << "Quantity: " << quantity << endl;
				cout << "Order Status: " << status << endl;
				cout << "Payment Status: " << payStatus << endl;
				cout << "--------------------------\n";
			}
		}
		system("pause");
	}
	void cancelord()
	{   
	 system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|           CANCEL ORDER             |\n";
		cout << "-------------------------------------------\n";
		int cancelID;
		cout << "Enter Order ID to cancel: ";
		cin >> cancelID;
		if (cancelID <= 0) {
			cout << "Invalid cancelID\n";
			return;
		}

		ifstream inFile("orders.txt");
		ofstream tempFile("tempn.txt");

		if (!inFile.is_open() || !tempFile.is_open()) {
			cout << "Error: Could not open file.\n";
			return;
		}

		string productID, productName, status, payStatus;
		float price;
		int quantity, orderID;
		bool found = false;

		while (inFile >> orderID >> productID >> productName >> price >> quantity >> status >> payStatus) {
			if (orderID == cancelID && payStatus == "Unpaid") {
				tempFile << orderID << " " << productID << " " << productName << " "
					<< price << " " << quantity << " Cancelled" << " " << "Unpaid" << endl;
				found = true;
			}
			else {
				tempFile << orderID << " " << productID << " " << productName << " "
					<< price << " " << quantity << " " << status << " " << payStatus << endl;
			}
		}
		inFile.close();
		tempFile.close();

		if (remove("orders.txt") != 0) {
			cout << "Error deleting old orders file.\n";
			return;
		}

		if (rename("tempn.txt", "orders.txt") != 0) {
			cout << "Error renaming temporary file.\n";
			return;
		}


		if (found) {
			cout << "Order ID " << cancelID << " has been cancelled.\n";
		}
		else {
			cout << "Order ID not found.\n";
		}
		system("pause");
	}

	void removeCart() {
		string id, name, status, payStat;
		float price;
		int quantity, ordId;

		ifstream cartFile("cart.txt");
		ofstream tempFile("tempu.txt");


		string prodId, prodName;
		float prodPrice;
		int prodQty;

		while (cartFile >> prodId >> prodName >> prodPrice >> prodQty) {
			bool isPaid = false;

			ifstream orderFile("orders.txt");
			if (orderFile.is_open()) {
				while (orderFile >> ordId >> id >> name >> price >> quantity >> status >> payStat) {
					if (id == prodId && payStat == "Paid") {
						isPaid = true;
						break;
					}
				}
				orderFile.close();
			}
			if (!isPaid) {
				tempFile << prodId << " " << prodName << " " << prodPrice << " " << prodQty << endl;
			}
		}

		cartFile.close();
		tempFile.close();

		if (remove("cart.txt") != 0) {
			perror("Error deleting old cart file");
			return; 
		}

		if (rename("tempu.txt", "cart.txt") != 0) {
			perror("Error renaming temporary file to cart.txt");
			return; 
		}

		cout << "Paid items removed from cart.\n";
		system("pause");
	}

	void makePayment() {
		system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|              MAKE PAYMENT               |\n";
		cout << "-------------------------------------------\n";
		ifstream inFile("orders.txt");
		ofstream tempFile("tempp.txt");

		if (!inFile || !tempFile) {
			cout << "Error opening files.\n";
			return;
		}

		int orderID;
		cout << "Enter the order ID you want to make payment for: ";
		cin >> orderID;
		if (orderID <= 0) {
			cout << "Invalid cancelID\n";
			return;
		}

		string productID, name, status, payStatus;
		float price;
		int qty,id;
		float totalAmount = 0;
		bool foundUnpaid = false;

		while (inFile >> id >> productID >> name >> price >> qty >> status >> payStatus) {
			if (id == orderID && payStatus == "Unpaid") {
				totalAmount += price * qty;
				foundUnpaid = true;
			}
		}


		inFile.clear();

		if (!foundUnpaid) {
			cout << "Order ID not found or all items are already paid.\n";
			inFile.close();
			tempFile.close();
			remove("tempp.txt");
			return;
		}
		else {
			cout << fixed << setprecision(2);
			cout << "Total Amount: Rs." << totalAmount << endl;
		}

		inFile.clear();
		inFile.seekg(0);
		while (inFile >> id >> productID >> name >> price >> qty >> status >> payStatus) {
			if (id == orderID && payStatus == "Unpaid") {
				tempFile << id << " " << productID << " " << name << " "
					<< price << " " << qty << " " << status << " Paid" << endl;
			}
			else {
				tempFile << id << " " << productID << " " << name << " "
					<< price << " " << qty << " " << status << " " << payStatus << endl;
			}
		}

		inFile.close();
		tempFile.close();

		if (remove("orders.txt") != 0) {
			cout << "Error deleting old orders file.\n";
			return;
		}
		if (rename("tempp.txt", "orders.txt") != 0) {
			cout << "Error renaming temporary file.\n";
			return;
		}
		cout << "Payment successful. All items under Order ID " << orderID << " marked as Paid.\n";
		removeCart();
		system("pause");
	}



};

//--------------------------------ADMIN CLASS-------------------------------------

class admin : public Person
{

public:

	// FUNCTION TO DELETE EMPLOYEE
	void delete_employee()
	{  system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|          DELETE EMPLOYEE               |\n";
		cout << "-------------------------------------------\n";
		string target;
		
		do {
			cout << "Enter employee name to delete: ";
			getline(cin, target);
		} while (Validation::isEmptyOrWhitespace(target));

		ifstream read("employee.txt");
		if (!read)
		{
			cout << "Error: Cannot open employee.txt for reading.\n";
			return;
		}

		ofstream write("temp.txt");
		if (!write)
		{
			cout << "Error: Cannot open temp.txt for writing.\n";
			read.close();
			return;
		}

		string name, pass;
		bool found = false;

		while (read >> name >> pass)
		{

			if (name == target)
			{
				found = true;
				continue;
			}
			write << name << " " << pass << endl;
		}

		read.close();
		write.close();
		if (remove("employee.txt") != 0)
		{
			cout << "Error: Unable to delete employee.txt.\n";
			return;
		}

		if (rename("temp.txt", "employee.txt") != 0)
		{
			cout << "Error: Unable to rename temp.txt to employee.txt.\n";
			return;
		}

		if (found)
			cout << "Employee deleted successfully.\n";
		else
			cout << "Employee not found.\n";
		system("pause");
	}

	// FUNCTION TO DELETE USERS
	void delete_users()
	{ system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|           DELETE USERS                  |\n";
		cout << "-------------------------------------------\n";
		string target;
		do {
			cout << "Enter username to delete: ";
			getline(cin, target);
		} while (Validation::isEmptyOrWhitespace(target));

		ifstream read("users.txt");
		if (!read)
		{
			cout << "Error: Cannot open users.txt for reading.\n";
			return;
		}

		ofstream write("temp.txt");
		if (!write) {
			cout << "Error: Cannot open temp.txt for writing.\n";
			read.close();
			return;
		}

		string username, password;
		bool found = false;

		while (read >> username >> password) {
			if (username == target) {
				found = true;
				continue; // Skip the user to be deleted
			}
			write << username << " " << password << endl;
		}

		read.close();
		write.close();

		if (remove("users.txt") != 0)
		{
			cout << "Error: Unable to delete users.txt.\n";
			return;
		}

		if (rename("temp.txt", "users.txt") != 0)
		{
			cout << "Error: Unable to rename temp.txt to users.txt.\n";
			return;
		}

		if (found)
			cout << "User deleted successfully.\n";
		else
			cout << "User not found.\n";
			system("pause");
	}

	// FUNCTION TO VIEW EMPLOYEE
	void view_employee()
	{
		system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|           VIEW EMPLOYEES                |\n";
		cout << "-------------------------------------------\n";
		ifstream read("employee.txt");
		string empname, password;

		if (!read.is_open())
		{
			cout << "Error! Cannot open employee.txt file.\n";
			system("pause");
			return;
		}

		cout << "Hired Employees:\n";
		while (read >> empname >> password)
		{
			if (!empname.empty() && !password.empty())
			{
				cout << "Employee's name: " << empname << endl;
			}
			else
			{
				cout << "Warning: Skipped invalid or incomplete entry.\n";
			}
		}
		read.close();
		system("pause");
		return;
	}

	// FUNCTION TO SEARCH PRODUCT
	void search_product()
	{
		system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|             SEARCH PRODUCT                |\n";
		cout << "-------------------------------------------\n";
		string target;
		do{
		cout << "Enter product ID to search: ";
		getline(cin, target);
		} while (Validation::isEmptyOrWhitespace(target));
		ifstream read("products.txt");
		string name, proID, category, subcategory;
		float price;
		int stock;
		bool found = false;

		while (read >> proID >> name >> category >> subcategory >> price >> stock)
		{
			if (proID == target)
			{
				found = true;
				cout << "Found Product:\n";
				cout << "Product ID: " << proID << "\n";
				cout << "Name: " << name << "\n";
				cout << "Category:" << category << "\n";
				cout << "Subcategory: " << subcategory << "\n";
				cout << "Price: " << price << "\n";
				cout << "Quantity: " << stock << "\n";
			    cout << endl;
			}
		}
		system("pause");

		read.close();
	}

	//FUNCTION TO VIEW USERS
	void view_users()
	{ 
	   system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|           VIEW USERS                    |\n";
		cout << "-------------------------------------------\n";
		ifstream read("users.txt");
		string username, password;

		if (!read.is_open())
		{
			cout << "Error! Cannot open users.txt file.\n";
			return;
		}

		cout << "Registered Users:\n";
		int count = 1;

		while (read >> username >> password)
		{
			// Validate that username and password are not empty
			if (Validation :: validUsername(username))
			{
				cout << count++ << ". Username: " << username << endl;
		
		}
		if (!read.eof() && read.fail())
		{
			cout << " cannot read from the file!!\n";
		}
	    }
		read.close();
		cout <<"\n------------------------------------------------\n";
		system("pause");
	}
	
};

//--------------------------------USER CLASS------------------------------------

class User : public Person
{
private :
	CartOrder cart;
public:
	void addToCart() {
		cart.addItem();
	}

	void viewCart() {
		cart.viewCart();
	}

	void placeOrder() {
		cart.selectItems();
	}

	void Payment() {
		cart.makePayment();
	}
	void removeItemFromCart() {
		cart.removeItem();
	}
	void updateQuantityOfItem()
	{
		cart.updateQuantity();
	}
	void cancelOrder()
	{
		cart.cancelord();
	}

	void reviewProduct() {
		Product p;
		p.reviewProducts();
	}

};

//---------------------------------------EMPLOYEE CLASS------------------------------------
class Employee : public Person
{

public:
	//FUNCTION TO ADD CATEGORY
	void addCategory()
	{
		system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|           ADD CATEGORY              |\n";
		cout << "-------------------------------------------\n";
		string cat, sub1, sub2;

		ofstream addToFile;
		addToFile.open("cat.txt", ios::app);

		if (!addToFile.is_open())
		{
			cout << "Error! File can't be opened!\n";
			return;
		}
		do {
			cout << "Enter category name: ";
			getline(cin, cat);
		} while (Validation :: isEmptyOrWhitespace(cat));

		do {
			cout << "Enter first subcategory: ";
			getline(cin, sub1);
		} while (Validation :: isEmptyOrWhitespace(sub1));

		do {
			cout << "Enter second subcategory: ";
			getline(cin, sub2);
		} while (Validation :: isEmptyOrWhitespace(sub2));

		addToFile << cat << " " << sub1 << " " << sub2 << endl;
		addToFile.close();
		cout << "Category and subcategories added successfully!\n";
		system("pause");
		return;
	}

	//FUNCTION TO UPDATE CATEGORY

	void updatecategory()
	{
		system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|           UPDATE CATEGORY              |\n";
		cout << "-------------------------------------------\n";
		string targetCategory;
		do {
			cout << "\nEnter category name to be updated: ";
			cin >> targetCategory;
		}while(Validation::isEmptyOrWhitespace(targetCategory));
		ifstream read("cat.txt");
		ofstream write("tempc.txt");

		bool found = false;
		string cat, sub1, sub2;
		while (read >> cat >> sub1 >> sub2)
		{

			if (cat == targetCategory)
			{
				found = true;
				system("cls");
				do {
					cout << "Enter the updated category: \n";
					getline(cin, cat);
				}while (Validation::isEmptyOrWhitespace(cat));
				do {
					cout << " Enter the Name of Subcategory 1: \n";
					getline(cin, sub1);
				} while(Validation::isEmptyOrWhitespace(sub1));
				do {
					cout << "Enter the Name of Subcategory 2: \n";
					getline(cin, sub2);
				}while (Validation::isEmptyOrWhitespace(sub2));
			}
			write << cat << " " << sub1 << " " << sub2 << endl;
		}
		if (remove("cat.txt") != 0) {
			perror("Error deleting old cat.txt file");
			return; 
		}
		if (rename("tempc.txt", "cat.txt") != 0) {
			perror("Error renaming tempc.txt to cat.txt");
			return; 
		}

		read.close();
		write.close();

		if (found)
			cout << "Category updated successfully.\n";
		else
			cout << "Category not found.\n";
		system("pause");


	}

	// FUNCTION TO UPDATE PRODUCT FOR ADMIN
	void updateProduct()
	{  	system("cls");
	
		cout << "\n-------------------------------------------\n";
		cout << "|           UPDATE A PRODUCT              |\n";
		cout << "-------------------------------------------\n";
		string targetProduct;
		do {
			cout << "Enter Product ID to update: ";
			getline(cin, targetProduct);
		} while (Validation::isEmptyOrWhitespace(targetProduct));

		ifstream read("products.txt");
		if (!read)
		{
			cout << "Error: Cannot open products.txt for reading.\n";
			return;
		}

		ofstream write("tempc.txt");
		if (!write)
		{
			cout << "Error: Cannot open temp.txt for writing.\n";
			read.close();
			return;
		}
		cin.ignore();
		bool found = false;
		string name, proID, category, subcategory;
		double price;
		int stock;

		while (read >> proID >> name >> category >> subcategory >> price >> stock)
		{
			if (proID == targetProduct)
			{
				found = true;
             
				cout << "\nUpdating product " << proID << "...\n";
				do {
					cout << "Enter new Product ID: ";
					getline(cin, proID);
				} while (!Validation::checkproID(proID) || Validation::isEmptyOrWhitespace(proID));

				do {
					cout << "Enter new Name: ";
					getline(cin, name);
				} while (Validation::isEmptyOrWhitespace(name));
				do {
    cout << "Enter new Price: ";
    cin >> price;
    if (cin.fail() || price < 0) {
        cout << "Invalid price!\n";
        cin.clear();
          }
       } while (price < 0);
					do {
						cout << "Enter new Category: ";
						getline(cin, category);
					} while (Validation::isEmptyOrWhitespace(name));

					do {
						cout << "Enter new Subcategory: ";
						getline(cin, subcategory);
					} while (Validation::isEmptyOrWhitespace(name));

					cout << "Enter the Stock: ";
					cin >> stock;
					while (cin.fail() || stock < 0)
					{

						cout << "Invalid input! Enter a valid stock quantity: ";
						cin.clear();
					}
				}
				write << proID << " " << name << " " << category << " " << subcategory << " " << price << " " << stock << endl;
		}

			read.close();
			write.close();

			if (remove("products.txt") != 0) {
				perror("Error deleting old cat.txt file");
				return; 
			}
			if (rename("tempc.txt", "products.txt") != 0) {
				perror("Error renaming tempc.txt to products.txt");
				return; 
			}

			if (found)
			{
				cout << "\nProduct updated successfully.\n";
			}
			else
			{
				cout << "\nProduct not found.\n";
			}
			system("pause");
		
	}
	//FUNCTION TO DELETE CATEGORY
	void deleteCategory()
	{
		system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|           DELETE CATEGORY               |\n";
		cout << "-------------------------------------------\n";
		string target;
		
		do {
			cout << "Enter category or subcategory to delete: ";
			getline(cin, target);
		} while (Validation::isEmptyOrWhitespace(target));
		ifstream inFile("cat.txt");
		ofstream tempFile("tempc.txt");

		if (!inFile.is_open() || !tempFile.is_open())
		{
			cout << "Error! File can't be opened.\n";
			return;
		}

		string cat, sub1, sub2;
		bool found = false;

		while (inFile >> cat >> sub1 >> sub2)
		{
			if (cat == target || sub1 == target || sub2 == target)
			{
				found = true;
				cout << "Deleted: " << cat << " " << sub1 << " " << sub2 << endl;
				continue;
			}
			tempFile << cat << " " << sub1 << " " << sub2 << endl;
		}

		inFile.close();
		tempFile.close();

		if (remove("cat.txt") != 0) {
			perror("Error deleting old cat.txt file");
			return;
		}
		if (rename("tempc.txt", "cat.txt") != 0) {
			perror("Error renaming tempc.txt to cat.txt");
			return;
		}

		if (!found)
		{
			cout << "No matching category or subcategory found.\n";
		}
		else
		{
			cout << "Deletion completed successfully.\n";
		}

		system("pause");
	}
	// FUNCTION TO CHECK LOW STOCK
	void checkLowStock()
	{
		system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|            CHECK LOW STOCKS              |\n";
		cout << "-------------------------------------------\n";
		ifstream read("products.txt");

		if (!read)
		{
			cout << "Error: Cannot open products.txt for reading.\n";
			return;
		}
         const int low=15;
		string name, proID, category, subcategory;
		float price;
		int stock;
		bool found = false;

		
		cout << "Checking for products with low stock (less than 15 units)...\n";
        if(read.is_open())
		{	
		while (read >> proID >> name >> category >> subcategory >> price >> stock )
		{   
	
			if (stock < low)
			{
				found = true;
				cout << "\n------------------------------\n";
				cout << "Product ID    : " << proID << endl;
				cout << "Product Name  : " << name << endl;
				cout << "Category      : " << category << endl;
				cout << "Subcategory   : " << subcategory << endl;
				cout << "Price         : " << price << endl;
				cout << "Stock         : " << stock << endl;
			}
		}

		if (!found)
		{
			cout << "\nNo products with low stock found.\n";
		}
 	 }
		read.close();
		system("pause");
	}

	// FUNCTION TO SEARCH PRODUCT
	void search_product()
	{   system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|           SEARCH A PRODUCT              |\n";
		cout << "-------------------------------------------\n";
		string target;

		do {
			cout << "Enter product ID to search: ";
			getline(cin, target);
		} while (Validation::isEmptyOrWhitespace(target));
		ifstream read("products.txt");
		string name, proID, category, subcategory;
		float price;
		int stock;
		bool found = false;

		while (read >> proID >> name >> category >> subcategory >> price >> stock)
		{
			if (proID == target)
			{
				found = true;
				cout << "Found Product:\n";
				cout << "Product ID: " << proID << "\n";
				cout << "Name: " << name << "\n";
				cout << "Category:" << category << "\n";
				cout << "Subcategory: " << subcategory << "\n";
				cout << "Price: " << price << "\n";
				cout << "Quantity: " << stock << "\n";
				system("pause");
			}
		}

		read.close();
	}
	//UPDATE STOCK FUNCTION
	void updatestock()
	{
		system("cls");
		string targetProduct;
		cout << "\n-------------------------------------------\n";
		cout << "|            Update Stock              |\n";
		cout << "-------------------------------------------\n";
		do {
			cout << "Enter Product ID to update the stock: ";
			getline(cin, targetProduct);
		} while (Validation::isEmptyOrWhitespace(targetProduct));
		ifstream read("products.txt");
		ofstream write("temps.txt");

		bool found = false;
		string name, proID, category, subcategory;
		float price;
		int stock;

		while (read >> proID >> name >> category >> subcategory >> price >> stock)
		{
			if (proID == targetProduct)
			{
				found = true;
				cout << "Enter the Stock: ";
				cin >> stock;

				if (stock < 0)
				{
					cout << "Enter value more than 0 !" << endl;
				}

			}
			write << proID << " " << name << " " << price << " " << category << " " << subcategory << " " << stock << endl;
		}

		read.close();
		write.close();
		remove("products.txt");
		if (rename("temps.txt", "products.txt"))
		{
			perror("Error renaming files!");
		}
		if (found)
			cout << "Stock was updated successfully.\n";
		else
			cout << "Stock was  not updated.\n";
		system("pause");
	}
	//FUNCTION TO ADD PRODUCT
	void addProduct()
	{
		system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|          ADD A PRODUCT              |\n";
		cout << "-------------------------------------------\n";
		int ch, proCount = 0;
		string proID, name, category, subcategory, temp;
		float price;
		int stock;
	
		
		 // Input and validate how many products to add
   		do {	
				cout << "How many products do you want to add?" << endl;
				getline(cin, temp);
			} while ( !Validation::checkproID(proID));
			
			if (Validation::validInteger(temp))
			{
				ch = stoi(temp);

			}
		
		ofstream file("products.txt", ios::app);
		if (file.is_open())
		{
			for (int i = 0; i < ch; i++)
			{ 
				Product p;
				do {
					cout << "Product Id :" << endl;
					getline(cin, proID);
				} while (Validation::isEmptyOrWhitespace(proID) || Validation :: checkproID(proID));
				p.setproID(proID);

				do {
					cout << "Product Name :" << endl;
					getline(cin, name);
				} while (Validation::isEmptyOrWhitespace(name));
				p.setname(name);
				do {
					cout << "Category:" << endl;
					getline(cin, category);
				} while (Validation::isEmptyOrWhitespace(category));
				p.setcategory(category);
				do {
					cout << "Subcategory: " << endl;
					getline(cin, subcategory);
				} while (Validation::isEmptyOrWhitespace(subcategory));
				p.setsubcat(subcategory);
				do {
					cout << "Price: ";
					cin >> price;
					if (cin.fail() || price <= 0) {
						cout << "Invalid price!" << endl;
						cin.clear();
						cin.ignore();
					}
				} while (price <= 0);
				p.setprice(price);
				do {
					cout << "Stock: ";
					cin >> stock;
					if (cin.fail() || stock <= 0) {
						cout << "Invalid stock!" << endl;
						cin.clear();
					}
				} while (stock <= 0);
				p.setstock(stock);
				file << proID << " " << name << " " << category << " " << subcategory << " " << price << " " << stock << endl;
				proCount++;
				system("pause");
			}
		}
	}
	//FUNCTION TO DELETE PRODUCT
	void deleteProduct()
	{ 
	system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "|           DELETE A PRODUCT              |\n";
		cout << "-------------------------------------------\n";
		string targetID;
		
		do {
			cout << "Enter Product ID to delete: ";
			getline(cin, targetID);
		} while (Validation::isEmptyOrWhitespace(targetID));
		ifstream inFile("products.txt");
		ofstream tempFile("tempd.txt");

		if (!inFile || !tempFile)
		{
			cout << "Error opening file!" << endl;
			return;
		}
		string proID, name, category, subcategory;
		double price;
		int stock;
		bool found = false;

		while (inFile >> proID >> name >> category >> subcategory >> price >> stock)
		{
			if (proID != targetID)
			{
				tempFile << proID << " " << name << " " << category << " " << subcategory << " " << price << " " << stock << endl;
			}
			else
			{
				found = true;
			}
		}

		inFile.close();
		tempFile.close();
		
       
		// Replace old file with updated one
		remove("products.txt");
		if (rename("tempd.txt", "products.txt") != 0)
		{

		}

		if (found)
		{
			cout << "Product with ID " << targetID << "has been deleted.\n";
		}
		else
		{
			cout << "Product ID not found.\n";
		}
		system("pause");
	}
};
//----------------------------------MENU CLASS--------------------------------------------
class Menu {
public:
	// Menu for USER LOGIN AND SIGNUP
	static bool menu_up(string role)
	{
		Person p;
		bool loggedin = false;
		string choice;
		do {
			system("cls");
			cout << "\n---------------------------------------------\n";
			cout << "|              USER                      |\n";
			cout << "----------------------------------------------\n";
			cout << "1. USER SIGNUP\n";
			cout << "2. USER LOGIN\n";
			cout << "3. FORGOTTEN PASSWORD\n";
			cout << "4. Exit\n";
			do {
				cout << "\nEnter your choice: ";
				getline(cin, choice);
			} while (Validation::isEmptyOrWhitespace(choice));
			if (choice == "1")
			{
				p.signup(role);
			}
			else if (choice == "2")
			{
				bool loggedin = Person::login(role);
				if (loggedin)
				{
					Menu::showUserMenu();
					return true;
				}
				else
				{
					return false;
				}

			}
			else if (choice == "3")
			{
				string role;
				role = "User";
				p.forgotPass(role);

			}
			else if (choice == "4")
			{
				cout << "\nExiting........\n";
				return false;
			}
			else {
				cout << "\nInvalid choice. Please enter 1 - 4.\n";
				system("pause");
			}
		} while (choice != "4" && choice < "4");
		system("pause");
		return loggedin;

	}

	// START-UP MENU FUNCTION
	static bool start_up(string role)
	{
		bool isLoggedIn = false;
		string choice;
		do {
			system("cls");
			cout << "\n-------------------------------------------\n";
			cout << "|                   ADMIN                   |\n";
			cout << "---------------------------------------------\n";
			cout << "1. ADMIN SIGNUP\n";
			cout << "2. ADMIN LOGIN\n";
			cout << "3. FORGOT PASS\n";
			cout << "4. EXIT\n";
			do {
				cout << "\nEnter your choice: ";
				getline(cin, choice);
			} while (Validation::isEmptyOrWhitespace(choice));
			if (choice == "1")
			{
				Person::signup(role);
				system("pause");

			}
			else if (choice == "2")
			{
				bool isLoggedIn = Person::login(role);
				if (isLoggedIn)
				{
					Menu::showadminmenu();
					system("pause");
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (choice == "3")
			{

				Person::forgotPass(role);
				system("cls");
				system("pause");
			}
			else if (choice == "4")
			{
				cout << "\nExiting........\n";
				system("pause");
				return false;
				break;

			}
			else
			{
				cout << "\nInvalid choice. Please enter 1 - 4.\n";
				system("pause");
			}

		} while (choice != "4");
		system("pause");
		return isLoggedIn;
	}
	// ADMIN MENU 
	static void showadminmenu()
	{
		admin adobj;
		Product p;
		string choice;
		do {
			system("cls");
			cout << "\n-----------------------------------------\n";
			cout << "|               ADMIN MENU                |\n";
			cout << "------------------------------------------\n";
			cout << "1. DISPLAY PRODUCTS\n";
			cout << "2. DISPLAY CATEGORIES\n";
			cout << "3. VIEW EMPLOYEES\n";
			cout << "4. VIEW USERS\n";
			cout << "5. DELETE EMPLOYEE\n";
			cout << "6. SEARCH PRODUCT\n";
			cout << "7. DELETE USERS\n";
			cout << "8. VIEW REVIEWS\n";
			cout << "9. EXIT\n";
			do {
				cout << "\nEnter your choice: ";
				getline(cin, choice);
			} while (Validation::isEmptyOrWhitespace(choice));

			if (choice == "1")
			{
				p.displayProducts();

			}
			else if (choice == "2")
			{
				p.displayCategories();

			}
			else if (choice == "3")
			{
				adobj.view_employee();

			}
			else if (choice == "4")
			{
				adobj.view_users();
				system("pause");

			}
			else if (choice == "5")
			{
				adobj.delete_employee();

			}
			else if (choice == "6")
			{
				adobj.search_product();

			}
			else if (choice == "7")
			{
				adobj.delete_users();

			}
			else if (choice == "8")
			{
				p.viewReviews();
			}
			else if (choice == "9")
			{
				system("cls");
				cout << "\nExiting........\n";
				system("pause");
				return;
			}
			else
			{
				cout << "\nInvalid choice. Please enter 1 or 8.\n";
				system("pause");
			}
		} while (choice != "9");
		system("pause");

	}
	//USER MENU
	static void showUserMenu()
	{
		User u;
		Product p;
		string ch1;
		do {
			system("cls");
			cout << "\n----------------------------------------------\n";
			cout << "|              USER MENU                     |\n";
			cout << "----------------------------------------------\n";
			cout << "1.DISPLAY PRODUCTS" << endl;
			cout << "2.ADD ITEM TO CART" << endl;
			cout << "3.VIEW CART" << endl;
			cout << "4.CHECKOUT SELECTED ITEMS" << endl;
			cout << "5.MAKE PAYMENT" << endl;
			cout << "6.REMOVE AN ITEM" << endl;
			cout << "7.CANCEL ORDER" << endl;
			cout << "8.UPDATE QUANTITY" << endl;
			cout << "9.REVIEW A PRODUCT" << endl;
			cout << "10.DISPLAY CATEGORIES " << endl;
			cout << "11.Exit" << endl;
			do {
				cout << "Enter your choice :" << endl;
				getline(cin, ch1);
			} while (Validation::isEmptyOrWhitespace(ch1));
			if (ch1 == "1")
			{
				p.displayProducts();
			
			}
			else if (ch1 == "2")
			{
				u.addToCart();
			}
			else if (ch1 == "3")
			{
				u.viewCart();


			}
			else if (ch1 == "4")
			{
				u.placeOrder();


			}
			else if (ch1 == "5") {

				u.Payment();

			}
			else if (ch1 == "6") {

				u.removeItemFromCart();

			}
			else if (ch1 == "7") {

				u.cancelOrder();

			}
			else if (ch1 == "8") {

				u.updateQuantityOfItem();


			}
			else if (ch1 == "9") {

				u.reviewProduct();


			}
			else if (ch1 == "10") {

				p.displayCategories();
				system("pause");

			}

			else if (ch1 == "11") {
				cout << " Exiting........\n";
				system("pause");
				return;
			}
			else {
				cout << "\nInvalid choice. Please enter 1 - 4.\n";
			}

		} while (ch1 != "11");
		system("pause");
	}
	//EMPLOYEE MENU
	static bool empMenu_up(string role)
	{
		string choice;
		bool loggedin = false;
		do {
			system("cls");
			cout << "\n---------------------------------------------\n";
			cout << "|              EMPLOYEE                   |\n";
			cout << "----------------------------------------------\n";
			cout << "1. EMPLOYEE SIGNUP\n";
			cout << "2. EMPLOYEE LOGIN\n";
			cout << "3. FORGOTTEN PASSWORD\n";
			cout << "4. Exit\n";
			do {
				cout << "\nEnter your choice: ";
				getline(cin, choice);
			}
			while (Validation::isEmptyOrWhitespace(choice));
			if (choice == "1")
			{
				Person::signup(role);
				system("pause");
			}
			else if (choice == "2")
			{
				bool loggedin = Person::login(role);
				if (loggedin)
				{
					Menu::empMenu();
					return true;
				}
				else
				{
					return false;
				}
				system("pause");
			}
			else if (choice == "3")
			{
				string role;
				role = "Employee";
				Person::forgotPass(role);
				break;
			}
			else if (choice == "4")
			{
				cout << "\nExiting........\n";
				break;
				return false;
			}
			else
			{
				cout << "\nInvalid choice. Please enter 1 - 4.\n";
			}
		} while (choice != "4");
		system("pause");
		return loggedin;
	}
	static void empMenu()
	{
		Employee emp;
		Product p;
		CartOrder c;
		string ch1;
		do {
			system("cls");
			cout << "\n---------------------------------------------\n";
			cout << "|              EMPLOYEE MENU                   |\n";
			cout << "----------------------------------------------\n";
			cout << "1. VIEW ORDERS\n";
			cout << "2. UPDATE STOCK\n";
			cout << "3. CHECK LOW STOCK ITEMS\n";
			cout << "4. UPDATE ORDER STATUS\n";
			cout << "5. SEARCH PRODUCT\n";
			cout << "6. ADD PRODUCT\n";
			cout << "7. DELETE PRODUCT\n";
			cout << "8. CANCEL ORDER \n";
			cout << "9. UPADATE CATEGORY\n";
			cout << "10. UPDATE PRODUCT \n";
			cout << "11. DISPLAY CATEGORY\n";
			cout << "12. ADD CATEGORY \n";
			cout << "13. DISPLAY PRODUCTS\n";
			cout << "14. VIEW REVIEWS\n";
			cout << "15. Exit\n";
			do {
				cout << "\nEnter your choice: ";
				getline(cin, ch1);
			} while (Validation::isEmptyOrWhitespace(ch1));
			if (ch1 == "1")
			{
				c.viewOrder();
			}
			else if (ch1 == "2")
			{
				emp.updatestock();


			}
			else if (ch1 == "3")
			{
				emp.checkLowStock();


			}
			else if (ch1 == "4")
			{
				c.updateOrderStatus();


			}
			else if (ch1 == "5")
			{
				emp.search_product();

			}
			else if (ch1 == "6")
			{
				emp.addProduct();

			}
			else if (ch1 == "7")
			{
				emp.deleteProduct();

			}
			else if (ch1 == "8")
			{
				c.cancelord();

			}

			else if (ch1 == "9")
			{
				emp.updatecategory();

			}
			else if (ch1 == "10")
			{
				emp.updateProduct();

			}
			else if (ch1 == "11")
			{
				p.displayCategories();

			}
			else if (ch1 == "12")
			{
				emp.addCategory();

			}
			else if (ch1 == "13")
			{
				p.displayProducts();

			}
			else if (ch1 == "14")
			{
				p.viewReviews();

			}
			else if (ch1 == "15")
			{
				cout << "\nExiting........\n";
				return;
			}
			else
			{
				cout << "\nInvalid choice. Please enter 1 - 14.\n";
			}
		} while (ch1 != "15");

		system("pause");
	}
};
//----------------------------------SYSTEM CLASS--------------------------------------------

class System {
public:
	void start()
	{
		string role;
		system("cls");
		do {
			cout << "\n-----------------------------------------------\n";
			cout << "|          E-COMMERCE MANAGEMENT SYSTEM        |\n";
			cout << "-----------------------------------------------\n";
			cout << "1. ADMIN \n";
			cout << "2. USER \n";
			cout << "3. EMPLOYEE \n";
			do{
				cout << "\nEnter your choice: ";
				getline(cin, role);
			} while (Validation::isEmptyOrWhitespace(role));
			if (role == "1" || role == "Admin")
			{

				bool success = Menu::start_up(role);
				if (success)
					Menu::showadminmenu();
			}
			else if (role == "2" || role == "User")
			{
				bool success1 = Menu::menu_up(role);
				if (success1)
					Menu::showUserMenu();

			}
			else if (role == "3" || role == "Employee")
			{
				bool success2 = Menu::empMenu_up(role);
				if (success2)
					Menu::empMenu();
			}

			else if (role == "4") {
				cout << "Exiting....";
				return;
			}
			else
			{
				cout << "\nInvalid role selection.";
			}
		} while (role != "4");
	}

};
//---------------------------------------MAIN FUNCTION-------------------------------------
int main()
{
	System eco;
	eco.start();
}
