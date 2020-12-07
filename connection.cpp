#include "connection.h"


connection_metadata::connection_metadata(){}


connection_metadata::connection_metadata(websocketpp::connection_hdl hdl, std::string uri)
	: m_hdl(hdl), m_status("Connecting"), m_uri(uri), m_server("N/A")
{
}


void connection_metadata::on_open(client *c, websocketpp::connection_hdl hdl)
{
  m_status = "Open";

  client::connection_ptr con = c->get_con_from_hdl(hdl);
  m_server = con->get_response_header("Server");
}

void connection_metadata::on_message(websocketpp::connection_hdl, client::message_ptr msg)
{
  if (msg->get_opcode() == websocketpp::frame::opcode::text)
  {
    std::cout << "connection_metadata << " << msg->get_payload() << std::endl;
  }
  else
  {
    // TODO: decide if this needs to be handled
  }
}