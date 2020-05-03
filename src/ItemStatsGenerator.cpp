#include<bits/stdc++.h>
#include <stdexcept> 
#include "FileManager.cpp"
#include "ItemManager.cpp"
#include "InvoiceManager.cpp"
#include "utilityFunctions.cpp"
#pragma once

using namespace std;


class ItemStatsGenerator{
    string months[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    ItemManager im;
    InvoiceManager tm;
public:
    bool generateItemStats();
    list<string> getItemStatsData();
private:
    string   getAggregatedLine(list<list<string>> Invoices);
    string getItemStatsFileName();
    string getItemStatsHeader();
    list<list<string>> getAllMatchingInvoice(string Item_no,list<string> Invoice_records);
    int getMonth();
};



bool ItemStatsGenerator::generateItemStats(){
    try{
        FileManager ItemStats(getItemStatsFileName());
        ItemStats.clearFile();
        ItemStats.addLineToFile(getItemStatsHeader());

        cout<<"Added ItemStats Headers"<<endl;
        list<string> master_records = im.getAllItemDetails();
        cout<<"Got Item Manager id = "<<master_records.front()<<endl;
        list<string> Invoice_records = tm.getAllInvoiceDetails();
        cout<<"Got Invoice Records "<<Invoice_records.front()<<endl;

        for(auto master : master_records ){
            cout<<"Got master value "<<master<<endl;
            list<string> master_values = splitString(master,'|');
            cout<<"Got list"<<endl;
            string Item_no = getAtIndex(master_values,0); //Item no is first column
            cout<<"Got Item no "<<Item_no<<endl;
            list<list<string>> matching_Invoices = getAllMatchingInvoice(Item_no,Invoice_records);
            cout<<"Got matching Invoices Get At Index "<<getAtIndex(master_values,1)<<endl;
            string ItemStats_line = Item_no + "|" + getAtIndex(master_values,1) + "|" + getAggregatedLine(matching_Invoices);
            cout<<"Got  ItemStats Line"<<endl;
            ItemStats.addLineToFile(ItemStats_line);
            cout<<"Done"<<endl;
        }

        return true;

    }   
    catch(const char* message){
        cout<<message<<endl;
        return false;
    }
}





list<list<string>> ItemStatsGenerator::getAllMatchingInvoice(string Item_no,list<string> Invoice_records){
    list<list<string>> matching_records;

    for(auto Invoice : Invoice_records){
        list<string> Invoice_values = splitString(Invoice,'|');
        //Item no is stored in second column (indexing from 0,1)
        if(getAtIndex(Invoice_values,1)==Item_no)
            matching_records.push_back(Invoice_values);
    }

    return matching_records;
}
string  ItemStatsGenerator::getAggregatedLine(list<list<string>> Invoices){
    string aggregate_line = "";
    list<string> month_calc;
    // <month,balance>
    map<int,int> month_holder;
    for(int i=1;i<=12;i++){
        month_holder.insert(pair<int,int>(i,0));
    }

    cout<<"Inserted Month Holder"<<endl;
    for(auto Invoice : Invoices){
        cout<<"Invoice id = "<<Invoice.front()<<endl;
        //date is in 4(4-1 index)rd column and debit/credit in 6(6-1 index)th colummn (index starts at 0)
        string date = getAtIndex(Invoice,3);
        cout<<"Date = "<<date<<endl;
        list<string> split_date =  splitString(date,'/');
        int month = stoi(getAtIndex(split_date,1));
        cout<<"Got month"<<month<<endl;
        int amount = stoi(getAtIndex(Invoice,5));
        cout<<"Got amount "<<amount<<endl;
        month_holder[month] = month_holder[month] + amount;
        cout<<"Month_holder[month] = "<<month_holder[month]<<endl;
    }

    cout<<"Out of loop"<<endl;
    for(int i=1;i<=12;i++){
        cout<<"Getting i="<<i<<endl;
        aggregate_line = aggregate_line + to_string(month_holder[i]);
        cout<<"aggregate line = "<<aggregate_line<<endl;
        if(i<12) //donot add |
            aggregate_line = aggregate_line + "|";
    }
    cout<<"Aggregate line "<<aggregate_line;
    return aggregate_line;
}

string ItemStatsGenerator::getItemStatsFileName(){
    return "ItemStats.txt";
}

string ItemStatsGenerator::getItemStatsHeader(){
    string headers = "Item_No | Item_Name |";
    for(int i=0;i<12;i++){
        headers = headers + months[i];
        if(i<11) //donot add to last one
             headers = headers + "|";
    }
    return headers;
}

list<string> ItemStatsGenerator::getItemStatsData(){
    FileManager fm(getItemStatsFileName());
    return fm.getFileContent();
}