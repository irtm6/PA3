#!/bin/bash

# Helper function to check if a container is busy
is_busy() {
    local container=$1
    local cpu_threshold=5

    cpu_usage=$(docker stats --no-stream --format "{{.CPUPerc}}" "$container" | sed 's/%//')
    busy=$(echo "$cpu_usage > $cpu_threshold" | bc)
    echo $busy
}

# Function to update containers
update_containers() {
    local containers=(srv1 srv2 srv3)
    local image_name="artnos1/optimafuncanew"

    docker pull $image_name

    for container in "${containers[@]}"; do
        if docker ps --format "{{.Names}}" | grep -q "^$container$"; then
            echo "Updating $container..."

           
            available_container=$(docker ps --format "{{.Names}}" | grep -E 'srv[1-3]' | head -n 1)

            if [[ $container == $available_container ]]; then
                echo "$container remains running during update."
                continue
            fi

            
            docker stop $container
            docker rm $container
            docker run -d --name $container --cpuset-cpus="${container:3:1}" --network server-network $image_name
        fi
    done
}

# Track idle states for containers
idle_srv3_counter=0
idle_srv2_counter=0

# Launch the first container on CPU core 0
if ! docker ps --format "{{.Names}}" | grep -q "^srv1$"; then
    docker run -d --name srv1 --cpuset-cpus="0" --network server-network artnos1/optimafuncanew
fi

# Monitor containers
while :; do
    sleep 8 

    if docker ps --format "{{.Names}}" | grep -q "^srv1$"; then
        if [ $(is_busy srv1) -eq 1 ]; then
            echo "srv1 is busy for 8 seconds."

            if ! docker ps --format "{{.Names}}" | grep -q "^srv2$"; then
                docker run -d --name srv2 --cpuset-cpus="1" --network server-network artnos1/optimafuncanew
            fi
        fi
    fi

    if docker ps --format "{{.Names}}" | grep -q "^srv2$"; then
        if [ $(is_busy srv2) -eq 1 ]; then
            echo "srv2 is busy for 8 seconds."

            if ! docker ps --format "{{.Names}}" | grep -q "^srv3$"; then
                docker run -d --name srv3 --cpuset-cpus="2" --network server-network artnos1/optimafuncanew
                
                
            fi
        else
            idle_srv2_counter=$((idle_srv2_counter + 1))
            if [ $idle_srv2_counter -ge 2 ]; then
                echo "srv2 is idle for 16 consecutive seconds. Stopping it."
                docker stop srv2
                docker rm srv2
                idle_srv2_counter=0
            fi
        fi
    fi

    if docker ps --format "{{.Names}}" | grep -q "^srv3$"; then
        if [ $(is_busy srv3) -eq 0 ]; then
            idle_srv3_counter=$((idle_srv3_counter + 1))
            if [ $idle_srv3_counter -ge 2 ]; then
                echo "srv3 is idle for 16 consecutive seconds. Stopping it."
                docker stop srv3
                docker rm srv3
                idle_srv3_counter=0
            fi
        else
            idle_srv3_counter=0
        fi
    fi

    #check for updates (every 10 minutes)
    if (( $(date +%s) % 600 == 0 )); then
        echo "Checking for container updates..."
        update_containers
    fi

done

