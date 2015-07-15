# JSQuery_Example
Example of a javascript call to a thrift backend using both a java and c++ backend service

## To Run
First run ``` ./compile.sh ``` and then ``` ./run.sh <port> ``` in the sudo_cc/ folder.

Then, in the sudo_service/ folder, run ``` make ``` followed by ``` ./server <port> <sudo_cc_port> ```

You can then open up JSQueryClient.html in your browser, add inputs, and press Ask Server to send. The client first asks the sudo_cc for a service with the name sirius (the sudo_service registers itself as sirius) and gets a HostPort value back. The client then constructs a query and sends it to the host and port it received from the sudo_cc. The service prints out the query data and returns "Done". All communication is done with JSON protocol and Http Transports, but the Java Http server (sudo_cc) is not multithreaded. It is based on the example java server in the [Thrift JS Lib](https://github.com/apache/thrift/tree/master/lib/js/test/src/test), but with a lot of unnecessary code removed. The sudo_service is written in C++, using the HttpClient to talk to the command center and the HttpServer Transport to recieve requests from the client. The sudo_service HttpClient transport throws a "No more data to read" error when registering with the sudo_cc, which I swallow and print, but ignore.
