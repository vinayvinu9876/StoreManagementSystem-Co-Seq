#include<iostream>
#include<string>
#include<list>
#include <JavaScriptCore/JavaScript.h>
#include "utilityFunctions.cpp"
#include "convertJSStringToString.cpp"
#include "InvoiceManager.cpp"

using namespace std;

void setInvoiceTable(JSContextRef ctx){
    InvoiceManager im;
    list<string> all_Invoice_data = im.getAllInvoiceDetails();  
    string javascript_data_array = "["; //start;
    
    for(auto x : all_Invoice_data){
        javascript_data_array = javascript_data_array + "\""+ x + "\"" + ",";
    }

    if(all_Invoice_data.size()>0)
        javascript_data_array = javascript_data_array.substr(0, javascript_data_array.size()-1); //remove last ","
    
    javascript_data_array = javascript_data_array + "]" ; //end
    string to_set_table = "setTable('"+javascript_data_array+"');";
    cout<<to_set_table<<endl;
    cout.flush();
    modifyHTML(ctx,to_set_table.c_str());
}

JSValueRef addInvoice(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, 
                        const JSValueRef arguments[], JSValueRef* exception){
    InvoiceManager im;

    string account_no = JSStringToStdString(JSValueToStringCopy(ctx,arguments[0],exception));
    string check_no = JSStringToStdString(JSValueToStringCopy(ctx,arguments[1],exception));
    string date = JSStringToStdString(JSValueToStringCopy(ctx,arguments[2],exception));
    string description = JSStringToStdString(JSValueToStringCopy(ctx,arguments[3],exception));
    string debit_credit = JSStringToStdString(JSValueToStringCopy(ctx,arguments[4],exception));

    bool result = im.addInvoice(account_no,check_no,date,description,debit_credit);

    string message;
    
    if(result)
        message = "Invoice Succesfully";
    else
        message = "Invoice Failed";

    string to_notify = "showNotification( '"+message+"', 'Invoice Manager');";
    modifyHTML(ctx,to_notify.c_str());

    return JSValueMakeNull(ctx);
}


JSValueRef getInvoice(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, 
                        const JSValueRef arguments[], JSValueRef* exception){

    setInvoiceTable(ctx);
    return JSValueMakeNull(ctx);
}

JSValueRef deleteInvoice(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, 
                        const JSValueRef arguments[], JSValueRef* exception){
        InvoiceManager im;
        string Invoice_number = JSStringToStdString(JSValueToStringCopy(ctx,arguments[0],exception));
        bool result = im.removeInvoice(Invoice_number);

        string message;
    
        if(result)
            message = "Invoice Deleted Succesfully";
        else
            message = "Invoice Delete Failed";

        string to_notify = "showNotification( '"+message+"', 'Invoice Manager');";
        modifyHTML(ctx,to_notify.c_str());

        setInvoiceTable(ctx);

        return JSValueMakeNull(ctx);
        
} 