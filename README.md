# ESP-NOW Stasis Workshop
#### Questions? Send a message to @mpk or find me in-person

## Step One: find MAC address of receiver
To begin, clone and extract this here repository. All relevant code files _should_ be in the `/firmware` folder.

ESP-NOW can be configured as either one-way or two-way. This demonstration uses one-way funcitonality.

1. Open the `mac-address` Arduino file in your IDE of choice and upload it to the **receiver ESP32**.
2. Once uploaded, open the Serial monitor (magnifying glass in top-right), set baud rate to 115200, and find the copy the 6-digit hex address _(e.x. E8:DB:84:DD:DA:16)_

## Step Two: Configure & upload sender code
Next, we need to configure our sender code to address to the MAC address of the receiver!

1. Open the `sender` Arduino file in you IDE of choice. **Don't upload yet**
2. Modify the `broadcastAddress` array (line 5) to the MAC address. Example:
    1. Given address `E8:DB:84:DD:DA:16`, -> `uint8_t broadcastAddress[] = {0xE8, 0xDB, 0x84, 0xDD, 0xDA, 0x16};`
3. Upload to **sender ESP32**. Monitor the Serial Monitor for packet statuses.

## Step Three: Upload receiver code
Finally, we need to upload our receiver code.

1. Open the `receiver` Arduino file in your IDE of choice.
2. Make sure the receive struct on line 6 matches that of the sender struct! Otherwise, you'll get garbled data since the bytes don't match.
3. Upload to **receiver ESP32**, the same one we uploaded the MAC address code.
4. Monitor the Serial Monitor for incoming packets.