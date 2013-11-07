
#include <sstream>
#include <iostream>
#include<vector>
#include<cstring>
#include<fstream>
#include<string.h>
#include <string>
#include <stdlib.h>
#include "../include/UniCoffeeShop.h"
using namespace std;


int main(int argc, char *argv[]) {
	
	vector<string> suppliers = readfile_H("../Suppliers.conf");//reads the file
	cout << "******************************** PRINTING THE SUPPLIERS'S VECTOR" << endl;
	for (int i=0 ; i<suppliers.size(); i++) {
		cout << suppliers[i] << endl;
	}
	cout << "******************************** Finished printing the suplliers's vector " << endl;
	
	vector<Ingredient> ingredients = newReadIngredients(suppliers);
	cout <<"******************************** PRINTING THE INGREDIENTS'S VECTOR" <<endl;
	cout << "ingredients.size()" << ingredients.size() << endl;
	for (int i=0; i<ingredients.size(); i++) {
		cout << ingredients[i].name<< " " << ingredients[i].price << " from supplier " << ingredients[i].supplier << endl;
	}
	cout <<"******************************** Finished printing the ingredients's vector" << endl;
	
	
	vector<string> productsString = readfile_H("../Products.conf");//reads the file
	cout <<"******************************** PRINTING THE PRODUCTS_STRING VECTOR" <<endl;
	cout << "productsString.size() = " << productsString.size() << endl;
	for (int i=0; i<productsString.size(); i++) {
		cout << productsString[i] << endl;
	}
	cout <<"******************************** Finished printing the productsString vector" << endl;
	
	vector<Product> products = makeTheMenu(ingredients, productsString);
	cout <<"******************************** PRINTING THE MENU VECTOR" <<endl;
	cout << "products.size() = " << products.size() << endl;
	for (int i=0; i<products.size(); i++) {
		cout << products[i].name << ", ingredients: ";
		for (int j=0 ; j<products[i].ingredients.size() ; j++) {
			cout << products[i].ingredients[j]->name << ", ";
		}
		cout << products[i].finalPrice << endl;
	}
	cout <<"******************************** Finished printing the productsString vector" << endl;
	
	vector<string> output = writeTheOutput(products);
	
	writefile_H(output ,"Menu.out");
	
	return 0;
}

