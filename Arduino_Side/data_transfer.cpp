#include "data_transfer.h"

// Define the server's address
const char server1[] = "";  // Flask Server 1 IP address
const char server2[] = "";    // Flask Server 2 IP address

// Define global client and HTTP objects
WiFiClient client1;
HttpClient http1(client1, server1, 5000);  // Port 5000 for Flask

WiFiClient client2;
HttpClient http2(client2, server2, 5000);  // Port 5000 for Flask

void send_data1(String data) {
  // Send HTTP POST request
  http1.beginRequest();
  http1.post("/process");  // Endpoint on the server
  http1.sendHeader("Content-Type", "application/x-www-form-urlencoded");
  http1.sendHeader("Content-Length", String("data=" + data).length());
  http1.print("data=" + data);
  http1.endRequest();
}

void send_data2(String data) {
  // Send HTTP POST request
  http2.beginRequest();
  http2.post("/process");  // Endpoint on the server
  http2.sendHeader("Content-Type", "application/x-www-form-urlencoded");
  http2.sendHeader("Content-Length", String(5 + data.length()));  // Calculate content length
  http2.print("data=" + data);  // Send the data
  http2.endRequest();

  // Optionally, log the server response
  int statusCode = http2.responseStatusCode();
  String response = http2.responseBody();
  Serial.println("Server Response from send_data2: " + response);
}

String get_data1() {
  // Get the response
  int statusCode = http1.responseStatusCode();
  String response = http1.responseBody();
  return response;
}

String get_data2() {
  // Fetch the latest command from Server 2
  http2.get("/get_command");  // Endpoint to fetch the latest command
  http2.endRequest();

  // Wait for the server response
  int statusCode = http2.responseStatusCode();
  String response = http2.responseBody();
  Serial.println("Latest command from Server 2: " + response);
  return response;
}





