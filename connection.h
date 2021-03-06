#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>



typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;


class connection_metadata
{

public:
  typedef websocketpp::lib::shared_ptr<connection_metadata> ptr;
	

	connection_metadata();
  connection_metadata(websocketpp::connection_hdl hdl, std::string uri);
	void on_open(client *c, websocketpp::connection_hdl hdl);
  void on_message(websocketpp::connection_hdl, client::message_ptr msg);


	websocketpp::connection_hdl get_hdl() const;
  int get_id() const;
  std::string get_status() const;
  std::string get_hostname() const;

protected:
  int m_id;
  websocketpp::connection_hdl m_hdl;
  std::string m_status;
  std::string m_uri;
  std::string m_server;
  std::string m_error_reason;

};
