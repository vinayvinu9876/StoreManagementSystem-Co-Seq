#include <bits/stdc++.h> 
#include <JavaScriptCore/JavaScript.h>
#include "utilityFunctions.cpp"
#include "ItemStatsGenerator.cpp"

using namespace std;


void setItemStatsTable(JSContextRef ctx){
    ItemStatsGenerator is;
    list<string> all_ItemStats_data = is.getItemStatsData();  
    string javascript_data_array = "["; //start;
    
    for(auto x : all_ItemStats_data){
        javascript_data_array = javascript_data_array + "\""+ x + "\"" + ",";
    }

    if(all_ItemStats_data.size()>0)
        javascript_data_array = javascript_data_array.substr(0, javascript_data_array.size()-1); //remove last ","
    
    javascript_data_array = javascript_data_array + "]" ; //end
    string to_set_table = "setTable('"+javascript_data_array+"');";
    cout<<to_set_table<<endl;
    cout.flush();
    modifyHTML(ctx,to_set_table.c_str());
}

JSValueRef genItemStats(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, 
                        const JSValueRef arguments[], JSValueRef* exception){
    ItemStatsGenerator is;
    is.generateItemStats();
    setItemStatsTable(ctx);
    return JSValueMakeNull(ctx);
}   