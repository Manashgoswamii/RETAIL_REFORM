#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>
#include <chrono>
#include <windows.h>
#include <iomanip> 
// ANSI Escape Codes for Colors
#define WHITE   "\033[37m"
#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"
#define RED     "\033[31m"
#define BOLD    "\033[1m"

using namespace std;



void delay(int timeMs){
    for (int i = 0; i < 30; i++) {
        Sleep(timeMs/30); // Sleep takes time in milliseconds
    }
}    

void animatedPrint(const string& text, int delayMs=30) {
    for (char ch : text) {
        cout << ch << flush;
        Sleep(delayMs);
     
    }
}

string toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
// Function to find LCS length
int lcs(string s1, string s2) {
    s1 = toLowerCase(s1);
    s2 = toLowerCase(s2);
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[m][n];
}

// Suggest products based on LCS
string suggestProduct(string input, vector<string>& products) {
    int maxMatch = 0;
    string bestMatch = "";

    for (auto& product : products) {
        int match = lcs(input, product);
        if (match > maxMatch) {
            maxMatch = match;
            bestMatch = product;
        }
    }
    return bestMatch;
}





class User {
    protected:
        string password;
    public:
        string name;
        string contact;
        string userId;
        User(string id, string n, string c, string p) : userId(id), name(n), contact(c), password(p) {};

       
    };
    

 class UnregisteredUser : public User {
    public:
        UnregisteredUser(string id, string n, string c, string p) : User(id, n, c, p) {};
    
        static UnregisteredUser registerUser() {
            string id, name, contact, password;
        
            cout << CYAN << BOLD << "\n📝 New User Registration Portal\n" << RESET;
            cout << YELLOW << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET;
        
            cout << GREEN << "🔑 Enter User ID     : " << RESET;
            cin >> id;
        
            cout << GREEN << "🙍 Enter Name        : " << RESET;
            cin >> name;
        
            cout << GREEN << "📞 Enter Contact     : " << RESET;
            cin >> contact;
        
            cout << GREEN << "🔐 Enter Password    : " << RESET;
            cin >> password;
        
            UnregisteredUser newUser(id, name, contact, password);
            writeUserToFile(newUser);
        
            cout << YELLOW << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET;

            animatedPrint(GREEN "\n✅ Registration Successful!\n" RESET, 4);
            delay(1000);
            system("cls");
            animatedPrint(BLUE "🎉 Welcome, " + name + "! 🎉\n\n", 4);
        
            return newUser;
        }
        
    
        static void writeUserToFile(const UnregisteredUser& user) {
            ofstream file("users.txt", ios::app);
            file << user.userId << "," << user.name << "," << user.contact << "," << user.password << endl;
            file.close();
        }
   
    };
    
    class RegisteredUser : public User {
    public:
        RegisteredUser(string id, string n, string c, string p) : User(id, n, c, p) {}
    
        static vector<RegisteredUser> readUsersFromFile() {
            vector<RegisteredUser> users;
            ifstream file("users.txt");
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string userId, name, contact, password;
                getline(ss, userId, ',');
                getline(ss, name, ',');
                getline(ss, contact, ',');
                getline(ss, password, ',');
                users.push_back(RegisteredUser(userId, name, contact, password));
            }
            return users;


        }
    
        static bool loginUser(const string& id, const string& password) {
            vector<RegisteredUser> users = readUsersFromFile();
            for (const auto& user : users) {
                if (user.userId == id && user.password == password) {
                    return true;
                }
            }
            return false;
        }

        static RegisteredUser findUserById(const string& userId) {
            vector<RegisteredUser> users = readUsersFromFile();
            for (const auto& user : users) {
                if (user.userId == userId) {
                    return user;
                }
            }
            throw runtime_error("User not found");
        }
    };

class Shop {
    private:
       string password;
    
     public:
     
        string shopId;
        string name;
        string address;
        vector<string> items;
        vector<double> prices;
        vector<int>quantities;

        Shop() {};
        Shop(string id, string n, string a, string p) : shopId(id), name(n), address(a), password(p) {}
        
         static  bool loginShop(string id, string pass){
            vector<Shop> shops = Shop::readShopsFromFile();
           
            for (auto& shop : shops) {
                if (shop.shopId == id && shop.password == pass) {
                    return true;
                }
            }
            return false;
        }

