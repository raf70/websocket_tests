// #include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>
#include "connection.h"

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <sstream>


////////////////////////////////////////////////////////////////////////

class websocket_endpoint
{
public:
  websocket_endpoint();
  ~websocket_endpoint();

  connection_metadata::ptr connect(std::string const &uri);
  // void close(connection_metadata::ptr metadata_ptr, websocketpp::close::status::value code, std::string reason);
  void send(connection_metadata::ptr metadata_ptr, std::string message);
  // connection_metadata::ptr get_metadata(int id) const;

private:

  client m_endpoint;
  websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_thread;

};