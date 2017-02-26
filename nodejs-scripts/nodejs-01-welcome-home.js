var mqtt = require('mqtt')
var request = require('request');

// Setup the MQTT client
var client = mqtt.connect({
  servers:[{'host':'<URL.OF.YOUR.MQTT.BROKER.HERE>'}], // for example mqtt.relayr.io
  username: "<YOUR.USER.NAME.HERE>",
  password: "<YOUR.PASSWORD.HERE>",
  protocol : 'mqtts'
});

// Connect to the client
client.on('connect', function() {

  // Subscribe to commands sent from the dashboard or other clients
  client.subscribe("<YOUR.MQTT.TOPIC.HERE>"); 

  // Start receiving data
  client.on('message', function(topic, message) {
	  
  	// Print the response message from the MQTT broker
  	console.log(message.toString())
	
	// Parse the message to JSON
	var obj = JSON.parse(message);
	
	// Extract the value from the door sensor (in our case: true = open and false = closed)
	var doorStatus = obj[0].value;
	
	// DEBUG: Prints the status of the door
	console.log(doorStatus);

	// If you have the sonos http server running on your local host, 
	// this request will trigger the sonos to start playing music once the door is opened:
	if (doorStatus === true){
		request('http://localhost:5005/salon/play', function (error, response, body) {
			if (!error && response.statusCode == 200) {
				console.log(body)
			}
		})
	  }
		
   });
  
});

