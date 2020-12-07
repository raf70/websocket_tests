#include "ws_client.h"


// class derived: public websocket_endpoint
// {
// private:
	
	
// public:
// 	derived(/* args */);
// 	~derived();
// };

// derived::derived(/* args */)
// {
// }

// derived::~derived()
// {
// }


class listener: public connection_metadata {  

	public:
  typedef websocketpp::lib::shared_ptr<listener> ptr;

  listener(websocketpp::connection_hdl hdl, std::string uri);
  void on_open(client *c, websocketpp::connection_hdl hdl);
  void on_message(websocketpp::connection_hdl, client::message_ptr msg);


};