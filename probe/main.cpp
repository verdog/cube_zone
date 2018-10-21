#include <SFML/Network.hpp>

int main(int argc, char* argv[]) {
    sf::UdpSocket socket;
    char data[8] = "abcd123";
    std::size_t received;

    sf::IpAddress ip = "localhost";
    unsigned short port = 3001;

    socket.send(data, 8, ip, port);
    socket.receive(data, 8, received, ip, port);

    printf("Data: %s", data);
}