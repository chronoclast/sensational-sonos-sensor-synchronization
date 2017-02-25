
var request = global.get('request');

var obj = JSON.parse(msg.payload);

var doorStatus = obj[0].value;

// DEBUG: Prints the status of the door
// console.log(doorStatus);

if (doorStatus === true){
    request('http://localhost:5005/salon/volume/25', function (error, response, body) {
        if (!error && response.statusCode == 200) {
        	console.log(body)
        }
    })
}

msg = doorStatus;

return msg;