        void addItem(string item, double price,int quantity) {
            items.push_back(item);
            prices.push_back(price);
            quantities.push_back(quantity);
        
            // Read all shops
            vector<Shop> shops = Shop::readShopsFromFile();
            
            // Find current shop and update its items
            for (auto& shop : shops) {
                if (shop.shopId == this->shopId) {
                    shop.items = this->items;
                    shop.prices = this->prices;
                    shop.quantities=  this-> quantities;
                    break;
                }
            }
        
            // Write back to the file
            Shop::updateShopsFile(shops);
        }
        
      
void deleteItem(string item) {
    bool itemFound = false;
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i] == item) {
            items.erase(items.begin() + i);
            prices.erase(prices.begin() + i);
            itemFound = true;
            break;
        }
    }

    if (!itemFound) {
        cout << "Item not found.\n";
        return;
    }

    // Read all shops
    vector<Shop> shops = Shop::readShopsFromFile();

    // Find current shop and update its items
    for (auto& shop : shops) {
        if (shop.shopId == this->shopId) {
            shop.items = this->items;
            shop.prices = this->prices;
            break;
        }
    }

    // Write back to the file
    Shop::updateShopsFile(shops);
}

  
void updateItemPrice(string item, double newPrice) {
    bool itemFound = false;
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i] == item) {
            prices[i] = newPrice;
            itemFound = true;
            break;
        }
    }

    if (!itemFound) {
        cout << "Item not found.\n";
        return;
    }

    // Read all shops
    vector<Shop> shops = Shop::readShopsFromFile();

    // Find current shop and update its items
    for (auto& shop : shops) {
        if (shop.shopId == this->shopId) {
            shop.items = this->items;
            shop.prices = this->prices;
            shop.quantities=  this-> quantities;
            break;
        }
    }

    // Write back to the file
    Shop::updateShopsFile(shops);
}
       

void writeShopToFile() const {
    ofstream file("shops.txt", ios::app);  // Open in append mode
    if (!file.is_open()) {
        cerr << "Error: Unable to open shops.txt\n";
        return;
    }

    // Write shop details
    file << shopId << ',' << name << ',' << address << ',' << password;

    // Write items and prices
    for (size_t i = 0; i < items.size(); ++i) {
        file << ',' << items[i] << ',' << prices[i] <<','<< quantities[i];
    }
    file << '\n';

    file.close();
}


static vector<Shop> readShopsFromFile() {
    vector<Shop> shops;
    ifstream file("shops.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open shops.txt\n";
        return shops;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string shopId, name, address, password;

        // Read shop details
        getline(ss, shopId, ',');
        getline(ss, name, ',');
        getline(ss, address, ',');
        getline(ss, password, ',');

        // Create shop object
        Shop shop(shopId, name, address, password);

        // Read items and prices
        string item;
        double price;
        int quantity;
        while (getline(ss, item, ',') && ss >> price) {
            ss.ignore();  // Ignore comma after price
            ss >> quantity;
            shop.items.push_back(item);
            shop.prices.push_back(price);
            shop.quantities.push_back(quantity);
            if (ss.peek() == ',') ss.ignore();  // Ignore trailing comma if any
        }
        

        shops.push_back(shop);
    }

    file.close();
    return shops;
}

static void updateShopsFile(vector<Shop>& shops) {
            ofstream file("shops.txt", ios::trunc);
            for (auto& shop : shops) {
                file << shop.shopId << "," << shop.name << "," << shop.address << "," << shop.password;
                for (size_t i = 0; i < shop.items.size(); i++) {
                    file << "," << shop.items[i] << "," << shop.prices[i]<< ","<< shop.quantities[i];
                }
                file << endl;
            }
            file.close();
        }


        static Shop findShopById(const string& shopId) {
            vector<Shop> shops = readShopsFromFile();
            for (const auto& shop : shops) {
                if (shop.shopId == shopId) {
                    return shop;
                }
            }
            throw runtime_error("Shop not found");
        }
    
    
};

unordered_map<string, vector<pair<string, int>>> locationGraph;

// Function to read location.txt and build graph
void loadLocations(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open location.txt" << endl;
        return;
    }

    string loc1, loc2;
    int distance;
    while (file >> loc1 >> loc2 >> distance) {
        locationGraph[loc1].push_back({loc2, distance});
        locationGraph[loc2].push_back({loc1, distance});
    }
    file.close();
}

// Dijkstra’s Algorithm to find shortest distance from `start`
unordered_map<string, int> dijkstra(const string& start) {
    unordered_map<string, int> distances;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

    // Initialize distances
    for (const auto& node : locationGraph) {
        distances[node.first] = numeric_limits<int>::max();
    }
    distances[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        pair<int, string> topElement = pq.top();
        int dist = topElement.first;
        string current = topElement.second;
        pq.pop();
        
        for (const auto& edge : locationGraph[current]) {
            string neighbor = edge.first;
            int weight = edge.second;
            
            int newDist = dist + weight;
            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                pq.push({newDist, neighbor});
            }
        }
        
    }
    return distances;
}

