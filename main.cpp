#include "ws_client.h"


int main() {
    bool done = false;
    std::string input;
    websocket_endpoint endpoint;
		connection_metadata::ptr hdl_id;

    while (!done) {
        std::cout << "Enter Command: ";
        std::getline(std::cin, input);

        if (input == "quit") {
            done = true;
        } else if (input == "help") {
            std::cout
                << "\nCommand List:\n"
                << "connect <ws uri>\n"
                << "send <connection id> <message>\n"
                << "show <connection id>\n"
                << "help: Display this help text\n"
                << "quit: Exit the program\n"
                << std::endl;
        } else if (input == "connect") {
            hdl_id = endpoint.connect("wss://echo.websocket.org");
            if (hdl_id != nullptr) {
                std::cout << "> Created connection with id " << hdl_id->get_id() << std::endl;
            } else {
							std::cout << "Connection failed" << std::endl;
						}
        } else if (input.substr(0,4) == "send") {
            std::stringstream ss(input);
            
            std::string cmd;
            int id;
            std::string message;
            
            ss >> cmd >> id;
            std::getline(ss,message);
            
            endpoint.send(hdl_id, message);
        } else {
           endpoint.send(hdl_id, input);
        }
    }

    return 0;
}