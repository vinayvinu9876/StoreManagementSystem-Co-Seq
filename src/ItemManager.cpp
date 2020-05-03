#include<bits/stdc++.h> 
#include "FileManager.cpp"
#include "utilityFunctions.cpp"
#pragma once

using namespace std;

class ItemManager{
    string filename = "Item.txt";
public:
    bool addItem(string name,string brand,string desc);
    bool removeItem(string Item_no);
    bool checkItemExists(string Item_no);
    list<string> getAllItemDetails();
private:
    string getNewItemNo();
};

bool ItemManager::addItem(string name,string brand,string desc){
    string new_Item_no = getNewItemNo();
    string details_line = "";
    try{
        if(new_Item_no=="-1") throw runtime_error("ERROR Generating Item No.");
        FileManager fm(filename);
        details_line = details_line + new_Item_no + "|" + name + "|" + brand + "|" + desc;
        cout<<"Detials Line = "<<details_line<<endl;
        cout.flush(); 
        return fm.addLineToFile(details_line); 
    }
    catch(const char* message){
        cout<<message<<endl;
        return false;
    }
}

string ItemManager::getNewItemNo(){
    try{
        FileManager fm(filename);
        list<string> result = fm.getFileContent();
        if(result.size()==0) return "1" ;
        
        string last_record = result.back();

        string last_Item_no = splitString(last_record,'|').front(); //get only key
        string new_Item_no = to_string(stoi(last_Item_no)+1);
        return new_Item_no;
    }
    catch(const char* message){
        cout<<message<<endl;
        return "-1";
    }
}

bool ItemManager::removeItem(string Item_no){
    try{
        FileManager fm(filename);
        list<string> content = fm.getFileContent();
        for(auto line : content){
            string key = splitString(line,'|').front();
            if(key==Item_no)
                return fm.removeLine(line);
        }
        throw runtime_error("No Records Found");
    }
    catch(const char* message){
        cout<<message<<endl;
        return false;
    }
}

bool ItemManager::checkItemExists(string Item_no){
    try{
        FileManager fm(filename);
        list<string> content = fm.getFileContent();
        if(content.size()==0) throw runtime_error("NO records found");
        for(auto line : content){
            string key = splitString(line,'|').front();
            if(key==Item_no)
                return true;
        }
        return false;
    }
    catch(const char* message){
        cout<<message<<endl;
        return false;
    }
}

list<string> ItemManager::getAllItemDetails(){
    FileManager fm(filename);
    return fm.getFileContent();
}
