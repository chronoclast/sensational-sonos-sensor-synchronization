import urllib2

def lambda_handler(event, context):
    if (event['session']['application']['applicationId'] != "<YOUR_ALEXA_ACCPLICATION_ID_HERE>"):
        #raise ValueError("Invalid Application ID")
        pass # when your application id is set, comment this line and uncomment the one above.
    
    if event['session']['new']:
        on_session_started({'requestId': event['request']['requestId']}, event['session'])

    if event['request']['type'] == "LaunchRequest":
        return on_launch(event['request'], event['session'])
    elif event['request']['type'] == "IntentRequest":
        return on_intent(event['request'], event['session'])
    elif event['request']['type'] == "SessionEndedRequest":
        return on_session_ended(event['request'], event['session'])
		
def on_session_started(session_started_request, session):
    print "Starting new session."

def on_launch(launch_request, session):
    return get_welcome_response()

def on_intent(intent_request, session):
    intent = intent_request['intent']
    intent_name = intent_request['intent']['name']

    if intent_name == "SonosIntent":
        return get_train_times(intent)
    elif intent_name == "AMAZON.HelpIntent":
        return get_help_response()
    elif intent_name == "AMAZON.CancelIntent":
        return handle_session_end_request()
    elif intent_name == "AMAZON.StopIntent":
        return handle_session_end_request()
    else:
        raise ValueError("Invalid intent")

def on_session_ended(session_ended_request, session):
    return handle_session_end_request()
    print "Ending session."
    # Cleanup goes here...

def get_welcome_response():
    session_attributes = {}
    card_title = "Sonos"
    speech_output = "Hallo! What would you like your Sonos to do? You can say for example play, pause or next."
    reprompt_text = "What do you want your Sonos to do?"
    should_end_session = False
    return build_response(session_attributes, build_speechlet_response(
        card_title, speech_output, reprompt_text, should_end_session))

def handle_session_end_request():
    card_title = "Sonos"
    speech_output = "Bye bye!"
    should_end_session = True

    return build_response({}, build_speechlet_response(card_title, speech_output, None, should_end_session))

def get_train_times(intent):
    session_attributes = {}
    card_title = "SONOS"
    speech_output = "Something went wrong here. Oops."
    reprompt_text = "I am not sure what you want me to tell your sonos to do for you."
    
    try:
        itemOne = str(intent['slots']['itemOne']['value'])
        
        if itemOne == "play":
            response = urllib2.urlopen('http://<YOUR_SONOS_SERVER_DOMAIN>/<ROOM_NAME>/play')
        elif itemOne == "next":
            response = urllib2.urlopen('http://<YOUR_SONOS_SERVER_DOMAIN>/<ROOM_NAME>/next') 
        elif itemOne in ("louder", "volume up") :
            response = urllib2.urlopen('http://<YOUR_SONOS_SERVER_DOMAIN>/<ROOM_NAME>/volume/+10')
        elif itemOne in ("softer", "volume down"):
            response = urllib2.urlopen('http://<YOUR_SONOS_SERVER_DOMAIN>/<ROOM_NAME>/volume/-10')
        elif itemOne ==  "pause":
            response = urllib2.urlopen('http://<YOUR_SONOS_SERVER_DOMAIN>/<ROOM_NAME>/pause')
        try:
            html = response.read()
            html = html.split(":")[1]
            resp = html.replace("}", "")
            should_end_session = True
        except:
           resp = "Oops. I did not quite get that. Please try again."
           should_end_session = False
        
        speech_output = resp
		 
    except:
        pass

    return build_response(session_attributes, build_speechlet_response(
        card_title, speech_output, reprompt_text, should_end_session))

def build_speechlet_response(title, output, reprompt_text, should_end_session):
    return {
        'outputSpeech': {
            'type': 'PlainText',
            'text': output
        },
        'card': {
            'type': 'Simple',
            'title': title,
            'content': output
        },
        'reprompt': {
            'outputSpeech': {
                'type': 'PlainText',
                'text': reprompt_text
            }
        },
        'shouldEndSession': should_end_session
    }

def build_response(session_attributes, speechlet_response):
    return {
        'version': '1.0',
        'sessionAttributes': session_attributes,
        'response': speechlet_response
    }
