#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>

// Let's party on this port! 🎉
const int PARTY_PORT = 9999;

int main()
{
    // Time to summon our magical communication portal!
    int magicPortal = socket(AF_INET, SOCK_STREAM, 0);
    if (magicPortal < 0)
        std::cout << "Oops! Our magic portal failed to materialize! 🙈\n";

    // Prepare the ritual circle (aka server address)
    struct sockaddr_in wizardTower, guestBook;
    memset(&wizardTower, 0, sizeof(wizardTower));
    wizardTower.sin_family = AF_INET;  // Internet spells only!
    wizardTower.sin_port = htons(PARTY_PORT);
    wizardTower.sin_addr.s_addr = INADDR_ANY;  // We welcome all dimensional travelers!

    // Bind our magic to this realm
    if (bind(magicPortal, (struct sockaddr*)&wizardTower, sizeof(wizardTower)) < 0)
    {
        std::cout << "Oh no! Our magic is too strong for this realm! 💥\n";
    }

    // Listen for the whispers of incoming connections
    listen(magicPortal, 5);  // We can handle 5 simultaneous interdimensional calls!

    while (true) {  // The eternal dance of the server
        socklen_t guestBookSize = sizeof(guestBook);
        int newVisitor = accept(magicPortal, (struct sockaddr*)&guestBook, &guestBookSize);

        // Prepare the mystical scrolls
        char ancientScroll[512];
        memset(&ancientScroll, 0, 512);

        // Our secret message to the universe!
        const char* cosmicResponse = 
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Content-Length: 67\r\n"
                "\r\n"
                "<html><body>Greetings, traveler of the digital realm! 🌌</body></html>";

        // Read the visitor's message from the ether
        int scrollLength = read(newVisitor, ancientScroll, 511);
        
        // Send our cosmic response
        write(newVisitor, cosmicResponse, strlen(cosmicResponse));

        if (scrollLength < 0)
            std::cout << "The cosmic winds are too strong! We couldn't read the message! 🌪️\n";

        // Echo the traveler's message to our mystical log
        std::cout << "A visitor whispers: " << ancientScroll << "\n";

        // Close the interdimensional portal for this visitor
        close(newVisitor);

        // Easter egg: Every 42nd visitor gets a special message!
        static int visitorCount = 0;
        if (++visitorCount % 42 == 0) {
            std::cout << "Don't panic! You're the 42nd visitor! 🎊🐬\n";
        }
    }

    // Close the master portal (but we never reach here in this eternal server)
    close(magicPortal);
    
    return 0;  // The journey ends, but the legend lives on!
}
