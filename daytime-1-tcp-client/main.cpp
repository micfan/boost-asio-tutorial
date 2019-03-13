#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    try {
        if (argc != 2)
        {
            std::cerr << "Usage: client <host>, eg. $ client time.nist.gov" << std::endl;
            return 1;
        }
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "daytime");
        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        while (true)
        {
            boost::array<char, 1278> buf;
            boost::system::error_code ec;

            size_t len = socket.read_some(boost::asio::buffer(buf), ec);
            if (ec == boost::asio::error::eof)
            {
                break;
            } else if (ec) {
                throw boost::system::system_error(ec);
            }

            std::cout.write(buf.data(), len);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}