$("#addbutton").click(function(){
    var name = $("#name").val();
    var brand = $("#brand").val();
    var desc = $("#description").val();
    addItem(name,brand,desc);
})

function showNotification(message,header){
    $("#content").html(`
        <div class="m-3">
            <p>`+message+`</p>
            <a href="./addItem.html" class="btn btn-primary m-2" style="height:40px">Okay</a>
        </div>    
    `);   
}

$("#close").click(function(){
    window.location.href = "./ItemManager.html";
})