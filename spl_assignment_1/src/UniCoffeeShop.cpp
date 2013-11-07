//
//  UniCoffeeShop.cpp
//  spl_assignment_1
//
//  Created by Hagai Levi on 11/7/13.
//  Copyright (c) 2013 Hagai Levi. All rights reserved.
//

#include "../include/UniCoffeeShop.h"

#include <sstream>
#include <iostream>
#include<vector>
#include<cstring>
#include<fstream>
#include<string.h>
#include <string>
#include <stdlib.h>
using namespace std;

vector<Product> makeTheMenu(vector<Ingredient> ingredients, vector<string> products)
{
    vector<Product>  menu;
    for (int i = 0 ; i < products.size(); i++) {//reading the products.conf file
        vector<string> line = split_string(products[i]);
		if (line.size()==0) {//reached the end of the file.
			break;
		}
        Product p;
		//cout <<"for i=" << i << ", line.size = " <<line.size() << endl;
        p.name = line[0];
        
        for (int j = 1 ; j<line.size() ; j++) {//fill p.ingridients
            string ingredientName = line[j];
            Ingredient* ing = searchForIngredient(ingredients, ingredientName);
            if (ing != NULL) {
                p.ingredients.push_back(ing);
            }
            
        }
        
        p.finalPrice = calculateFinalPrice(p);
		cout << "in make the menu, " << p.name << "'s price is " <<p.finalPrice << endl ;
        
        if (p.finalPrice <= 5) {
            menu.push_back(p);
			for (int i=0 ; i < p.ingredients.size() ; i++) {
				p.ingredients[i]->isIncluded = true;
			}
        }
    }
    return menu;
}

vector<Ingredient> readIngredients(vector<string> vec)
{
	vector<Ingredient> ingredients_vec;
	Ingredient ingredient;
	for (size_t i = 0; i < vec.size(); ++i) {
		vector<string> line =split_string(vec[i]);
		
		if (line.size()==0) {//means that this is an empty string and that we ave reached the end of the file.
			cout << "In function readIngredients, for i=" << i <<"line.size()=0" <<endl;
			break;
		}
		string supplier=line[0];
		string ingrid=line[1];
		//cout << "for i=" << i << ", line[2].length() = " << line[2].length() << endl;
		char *cstr = new char[line[2].length() + 1];
		strcpy(cstr, line[2].c_str());
		// do stuff
		
		double price= atof(cstr);
		delete [] cstr;
		bool found=false;
		for (size_t j = 0; j < ingredients_vec.size() &&  found==false; ++j) {
			if(ingrid.compare(ingredients_vec[i].name) == 0)
			{
				if(ingredients_vec[i].price >=price)
				{
					ingredients_vec[i].price=price;
					
					found=true;
				}
				else found=false;
			}
			if(!found)
			{
				ingredient.name=ingrid;
				ingredient.supplier=supplier;
				ingredient.price=price;
				ingredients_vec.push_back(ingredient);
				
			}
			
			
		}
	}
	cout << "In function readIngredients, ingredients_vec.size() = " << ingredients_vec.size() << endl;
	return ingredients_vec;
}

vector<string> writeTheOutput(vector<Product> menu)
{
	vector<string> vec;
	string str="";
	for (size_t i = 0; i < menu.size(); ++i) {
		str="";
		str+=menu[i].name;
		str+=',';       // number to be converted to a string
		string Result;          // string which will contain the result
		ostringstream convert;   // stream used for the conversion
		convert << menu[i].finalPrice;      // insert the textual representation of 'Number' in the characters in the stream
		
		Result = convert.str(); // set 'Result'
		str+=Result;
		
		vec.push_back(str);
	}
	return vec;
}

double calculateFinalPrice(Product product)
{
    double finalPrice = 0.0;
    for (int i=0; i < product.ingredients.size() ; i++) {
        double ingredientPrice = product.ingredients[i]->price;
        finalPrice = finalPrice + ingredientPrice;
		
    }
    finalPrice++;
    finalPrice = finalPrice * 1.5;
    product.finalPrice = finalPrice;
	cout << product.name << "'s price is " <<product.finalPrice << endl ;
	return product.finalPrice;
}

void writefile_H(vector<string> Vec ,string filename)
{
	char *cstr = new char[filename.length() + 1];
	strcpy(cstr, filename.c_str());
	ofstream myfile (cstr);
	if (myfile.is_open())
	{
		for (size_t i = 0; i < Vec.size(); ++i) {
			myfile << Vec[i]<< '\n';
		}
		myfile.close();
	}
	else cout << "Unable to open file";
	
}

vector<string> readfile_H(string filename)
{
	string str;
	char *cstr = new char[filename.length() + 1];
	strcpy(cstr, filename.c_str());
	vector<string> Vec;
	ifstream infile (cstr);
	if (infile.is_open())
		while ( getline (infile,str) )
		{
			Vec.push_back(str); // push the line inside vec
		}
	else cout << "Unable to open file";
	infile.close();
	return Vec;
}

vector<string> split_string(string str)
{
	vector<string> result;
	if (str.length()>0) {
		
		str = str + ",";//allows the for loop to dicover the last word.
		//cout << "str=" << str << endl;
		
		
		for(long index = str.find(','); index!= string::npos ; index = str.find(',')){
			string tmp = str.substr(0,index);
			result.push_back(tmp);
			str = str.substr(index + 1, str.length());
			
			//this while loop removes unneccesery spaces.
			while (str.length() > 0 && str.at(0) == ' ') {
				str = str.substr(1);
			}
		}
	}
	return result;
	
}

Ingredient* searchForIngredient(vector<Ingredient> ingredients, string ingredientName)
{
    for(int i = 0 ; i<ingredients.size() ; i++) {
        if (ingredients[i].name == ingredientName) {
            return &(ingredients[i]);
        }
    }
    return NULL;
}

vector<Ingredient> newReadIngredients(vector<string> suplliers)
{
	vector<Ingredient> res;
	for (int i=0 ; i<suplliers.size(); i++) {
		vector<string> line = split_string(suplliers[i]);
		if (line.size()==0) {
			break;
		}
		Ingredient toInsert;
		toInsert.supplier = line[0];
		toInsert.name = line[1];
		toInsert.price = atof(line[2].c_str());
		bool isInTheVector = false;
		for (int j=0 ; (j<res.size()) & !isInTheVector ; j++) {
			if ((res[j].name).compare(toInsert.name)==0) {
				isInTheVector = true;
				if ((toInsert.price < res[j].price)) {
					//cout << res[j].name << "?=?" << toInsert.name << endl;
					cout << "Erasing " << res[j].name << " from supplier " <<res[j].supplier << res[j].price << ", Instead inserting supplier " << toInsert.supplier << toInsert.price << endl;
					res.erase(res.begin() + j);//remove the supllier that as the higher price
					res.push_back(toInsert);
				}
			}
		}
		if (!isInTheVector) {
			cout << "*Inserting " << toInsert.name << " from supplier " << toInsert.supplier << " with price " << toInsert.price << endl;
			res.push_back(toInsert);
		}
	}
	cout << "In newReadIngredients, res.size = "<< res.size() << endl;
	return res;
	
}



