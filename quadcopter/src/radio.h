//wireless transceiver library
#include "RFM69.h"
#include <SPI.h>

// Addresses for this node. CHANGE THESE FOR EACH NODE!

#define NETWORKID     30   // Must be the same for all nodes
#define MYNODEID      1   // My node ID
#define TONODEID      2   // Destination node ID

// RFM69 frequency, uncomment the frequency of your module:

#define FREQUENCY     RF69_915MHZ

// AES encryption (or not):

#define ENCRYPT       false // Set to "true" to use encryption
#define ENCRYPTKEY    "TOPSECRETPASSWRD" // Use the same 16-byte key on all nodes

// Use ACKnowledge when sending messages (or not):

#define USEACK        true // Request ACKs or not

struct Radio 
{
private:
        RFM69 rfm69;
public:
        Radio();

        const char* Receive();
        void Send(const char* message, int len);
};