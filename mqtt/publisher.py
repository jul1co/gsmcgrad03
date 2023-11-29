import paho.mqtt.client as mqtt
import time, random


def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))


client = mqtt.Client()
client.on_connect = on_connect

# Replace "localhost" with the IP address of the machine running Docker, if necessary
client.connect("localhost", 1883, 60)
client.loop_start()


for _ in range(30):
    value = random.randint(0, 1)
    sleep_time = random.randint(1, 60)

    client.publish("test/topic", value)
    time.sleep(sleep_time)


client.loop_stop()
