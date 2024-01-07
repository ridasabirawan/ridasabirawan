
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
const int MAX_USERS = 100; // Assuming a maximum of 100 users for demonstration purposes
const int MAX_PRODUCTS = 50; // Assuming a maximum of 50 products for demonstration purposes

class Product {
protected:
    string name;
    double price;
 string description;
    string reviews;
public:
	
    Product(const string& n, double p) : name(n), price(p) {}
    Product() : name(""), description(""), price(0.0), reviews("") {}
    Product(string n, string d, double p, string r) : name(n), description(d), price(p), reviews(r) {}

    void displayProductInfo() {
        cout << "Name: " << name << endl;
        cout << "Description: " << description << endl;
        cout << "Price: $" << price << endl;
        cout << "Reviews: " << reviews << endl;
        cout << endl;
    }
    // Getter for product name
    string getName() const {
        return name;
    }

    // Getter for product price
    double getPrice() const {
        return price;
    }

    // Virtual function to display product details
    virtual void displayDetails() const {
        cout << name << " RS" << fixed << setprecision(2) << price << ")\n";
    }

    // Virtual destructor for polymorphism
    virtual ~Product() {}
};
class User {
private:
    string firstName;
    string lastName;
    string username;
    string email;
    string password;
    string securityQuestion;
    string securityAnswer;

public:
    void signUp() {
        cout << "Welcome to the sign-up process." << endl;
        cout << "Enter your first name: ";
        cin >> firstName;
        cout << "Enter your last name: ";
        cin >> lastName;
        cout << "Enter a username: ";
        cin >> username;
        cout << "Enter your email: ";
        cin >> email;
        cout << "Enter a password: ";
        cin >> password;
        cout << "Enter the security question: ";
        cin.ignore();
        getline(cin, securityQuestion);
        cout << "Enter the answer to the security question: ";
        getline(cin, securityAnswer);

        // Save user data to file
        ofstream file("user_data.txt");
        if (file.is_open()) {
            file << firstName << endl;
            file << lastName << endl;
            file << username << endl;
            file << email << endl;
            file << password << endl;
            file << securityQuestion << endl;
            file << securityAnswer << endl;
            file.close();
            cout << "Sign-up successful. Your data has been saved." << endl;
        }
        else {
            cout << "Failed to save user data." << endl;
        }
    }

    void login() {
        cout << "Welcome to the login process." << endl;
        string enteredUsername, enteredPassword;
        cout << "Enter your username: ";
        cin >> enteredUsername;
        cout << "Enter your password: ";
        cin >> enteredPassword;

        // Load user data from file
        ifstream file("user_data.txt");
        if (file.is_open()) {
            getline(file, firstName);
            getline(file, lastName);
            getline(file, username);
            getline(file, email);
            getline(file, password);
            getline(file, securityQuestion);
            getline(file, securityAnswer);
            file.close();

            // Check if username and password match stored data
            if (enteredUsername == username && enteredPassword == password) {
                cout << "Login successful." << endl;
                // Continue to cart for further processing
            }
            else {
                cout << "Incorrect username or password." << endl;
                cout << "Forgot password? Type 'retry' or 'change' to answer the security question: ";
                string answer;
                cin >> answer;

                if (answer == "retry") {
                    login();
                }
                else if (answer == "change") {
                    string enteredSecurityAnswer;
                    cout << securityQuestion << ": ";
                    cin.ignore();
                    getline(cin, enteredSecurityAnswer);

                    if (enteredSecurityAnswer == securityAnswer) {
                        string newPassword;
                        cout << "Enter a new password: ";
                        cin >> newPassword;
                        password = newPassword;

                        // Update password in file
                        ofstream file("user_data.txt");
                        if (file.is_open()) {
                            file << firstName << endl;
                            file << lastName << endl;
                            file << username << endl;
                            file << email << endl;
                            file << password << endl;
                            file << securityQuestion << endl;
                            file << securityAnswer << endl;
                            file.close();
                            cout << "Password changed successfully. Please log in again." << endl;
                            login();
                        }
                        else {
                            cout << "Failed to update password." << endl;
                        }
                    }
                    else {
                        cout << "Incorrect security answer." << endl;
                    }
                }
                else {
                    cout << "Invalid input." << endl;
                }
            }
        }
        else {
            cout << "Failed to load user data." << endl;
        }
    }
};