void merge(vector<pair<Shop, int>>& shops, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<pair<Shop, int>> leftArray(n1);
    vector<pair<Shop, int>> rightArray(n2);

    for (int i = 0; i < n1; i++)
        leftArray[i] = shops[left + i];
    for (int i = 0; i < n2; i++)
        rightArray[i] = shops[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArray[i].second < rightArray[j].second || 
            (leftArray[i].second == rightArray[j].second && leftArray[i].first.prices[0] < rightArray[j].first.prices[0])) {
            shops[k++] = leftArray[i++];
        } else {
            shops[k++] = rightArray[j++];
        }
    }

    while (i < n1) shops[k++] = leftArray[i++];
    while (j < n2) shops[k++] = rightArray[j++];
}

void mergeSort(vector<pair<Shop, int>>& shops, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(shops, left, mid);
    mergeSort(shops, mid + 1, right);
    merge(shops, left, mid, right);
}




class Booking {
    public:
        string userId;
        string shopId;
        string item;
        double price;
        Booking() {};
        Booking(string uId, string sId, string itm, double pr) : userId(uId), shopId(sId), item(itm), price(pr) {}
        
        friend void generateBookingReceipt(const Booking& booking, const RegisteredUser& user, const Shop& shop);


        static void writeBookingToFile(const Booking& booking) {
            ofstream file("bookings.txt", ios::app);
            file << booking.userId << "," << booking.shopId << "," << booking.item << "," << booking.price << endl;
            file.close();
        }
    
