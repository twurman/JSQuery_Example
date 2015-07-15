# JSQuery_Example
Example of a javascript call to a thrift backend using both a java and c++ backend service

## To Run
First run ``` ./compile.sh ``` and then ``` ./run.sh <port> ``` in the pseudo_cc/ folder.

Then, in the pseudo_service/ folder, run ``` make ``` followed by ``` ./server <port> <pseudo_cc_port> ```

You can then open up JSQueryClient.html in your browser, add inputs, and press Ask Server to send. 

## How it works
The client first asks the pseudo_cc for a service with the name sirius (the pseudo_service registers itself as sirius) and gets a HostPort value back. The client then constructs a query and sends it to the host and port it received from the pseudo_cc. The service prints out the query data and returns "Done". All communication is done with JSON protocol and Http Transports, but the Java Http server (pseudo_cc) is not multithreaded. It is based on the example java server in the [Thrift JS Lib](https://github.com/apache/thrift/tree/master/lib/js/test/src/test), but with a lot of unnecessary code removed. The pseudo_service is written in C++, using the HttpClient to talk to the command center and the HttpServer Transport to recieve requests from the client. The pseudo_service HttpClient transport throws a "No more data to read" error when registering with the pseudo_cc, which I swallow and print, but ignore.
