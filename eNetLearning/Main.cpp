#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#define ENET_IMPLEMENTATION
#include "enet.h"

#define newline "\n"

#ifdef _DEBUG // defing logging macros in debug mode.
#define log(msg) cout << msg << newline;
#define logv(var) cout << #var << " is: " << var << newline;
#else // deleting logging macros in release mode.
#define log(msg)
#define logv(var)
#endif

using std::cout;
using std::cin;

#define MAX_CLIENTS 30

int main()
{
    if (enet_initialize() != 0) {
        cout << "ENet failed to initialize!\n";
        return EXIT_FAILURE;
    }

    cout << "ENet initialized successfully!\n";

    ENetAddress address = { 0 };
    address.host = ENET_HOST_ANY;
    address.port = 7777;

    ENetHost* server = enet_host_create(&address, MAX_CLIENTS, 5, 0, 0);

    if (server == nullptr) {
        cout << "ENet failed to create a server! Firewall is blocking the socket.\n";
        enet_deinitialize();
        return EXIT_FAILURE;
    }

    cout << "Survival game server is up and running successfully on port 7777! 🎉\n";

    // Keep the server alive waiting for input
    ENetEvent event;
    int counter = 0;
    while (true) {
        while (enet_host_service(server, &event, 10) > 0) {
            log("we caught a network event!");

            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT: {
                log("new player connected to he server!");
                char ipBuffer[64];
                enet_address_get_host_ip(&event.peer->address, ipBuffer, sizeof(ipBuffer));
                logv(event.peer->address.port);
                break;
            }

            case ENET_EVENT_TYPE_RECEIVE: {
                char ipBuffer[64];
                enet_address_get_host_ip(&event.peer->address, ipBuffer, sizeof(ipBuffer));
                logv(event.peer->address.port);
                enet_packet_destroy(event.packet);
                break;
            }

            case ENET_EVENT_TYPE_DISCONNECT: {
                log("player disconnected from the game!");
                char ipBuffer[64];
                enet_address_get_host_ip(&event.peer->address, ipBuffer, sizeof(ipBuffer));
                logv(event.peer->address.port);
                event.peer->data = (void*)nullptr;
                break;
            }

            case ENET_EVENT_TYPE_NONE:
                break;
            }
        }
        log("Waiting for event...");
        counter++;
        if (counter == 5) break;
    }

    enet_host_destroy(server);
    enet_deinitialize();

    cout << "Server shutdown clearly & safely!\n";
    return 0;
}