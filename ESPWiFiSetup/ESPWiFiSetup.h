#ifndef ESPWiFiSetup_h
#define ESPWiFiSetup_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <EEPROM.h>

static const char CACHE_CONTROL_SEND_HEADER[] PROGMEM = "Cache-Control";
static const char NO_CACHE_STORE_REVALIDATE_SEND_HEADER[] PROGMEM = "no-cache, no-store, must-revalidate";
static const char PRAGMA_SEND_HEADER[] PROGMEM = "Pragma";
static const char NO_CACHE_SEND_HEADER[] PROGMEM = "no-cache";
static const char EXPIRES_SEND_HEADER[] PROGMEM = "Expires";
static const char MINUS_ONE_SEND_HEADER[] PROGMEM = "-1";
static const char TEXT_HTML_SEND[] PROGMEM = "text/html";

static const char HTTP_HEAD[] PROGMEM                 = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/><title>{v}</title>";
static const char HTTP_STYLE[] PROGMEM                = "<style>.login{margin:0 auto auto;max-width:80%;max-height:60%} .login-header{text-align:center;margin:0;max-width:140%;padding:0;} .c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:95%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#fff;color:#1fa3ec;line-height:2.4rem;font-size:1.2rem;width:100%;} .q{float: right;width: 64px;text-align: right;} .l{background: url(\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAALVBMVEX///8EBwfBwsLw8PAzNjaCg4NTVVUjJiZDRUUUFxdiZGSho6OSk5Pg4eFydHTCjaf3AAAAZElEQVQ4je2NSw7AIAhEBamKn97/uMXEGBvozkWb9C2Zx4xzWykBhFAeYp9gkLyZE0zIMno9n4g19hmdY39scwqVkOXaxph0ZCXQcqxSpgQpONa59wkRDOL93eAXvimwlbPbwwVAegLS1HGfZAAAAABJRU5ErkJggg==\") no-repeat left center;background-size: 1em;}";
static const char HTTP_FORM_STYLE[] PROGMEM           = ".login-form {text-align:left;display:inline-block;min-width:260px;border:.5px solid #fff;background:#4facff;border-radius:10px;box-shadow:0px 0px 10px #000;box-sizing:border-box;padding-top:10%;padding-bottom:10%;margin:5% auto;}";
static const char HTTP_HEAD_END[] PROGMEM             = "</style></head>";
static const char HTTP_IMAGE_HEAD[] PROGMEM           = "<body><div class='login'><div class='login-header'><img src='";
static const char HTTP_IMAGE_END[] PROGMEM            = "' style='width:100%;'></div></div>";
static const char HTTP_FORM_START[] PROGMEM           = "<div class='login-form'><form method='post' action='/submit'><input id='s' name='ssid' length=32 placeholder='SSID'><br/><br/><input id='p' name='password' length=64 type='password' placeholder='Password'><br/>";
static const char HTTP_FORM_END[] PROGMEM             = "<br/><button type='submit'>save</button></form>";
static const char HTTP_END[] PROGMEM                  = "</div></body></html>";
static const char HTTP_HEAD_SAVED_PAGE[] PROGMEM      = "<!DOCTYPE html><html><head>";
static const char HTTP_SAVED[] PROGMEM                = "</br></br></br><h2 style='text-align:center;font-size:48px;'>WiFi credentials saved!<br/><br/>If successfully connected to Wifi, this will automatically exit.<br/>Otherwise you can repeat this process and try again.</h2>";

class ESPWiFiSetup
{
    public:
        ESPWiFiSetup();
    
        //image is a string stored in flash which contains a base 64 encoded image string.
        void start(char const *apSSID, char const *apPassword = NULL, const __FlashStringHelper *image = FPSTR(""));
        void setDebugOutput(boolean debug);

    private:
        std::unique_ptr<DNSServer>        dnsServer;
        std::unique_ptr<ESP8266WebServer> server;

        //Access Point credentials.
        const char *_apSSID;
        const char *_apPassword;
        // This image is shown on the  access point config portal.
        const __FlashStringHelper *_image;

        //Station mode credentials.
        char ssid[20] = {'\0'};
        char password[20] = {'\0'};

        //Access Point IP. Also used by DNS.
        IPAddress _apIP = IPAddress(192, 168, 1, 1);

        // DNS Server.
        const byte DNS_PORT = 53;
        boolean connect;
        boolean _debug = false;

        void start();
        void handleRoot();
        void submit();
        
        int connectWiFi();
        void printWiFi();

        template <typename Generic>
        void DEBUG_EWS(Generic text);
};

#endif
