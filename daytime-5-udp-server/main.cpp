#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::udp;

std::string make_daytime_string() {
    using namespace std; // For time_t, time, and ctime;
    time_t now = time(0);
    return ctime(&now);
}

int main(int argc, char* argv[])
{
    try {
        std::cout << "Listening on ipv4 port: 13" << std::endl;

        boost::asio::io_context io_context;
        udp::socket socket(io_context, udp::endpoint(udp::v4(), 13));

        while (true)
        {
            boost::array<char, 1> recv_buf;
            udp::endpoint remote_endpoint;

            socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint);

            std::string message = make_daytime_string();

            boost::system::error_code ignored_error;
            socket.send_to(boost::asio::buffer(message),
                    remote_endpoint, 0, ignored_error);

            std::cout << message << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}