class Electronics : public Product {
public:
    Electronics(const string& n, double p) : Product(n, p) {}

    // Override displayDetails for Electronics
    void displayDetails() const override {
        cout << "Electronics - ";
        Product::displayDetails();
    }
};                                                                                                 //  quantity required ; for example 5 so it automatically adds 5 baar baar na krna parhay add

class Fashion : public Product {
public:
    Fashion(const string& n, double p) : Product(n, p) {}

    // Override displayDetails for Fashion
    void displayDetails() const override {
        cout << "Fashion - ";
        Product::displayDetails();
    }
};

class HomeAndKitchen : public Product {
public:
    HomeAndKitchen(const string& n, double p) : Product(n, p) {}

    // Override displayDetails for Home and Kitchen
    void displayDetails() const override {
        cout << "Home and Kitchen - ";
        Product::displayDetails();
    }
};

class HealthAndBeauty : public Product {
public:
    HealthAndBeauty(const string& n, double p) : Product(n, p) {}

    // Override displayDetails for Health and Beauty
    void displayDetails() const override {
        cout << "Health and Beauty - ";
        Product::displayDetails();
    }
};

class BooksAndMedia : public Product {
public:
    BooksAndMedia(const string& n, double p) : Product(n, p) {}

    // Override displayDetails for Books and Media
    void displayDetails() const override {
        cout << "Books and Media - ";
        Product::displayDetails();
    }
};

class ShoppingCart : public User {
private: 

    Product* cart[100];  // Assuming a maximum of 100 products in the cart
    int itemCount;

public:
    ShoppingCart() : itemCount(0) {}

    // Function to add a product to the cart
    void addToCart(Product* product) {
        if (itemCount < 100) {
            cart[itemCount++] = product;
            cout << "Product added to the cart: " <<     product->getName() << "\n";
        } else {
            cout << "Cart is full. Cannot add more items.\n";
        }
    }

    // Function to remove a product from the cart
    void removeFromCart(int index) {
        if (index >= 0 && index < itemCount) {
            cout << "Product removed from the cart: " << cart[index]->getName() << "\n";
            delete cart[index];  // Release memory occupied by the product
            for (int i = index; i < itemCount - 1; ++i) {
                cart[i] = cart[i + 1];
            }
            itemCount--;
        } else {
            cout << "Invalid index. Cannot remove product from the cart.\n";
        }
    }

