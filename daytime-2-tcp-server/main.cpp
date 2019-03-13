#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

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
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

        while (true)
        {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::string message = make_daytime_string();
            boost::system::error_code ignored_ec;

            boost::asio::write(socket, boost::asio::buffer(message), ignored_ec);

            std::cout << message << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}