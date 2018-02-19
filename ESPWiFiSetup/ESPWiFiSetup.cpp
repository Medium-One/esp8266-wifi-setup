#include "ESPWiFiSetup.h"

ESPWiFiSetup::ESPWiFiSetup() {
}

/*
 * This starts the WiFi in AP mode and initializes the DNS and webserver.
 */
void ESPWiFiSetup::start() {
    WiFi.mode(WIFI_AP);
    DEBUG_EWS(F("WiFi AP mode"));
    WiFi.softAPConfig(_apIP, _apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(_apSSID, _apPassword);

    IPAddress myIP = WiFi.softAPIP();
    DEBUG_EWS(F("AP IP address: "));
    DEBUG_EWS(myIP);

    // Setup DNS.
    dnsServer.reset(new DNSServer());
    // If DNS is started with "*" for domain name, it will reply with provided IP to all DNS request.
    dnsServer->setErrorReplyCode(DNSReplyCode::NoError);
    dnsServer->start(DNS_PORT, "*", _apIP);

    // Setup Webserver.
    server.reset(new ESP8266WebServer(80));
    server->on("/", std::bind(&ESPWiFiSetup::handleRoot, this));
    server->on("/submit", std::bind(&ESPWiFiSetup::submit, this));
    server->onNotFound(std::bind(&ESPWiFiSetup::handleRoot, this));
    
    server->begin();
    DEBUG_EWS(F("HTTP server started"));
}

void ESPWiFiSetup::start(const char *apSSID, const char *apPassword, const __FlashStringHelper *image) {
    _apSSID = apSSID;
    _apPassword = apPassword;
    _image = image;
    int count = 0;
    connect = false;
    // Start the WiFi AP, Web server and DNS server.
    start();

    while(1) {
        // Handle DNS request.
        dnsServer->processNextRequest();

        // Handle HTTP request.
        server->handleClient();

        if (connect) {
            connect = false;

            if (connectWiFi() != WL_CONNECTED) {
                Serial.println(F("Failed to connect to WiFi"));
            } else {
                printWiFi();
                // Connected to WiFi. Switch to station mode.
                WiFi.mode(WIFI_STA);
                break;
            }
        } else {
            if (WiFi.SSID()) {
                // Connect to wifi using old credentials. Comment it, if require to start without using old credentials.
                WiFi.begin();

                int result = WiFi.waitForConnectResult();
                DEBUG_EWS(F("Conn result: "));
                DEBUG_EWS(result);
                
            	if (WiFi.status() != WL_CONNECTED) {
                    if(count == 0){
                    DEBUG_EWS(F("Failed to connect to old WiFi."));
                    count++;
                    }
            	} else {
                    Serial.println(F("\nConnected to last saved WiFi credentials:"));
                    printWiFi();
                    // Connected to WiFi. Switch to station mode.
                    WiFi.mode(WIFI_STA);
                    break;
                }
            }
        }
        yield();
    }

    server.reset();
    dnsServer.reset();
}

void ESPWiFiSetup::handleRoot() { 
    String first_page = FPSTR(HTTP_HEAD);
    first_page.replace("{v}", "Configure with WiFi Credentials");
    first_page += FPSTR(HTTP_STYLE);
    first_page += FPSTR(HTTP_FORM_STYLE);
    first_page += FPSTR(HTTP_HEAD_END);
    first_page += FPSTR(HTTP_IMAGE_HEAD);
    first_page += _image;
    first_page += FPSTR(HTTP_IMAGE_END);
    first_page += FPSTR(HTTP_FORM_START);
    first_page += FPSTR(HTTP_FORM_END);
    first_page += FPSTR(HTTP_END);

    server->sendHeader("Content-Length", String(first_page.length()));
    server->send(200, FPSTR(TEXT_HTML_SEND), first_page);
}

int ESPWiFiSetup::connectWiFi() {
    WiFi.begin(ssid, password);
    int result = WiFi.waitForConnectResult();

    DEBUG_EWS(F("Conn result: "));
    DEBUG_EWS(result);
    return result;
}

/*
 * This is called when WiFi information is submitted.
 */
void ESPWiFiSetup::submit() {
    String configured_page = FPSTR(HTTP_HEAD_SAVED_PAGE);
    configured_page.replace("{v}", "WiFi Configured");
    configured_page += FPSTR(HTTP_STYLE);
    configured_page += FPSTR(HTTP_HEAD_END);
    configured_page += FPSTR(HTTP_IMAGE_HEAD);
    configured_page += _image;
    configured_page += FPSTR(HTTP_IMAGE_END);
    configured_page += FPSTR(HTTP_SAVED);
    configured_page += FPSTR(HTTP_END);
    
    if (server->hasArg("ssid") && server->hasArg("password")) {
        server->arg("ssid").toCharArray(ssid, sizeof(ssid) - 1);
        server->arg("password").toCharArray(password, sizeof(password) - 1);

        server->sendHeader(FPSTR(CACHE_CONTROL_SEND_HEADER), FPSTR(NO_CACHE_STORE_REVALIDATE_SEND_HEADER));
        server->sendHeader(FPSTR(PRAGMA_SEND_HEADER), FPSTR(NO_CACHE_SEND_HEADER));
        server->sendHeader(FPSTR(EXPIRES_SEND_HEADER), FPSTR(MINUS_ONE_SEND_HEADER));
        server->send(200, FPSTR(TEXT_HTML_SEND), configured_page);
        
        // Try connecting to this new WiFi.
        connect = true;
    }
}

/*
 * Print WiFi information.
 */
void ESPWiFiSetup::printWiFi() {
    Serial.println (F( "" ));
    Serial.print (F( "Connected to " ));
    Serial.println ( WiFi.SSID() );
    Serial.print (F( "IP address: " ));
    Serial.println ( WiFi.localIP() );
}

void ESPWiFiSetup::setDebugOutput(boolean debug) {
    _debug = debug;
}

template <typename Generic>
void ESPWiFiSetup::DEBUG_EWS(Generic text) {
    if (_debug) {
        Serial.print("*EWS: ");
        Serial.println(text);
    }
}