    // Function to display the contents of the cart and calculate total cost
    bool displayCart() const {
        if (itemCount == 0) {
            cout << "Your cart is empty.\n";
            return false;
        } else {
            double totalCost = 0.0;
            cout << "Cart Contents:\n";
            for (int i = 0; i < itemCount; ++i) {
                cout << i + 1 << ". ";
                cart[i]->displayDetails();
                totalCost += cart[i]->getPrice();
            }
            cout<<"************"<<endl;
            cout << "Your Total Cost is : RS" << fixed << setprecision(2) << totalCost << "\n";
            return true;
        }
    }
     void display() {
        cout << "*******************************************************************************************" << endl;
        cout << "*               *               *               *               *               *         *" << endl;
        cout << "*             *   *           *   *           *   *           *   *           *   *       *" << endl;
        cout << "*           *       *       *       *       *       *       *       *       *       *     *" << endl;
        cout << "*         *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *" << endl;
        cout << "*       *               *               *               *               *               * *" << endl;
        cout << "*     *   *           *   *           *   *           *   *           *   *           *   *" << endl;
        cout << "*   *       *       *       *       *       *       *       *       *       *       *     *" << endl;
        cout << "*     *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *" << endl;
        cout << "*       *               *               *               *               *               * *" << endl;
        cout << "*     *   *           *   *           *   *           *   *           *   *           *   *" << endl;
        cout << "*   *       *       *       *       *       *       *       *       *       *       *     *" << endl;
        cout << "*     *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *" << endl;
        cout << "*       *               *               *               *               *               * *" << endl;
        cout << "*     *   *           *   *           *   *           *   *           *   *           *   *" << endl;
        cout << "*   *       *       *       *       *       *       *       *       *       *       *     *" << endl;
        cout << "*     *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *" << endl;
        cout << "*               *               *               *               *               *         *" << endl;
        cout << "*--o--***--o-----o--*o----o--*--o---o--*-----o--o--o--o--*--o--***--o-----o--**o----o-o---*" << endl;
        cout << "*                                                                                         *" << endl;
        cout << "*           CCCCC   AAAA   RRRRR  TTTTTTT  OOOO   PPPP   III   AAAA                       *" << endl;
        cout << "*          CC      AA  AA  RR  RR   TT    OO  OO  PP PP  III  AA  AA                      *" << endl;
        cout << "*          CC      AAAAAA  RRRRR    TT    OO  OO  PPPP   III  AAAAAA                      *" << endl;
        cout << "*          CC      AA  AA  RR  RR   TT    OO  OO  PP     III  AA  AA                      *" << endl;
        cout << "*           CCCCC  AA  AA  RR   RR  TT     OOOO   PP     III  AA  AA                      *" << endl;
        cout << "*\n--o--***--o-----o--*o----o--*--o---o--*-----o--o--o--o--*--o--***--o-----o--**o----o-o--***" << endl;
        cout << "*                                                                                         *" << endl;
             //   cout << "*****************************************************************************************" << endl;
        cout << "*               *               *               *               *               *         *" << endl;
        cout << "*             *   *           *   *           *   *           *   *           *   *       *" << endl;
        cout << "*           *       *       *       *       *       *       *       *       *       *     *" << endl;
        cout << "*         *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *" << endl;
        cout << "*       *               *               *               *               *               * *" << endl;
        cout << "*     *   *           *   *           *   *           *   *           *   *           *   *" << endl;
        cout << "*   *       *       *       *       *       *       *       *       *       *       *     *" << endl;
        cout << "*     *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *" << endl;
        cout << "*       *               *               *               *               *               * *" << endl;
        cout << "*     *   *           *   *           *   *           *   *           *   *           *   *" << endl;
        cout << "*   *       *       *       *       *       *       *       *       *       *       *     *" << endl;
        cout << "*     *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *" << endl;
        cout << "*       *               *               *               *               *               * *" << endl;
        cout << "*     *   *           *   *           *   *           *   *           *   *           *   *" << endl;
        cout << "*   *       *       *       *       *       *       *       *       *       *       *     *" << endl;
        cout << "*     *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *" << endl;
        cout << "*               *               *               *               *               *         *" << endl;
        cout << "*******************************************************************************************" << endl;
        
        cout << "*                                                                                         *" << endl;   
        cout << "*                   ___WELCOME TO OUR ONLINE SHOPPING SYSTEM!___                          *" << endl;
        cout << "*                                                                                         *" << endl;   

        cout << "*       Explore our wide range of products and enjoy a convenient shopping experience.    *" << endl;
        cout << "*                                                                                         *" << endl;  
        
          cout << "*******************************************************************************************" << endl;
          cout << "*               *               *               *               *               *         *" << endl;
          cout << "*             *   *           *   *           *   *           *   *           *   *       *" << endl;
          cout << "*           *       *       *       *       *       *       *       *       *       *     *" << endl;
          cout << "*         *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *" << endl;
          cout << "|/__\|/__\|/__\|/__\|/__\|/__\|/__\|/__\|/_/__\|/__\|/__\|/__\|/__\|/__\|/__\|/__\|/__\|/__\|/__\|/__\|/__\|/__\|" << endl; 
    }

   

