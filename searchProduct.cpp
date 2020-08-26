#include<bits/stdc++.h>
using namespace std;

class Inventory;
class Product;
class ProductSpec;

class Inventory {
    private:
    map<string, Product> product_list;
    public:
    void addProduct(string serialNum, double price, ProductSpec &spec){
        Product product(serialNum, price, spec);//constructor?
        product_list[serialNum] = product;
    }
    Product* getProduct(string number){
        for(map<string, product>::iterator it = product_list.begin(); it != product_list.end()){
            if ((*it).serialNum == number){
                return *it;
            }
        }
        return nullptr;
    }
    vector<Product> searchProduct(ProductSpec spec){
        //search logic
        vector<Product> results;
        map<string, Attr> attrTarget = spec.getProperties();
        for(map<string, product>::iterator it = product_list.begin(); it != product_list.end(); it++){
            Product _product = (*it)->second;
            ProductSpec _spec = _product.getSpec();
            //5 attrs: pBrand, pType, priceSpan, pSize, pCPU, pSubclass
            map<string, Attr> _attr = _spec.getProperties();

            bool isTarget = true;
            for(map<string, Attr>::iterator it = _attr.begin(); it != _attr.end(); it++){
                string attrName = (*it)->first; //
                if(_attr[attrName] != attrTarget[attrName]){
                    isTarget = false;
                    break;
                }
            }
            if(isTarget){
                results.push_back(_product);
            }
            else{
                continue;
            }
        }
        return results;
    }
};

class Product {
    private:
    string serialNum;
    double price;
    ProductSpec spec;
    public:
    Product(string number, double _price, ProductSpec _spec) : serialNum(number), price(_price), spec(_spec){}
    ProductSpec getSpec(){
        return this->spec;
    }
    string getSerialNum(){
        return this->serialNum;
    }
    void printProduct(){
        cout << "SerialNumer: " << this->getSerialNum() << endl;
    }
};

class ProductSpec {
    private:
    map<string, string> properties;
    public:
    ProductSpec(ProductSpec _spec){
        this->properties = _spec.properties;
    }
    Attr getProperty(string name) {
        return properties[name];
    }
    map<string, Attr> getProperties(){
        return this->properties;
    }
    void setProperty(string attrName, string attrVal){
        properties[attrName] = attrVal;
    }
};

int main(){
    Inventory inventory;

    ProductSpec spec1;
    spec1.setProperty("pBrand", "Lenove");
    spec1.setProperty("pType", "computer");
    spec1.setProperty("priceSpan", "cheap");
    spec1.setProperty("pSize", "24");
    spec1.setProperty("pCPU", "i5");
    spec1.setProperty("pSubclass", "game");

    Product product1("ABC", 5000, spec1);
    inventory.addProduct(product1);
    
    ProductSpec _spec;
    spec1.setProperty("pType", "computer");
    spec1.setProperty("priceSpan", "cheap");
    spec1.setProperty("pSize", "24");
    spec1.setProperty("pCPU", "i5");

    vector<Product> results = inventory.searchProduct(_spec);
    if(results.size() == 0)
        cout << "No such product !" << endl;
    else{
        for(vector<Product>::iterator it = results.begin(); it != results.end(); it++){
            (*it).printProduct();
        }
    }
    return 0;   
}