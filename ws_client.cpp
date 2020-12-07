#include "ws_client.h"



websocketpp::connection_hdl connection_metadata::get_hdl() const
{
  return m_hdl;
}

int connection_metadata::get_id() const
{
  return m_id;
}

std::string connection_metadata::get_status() const
{
  return m_status;
}


//// websocket_endpoint ///

websocket_endpoint::websocket_endpoint()
{
  m_endpoint.set_access_channels(websocketpp::log::alevel::all);
  m_endpoint.clear_access_channels(websocketpp::log::alevel::frame_payload);
  m_endpoint.set_error_channels(websocketpp::log::elevel::all);

  m_endpoint.init_asio();
  m_endpoint.start_perpetual();

  m_thread = websocketpp::lib::make_shared<websocketpp::lib::thread>(&client::run, &m_endpoint);
}

websocket_endpoint::~websocket_endpoint(){
	m_thread->join();
}

connection_metadata::ptr websocket_endpoint::connect(std::string const &uri)
{
  websocketpp::lib::error_code ec;

  m_endpoint.set_tls_init_handler([this](websocketpp::connection_hdl) {
    return websocketpp::lib::make_shared<websocketpp::lib::asio::ssl::context>(websocketpp::lib::asio::ssl::context::tlsv12);
  });

  client::connection_ptr con = m_endpoint.get_connection(uri, ec);

  if (ec)
  {
    std::cout << "> Connect initialization error: " << ec.message() << std::endl;
    return nullptr;
  }

  connection_metadata::ptr metadata_ptr = websocketpp::lib::make_shared<connection_metadata>(con->get_handle(), uri);

  con->set_open_handler(websocketpp::lib::bind(
      &connection_metadata::on_open,
      metadata_ptr,
      &m_endpoint,
      websocketpp::lib::placeholders::_1));
  con->set_message_handler(websocketpp::lib::bind(
      &connection_metadata::on_message,
      metadata_ptr,
      websocketpp::lib::placeholders::_1,
      websocketpp::lib::placeholders::_2));

  m_endpoint.connect(con);

  return metadata_ptr;
}

// void websocket_endpoint::close(connection_metadata::ptr metadata_ptr, websocketpp::close::status::value code, std::string reason)
// {
//   websocketpp::lib::error_code ec;
//   m_endpoint.close(metadata_ptr->get_hdl(), code, reason, ec);
//   if (ec)
//   {
//     std::cout << "> Error initiating close: " << ec.message() << std::endl;
//   }
// }

void websocket_endpoint::send(connection_metadata::ptr metadata_ptr, std::string message)
{
  websocketpp::lib::error_code ec;



  m_endpoint.send(metadata_ptr->get_hdl(), message, websocketpp::frame::opcode::text, ec);
  if (ec)
  {
    std::cout << "> Error sending message: " << ec.message() << std::endl;
    return;
  }
}

// connection_metadata::ptr websocket_endpoint::get_metadata(int id) const
// {
//   con_list::const_iterator metadata_it = m_connection_list.find(id);
//   if (metadata_it == m_connection_list.end())
//   {
//     return connection_metadata::ptr();
//   }
//   else
//   {
//     return metadata_it->second;
//   }
// }