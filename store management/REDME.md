The code above is a simple store management program written in C++ that allows the user to manage products, including adding, selling, and displaying them. Here’s a detailed explanation of the different parts of the code:



1. Including Libraries
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <stdexcept>
iostream: For input and output operations (e.g., std::cout and std::cin).
vector: For using dynamic arrays.
string: For using string variables.
fstream: For working with file input and output (reading and writing).
sstream: For processing strings.
map: For using dictionaries (key-value pairs).
stdexcept: For handling exceptions (error management).



2. Defining Product Categories
enum class ProductCategory {
    Food,
    NonFood,
    Electronics,
    Clothing,
    Home,
    Sports,
    Books
};
This section defines a new data type called ProductCategory which includes different types of products.





3. Product Class

class Product {
public:
    std::string name;
    float price;
    int quantity;
    ProductCategory category;

    Product(const std::string& n, float p, int q, ProductCategory c)
        : name(n), price(p), quantity(q), category(c) {}

    std::string getCategoryString() const {
        switch (category) {
            case ProductCategory::Food: return "غذایی";
            case ProductCategory::NonFood: return "غیر غذایی";
            case ProductCategory::Electronics: return "الکترونیکی";
            case ProductCategory::Clothing: return "پوشاک";
            case ProductCategory::Home: return "خانگی";
            case ProductCategory::Sports: return "ورزشی";
            case ProductCategory::Books: return "کتاب";
            default: return "ناشناخته";
        }
    }
};
Class Members:

name: The name of the product.
price: The price of the product.
quantity: The available quantity of the product.
category: The category of the product.
Constructor: The constructor Product initializes the class members with provided values.

Method getCategoryString: This method returns the category name in Persian.



4. Store Class
class Store {
private:
    std::map<std::string, Product> products;

public:
    void addProduct(const Product& product) {
        products[product.name] = product;
    }

    void sellProduct(const std::string& productName, int quantitySold) {
        auto it = products.find(productName);
        if (it == products.end()) {
            throw std::runtime_error("محصول یافت نشد");
        }

        if (it->second.quantity >= quantitySold) {
            it->second.quantity -= quantitySold;
            std::cout << "محصول '" << productName << "' به مقدار " << quantitySold << " فروخته شد." << std::endl;
        } else {
            throw std::runtime_error("موجودی کافی نیست");
        }
    }

    void displayProducts() const {
        std::cout << "محصولات موجود:\n";
        for (const auto& pair : products) {
            const Product& product = pair.second;
            std::cout << "نام: " << product.name
                      << ", قیمت: " << product.price
                      << ", مقدار: " << product.quantity
                      << ", دسته‌بندی: " << product.getCategoryString() << std::endl;
        }
    }

    void saveToFile(const std::string& filename = "products.txt") {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("خطا در باز کردن فایل برای نوشتن");
        }
        for (const auto& pair : products) {
            const Product& product = pair.second;
            file << product.name << "," << product.price << "," << product.quantity << "," << static_cast<int>(product.category) << "\n";
        }
        file.close();
    }

    void loadFromFile(const std::string& filename = "products.txt") {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("خطا در باز کردن فایل برای خواندن");
        }
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name;
            float price;
            int quantity;
            int categoryInt;
            std::getline(ss, name, ',');
            ss >> price;
            ss.ignore();
            ss >> quantity;
            ss.ignore();
            ss >> categoryInt;
            addProduct(Product(name, price, quantity, static_cast<ProductCategory>(categoryInt)));
        }
        file.close();
    }
};
Class Members:

products: A map for storing products with their names as keys.
Method addProduct: Adds a product to the store.

Method sellProduct: Handles selling a product. It checks if the product exists, if the quantity sold is valid, and if there is enough stock. If any conditions fail, it throws an exception.

Method displayProducts: Displays the list of available products in the store.

Method saveToFile: Saves the existing products to a file.

Method loadFromFile: Loads products from a file.




