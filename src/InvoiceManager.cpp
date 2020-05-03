#include<bits/stdc++.h>
#include <stdexcept> 
#include "FileManager.cpp"
#include "ItemManager.cpp"
#include "utilityFunctions.cpp"
#pragma once

using namespace std;

class InvoiceManager{
    string filename = "Invoices.txt";
public:
    bool addInvoice(string item_no,string payment_method,string date,string description,string amount);
    bool removeInvoice(string invoice_id);
    list<string> getAllInvoiceDetails();
private:
    string getNewInvoiceNumber();
};

bool InvoiceManager::addInvoice(string item_no,string payment_method,string date,string description,string amount){
    string newInvoiceid = getNewInvoiceNumber();
    string record_line = "";
    ItemManager im;
    try{
        if(newInvoiceid=="-1") throw runtime_error("ERROR Generating Invoice ID");
        if(!validDate(date)) throw runtime_error("Invalid Date");
        cout<<"item No = "<<item_no<<endl;
        if(!im.checkItemExists(item_no)) throw runtime_error("item Doesnt Exist"); 

        FileManager fm(filename);
        record_line = record_line + newInvoiceid + "|" + item_no + "|" + payment_method + "|" + date + "|" + description + "|" + amount; 
        return fm.addLineToFile(record_line); 
    }
    catch(const char* message){
        cout<<message<<endl;
        return false;
    }
}

bool InvoiceManager::removeInvoice(string Invoice_id){
    try{
        FileManager fm(filename);
        list<string> content = fm.getFileContent();
        for(auto line : content){
            string key = splitString(line,'|').front();
            if(key==Invoice_id)
                return fm.removeLine(line);
        }
        throw runtime_error("No Records Found");
    }
    catch(const char* message){
        cout<<message<<endl;
        return false;
    }
}

list<string> InvoiceManager::getAllInvoiceDetails(){
    FileManager fm(filename);
    return fm.getFileContent();
}

string InvoiceManager::getNewInvoiceNumber(){
    try{
        FileManager fm(filename);
        list<string> result = fm.getFileContent();
        if(result.size()==0) return "1";
        string last_record = result.back();

        string last_Invoice_no = splitString(last_record,'|').front(); //get only key
        string new_Invoice_no = to_string(stoi(last_Invoice_no)+1);
        return new_Invoice_no;
    }
    catch(const char* message){
        cout<<message<<endl;
        return "-1";
    }
}