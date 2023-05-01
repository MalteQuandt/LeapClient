# code taken from: https://pypi.org/project/python-osc/

import argparse

from pythonosc.dispatcher import Dispatcher
from pythonosc import osc_server
  
if __name__ == "__main__": 
  # generate arguments and their help list
  parser = argparse.ArgumentParser()
  parser.add_argument("--ip", default="127.0.0.1", help="The ip to listen to!")
  parser.add_argument("--port", type=int, default=9000, help="The port to listen to!")
  args = parser.parse_args()

  dispatcher = Dispatcher()
  # basic parameters, handle all requests
  dispatcher.map("/server/*", print)
  dispatcher.map("/godot/*", print)

  server = osc_server.ThreadingOSCUDPServer(
    server_address=(args.ip, args.port),
    dispatcher=dispatcher)
  print(f"Serving on {server.server_address}")
  server.serve_forever()