5. Main Function
int main() {
    Store store;

    // Adding various products to the store
    try {
        store.addProduct(Product("سیب", 1000, 50, ProductCategory::Food));
        store.addProduct(Product("شیر", 800, 30, ProductCategory::Food));
        store.addProduct(Product("شامپو", 2000, 20, ProductCategory::NonFood));
        store.addProduct(Product("گوشی همراه", 5000000, 10, ProductCategory::Electronics));
        store.addProduct(Product("کتاب داستان", 15000, 25, ProductCategory::Books));
        store.addProduct(Product("کتانی", 300000, 15, ProductCategory::Clothing));
        store.addProduct(Product("مبل", 2000000, 5, ProductCategory::Home));
        store.addProduct(Product("وزنه", 50000, 10, ProductCategory::Sports));
    } catch (const std::exception& e) {
        std::cerr << "خطا: " << e.what() << std::endl;
    }

    // Display available products
    store.displayProducts();

    // Selling a product
    try {
        store.sellProduct("سیب", 5);
        store.displayProducts();
    } catch (const std::exception& e) {
        std::cerr << "خطا: " << e.what() << std::endl;
    }

    // Saving to file
    try {
        store.saveToFile();
    } catch (const std::exception& e) {
        std::cerr << "خطا: " << e.what() << std::endl;
    }

    return 0;
}
Creating a Store Object: A new store object is created initially.

Adding Products: Various products are added to the store inside a try block. If there is a product with a duplicate name, an error message is printed.

Displaying Available Products: After adding products, the available product list is displayed.

Selling a Product: The program sells a product named "سیب" (apple) in a quantity of 5 and then displays the product list again.

Saving to File: Finally, the existing products in the store are saved to a file.

Conclusion
This program serves as a simple system for managing products in a store, which can be further developed for various applications. Additional features like searching for products, editing product information, and a graphical user interface (GUI) could also be added to enhance the system.








کد بالا یک برنامه مدیریت فروشگاه ساده به زبان C++ است که به کاربر اجازه می‌دهد محصولات را مدیریت کند، از جمله افزودن، فروش و نمایش محصولات. در ادامه، بخش‌های مختلف کد را شرح می‌دهیم:

1. شامل کردن کتابخانه‌ها

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <stdexcept>
iostream: برای ورودی و خروجی (مانند std::cout و std::cin).
vector: برای استفاده از آرایه‌های دینامیک.
string: برای استفاده از رشته‌ها.
fstream: برای کار با فایل‌ها (خواندن و نوشتن).
sstream: برای پردازش رشته‌ها.
map: برای استفاده از دیکشنری‌ها (جفت‌های کلید-مقدار).
stdexcept: برای استفاده از استثناها (برای مدیریت خطاها).
2. تعریف دسته‌بندی محصولات
enum class ProductCategory {
    Food,
    NonFood,
    Electronics,
    Clothing,
    Home,
    Sports,
    Books
};
این قسمت یک نوع داده جدید به نام ProductCategory تعریف می‌کند که شامل انواع مختلف محصولات است.
3. کلاس Product
class Product {
public:
    std::string name;
    float price;
    int quantity;
    ProductCategory category;

    Product(const std::string& n, float p, int q, ProductCategory c)
        : name(n), price(p), quantity(q), category(c) {}

    std::string getCategoryString() const {
        switch (category) {
            case ProductCategory::Food: return "غذایی";
            case ProductCategory::NonFood: return "غیر غذایی";
            case ProductCategory::Electronics: return "الکترونیکی";
            case ProductCategory::Clothing: return "پوشاک";
            case ProductCategory::Home: return "خانگی";
            case ProductCategory::Sports: return "ورزشی";
            case ProductCategory::Books: return "کتاب";
            default: return "ناشناخته";
        }
    }
};
اعضای کلاس:

name: نام محصول.
price: قیمت محصول.
quantity: مقدار موجود از محصول.
category: دسته‌بندی محصول.
سازنده: سازنده Product برای مقداردهی اولیه اعضای کلاس استفاده می‌شود.

متد getCategoryString: این متد نام دسته‌بندی محصول را به زبان فارسی برمی‌گرداند.

4. کلاس Store
class Store {
private:
    std::map<std::string, Product> products;

public:
    void addProduct(const Product& product) {
        // بررسی وجود محصول با نام مشابه
        if (products.find(product.name) != products.end()) {
            throw std::runtime_error("محصول با نام مشابه وجود دارد");
        }
        products[product.name] = product;
    }

    void sellProduct(const std::string& productName, int quantitySold) {
        if (quantitySold <= 0) {
            throw std::runtime_error("مقدار فروش باید بزرگتر از صفر باشد");
        }

        auto it = products.find(productName);
        if (it == products.end()) {
            throw std::runtime_error("محصول یافت نشد");
        }

        if (it->second.quantity >= quantitySold) {
            it->second.quantity -= quantitySold;
            std::cout << "محصول '" << productName << "' به مقدار " << quantitySold << " فروخته شد." << std::endl;
        } else {
            throw std::runtime_error("موجودی کافی نیست");
        }
    }

