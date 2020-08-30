#include <ESP8266WiFi.h> 
#include <PubSubClient.h> 
#include "displaySystem.h"

#ifndef CONNECTIONSYSTEM
#define CONNECTIONSYSTEM

#define NO_OF_SAVED_WIFI 3
char * wifiPoints[NO_OF_SAVED_WIFI][2] = {
    {
        "TP-Link_6329",
        "2051313908"
    }, {
        "ECUA",
        "godofwar"
    }, {
        "abc",
        "joshua123"
    }
};
void handleClientConn(WiFiClient client_conn);

class ConnectionSystem
{
    private : const char * mqttServer = "192.168.0.121";
    const int mqttPort = 1885;
    const char * mqttUser = "";
    const char * mqttPassword = "";

    char * fallback_ssid = "TP-Link_6329";
    char * fallback_password = "2051313908";

    char * current_ssid;

    std :: function < void(char *, uint8_t *, unsigned int) > callback;

    WiFiClient espClient;
    PubSubClient * client;
    WiFiServer * server;

    char * device_id;

    public : ConnectionSystem(char * mqtt_device_id, std :: function < void(char *, uint8_t *, unsigned int) > callback_fn) {
        client = new PubSubClient(espClient);
        server = new WiFiServer(80);

        callback = callback_fn;
        device_id = mqtt_device_id;
    } ~ConnectionSystem() {
        delete(client);
        delete(server);
    }

    char * getSSID() {
        return current_ssid;
    }

    void setCallback(std :: function < void(char *, uint8_t *, unsigned int) > callback) {
        client-> setCallback(callback);
    }

    void loop() {
        client->loop();

        WiFiClient client_conn = server-> available(); // Listen for incoming clients
        String header;
        String output5State = "off";
        String output4State = "off";

        if (client_conn) { // If a new client_conn connects,
            handleClientConn(client_conn);

        }

        ////////////////////////////////////////////////////////////////////////////////
        // ////////////////////////////////////////////////////////
        // //////////////////////////////////////////////////////////////////////////////
        // ////////////////////////////////////////////////////////
        // //////////////////////////////////////////////////////////////////////////////
        // ////////////////////////////////////////////////////////
    }

    void sendMessage(char * topic, char * message) {
        client-> publish(topic, message);
    }

    void connectToMQTT() {
        client-> setServer(mqttServer, mqttPort);
        setCallback(callback);
        while (!client-> connected()) {
            Serial.println("Connecting to MQTT...");

            if (client-> connect(device_id, mqttUser, mqttPassword)) {
                Serial.println("connected");
            } else {
                Serial.print("failed with state ");
                Serial.print(client-> state());
                delay(2000);
            }
        }

        subscribeToAll();
    }

    void subscribeToAll() {
        // For Test
        client-> subscribe("esp/test");

    }

    void reconnectOnDisconnect(int interval) {
        while (!client-> connected()) {
            Serial.println();
            Serial.println("Reconnecting to MQTT...");

            if (client-> connect(device_id, mqttUser, mqttPassword)) {
                Serial.println("connected");
                subscribeToAll();
            } else {
                Serial.print("\nFailed with state: ");
                Serial.println(client-> state());
                delay(interval);
            }
        }
    }
    void connectToWifi() {
        connectToWifi(fallback_ssid, fallback_password);
    }
    void connectToWifi(char * ssid, char * password) {
        WiFi.begin(ssid, password);
        current_ssid = ssid;

        Serial.println();
        Serial.print("Connecting to ");
        Serial.println(ssid);
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println();
        Serial.print("Connected, IP address: ");
        Serial.println(WiFi.localIP());

    }

    void searchAndConnectWifi(DisplaySystem * drawer) {
        drawer-> drawStartScreen("Searching");

        int noOfWifi = WiFi.scanNetworks();
        Serial.print("No. of wifis in range: ");
        Serial.println(noOfWifi);

        Serial.println(" network(s) found");
        bool connected = false;
        for (int i = 0; i < noOfWifi && !connected; i++) {
            Serial.printf("%d: %s, Ch:%d (%ddBm) %s\n", i + 1, WiFi.SSID(i).c_str(), WiFi.channel(i), WiFi.RSSI(i), WiFi.encryptionType(i) == ENC_TYPE_NONE
                ? "open"
                : "");

            for (int j = 0; j < NO_OF_SAVED_WIFI; j++) {
                if (strcmp(WiFi.SSID(i).c_str(), wifiPoints[j][0]) == 0) {
                    drawer -> drawStartScreen("Connecting", wifiPoints[j][0]);

                    connectToWifi(wifiPoints[j][0], wifiPoints[j][1]);
                    server -> begin(); // for the control panel

                    connected = true;
                    break;
                }
            }
        }
    }
};

