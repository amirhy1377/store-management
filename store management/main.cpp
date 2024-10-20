#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <stdexcept>

enum class ProductCategory {
    Food,
    NonFood,
    Electronics,
    Clothing,
    Home,
    Sports,
    Books
};

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
};

int main() {
    Store store;

    // افزودن محصولات مختلف به فروشگاه
    store.addProduct(Product("سیب", 1000, 50, ProductCategory::Food));
    store.addProduct(Product("شیر", 800, 30, ProductCategory::Food));
    store.addProduct(Product("شامپو", 2000, 20, ProductCategory::NonFood));
    store.addProduct(Product("گوشی همراه", 5000000, 10, ProductCategory::Electronics));
    store.addProduct(Product("کتاب داستان", 15000, 25, ProductCategory::Books));
    store.addProduct(Product("کتانی", 300000, 15, ProductCategory::Clothing));
    store.addProduct(Product("مبل", 2000000, 5, ProductCategory::Home));
    store.addProduct(Product("وزنه", 50000, 10, ProductCategory::Sports));

    // نمایش محصولات موجود
    store.displayProducts();

    // فروش یک محصول
    try {
        store.sellProduct("سیب", 5);
        store.displayProducts();
    } catch (const std::exception& e) {
        std::cerr << "خطا: " << e.what() << std::endl;
    }

    return 0;
}
