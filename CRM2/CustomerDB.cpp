/*
 * Copy the contents of header.txt (filled out) and paste here
 */
#include <iostream>
#include <cassert>
#include "UTString.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(UTString name) { // done, please do not edit
    this->bottles = 0;
    this->rattles = 0;
    this->diapers = 0;
    this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

int CustomerDB::size(void) { // done, please do not edit
    return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
    delete[] this->data;
}



void CustomerDB::clear(void) { // done, please do not edit
    delete[] this->data;
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
    assert(k >= 0 && k < this->length);
    return this->data[k];
}

Customer& CustomerDB::operator[](UTString name) { // not done, your effort goes here
    if(isMember(name)){
        for(int i=0; i<this->length;i++){
            if(this->data[i].name.operator==(name)){
                return this->data[i];
            }
        }
    }
    else{
        if(this->length >= this->capacity){
            Customer* temp = new Customer[this->capacity*2];
            for(int i=0; i<this->length;i++){
                 temp[i] = this->data[i];
            }
            delete[] this->data;
            this->capacity *=2;
            this->data = new Customer[this->capacity];
            for(int i=0; i<this->length;i++){
                this->data[i] = temp[i];
            }
        }
        Customer new_customer(name);
        this->data[this->length] = new_customer;
        this->length++;
        return this->data[this->length - 1];
    }



}


bool CustomerDB::isMember(UTString name) { // not done, your effort goes here
    for(int i=0; i<this->length;i++){
        if(data[i].name == name){
            return true;
        }
    }
    return false;
}
