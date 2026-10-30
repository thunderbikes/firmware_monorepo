#imports 

import argparse
import can
import cantools
import time 

#what is argparse? It is a module in Python that allows you to create user-friendly command-line interfaces. 
# It provides a way to define the arguments your program requires, parse those arguments from the command line, 
# and automatically generate help and usage messages.
# -------------------------
# Command-line arguments
# -------------------------

parser = argparse.ArgumentParser(
    description="telemetry CAN simulator"
)

parser.add_argument(
    "dbc",
    help="Path to the DBC file"
)

parser.add_argument(
    "interface",
    help="CAN interface, e.g. vcan0 or can0"
)

args = parser.parse_args() #what does this do? It parses the command line arguments and stores them in the args variable.


# -------------------------
# Setup
# -------------------------

dbc = cantools.database.load_file(args.dbc)

#configure bus using socketcan and network interface
bus = can.Bus(
    interface="socketcan",
    channel=args.interface
)

print(f"Loaded DBC: {args.dbc}")
print(f"Connected to: {args.interface}")


#-------------------------------------
# logic 
#-------------------------------------
try:     


    #create a list with all the messages mapped to their signal values and last sent times,  set all values to 0

    message_states = []
    for message in dbc.messages: 
        signal_values = {}

        for signal in message.signals: 
            signal_values[signal.name] = 0  # Initialize all signal values to 0 while adding them 

        message_states.append({
            "message": message,
            "signal_values": signal_values,
            "last_sent_time": 0  # Initialize last sent time to 0
        })
    # define increment signals function to increment the signal values for a given message index, wrapping around to 0 if the value exceeds the maximum defined in the DBC.
    def increment_signals(message_index):
        
        #Increment the signal values for the specified message index.
        #Wrap around to 0 if the value exceeds the maximum defined in the DBC.
        
        message = dbc.messages[message_index]
        signal_values = message_states[message_index]["signal_values"]

        for signal in message.signals:
            # Increment the signal value
            signal_values[signal.name] += 1

            #Wrap around if it exceeds the maximum value
            if signal_values[signal.name] > signal.maximum:
                signal_values[signal.name] = 0

    # enter while loop to send messages at their defined cycle times, incrementing signal values each time a message is sent.


    while True:
        
        for message in dbc.messages:
            now = time.monotonic()*1000  # Current time in milliseconds

            # get the last sent time for the current message
            last_sent_time = message_states[dbc.messages.index(message)]["last_sent_time"] #dbc.messages.index gets the index of the current message in the dbc.messages list, 
                                                                                        #and we use that index to access the corresponding last_sent_time in the message_states list.
            if now - last_sent_time >= message.cycle_time:  # Check if it's time to send the message
                increment_signals(dbc.messages.index(message))  # Increment the signal values for the current message
                
                data_payload =  message.encode(message_states[dbc.messages.index(message)]["signal_values"])  # Encode the signal values into a data payload

                frame = can.Message(
                        arbitration_id = message.frame_id,
                        data = data_payload,
                        is_extended_id = False 
                        )
                
                message_states[dbc.messages.index(message)]["last_sent_time"] = time.monotonic() * 1000  # Update to current time in milliseconds]
                bus.send(frame) # Send the CAN message


    
    

finally: 

    bus.shutdown()  # Ensure the CAN bus is properly shut down when exiting the script 
    print("CAN bus shutdown. Exiting script.")       





 



    


    