        static vector<Booking> readBookingsFromFile() {
            vector<Booking> bookings;
            ifstream file("bookings.txt");
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string userId, shopId, item;
                double price;
                getline(ss, userId, ',');
                getline(ss, shopId, ',');
                getline(ss, item, ',');
                ss >> price;
                bookings.push_back(Booking(userId, shopId, item, price));
            }
            return bookings;
        }
    
        static void searchAndBookProduct(string userId,const string& userLocation) {
            animatedPrint(CYAN "\n  🔍 Enter product name: " RESET);
            string productName;
            cin.ignore();
            getline(cin, productName);
        
            vector<Shop> shops = Shop::readShopsFromFile();
            vector<pair<Shop, int>> validShops;
            vector<string> products;
            unordered_map<string, int> shopItemIndexMap; 
            for (const auto& shop : shops) {
                for (size_t i = 0; i < shop.items.size(); i++) {
                    products.push_back(shop.items[i]);
                }
            }
            productName = suggestProduct(productName, products);
        
            unordered_map<string, int> shortestPaths = dijkstra(userLocation);
        
            for (const auto& shop : shops) {
                for (size_t i = 0; i < shop.items.size(); i++) {
                    if (shop.items[i] == productName && shop.quantities[i] > 0) {
                        int distance = shortestPaths.count(shop.address) ? shortestPaths[shop.address] : 100;
                        validShops.push_back({shop, distance});
                        shopItemIndexMap[shop.shopId] = i;
                    }
                }
            }
        
            if (validShops.empty()) {
                animatedPrint(RED "\n🚫 Product not found in any nearby shop.\n" RESET);
                return;
            }
        
            mergeSort(validShops, 0, validShops.size() - 1);
        
            animatedPrint(GREEN "\n🏪 Available Shops (Sorted by Price & Distance):\n\n" RESET);
            cout << BOLD << CYAN << "┌────────────────────┬────────────────────┬────────────┬────────────┐\n";
            cout << "│ 🏬 Shop Name        │ 📍 Location         │ 💲 Price    │ 📏 Distance │\n";
            cout << "├────────────────────┼────────────────────┼────────────┼────────────┤" << RESET << endl;
        
            for (const auto& shopData : validShops) {
                const Shop& shop = shopData.first;
                int distance = shopData.second;
        
                cout << CYAN << "│ " << BOLD << shop.name
                     << string(20 - shop.name.length(), ' ') << RESET << CYAN << " │ "
                     << shop.address << string(20 - shop.address.length(), ' ') << " │ "
                     << "$" << fixed << setprecision(2) << shop.prices[0] << "      │ "
                     << distance << " km     │\n";
            }
        
            cout << CYAN << "└────────────────────┴────────────────────┴────────────┴────────────┘\n" RESET;
        
            animatedPrint(YELLOW "\n✏️  Enter the number of the shop you want to book the item from (1 to " + to_string(validShops.size()) + "): " RESET);
            int shopChoice;
            cin >> shopChoice;
        
            if (shopChoice < 1 || shopChoice > validShops.size()) {
                animatedPrint(RED "\n❗ Invalid choice.\n" RESET);
                return;
            }
        
            auto selectedShop = validShops[shopChoice - 1];
            Shop* shopToBookFrom = &selectedShop.first;
            int itemIndex = shopItemIndexMap[selectedShop.first.shopId];
        
            animatedPrint(GREEN "\n🛒 You have selected to book '" + shopToBookFrom->items[itemIndex] + "' from " + shopToBookFrom->name + "\n" RESET);
            animatedPrint(MAGENTA "💰 Price: $" + to_string(shopToBookFrom->prices[itemIndex]) + "\n" RESET);
            animatedPrint(YELLOW "✅ Do you want to proceed? (yes/no): " RESET);
        
            string confirm;
            cin >> confirm;
        
            if (confirm == "yes" || confirm == "Yes") {
                Booking booking(userId, shopToBookFrom->shopId, shopToBookFrom->items[itemIndex], shopToBookFrom->prices[itemIndex]);
                writeBookingToFile(booking);
                shopToBookFrom->quantities[itemIndex]--;
                Shop::updateShopsFile(shops);
        
                try {
                    // Booking b;
                    RegisteredUser user = RegisteredUser::findUserById(userId);
                    Shop shop = Shop::findShopById(shopToBookFrom->shopId);
                    animatedPrint(GREEN "\n🎉 Booking successful!\n" RESET);
                    cout<<GREEN<<"\n Generating recipt....\n";
                    delay(1500);
                    
                    generateBookingReceipt(booking, user, shop);
                    // b.generateBookingReceipt(booking, user, shop);
                    animatedPrint(RED "\n⚠️ Booking will get cancelled after 24 hour! \n ");
                    delay(3500);
                    

                } catch (const runtime_error& e) {
                    animatedPrint(RED "⚠️  Error generating receipt: " + string(e.what()) + "\n" RESET);
                }
        
               
            } else {
                animatedPrint(RED "\n❌ Booking cancelled.\n" RESET);
            }
        }
    
        static void searchAndBookProduct(const string& userLocation) {
            animatedPrint(GREEN "🛒 Enter the product you want to search for: " RESET);
            string productName;
            cin.ignore();
            getline(cin, productName);
        
            vector<Shop> shops = Shop::readShopsFromFile();
            vector<pair<Shop, int>> validShops;
        
            vector<string> products;
            for (const auto& shop : shops) {
                for (size_t i = 0; i < shop.items.size(); i++) {
                    products.push_back(shop.items[i]);
                }
            }
                
            productName = suggestProduct(productName, products);
        
            unordered_map<string, int> shortestPaths = dijkstra(userLocation);
        
            for (const auto& shop : shops) {
                for (size_t i = 0; i < shop.items.size(); i++) {
                    if (shop.items[i] == productName && shop.quantities[i] > 0) {
                        int distance = shortestPaths.count(shop.address) ? shortestPaths[shop.address] : numeric_limits<int>::max();
                      if(distance!= numeric_limits<int>::max())  validShops.push_back({shop, distance});
                    }
                }
            }
        
            if (validShops.empty()) {
                animatedPrint(RED "❌ Sorry! Product not found in any nearby shop.\n" RESET);
                return;
            }
        
            mergeSort(validShops, 0, validShops.size() - 1);
        
            animatedPrint(CYAN "\n📦 Available Shops (Sorted by Price & Distance):\n" RESET, 5);
            cout << BOLD << YELLOW;
            cout << "╔══════════════════════════════════════════════════════════════════════╗\n";
            cout << "║  🏪 Shop Name        📍 Location           💲 Price      📏 Distance (km) ║\n";
            cout << "╠══════════════════════════════════════════════════════════════════════╣\n";
            cout << RESET;
        
            for (const auto& shopData : validShops) {
                const Shop& shop = shopData.first;
                double distance = shopData.second;
        
                cout << "║  " << GREEN << std::setw(16) << std::left << shop.name
                     << CYAN << "  " << std::setw(18) << std::left << shop.address
                     << YELLOW << "  $" << std::fixed << std::setprecision(2) << std::setw(8) << shop.prices[0]
                     << BLUE << "  " << distance << " km" << RESET << "          ║\n";
            }
        
            cout << YELLOW << "╚══════════════════════════════════════════════════════════════════════╝\n" << RESET;
        
            animatedPrint(BLUE "\n📝 Note: Booking is only available for registered users.\n\n" RESET);
        }
        
    };

void generateBookingReceipt(const Booking& booking, const RegisteredUser& user, const Shop& shop) {
            string line = "========================================\n";
            string dashed = "----------------------------------------\n";
        
            animatedPrint(YELLOW + line + RESET, 2);
            animatedPrint(GREEN "         🧾 BOOKING RECEIPT\n" RESET, 3);
            animatedPrint(YELLOW + line + RESET, 2);
        
            animatedPrint(CYAN "📌 Booking Details:\n" RESET, 4);
            animatedPrint(MAGENTA + dashed + RESET, 2);
        
            cout << "👤 Customer      : " << BOLD << user.name << RESET << "  (ID: " << CYAN << user.userId << RESET << ")\n";
            cout << "🏪 Shop          : " << BOLD << shop.name << RESET << "  (ID: " << CYAN << shop.shopId << RESET << ")\n";
            cout << "📦 Item Purchased: " << GREEN << booking.item << RESET << "\n";
            cout << "💲 Price         : " << YELLOW << "$" << std::fixed << std::setprecision(2) << booking.price << RESET << "\n";
        
            animatedPrint(MAGENTA + dashed + RESET, 2);
            animatedPrint(GREEN "🙏 Thank you for your purchase!\n" RESET, 4);
            animatedPrint(YELLOW + line + RESET, 2);
        }