void generateHTMLPage(WiFiClient client_conn) {
    String header,output5State , output4State; 

    client_conn.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "<link rel=\"icon\" href=\"data:,\">"
    "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}"
    ".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;"
    "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}"
    ".button2 {background-color: #77878A;}</style>"
    "<link href='https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css' rel='stylesheet' integrity='sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO' crossorigin='anonymous'>"
    "<script src='https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js' integrity='sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy' crossorigin='anonymous'></script>        "
    "</head>"
    "<body>"
"<div class='row' style='height: 20%;'>"
"</div>"
"<div class='row'>"
"<div class='col-sm-2'></div>"
"<div class='col-sm-8'>"
"<h1>dWatch V0.8</h1>"
" <form class='form-horizontal' action='/submit'>"
"  <div class='form-group'>"
"    <label class='control-label col-sm-12' for='devicename'>Device name(No spaces):</label>"
"    <div class='col-sm-10'>"
"      <input type='text' class='form-control' id='devicename' placeholder='Enter Device Name'>"
"    </div>"
"  </div>"
"  <div class='form-group'>"
"    <label class='control-label col-sm-12' for='mqttip'>MQTT IP(like 192.168.1.103):</label>"
"    <div class='col-sm-10'>"
"      <input type='text' class='form-control' id='mqttip' placeholder='Enter MQTT Server IP'>"
"    </div>"
"  </div>"
"  <div class='form-group'>"
"    <label class='control-label col-sm-12' for='patientid'>Patient ID(nospaces):</label>"
"    <div class='col-sm-10'>"
"      <input type='text' class='form-control' id='patientid' placeholder='Enter Patient ID'>"
"    </div>"
"  </div>"
"  <div class='form-group'>"
"    <div class='col-sm-offset-2 col-sm-10'>"
"      <button type='submit' class='btn btn-default'>Submit</button>"
"    </div>"
"  </div>"
"</form> "
"</div>"
"<div class='col-sm-2'></div>"
"</div>"


"</body></html>");

    client_conn.println();    // The HTTP response ends with another blank line
}

void updateConfig(String data) {
    int devicename_index=data.indexOf("devicename=");
    int mqttserverip_index=data.indexOf("mqttip=");
    int patientid_index=data.indexOf("patientid=");
    int end=data.indexOf(" ", patientid_index);

    String devicename = data.substring(devicename_index, mqttserverip_index-1);// to remove the '&'
    String mqttserverip = data.substring(mqttserverip_index, patientid_index-1);// to remove the '&'
    String patientid = data.substring(patientid_index, end);
    
    Serial.println("-----------");
    Serial.println(devicename);
    Serial.println(mqttserverip);
    Serial.println(patientid);
    Serial.println();

    Serial.println("-----------");
    Serial.println("-----------");

}


void handleClientConn(WiFiClient client_conn) {
    Serial.println("New client_conn."); // print a message out in the serial port
    String currentLine = ""; // make a String to hold incoming data from the client_conn
    String header,output5State , output4State; 
    while (client_conn.connected()) { // loop while the client_conn's connected
        if (client_conn.available()) { // if there's bytes to read from the client_conn,
            char c = client_conn.read(); // read a byte, then
            Serial.write(c); // print it out the serial monitor
            header += c;
            
            if (c == '\n') { // if the byte is a newline character
                // if the current line is blank, you got two newline characters in a row. that's
                // the end of the client_conn HTTP request, so send a response:
                if (currentLine.length() == 0) {
                    // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK) and a
                    // content-type so the client_conn knows what's coming, then a blank line:
                    client_conn.println("HTTP/1.1 200 OK");
                    client_conn.println("Content-type:text/html");
                    client_conn.println("Connection: close");
                    client_conn.println();

                    // turns the GPIOs on and off
                    if (header.indexOf("GET /submit") >= 0) {
                        Serial.println("** an update request sent");
                        updateConfig(header);
                        
                    }
                    generateHTMLPage(client_conn);

                    // Break out of the while loop
                    break;
                } else { // if you got a newline, then clear currentLine
                    currentLine = "";
                }
            } else if (c != '\r' && c != '\n') { // if you got anything else but a carriage return character,
                currentLine += c; // add it to the end of the currentLine
            } 
        }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client_conn.stop();
    Serial.println("client_conn disconnected.");
    Serial.println("");
}

#endif