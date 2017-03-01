var mqtt = require('mqtt')
var request = require('request');

// Set up flag/counts
var flag = 0;
var false_count = 0;
var true_count = 0;

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
	// Extract the value from the presence sensor (in our case: true = presence and false = no presence)
	var presenceStatus = obj[1].value;

	// the flag changes to 1 when the presence sensor spots presence
	if (presenceStatus == true){
		true_count = true_count + 1;
		if (true_count > 1){
			flag = 1
		}	
	}
	
	// When there is no presence for some time, the flag changes back to 0
	if (presenceStatus == false){
		true_count = 0;
		false_count = false_count + 1;
		if (false_count > 10){
			flag = 0;
			false_count = 0;
		}
	}
	
	// If the flag is 0 and the door opens - the sonos will be triggered to start playing music
	if (flag == 0) {
		if (doorStatus === true){
			request('http://192.168.178.64:5005/salon/play', function (error, response, body) {
				if (!error && response.statusCode == 200) {
					console.log(body)
				}
			})
		}
	}
	
	// DEBUG: print statuses & flag
	console.log("door:"+doorStatus)
	console.log("presence: "+presenceStatus)
	console.log("flag: "+flag)
	
  	
  });
  
});