// Function to display the main menu
void mainMenu() {
    system("cls");
    cout << MAGENTA << "\n╔══════════════════════════════════════════════╗\n";
    cout << "║         " << CYAN << "🛍️  RETAILREFORM MAIN MENU  🛍️" << MAGENTA << "         ║\n";
    cout << "╠══════════════════════════════════════════════╣\n";
    cout << "║  " << GREEN << "1." << RESET << " " << YELLOW << "Buyer                                   " << MAGENTA << "║\n";
    cout << "║  " << GREEN << "2." << RESET << " " << YELLOW << "Shop Owner                             " << MAGENTA << "║\n";
    cout << "║  " << GREEN << "3." << RESET << " " << YELLOW << "Exit                                   " << MAGENTA << "║\n";
    cout << "╚══════════════════════════════════════════════╝" << RESET << endl;
    cout << CYAN << "\nPlease enter your choice (1-3): " << RESET;
}

// Function for buyer operations
void buy1Menu() {
    cout << "\n";
    cout << CYAN << "╔════════════════════════════════════════════╗\n";
    cout << "║   🛍️  " << YELLOW << "Welcome to the Buyer Section! " << CYAN << "🛒       ║\n";
    cout << "╠════════════════════════════════════════════╣\n";
    cout << "║  1️⃣  🔐 " << GREEN << "Login to Your Account          " << CYAN << "║\n";
    cout << "║  2️⃣  🆕 " << MAGENTA << "Register as a New User        " << CYAN << "║\n";
    cout << "║  3️⃣  ⏭️  " << BLUE << "Skip for Now and Explore       " << CYAN << "║\n";
    cout << "╚════════════════════════════════════════════╝\n" << RESET;
    cout << YELLOW << "👉 Please enter your choice (1-3): " << RESET;
}
void buyerMenu() {
    cout << CYAN << BOLD << "\n╔════════════════════════════════════════════╗\n";
    cout << "║         🛒  WELCOME TO BUYER MENU         ║\n";
    cout << "╚════════════════════════════════════════════╝\n\n" << RESET;

    animatedPrint(GREEN "1️⃣  Search for a Product 🔍\n");
    animatedPrint(YELLOW "2️⃣  View Past Bookings 📜\n");
    animatedPrint(MAGENTA "3️⃣  Logout 👋\n");
    cout << RESET;
}
// Function for shop owner operations

void shopMenu() {
    cout << CYAN << BOLD << "\n🛒 Welcome to the Shop Portal 🛒\n" << RESET;
    cout << YELLOW << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET;

    animatedPrint(GREEN "1️⃣  Login to your Shop 🧾\n", 4);
    animatedPrint(GREEN "2️⃣  Register a New Shop 🏪\n", 4);

    cout << YELLOW << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET;
}


void shopOwnerMenu() {
    cout << CYAN << BOLD << "\n🧑‍💼 Shop Owner Menu 🛒\n" << RESET;
    cout << YELLOW << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET;

    animatedPrint(GREEN "1️⃣  Add/Delete Items 🛠️\n");
    animatedPrint(GREEN "2️⃣  Update Prices 💵\n");
    animatedPrint(GREEN "3️⃣  View Shop Details 🧾\n");
    animatedPrint(RED   "4️⃣  Logout 🔐\n");

    cout << YELLOW << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET;
    cout << YELLOW << "👉 Please enter your choice (1-4): " << RESET;

}



// Function to display ASCII Art
void showWelcomeScreen() {
    cout << GREEN << R"( 
  ______  _______ _______ _______ _ _          ______  _______ _______ _______ ______  _______ 
 (_____ \(_______|_______|_______) (_)        (_____ \(_______|_______|_______|_____ \(_______)
  _____) )_____      _    _______| |_          _____) )_____   _____   _     _ _____) )_  _  _ 
 |  __  /|  ___)    | |  |  ___  | | |        |  __  /|  ___) |  ___) | |   | |  __  /| ||_|| |
 | |  \ \| |_____   | |  | |   | | | |_____   | |  \ \| |_____| |     | |___| | |  \ \| |   | |
 |_|   |_\\_______)  |_|  |_|   |_|_|_______)  |_|   |_|_______)_|      \_____/|_|   |_|_|   |_|    
    )" << RESET << endl;

    cout << YELLOW << "\n\tWelcome to RETAILREFORM - The Future of Retail!\n" << RESET;
    cout << BLUE << "\n\tInitializing system, please wait...\n" << RESET;
}
// Function to show a simple loading animation
void showLoadingBar(int timeMs) {
    cout << CYAN << "\nLoading: [";
    for (int i = 0; i < 30; i++) {
        cout << "=";
        cout.flush();
        Sleep(timeMs / 30); // Sleep takes time in milliseconds
    }
    cout << "] Done!\n" << RESET;
}