    void displayProducts() const {
        std::cout << "محصولات موجود:\n";
        for (const auto& pair : products) {
            const Product& product = pair.second;
            std::cout << "نام: " << product.name
                      << ", قیمت: " << product.price
                      << ", مقدار: " << product.quantity
                      << ", دسته‌بندی: " << product.getCategoryString() << std::endl;
        }
    }

    void saveToFile(const std::string& filename = "products.txt") {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("خطا در باز کردن فایل برای نوشتن");
        }
        for (const auto& pair : products) {
            const Product& product = pair.second;
            file << product.name << "," << product.price << "," << product.quantity << "," << static_cast<int>(product.category) << "\n";
        }
        file.close();
    }

    void loadFromFile(const std::string& filename = "products.txt") {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("خطا در باز کردن فایل برای خواندن");
        }
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name;
            float price;
            int quantity;
            int categoryInt;
            std::getline(ss, name, ',');
            ss >> price;
            ss.ignore();
            ss >> quantity;
            ss.ignore();
            ss >> categoryInt;
            addProduct(Product(name, price, quantity, static_cast<ProductCategory>(categoryInt)));
        }
        file.close();
    }
};
اعضای کلاس:

products: یک دیکشنری برای ذخیره محصولات به همراه نام آن‌ها.
متد addProduct: برای افزودن محصول به فروشگاه. اگر محصولی با نام مشابه وجود داشته باشد، استثنای مربوطه پرتاب می‌شود.

متد sellProduct: برای فروش محصول. اگر مقدار فروش منفی یا صفر باشد، یا محصول وجود نداشته باشد یا موجودی کافی نباشد، استثنای مربوطه پرتاب می‌شود.

متد displayProducts: برای نمایش لیست محصولات موجود در فروشگاه.

متد saveToFile: برای ذخیره محصولات موجود در فایل.

متد loadFromFile: برای بارگذاری محصولات از فایل.

5. تابع main
int main() {
    Store store;

    // افزودن محصولات مختلف به فروشگاه
    try {
        store.addProduct(Product("سیب", 1000, 50, ProductCategory::Food));
        store.addProduct(Product("شیر", 800, 30, ProductCategory::Food));
        store.addProduct(Product("شامپو", 2000, 20, ProductCategory::NonFood));
        store.addProduct(Product("گوشی همراه", 5000000, 10, ProductCategory::Electronics));
        store.addProduct(Product("کتاب داستان", 15000, 25, ProductCategory::Books));
        store.addProduct(Product("کتانی", 300000, 15, ProductCategory::Clothing));
        store.addProduct(Product("مبل", 2000000, 5, ProductCategory::Home));
        store.addProduct(Product("وزنه", 50000, 10, ProductCategory::Sports));
    } catch (const std::exception& e) {
        std::cerr << "خطا: " << e.what() << std::endl;
    }

    // نمایش محصولات موجود
    store.displayProducts();

    // فروش یک محصول
    try {
        store.sellProduct("سیب", 5);
        store.displayProducts();
    } catch (const std::exception& e) {
        std::cerr << "خطا: " << e.what() << std::endl;
    }

    // ذخیره به فایل
    try {
        store.saveToFile();
    } catch (const std::exception& e) {
        std::cerr << "خطا: " << e.what() << std::endl;
    }

    return 0;
}
ایجاد یک شی از کلاس Store: در ابتدا یک فروشگاه جدید ایجاد می‌شود.

افزودن محصولات: درون یک بلوک try، چند محصول به فروشگاه اضافه می‌شوند. اگر محصولی با نام مشابه وجود داشته باشد، خطا چاپ می‌شود.

نمایش محصولات موجود: بعد از افزودن محصولات، لیست محصولات موجود نمایش داده می‌شود.

فروش یک محصول: در این قسمت، محصولی به نام "سیب" به مقدار 5 فروخته می‌شود و سپس دوباره لیست محصولات نمایش داده می‌شود.

ذخیره به فایل: در انتها، محصولات موجود در فروشگاه به یک فایل ذخیره می‌شوند.

نتیجه‌گیری
این برنامه یک سیستم ساده برای مدیریت محصولات در یک فروشگاه است که می‌تواند برای کاربردهای مختلف توسعه یابد. قابلیت‌های بیشتری مانند اضافه کردن جستجوی محصولات، ویرایش اطلاعات محصول و غیره نیز می‌تواند به این سیستم افزوده شود. 





