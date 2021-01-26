#include "radio.h"

Radio::Radio()
{
    // Open a serial port so we can send keystrokes to the module:

    rfm69.initialize(FREQUENCY, MYNODEID, NETWORKID);
    rfm69.setHighPower(); // Always use this for RFM69HCW

    // Turn on encryption if desired:
    if (ENCRYPT)
        rfm69.encrypt(ENCRYPTKEY);

    Serial.print("Radio-");
    Serial.print(MYNODEID,DEC);
    Serial.println(" successfully initialized!"); 
}

const char* Radio::Receive()
{
    // RECEIVING

    // In this section, we'll check with the RFM69HCW to see
    // if it has received any packets:

    if (rfm69.receiveDone()) // Got one!
    {
        // Print out the information:

        Serial.print("received from node ");
        Serial.print(rfm69.SENDERID, DEC);
        Serial.print(", message [");

        // The actual message is contained in the DATA array,
        // and is DATALEN bytes in size:

        for (byte i = 0; i < rfm69.DATALEN; i++)
            Serial.print((char)rfm69.DATA[i]);

        // RSSI is the "Receive Signal Strength Indicator",
        // smaller numbers mean higher power.

        Serial.print("], RSSI ");
        Serial.println(rfm69.RSSI);

        // Send an ACK if requested.
        // (You don't need this code if you're not using ACKs.)

        if (rfm69.ACKRequested())
        {
            rfm69.sendACK();
            Serial.println("ACK sent");
        }
        return rfm69.DATA;
    }
    return nullptr;
}

void Radio::Send(const char* message, int len)
{
    // Set up a "buffer" for characters that we'll send:

    char sendbuffer[62];
    int sendlength = len;

    //copy the message we want to send into the sendbuffer
    for (int i = 0; i < sendlength; i++)
        sendbuffer[i] = message[i];

    // SENDING

    // Send the packet!
    Serial.print("sending to node ");
    Serial.print(TONODEID, DEC);
    Serial.print(", message [");
    for (byte i = 0; i < sendlength; i++)
        Serial.print(sendbuffer[i]);
    Serial.println("]");

    // There are two ways to send packets. If you want
    // acknowledgements, use sendWithRetry():

    if (USEACK) {     
        if (rfm69.sendWithRetry(TONODEID, sendbuffer, sendlength))
            Serial.println("ACK received!");
        else
            Serial.println("no ACK received");
    }
    // If you don't need acknowledgements, just use send():
    else // don't use ACK
    {
        rfm69.send(TONODEID, sendbuffer, sendlength);
    }

    sendlength = 0; // reset the packet
}