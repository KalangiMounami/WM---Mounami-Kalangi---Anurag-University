import paho.mqtt.publish as publish
import json
import time

data = {
    "bin_id": 1,
    "fill": 85
}

publish.single(
    topic="smartbin/data",
    payload=json.dumps(data),
    hostname="broker.hivemq.com"
)

print("Data published")
