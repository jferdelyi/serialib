/**
 * @file /example5/main.cpp
 * @author Jean-François Erdelyi
 * @date July 2024
 * @brief File containing example of serial port communication
 *
 * This example show simple, ping-pong like communication
 */

 // Serial library
#include "../lib/serialib.h"
#include <iostream>
#include <thread>

// ofSerial standalone example
int main(int argc, char* argv[]) {

	// Check and get params 
	serialib l_serial;
	if (argc < 3) {
		std::cout << "Usage: serial <port> <baudrate>" << std::endl << std::endl;
		std::cout << "List of serial ports detected:" << std::endl;
		for (const auto& l_port : l_serial.getDeviceList()) {
			std::cout << "\t- " << l_port.deviceName << std::endl;
		}

		return EXIT_FAILURE;
	}
	char* l_port = argv[1];
	int l_baudrate = atoi(argv[2]);

	// Setup and connect serial
	bool l_connected = l_serial.openDevice(l_port, l_baudrate);
	if (l_connected) {
		std::cout << "CONNECTED" << std::endl;
	} else {
		std::cerr << "NOT CONNECTED" << std::endl;
		return EXIT_FAILURE;
	}

	// While is running
	char l_bytes_to_process[512];
	std::cout << std::endl;
	while (true) {

		// Get and send data
		std::string l_input;
		std::cout << "SEND DATA (EXIT to quit): ";
		std::getline(std::cin, l_input);
		if (l_input == "") {
			continue;
		} else if (l_input == "EXIT") {
			break;
		}
		l_serial.writeString(l_input.c_str());

		// Wait the answer
		while (!l_serial.available()) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		while (l_serial.available()) {
			// Print number of bytes 
			int l_char_read = l_serial.readString(l_bytes_to_process, '\n', 512);
			std::cout << std::endl << "RECEIVED " << std::dec << l_char_read << " BYTES" << std::endl;

			if (l_char_read > 0) {
				// Print hexa data
				std::cout << std::hex << std::uppercase;
				for (int i = 0; i < l_char_read; ++i) {
					std::cout << static_cast<unsigned short>(l_bytes_to_process[i] & 0x00FF) << " ";
				}

				// Print string data
				std::string l_data(l_bytes_to_process);
				l_data.erase(std::remove(l_data.begin(), l_data.end(), '\n'), l_data.cend());
				std::cout << std::dec << "-> " << l_data << std::endl;
			} else {
				switch (l_char_read) {
				case 0:
					std::cerr << "Error code: " << std::to_string(l_char_read) << " timeout is reached" << std::endl;
					break;
				case -1:
					std::cerr << "Error code: " << std::to_string(l_char_read) << " error while setting the timeout" << std::endl;
					break;
				case -2:
					std::cerr << "Error code: " << std::to_string(l_char_read) << " error while reading the character" << std::endl;
					break;
				case -3:
					std::cerr << "Error code: " << std::to_string(l_char_read) << " maximum of bytes is reached" << std::endl;
					break;
				default:
					std::cerr << "Error code: " << std::to_string(l_char_read) << " unknown error" << std::endl;
					break;
				}
			}
		}
	}

	// Close and return
	l_serial.closeDevice();
	std::cout << "CLOSED" << std::endl;
	return EXIT_SUCCESS;
}
