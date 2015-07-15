//Thrift client test for JS 
var storage = window.localStorage;
var ip = "clarity04.eecs.umich.edu", port = "4444", numRuns = 0;

function onload() {
    document.getElementById("host").value = storage.getItem("host");
    document.getElementById("port").value = storage.getItem("port");

    document.getElementById("type").value = storage.getItem("type");
    document.getElementById("data").value = storage.getItem("data");
    document.getElementById("tags").value = storage.getItem("tags");
}
window.addEventListener("load", onload);

function updateDefaults(key, value) {
    storage.setItem(key, value);
}

function updateResponseDiv(value) {
    $('#response').empty();
    $('#response').append("<p>" + value + "</p>");
}

function getAddress(ip, port, destination) {
    return 'http://' + ip + ':' + port + '/' + destination;
}

function query() {
    console.log("Getting HostPort from command center");    
    var addr = getAddress(storage.getItem("host"), storage.getItem("port"), 'cc');
    var transport = new Thrift.TXHRTransport(addr);
    var protocol  = new Thrift.TJSONProtocol(transport);
    var client = new SchedulerServiceClient(protocol);
    var response = client.consultAddress("Sirius");
    console.log("Host: " + response.ip + ", Port: " + response.port);


	console.log("Sending Query");
    addr = getAddress(response.ip, response.port, 'sirius');
	transport = new Thrift.TXHRTransport(addr);
    protocol = new Thrift.TJSONProtocol(transport);
    client = new IPAServiceClient(protocol);    //ipaserviceclient

    var queryData = new JSQueryData();
    queryData.type = storage.getItem("type");
    queryData.data = new Array();
    queryData.data.push(storage.getItem("data"));
    queryData.data.push(storage.getItem("data"));
    queryData.data.push(storage.getItem("data"));
    queryData.tags = new Array();
    queryData.tags.push(storage.getItem("tags"));

    var query = new JSQuery();
    query.name = "";
    query.content = new Array();
    query.content.push(queryData);


    console.log(query);

    response = client.submitQuery(query);
    //response is in base64, so convert it with atob
    updateResponseDiv(window.atob(response));
    console.log(window.atob(response));
}
document.getElementById("askServer").addEventListener("click",query);

