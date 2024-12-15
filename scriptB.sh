#!/bin/bash

# Define the server to send requests to
server_url="http://10.0.2.15/compute"

# Function to send HTTP requests
send_request() {
    while :; do
        sleep_time=$((RANDOM % 6 + 5)) # Random delay between 5 and 10 seconds
        echo "Sending request to $server_url (waiting $sleep_time seconds)"
        curl -s "$server_url" > /dev/null
        sleep $sleep_time
    done
}

# Launch multiple asynchronous request loops
for i in {1..5}; do
    send_request &
done

# Wait for all background processes to complete
wait

