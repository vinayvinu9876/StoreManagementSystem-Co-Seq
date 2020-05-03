#include <bits/stdc++.h> 
#include <JavaScriptCore/JavaScript.h>
#include "utilityFunctions.cpp"
#include "convertJSStringToString.cpp"
#include "ItemManager.cpp"

using namespace std;

void setTable(JSContextRef ctx){
    ItemManager im;
    list<string> all_Item_data = im.getAllItemDetails();
    string javascript_data_array = "["; //start;
    
    for(auto x : all_Item_data){
        javascript_data_array = javascript_data_array + "\""+ x + "\"" + ",";
    }

    if(all_Item_data.size()>0)
        javascript_data_array = javascript_data_array.substr(0, javascript_data_array.size()-1); //remove last ","
    
    javascript_data_array = javascript_data_array + "]" ; //end
    string to_set_table = "setTable('"+javascript_data_array+"');";
    cout<<to_set_table<<endl;
    cout.flush();
    modifyHTML(ctx,to_set_table.c_str());
}


JSValueRef addItem(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, 
                        const JSValueRef arguments[], JSValueRef* exception){

    ItemManager im;
    //Get Parameters
    string name = JSStringToStdString(JSValueToStringCopy(ctx,arguments[0],exception));
    string brand = JSStringToStdString(JSValueToStringCopy(ctx,arguments[1],exception));
    string desc = JSStringToStdString(JSValueToStringCopy(ctx,arguments[2],exception));


    bool result = im.addItem(name,brand,desc);

    string message;
    if(result)
        message = "Item Created Succesfully";
    else
        message = "Item creation failed";


    string to_notify = "showNotification(' "+message+" ', 'ItemManager')";
    modifyHTML(ctx,to_notify.c_str());
    //refresh items
    //setDBTable(dba,ctx);
    //create database  
    return JSValueMakeNull(ctx);
}

JSValueRef getItem(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, 
                        const JSValueRef arguments[], JSValueRef* exception){
    cout<<"I got called"<<endl;
    cout.flush();
    setTable(ctx);
    return JSValueMakeNull(ctx);

} 

JSValueRef deleteItem(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, 
                        const JSValueRef arguments[], JSValueRef* exception){
    ItemManager im;
    //Get Parameters
    string Item_no = JSStringToStdString(JSValueToStringCopy(ctx,arguments[0],exception));

    bool result = im.removeItem(Item_no);

    string message;
    if(result)
        message = "Item Deleted Succesfully";
    else
        message = "Item Deletion failed";


    setTable(ctx);
    string to_notify = "showNotification(' "+message+" ', 'ItemManager')";
    modifyHTML(ctx,to_notify.c_str());


    return JSValueMakeNull(ctx);
}