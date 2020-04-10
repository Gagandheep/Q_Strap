# Q-Strap

## Description

The strap is fitted in the person's hand just like a watch. The two wifi are configured in such a way where the nodemcu present in the sticker acts as access point, while the one present at the strap , acts as a station.The station module gets connected to the access point. Thus for this connection  to happen between the two wifi modules, they have to be in a range of 30 meters, which almost lies in the distance from any part of the house to the door. Thus if the person moves out of his house, connection is lost as a result of which the buzzer and LED in both the strap and the sticker gets activated, thus alerting the neighbours and the public around the person that he has violated the quarantine period and they can alert the police officials. Also when communication between two modules is lost, the nodemcu waits for 3 minutes , if connection is not established, an SMS alert is sent to police control via GSM MODULE containing the ID of the person and necessary action will be taken
The user is provided with two lipo batteries and a charger module, while he is using one battery, he can charge the other, from calculations made by us one battery can last up to 10 hours, he will have to change the battery within 3 minutes.

## Hardware Requirements

### Strap
1. NodeMCU
2. Buzzer
3. 3.7V 240mAh li-polymer battery
4. LED
5. TP4056

### Sticker
1. NodeMCU
2. Buzzer
3. 18650 li-ion battery
4. GSM Module
5. LED

## Software Requirements
1. Arduino IDE (for setup)
