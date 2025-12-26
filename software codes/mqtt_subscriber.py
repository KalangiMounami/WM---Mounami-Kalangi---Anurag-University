import paho.mqtt.client as mqtt
import json

def on_message(client, userdata, msg):
    data = json.loads(msg.payload.decode())
    print("Received:", data)

client = mqtt.Client()
client.connect("broker.hivemq.com", 1883)
client.subscribe("smartbin/data")
client.on_message = on_message

client.loop_forever()
