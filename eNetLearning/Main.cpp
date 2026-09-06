#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#define ENET_IMPLEMENTATION
#include "enet.h"

#ifdef _DEBUG // defing logging macros in debug mode.
#define newline "\n"
#define log(msg) cout << msg << newline;
#define logv(var) cout << #var << " is: " << var << newline;
#else // deleting logging macros in release mode.
#define newline
#define log(msg)
#define logv(var)
#endif

using std::cout;
using std::cin;

#define MAX_CLIENTS 30

int main()
{
	if (enet_initialize() != 0) {
		log("ENet failed to initialize!");
		return EXIT_FAILURE;
	}

	log("ENet initialized successfully!");

	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = 7777;

	ENetHost* server = enet_host_create(&address, MAX_CLIENTS, 5, 0, 0);

	if (server == nullptr) {
		log("ENet failed to create a server, pls make sure your firewall doesnt block the conneciton or your computer connection drives arent broken!");
		log("Restart your internet if your internet connection got blocked!");
		return EXIT_FAILURE;
	}

	log("ENet created the server successfully!");
	log("Survival game is up and running on port 7777");

	enet_host_destroy(server);
	enet_deinitialize();

	log("Server shutdown clearly & safely!");
	std::cin.get();
}