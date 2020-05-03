$("#close").click(function(){
    window.location.href = "./InvoiceManager.html";
})

function validDate(date){
    try{
        date = date.split('/');
        if(parseInt(date[0])>31 || parseInt(date[0])<1){
            showNotification("Date "+date[0]+" is not valid","Invoice Manager");
            return false;
        }
        else if(parseInt(date[1])>12 || parseInt(date[1])<1){
            showNotification("Month "+date[1]+" is not valid","Invoice Manager");
            return false;
        }
        else if(parseInt(date[2])<1950 || parseInt(date[2])>2020){
            showNotification("Year "+date[2]+" is not valid","Invoice Manager");
            return false;
        }
        return true;
    }   
    catch(err){
        showNotification(err.message,"Invoice Manager");
        return false;
    }
}

$("#addbutton").click(function(){
    var item_no = $("#item_no").val();
    var payment_method = $("#payment_method").val();
    var date = $("#date").val();
    var description = $("#description").val();
    var amount = $("#amount").val();

    if(!validDate(date)){
        showNotification("Date invalid","Invoice Manager");
        return;
    }

    addInvoice(item_no,payment_method,date,description,amount);
})

function showNotification(message,header){
    $("#content").html(`
        <div class="m-3">
            <p>`+message+`</p>
            <a href="./addInvoice.html" class="btn btn-primary m-2" style="height:40px">Okay</a>
        </div>    
    `);   
}