    // Getter for item count
    int getItemCount() const {
        return itemCount;
    }

    // Destructor to release memory occupied by products in the cart
    ~ShoppingCart() {
        for (int i = 0; i < itemCount; ++i) {
            delete cart[i];
        }
    }
};

void clearScreen() {
    system("CLS");  
}
int main() {
    ShoppingCart cart;
    cart.display();
//    cart.ShoppingCart();
    cout << "        +------------------------------------------------------------------+" << endl;
    cout << "        *                           WELCOME TO OUR                         *" << endl;
    cout << "        +                            USER PORTAL                           +" << endl;
    cout << "        *------------------------------------------------------------------*" << endl;
    cout << "        +                        Enter '1' to Sign Up                      +" << endl;
    cout << "        *                        Enter '2' to Log In                       *" << endl;
    cout << "        +------------------------------------------------------------------+" << endl;

    int choice;
    cout << "Your choice: ";
    cin >> choice;
    if(choice==1){
	
    cart.signUp();
}
else {

    cart.login();
}
    // Main Menu 
    do {
    	 
        cout << " ******** Welcome to THE CARTOPIA!  ******** \n";
        
        
        cout << " Please select an option from the main menu:\n";
        cout << "1. (Electronics) \n";
        cout << "2. (Fashion)\n";
        cout << "3. (Home and Kitchen) \n";
        cout << "4. (Health and Beauty) \n";
        cout << "5. (Books and Media) \n";
        cout << "6. View Cart\n";
        cout << "7. Remove from Cart\n";
        cout << "0. Exit\n";
        
        cout << " Please enter your choice: ";
        cin >> choice;

        switch (choice) {
        	
            case 1: 
                {  clearScreen(); 
                    // Electronics Menu
                    int electronicsChoice;
                    do {
                        cout <<" **** Electronics Menu  **** "<<endl;
                        cout << "1. Samsung s23 ultra (Rs 520000)"<<endl;
                        cout << "2. Lenovo t470s (Rs 180000)"<<endl;
                        cout << "3. Beats Headphones (Rs 12000)"<<endl;
                        cout<<  "4. Apple watch (Rs 70000 )"<<endl;
                        cout<<  "5. Iphone 15pro max (Rs 660000) "<<endl;
                        cout<<  "6. HP Elitebook  (Rs 130000) "<<endl;
                        	
                        cout << "0. Back to Main Menu or see the total"<<endl;
                        cout << "Enter your choice: ";
                        cin >> electronicsChoice;

                        switch (electronicsChoice) {
                            case 1:
                                cart.addToCart(new Electronics("Samsung s23 ultra ", 520000));
                                break;
                            case 2:
                                cart.addToCart(new Electronics("Lenovo t470s", 180000));
                                break;
                            case 3:
                                cart.addToCart(new Electronics("Beats Headphones", 12000));
                                break;
                                 case 4:
                                cart.addToCart(new Electronics("Apple watch ", 70000));
                                break;
                                 case 5:
                                cart.addToCart(new Electronics("Iphone 15pro max", 660000));
                                break;
                                 case 6:
                                cart.addToCart(new Electronics("HP Elitebook  ", 130000));
                                break;
                            case 0:
                            	break; // Go back to the main menu
                            default:
                                cout << "Invalid choice.\n";
                        }
                          
                         
                    } while (electronicsChoice != 0);
                }
            
                break;
            case 2: // Fashion
                {  clearScreen(); 
                    // Fashion Menu
                    int fashionChoice;
                    do {
                        cout << " **** Fashion Menu **** "<<endl;
                        cout << "1. Jeans (Engine) (RS 6500)"<<endl;
                        cout << "2. Shoes (Nike) (RS 12000)"<<endl;
                        cout << "3. Braclet (RS 200)"<<endl;
                        cout << "4. Hoodie (outfitters) (RS 14000)"<<endl;
                         cout <<"5. Leather jacket (RS 14200)"<<endl;
                         cout <<"5. Ring (RS 140)"<<endl;
                        cout << "0. Back to Main Menu or see the total"<<endl;
                        cout << "Enter your choice: ";
                        cin >> fashionChoice;

                        switch (fashionChoice) {
                            case 1:
                                cart.addToCart(new Fashion(" Jeans (Engine)", 6500));
                                break;
                            case 2:
                                cart.addToCart(new Fashion("Shoes (Nike)", 12000));
                                break;
                            case 3:
                                cart.addToCart(new Fashion("Braclet ", 200));
                                break;
                                 case 4:
                                cart.addToCart(new Fashion(" Hoodie (outfitters)",14000));
                                break;
                                 case 5:
                                cart.addToCart(new Fashion("Leather jacket ", 14200));
                                break;
                                 case 6:
                                cart.addToCart(new Fashion("Ring ", 140));
                                break;
                            case 0:
                                break; // Go back to the main menu
                            default:
                                cout << "Invalid choice.\n";
                        }
                    } while (fashionChoice != 0);
                }
                break;
            case 3: // Home and Kitchen
                {
                	 clearScreen(); 
                    // Home and Kitchen Menu
                    int homeAndKitchenChoice;
                    do {
                        cout << "  **** Home and Kitchen Menu **** "<<endl;
                        cout << "1. Chairs (pack of 6) (Rs 20000)"<<endl;
                        cout << "2. Table  (RS 1890)"<<endl;
                        cout << "3. Microwave (RS 25400)"<<endl;
                        cout << "4. Toaster  (RS 4540)"<<endl;
                        cout << "5. Bed  (RS 98999)"<<endl;
                        cout << "6. Sofa (pack of 6)  (RS 249999)"<<endl;
                        cout << "0. Back to Main Menu or see the total"<<endl;
                        cout << "Enter your choice: ";
                        cin >> homeAndKitchenChoice;

                        switch (homeAndKitchenChoice) {
                            case 1:
                                cart.addToCart(new HomeAndKitchen("Chairs (pack of 6) ", 20000));
                                break;
                            case 2:
                                cart.addToCart(new HomeAndKitchen("Table ", 1890));
                                break;
                            case 3:
                                cart.addToCart(new HomeAndKitchen(" Microwave", 25400));
                                break;
                                 case 4:
                                cart.addToCart(new HomeAndKitchen("Toaster", 4540));
                                break;
                                 case 5:
                                cart.addToCart(new HomeAndKitchen("Bed ", 98999));
                                break;
                                 case 6:
                                cart.addToCart(new HomeAndKitchen("Sofa (pack of 6)", 249999));
                                break;
                            case 0:
                                break; // Go back to the main menu
                            default:
                                cout << "Invalid choice.\n";
                        }
                    } while (homeAndKitchenChoice != 0);
                }
                break;
            case 4: 
                {
                	 clearScreen(); 
                    // Health and Beauty Menu
                    int healthAndBeautyChoice;
                    do {
                        cout << " **** Health and Beauty Menu **** "<<endl;
                        cout << "1. Vasline  (RS 870)"<<endl;
                        cout << "2. head&shoulder  (RS 2230)"<<endl;
                        cout << "3. lipsticks (pack of 6)  (RS 3380)"<<endl;
                        cout << "4. Pound's  Facewash  (RS 380)"<<endl;
                        cout << "5. Aventus Creed  (RS 45980)"<<endl;
                        cout << "6. Nailpolishes (pack of 6)   (RS 1899)"<<endl;
                        cout << "0. Back to Main Menu or see the total"<<endl;
                        cout << "Enter your choice: ";
                        cin >> healthAndBeautyChoice;

                        switch (healthAndBeautyChoice) {
                            case 1:
                                cart.addToCart(new HealthAndBeauty("Vasline", 870));
                                break;
                            case 2:
                                cart.addToCart(new HealthAndBeauty("head&shoulder", 2230));
                                break;
                            case 3:
                                cart.addToCart(new HealthAndBeauty("lipsticks (pack of 6)", 3380));
                                break;
                                 case 4:
                                cart.addToCart(new HealthAndBeauty("Pound's  Facewash", 380));
                                break;
                                 case 5:
                                cart.addToCart(new HealthAndBeauty("Aventus Creed",  45980));
                                break;
                                 case 6:
                                cart.addToCart(new HealthAndBeauty("Nailpolishes (pack of 6) ",1899));
                                break;
                            case 0:
                                break; // Go back to the main menu
                            default:
                                cout << "Invalid choice.\n";
                        }
                    } while (healthAndBeautyChoice != 0);
                }
                break;
            case 5: 
			// Books and Media
                {
                     clearScreen(); 
                    int booksAndMediaChoice;
                    do {
                        cout << "**** Books and Media Menu **** \n"<<endl;
                        cout << "1. Nineteen Eighty-Four, by George Orwell(Novel) (RS 650)"<<endl;
                        cout << "2. The Dark Side (Novel) (RS 720)"<<endl;
                        cout << "3. The Haunted House (Novel) (RS 459)"<<endl;
                        cout << "4. Animal Movie (DVD) (RS 180)"<<endl;
                        cout << "5. Jawan Movie (DVD) (RS 170)"<<endl;
                        cout << "6. Tiger3 Movie (DVD) (RS 190)"<<endl;
                        cout << "0. Back to Main Menu or see the total \n"<<endl;
                        cout << "Enter your choice: ";
                        cin >> booksAndMediaChoice;

                        switch (booksAndMediaChoice) {
                            case 1:
                                cart.addToCart(new BooksAndMedia(" Nineteen Eighty-Four, by George Orwell(Novel)",650));
                                break;
                            case 2:
                                cart.addToCart(new BooksAndMedia("The Dark Side (Novel)", 720));
                                break;
                            case 3:
                                cart.addToCart(new BooksAndMedia("The Haunted House (Novel)", 459));
                                break;
                            case 4:
                                cart.addToCart(new BooksAndMedia("Animal Movie (DVD)",80));
                                break;    
                            case 5:
                                cart.addToCart(new BooksAndMedia("Jawan Movie (DVD)",70));
                                break;
							case 6:
                                cart.addToCart(new BooksAndMedia("Tiger3 Movie (DVD)",90));
                                break;   
                            case 0:
                                break; // Go back to the main menu
                            default:
                                cout << "Invalid choice.\n";
                        }
                    } while (booksAndMediaChoice != 0);
                    
                }
                break;
            case 6: // View Cart
             clearScreen(); 
                cart.displayCart();
                break;
            case 7: // Remove from Cart
             clearScreen(); 
                if (cart.displayCart()) {
                    int removeChoice;
                    cout << "Enter the index of the product to remove (0 to cancel): ";
                    cin >> removeChoice;
                    if (removeChoice > 0 && removeChoice <= cart.getItemCount()) {
                        cart.removeFromCart(removeChoice - 1);
                    } else if (removeChoice != 0) {
                        cout << "Invalid index.\n";
                    }
                }
                break;
            case 0:
                cout << "*|*|*|*|*|*|*|*|*|*|*|*|*|*  Thank you for your visit :)  *|*|*|*|*|*|*|*|*|*|*|*|* \n";
                break;
            default:
                cout << " Sorry!! Please try another option .\n";
        }

    } while (choice != 0);

    return 0;
}


