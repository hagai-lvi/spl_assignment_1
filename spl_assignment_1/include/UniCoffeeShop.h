//
//  file name: UniCoffeeShop.h
//  project: spl_assignment_1
//  Ilya Morgenshtern and Hagai Levi
//

#include <sstream>
#include <iostream>
#include<vector>
#include<cstring>
#include<fstream>
#include<string.h>
#include <string>
#include <stdlib.h>
using namespace std;

#ifndef _UniCoffeeShop_h
#define _UniCoffeeShop_h

struct Ingredient {
    std::string supplier;
    std::string name;
    double price;
    bool isIncluded;
};
struct Product{
    std::string name;
    std::vector<Ingredient*> ingredients;
    double finalPrice;
};

/**
 * Goes through the products.conf file, and for each product in this file, checks it's final price.
 * If the product meets the requirments (price<=5), the method adds it to the result vector.
 * @param products contain each line from the 'products.conf' file in a different line.
 * @param ingredients is the output of the readIngredients function.
 */
vector<Product> makeTheMenu(vector<Ingredient> ingredients, vector<string> products);

/**
 * Reads the file suplliers.conf and inserts only the cheapest supllier into this vector.
 */
vector<Ingredient> readIngredients(vector<string> vec);

/**
 * Gets the menu (which is vector<product>) and writes it to file Menu.out
 * and prints the ShoppingList.out file according to the items in the menu.
 */
vector<string> writeTheOutput(vector<Product> menu);

/*
 * Calculates the final price of a certain product based on it's ingredients
 * formula is: (sum(ingredients's prices) + labor)*1.5 when 'labor'=1
 */
void calculateFinalPrice(Product& product);

/*
 * Writes the file described by 'toWrite'
 * @param toWrite a vector<string> repersentation of the file that we want to write.
 * @param fileName the path in which we want to write the file.
 */
void writefile_H(vector<string> toWrite ,string fileName);

/*
 * Reads the file that is in the 'filename' path.
 * @return a vector<string> representaion of the file, in which each line is in a new cell of the vector.
 */
vector<string> readfile_H(string fileName);

/** splits a string into a vector of string in each place that has a ','.
 *  returns an empty string if it's an empty line.
 */
vector<string> split_string(string str);

/**
 * Looks for an ingredient with a certain name in the vector and returns it if it exists.
 * If it doesn't exist, returns NULL.
 */
Ingredient* searchForIngredient(vector<Ingredient> ingredients, string ingredientName);

/**
 *  Reads the vector<string> that represents the suppliers.conf file, and inserts into the result vector only the cheapes ones.
 */
vector<Ingredient> newReadIngredients(vector<string> suplliers);


#endif