int main() {
    system("chcp 65001");
    loadLocations("location.txt");
    int choice;
    bool outerRunning = true;

    system("cls"); // For Linux/Mac (Use "cls" on Windows)
    showWelcomeScreen();
    showLoadingBar(3000);
    cout << GREEN << "\nSystem Ready! Let's get started...\n" << RESET;

    while (outerRunning) {
        delay(1500);
        mainMenu();
        cin >> choice;
      
       
        switch (choice) {
        case 1: {
            system("cls");
            buy1Menu();
            int option;
            cin>>option;
            if(option==1){
                string userId, password;
                system("cls");
                cout << CYAN << BOLD << "\n🔐 User Login Portal\n" << RESET;
                animatedPrint(GREEN "🆔 Enter User ID: ");
                cin >> userId;

                animatedPrint(YELLOW "🔑 Enter Password: ");
                cin >> password;

                cout << CYAN << "\n\n✨ Logging you in, please wait..." << RESET << endl;
                delay(2000);
                
                system("cls");

                
                //After Login
                bool innerRunning1 = true;
                if (RegisteredUser::loginUser(userId, password)) {
                    cout << CYAN << BOLD<< "🎉🎉 Congratulations,you are successfully logged in !" << RESET << endl;
                    while(innerRunning1){ 
                      
                        buyerMenu();
                        int buyerChoice;
                        cin >> buyerChoice;
                        if (buyerChoice == 1) { // Search for a product
                            string userLocation;
                            system("cls");
                            cout << CYAN << BOLD << "\n🔎 Search Bar:\n" << RESET;
                            animatedPrint(YELLOW "📍 Enter your current location: ");
                            cin >> userLocation;
                            cout << GREEN << "✅ Location set to: " << userLocation << RESET << "\n";
                        
                            Booking::  searchAndBookProduct(userId,userLocation);
                            
                        }
                        else if (buyerChoice == 2) { // View Past Bookings
                            vector<Booking> bookings = Booking::readBookingsFromFile();
                                bool found = false;
                                system("cls");
                                animatedPrint(BOLD CYAN "\n🕒 Fetching Your Past Bookings...\n\n" RESET, 4);
                                
                                for (const auto& booking : bookings) {
                                    if (booking.userId == userId) {
                                        found = true;

                                        cout << YELLOW << "🧾 ─────────────────────────────────────" << RESET << "\n";
                                        cout << GREEN << "📦 Item       : " << RESET << booking.item << "\n";
                                        cout << BLUE  << "💲 Price      : " << RESET << "$" << std::fixed << std::setprecision(2) << booking.price << "\n";
                                        cout << MAGENTA << "🆔 Booking By : " << RESET << booking.userId << "\n";
                                        cout << YELLOW << "🧾 ─────────────────────────────────────" << RESET << "\n\n";
                                        
                                    }
                                }

                                if (!found) {
                                    animatedPrint(RED "\n🚫 No bookings found under your account.\n" RESET, 4);
                                }
                        }
                        else{
                            innerRunning1=false;
                        }
                    }  
                
                } else {
                    animatedPrint(RED "\n🚫 Invalid login credentials.\n" RESET, 4);
                    
                }
                break;      
          }        
            else if(option==2){
                UnregisteredUser user = UnregisteredUser ::registerUser();
                string userId = user.userId;
                // string password = user.password;
                 bool innerRunning2 = true;
               while(innerRunning2){

               
                //After Registration
                buyerMenu();
                int buyerChoice;
                cin >> buyerChoice;
                if (buyerChoice == 1) { // Search for a product
                    string userLocation;
                    system("cls");
                    cout << CYAN << BOLD << "\n🔎 Search Bar:\n" << RESET;
                    animatedPrint(YELLOW "📍 Enter your current location: ");
                    cin >> userLocation;
                    cout << GREEN << "✅ Location set to: " << userLocation << RESET << "\n";
                
                    Booking::  searchAndBookProduct(userId,userLocation);
                    system("cls");
                }
                else if (buyerChoice == 2) { // View Past Bookings
                    vector<Booking> bookings = Booking::readBookingsFromFile();
                        bool found = false;
                        system("cls");
                        animatedPrint(BOLD CYAN "\n🕒 Fetching Your Past Bookings...\n\n" RESET, 4);
                        
                        for (const auto& booking : bookings) {
                            if (booking.userId == userId) {
                                found = true;

                                cout << YELLOW << "🧾 ─────────────────────────────────────" << RESET << "\n";
                                cout << GREEN << "📦 Item       : " << RESET << booking.item << "\n";
                                cout << BLUE  << "💲 Price      : " << RESET << "$" << std::fixed << std::setprecision(2) << booking.price << "\n";
                                cout << MAGENTA << "🆔 Booking By : " << RESET << booking.userId << "\n";
                                cout << YELLOW << "🧾 ─────────────────────────────────────" << RESET << "\n\n";
                                
                            }
                        }

                        if (!found) {
                            animatedPrint(RED "\n🚫 No bookings found under your account.\n" RESET, 4);
                        }
                }
                else {
                    innerRunning2 = false;
                }
            }
            }
            else{
                string userLocation;
                    system("cls");
                    cout << CYAN << BOLD << "\n🔎 Search Bar:\n" << RESET;
                    animatedPrint(YELLOW "📍 Enter your current location: ");
                    cin >> userLocation;
                    cout << GREEN << "✅ Location set to: " << userLocation << RESET << "\n";
                bool innerRunning3 = true;
               while(innerRunning3){
                Booking::  searchAndBookProduct(userLocation);
                   
                   int num;
                   cout <<GREEN<<"\n\n To stop searching please enter 1:";
                   cin>>num;
                   if(num==1){
                      innerRunning3 = false;
                   }
                   system("cls");
               }
            }   
        
            break;
            
        }
     case 2: { // Login as Shop Owner
          
                    
                    int choice;
                  
                    vector<Shop> shops = Shop::readShopsFromFile();  // Read shops once at start
                    shopMenu();
                  
                    cin >> choice;
                   
                    

                    if (choice == 1) {
                    // Login Flow
                    string shopId, password;
                    system("cls");
                    cout << CYAN << BOLD << "\n🔐 Shop Owner Login\n" << RESET;
                    cout << YELLOW << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET;
                    
                    cout << GREEN << "🆔 Enter Shop ID: " << RESET;
                    cin >> shopId;
                    cout << GREEN << "🔑 Enter Password: " << RESET;
                    cin >> password;
                    
                    Shop* currentShop = nullptr;
              
                    bool isLogin=  Shop::loginShop(shopId,password);
                   if(isLogin){
                    for (auto& shop : shops) {
                        if (shop.shopId == shopId ) {
                            currentShop = &shop;
                            break;
                        }
                    }
                   }
                    
                    
                    if (!currentShop) {
                        cout << RED << "❌ Invalid credentials. Please try again.\n" << RESET;
                        continue;
                    }
                    
                    bool shopRunning = true;
                    cout << GREEN << "🎉🎉Logged in successfully!\n\n"  << RESET;
                    delay(500);
                    system("cls");
                    while (shopRunning) {
                        // system("cls");
                       
                        shopOwnerMenu(); 
                        int shopChoice;
                        cin >> shopChoice;
                         
                        system("cls");
                        switch (shopChoice) {
                           
                            case 1: {
                                cout << BLUE << "\n🛍️ Item Management\n\n";
                                cout << "1️⃣  Add Item\n2️⃣  Delete Item\n" << RESET;
                                cout << GREEN << "Select option: " << RESET;
                                int itemChoice;

                                cin >> itemChoice;
                    
                                if (itemChoice == 1) {
                                    string item;
                                    double price;
                                    int quantity;
                                    cout << GREEN << "📦 Enter item name: " << RESET;
                                    cin >> item;
                                    cout << GREEN << "💰 Enter price: " << RESET;
                                    cin >> price;
                                    cout << GREEN << "🔢 Enter quantity: " << RESET;
                                    cin >> quantity;
                                    currentShop->addItem(item, price, quantity);
                                    cout << CYAN << "✅ Item added successfully!\n" << RESET;
                                } else {
                                    string item;
                                    cout << RED << "🗑️ Enter item name to delete: " << RESET;
                                    cin >> item;
                                    currentShop->deleteItem(item);
                                    cout << CYAN << "✅ Item deleted successfully!\n" << RESET;
                                }
                                break;
                            }
                            case 2: {
                                string item;
                                double newPrice;
                                cout << GREEN << "✏️ Enter item name to update price: " << RESET;
                                cin >> item;
                                cout << GREEN << "💵 Enter new price: " << RESET;
                                cin >> newPrice;
                                currentShop->updateItemPrice(item, newPrice);
                                cout << CYAN << "✅ Price updated successfully!\n" << RESET;
                                break;
                            }
                            case 3: {
                                cout << CYAN << "\n🏪 Shop Details\n" << RESET;
                                cout << YELLOW << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET;
                                cout <<GREEN<< "📛 Name: " << currentShop->name <<RESET<< "\n";
                                cout <<RED<< "📍 Address: " << currentShop->address<<RESET << "\n";
                                cout <<BLUE<< "📦 Items Available:\n"<<RESET;
                                for (size_t i = 0; i < currentShop->items.size(); i++) {
                                    cout << "   - " << currentShop->items[i]
                                         << " | Price: $" << fixed << setprecision(2) << currentShop->prices[i]
                                         << " | Quantity: " << currentShop->quantities[i] << "\n";
                                }
                                cout << YELLOW << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET;
                                delay(2000);
                                break;
                            }
                            case 4: {
                                cout << RED << "\n🔓 Logging out...\n" << RESET;
                                delay(1000);
                                system("cls");
                                shopRunning = false;
                                break;
                            }
                            default:
                                cout << RED << "❌ Invalid choice. Please try again.\n" << RESET;
                                break;
                        }
                    }
                    
                    }

                 else if (choice == 2) {
                         // Registration Flow
                         string shopId, name, address, password;
                         system("cls");

                         cout << CYAN << BOLD << "\n🏪 Shop Registration\n" << RESET;
                         cout << YELLOW << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET;
                         
                         cout << GREEN << "🆔 Enter Shop ID: " << RESET;
                         cin >> shopId;
                         
                         cout << GREEN << "📛 Enter Shop Name: " << RESET;
                         cin >> name;
                         
                         cout << GREEN << "📍 Enter Shop Address: " << RESET;
                         cin >> address;
                         
                         cout << GREEN << "🔐 Set Password: " << RESET;
                         cin >> password;
                         
                         Shop newShop(shopId, name, address, password);
                         shops.push_back(newShop);
                         newShop.writeShopToFile();
                         Shop* currentShop = &shops.back();
                         
                         cout << CYAN << "\n✅ Shop registered successfully!\n" << RESET;
                         delay(1500);
                         system("cls");
                         bool shopRunning = true;
                         while (shopRunning) {
                             shopOwnerMenu(); 
                         
                             int shopChoice;
                             cin >> shopChoice;
                             
                             system("cls");
                             switch (shopChoice) {
                                 case 1: {
                                     cout << BLUE << "\n🛍️ Item Management\n\n";
                                     cout << "1️⃣  Add Item\n2️⃣  Delete Item\n" << RESET;
                                     cout << GREEN << "Select option: " << RESET;
                                     int itemChoice;
                                     cin >> itemChoice;
                                  
                                     if (itemChoice == 1) {
                                         string item;
                                         double price;
                                         int quantity;
                         
                                         cout << GREEN << "📦 Enter item name: " << RESET;
                                         cin >> item;
                         
                                         cout << GREEN << "💰 Enter price: " << RESET;
                                         cin >> price;
                         
                                         cout << GREEN << "🔢 Enter quantity: " << RESET;
                                         cin >> quantity;
                         
                                         currentShop->addItem(item, price, quantity);
                                         cout << CYAN << "✅ Item added successfully!\n" << RESET;
                         
                                     } else {
                                         string item;
                                         cout << RED << "🗑️ Enter item name to delete: " << RESET;
                                         cin >> item;
                                         currentShop->deleteItem(item);
                                         cout << CYAN << "✅ Item deleted successfully!\n" << RESET;
                                     }
                                     break;
                                 }
                                 case 2: {
                                     string item;
                                     double newPrice;
                         
                                     cout << GREEN << "✏️ Enter item name: " << RESET;
                                     cin >> item;
                         
                                     cout << GREEN << "💵 Enter new price: " << RESET;
                                     cin >> newPrice;
                         
                                     currentShop->updateItemPrice(item, newPrice);
                                     cout << CYAN << "✅ Price updated successfully!\n" << RESET;
                                     break;
                                 }
                                 case 3: {
                                     system("cls");
                                     cout << CYAN << "\n📋 Shop Details\n" << RESET;
                                     cout << YELLOW << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET;
                         
                                     cout << "📛 Name: " << currentShop->name << "\n";
                                     cout << "📍 Address: " << currentShop->address << "\n";
                                     cout << "🛒 Items Available:\n";
                         
                                     for (size_t i = 0; i < currentShop->items.size(); i++) {
                                         cout << "   • " << currentShop->items[i]
                                              << " | Price: $" << fixed << setprecision(2) << currentShop->prices[i]
                                              << " | Quantity: " << currentShop->quantities[i] << "\n";
                                     }
                         
                                     cout << YELLOW << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET;
                                     break;
                                 }
                                 case 4: {
                                     cout << RED << "\n👋 Logging out from shop dashboard...\n" << RESET;
                                     shopRunning = false;
                                     break;
                                 }
                                 default:
                                     cout << RED << "❌ Invalid choice. Try again!\n" << RESET;
                                     break;
                             }
                         }
                         
                     
                
             }
             
                break;
             }
             
             case 3:{
                cout << YELLOW << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET;
                cout << MAGENTA << BOLD << "🙏 Thank you for using our System!\n" << RESET;
                cout << CYAN << "We hope you had a smooth and productive experience.\n";
                cout << "Don't forget to come back for managing your product Search or Business! 😊\n" << RESET;
                cout << YELLOW << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n" << RESET;
                delay(1000);
                outerRunning=false;
             } 

    }
        

} 
    return 0;
}