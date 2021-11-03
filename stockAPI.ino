
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

//symbol[] =
void setup() {

  USE_SERIAL.begin(115200);
  // USE_SERIAL.setDebugOutput(true);


  WiFiMulti.addAP("", "");//ENter Network SSID and Password here

}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    for (int i = 0;i<4;i++) {  //Change i according to the length of symbol[]
    HTTPClient http;
    String symbol[] = {"BTC","AAPL","TSLA","F"};//Enter Tickers here
    String API[] = {"","","",""};//Enter API Key here
    String url = "/apps/thinghttp/send_request?api_key="+ API[i];
    USE_SERIAL.print("[HTTP] begin...");
    // configure traged server and url
    // get the entry_id from Thingspeak from the ThingHTTP TweetControl
    http.begin("api.thingspeak.com", 80, url); //HTTP

    USE_SERIAL.print("[HTTP] GET...");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      //USE_SERIAL.printf("[HTTP] GET... code: %d", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const char* payload = http.getString();
        // Print the string value from Thingspeak
        
        USE_SERIAL.println(symbol[i]+" "+ payload);

      }
    } else {
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
  }

  delay(10000);
}
