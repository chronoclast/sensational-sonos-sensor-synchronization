var mqtt = require('mqtt')
var request = require('request');

// Setup the MQTT client
var client = mqtt.connect({
  servers:[{'host':'<URL_OF_YOUR_MQTT_BROKER_HERE>'}], // for example mqtt.relayr.io
  username: "<YOUR_USER_NAME_HERE>",
  password: "<YOUR_PASSWORD_HERE>",
  protocol : 'mqtts'
});

// Connect to the client
client.on('connect', function() {

  // Subscribe to commands sent from the dashboard or other clients
  client.subscribe("<YOUR_MQTT_TOPIC_HERE>"); 

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

