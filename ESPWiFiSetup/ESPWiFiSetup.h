#ifndef ESPWiFiSetup_h
#define ESPWiFiSetup_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <memory>

static const char CACHE_CONTROL_SEND_HEADER[] PROGMEM               = "Cache-Control";
static const char NO_CACHE_STORE_REVALIDATE_SEND_HEADER[] PROGMEM   = "no-cache, no-store, must-revalidate";
static const char PRAGMA_SEND_HEADER[] PROGMEM                      = "Pragma";
static const char NO_CACHE_SEND_HEADER[] PROGMEM                    = "no-cache";
static const char EXPIRES_SEND_HEADER[] PROGMEM                     = "Expires";
static const char MINUS_ONE_SEND_HEADER[] PROGMEM                   = "-1";

static const char CON_LEN[] PROGMEM                                 = "Content-Length";
static const char TEXT_HTML_SEND[] PROGMEM                          = "text/html";

static const char HTTP_HEAD[] PROGMEM                               = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/><title>{v}</title>";
static const char HTTP_STYLE[] PROGMEM                              = "<style>.login{margin:0 auto auto;max-width:80%;max-height:60%} .login-header{text-align:center;margin:0;max-width:140%;padding:0;} .c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:95%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#fff;color:#1fa3ec;line-height:2.4rem;font-size:1.2rem;width:100%;} .q{float: right;width: 64px;text-align: right;}  .l{background: url(\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAALVBMVEX///8EBwfBwsLw8PAzNjaCg4NTVVUjJiZDRUUUFxdiZGSho6OSk5Pg4eFydHTCjaf3AAAAZElEQVQ4je2NSw7AIAhEBamKn97/uMXEGBvozkWb9C2Zx4xzWykBhFAeYp9gkLyZE0zIMno9n4g19hmdY39scwqVkOXaxph0ZCXQcqxSpgQpONa59wkRDOL93eAXvimwlbPbwwVAegLS1HGfZAAAAABJRU5ErkJggg==\")no-repeat left center;background-size: 1em;}";
static const char HTTP_FORM_STYLE[] PROGMEM                         = ".login-form {text-align:left;display:inline-block;min-width:260px;border:.5px solid #fff;background:#4facff;border-radius:10px;box-shadow:0px 0px 10px #000;box-sizing:border-box;padding-top:10%;padding-bottom:10%;margin:5% auto;}";
static const char HTTP_HEAD_END[] PROGMEM                           = "</style></head>";
static const char HTTP_IMAGE_HEAD[] PROGMEM                         = "<body><div class='login'><div class='login-header'><img src='";
static const char HTTP_IMAGE_END[] PROGMEM                          = "' style='width:100%;'></div></div>";
static const char HTTP_FORM_START[] PROGMEM                         = "<br/><br/><div class='login-form'><form method='post' action='/submit'><input id='s' name='ssid' length=32 placeholder='SSID'><br/><br/><input id='p' name='password' length=64 type='password' placeholder='Password'><br/>";
static const char HTTP_FORM_END[] PROGMEM                           = "<br/><button type='submit'>save</button></form>";
static const char HTTP_END[] PROGMEM                                = "</div></body></html>";
static const char HTTP_HEAD_SAVED_PAGE[] PROGMEM                    = "<!DOCTYPE html><html><head>";
static const char HTTP_SAVED[] PROGMEM                              = "</br></br></br><h2 style='text-align:center;font-size:48px;'>WiFi credentials saved!<br/><br/><br/>If successfully connected to Wifi, captive portal will automatically exit.<br/>Otherwise you can repeat this process and try again.</h2>";

static const char HTTP_IMAGE[] PROGMEM                              = "data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4NCjwhLS0gR2VuZXJhdG9yOiBBZG9iZSBJbGx1c3RyYXRvciAxNi4wLjAsIFNWRyBFeHBvcnQgUGx1Zy1JbiAuIFNWRyBWZXJzaW9uOiA2LjAwIEJ1aWxkIDApICAtLT4NCjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+DQo8c3ZnIHZlcnNpb249IjEuMSIgaWQ9IkxheWVyXzEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHg9IjBweCIgeT0iMHB4Ig0KCSB3aWR0aD0iNTc4Ljk3MXB4IiBoZWlnaHQ9IjExMi40OTVweCIgdmlld0JveD0iMCAwIDU3OC45NzEgMTEyLjQ5NSIgZW5hYmxlLWJhY2tncm91bmQ9Im5ldyAwIDAgNTc4Ljk3MSAxMTIuNDk1Ig0KCSB4bWw6c3BhY2U9InByZXNlcnZlIj4NCjxwb2x5Z29uIGZpbGw9IiM2NjY2NjYiIHBvaW50cz0iMTM1Ljc0MywzNy4zOTYgMTQ1Ljc3NywzNy4zOTYgMTYxLjU2NCw3NS4wMDUgMTYxLjg0NSw3NS4wMDUgMTc3LjQ5MiwzNy4zOTYgMTg3LjUyNiwzNy4zOTYgDQoJMTg3LjUyNiw4Ny4wNzQgMTgwLjc5LDg3LjA3NCAxODAuNzksNDYuMjM3IDE4MC42NSw0Ni4yMzcgMTYzLjg4LDg3LjA3NCAxNTkuMzg5LDg3LjA3NCAxNDIuNjE5LDQ2LjIzNyAxNDIuNDc5LDQ2LjIzNyANCgkxNDIuNDc5LDg3LjA3NCAxMzUuNzQzLDg3LjA3NCAiLz4NCjxwb2x5Z29uIGZpbGw9IiM2NjY2NjYiIHBvaW50cz0iMTk4LjA1LDM3LjM5NiAyMzAuMTE2LDM3LjM5NiAyMzAuMTE2LDQzLjcxIDIwNC43ODYsNDMuNzEgMjA0Ljc4Niw1OC41MTYgMjI4LjM2Miw1OC41MTYgDQoJMjI4LjM2Miw2NC44MzEgMjA0Ljc4Niw2NC44MzEgMjA0Ljc4Niw4MC43NTggMjMxLjM3OCw4MC43NTggMjMxLjM3OCw4Ny4wNzQgMTk4LjA1LDg3LjA3NCAiLz4NCjxnPg0KCTxkZWZzPg0KCQk8cmVjdCBpZD0iU1ZHSURfMV8iIHg9Ii0xMDMuNjA1IiB5PSItMjIxLjA5NCIgd2lkdGg9IjgwMCIgaGVpZ2h0PSI2MDAiLz4NCgk8L2RlZnM+DQoJPGNsaXBQYXRoIGlkPSJTVkdJRF8yXyI+DQoJCTx1c2UgeGxpbms6aHJlZj0iI1NWR0lEXzFfIiAgb3ZlcmZsb3c9InZpc2libGUiLz4NCgk8L2NsaXBQYXRoPg0KCTxwYXRoIGNsaXAtcGF0aD0idXJsKCNTVkdJRF8yXykiIGZpbGw9IiM2NjY2NjYiIGQ9Ik0yMzguMDQ2LDM3LjM5NmgxNy4zMzFjMy41MDgsMCw2LjU4NCwwLjM5Nyw5LjIyNiwxLjE5Mg0KCQljMi42NDMsMC43OTYsNC45MzUsMS44NTksNi44NzcsMy4xOTJjMS45NDEsMS4zMzQsMy41NTQsMi44NjcsNC44NDEsNC41OTdjMS4yODYsMS43MzEsMi4zMDQsMy41MDgsMy4wNTMsNS4zMzINCgkJYzAuNzQ3LDEuODI0LDEuMjg2LDMuNjUsMS42MTMsNS40NzRjMC4zMjcsMS44MjQsMC40OTEsMy41MDgsMC40OTEsNS4wNTJjMCwzLjE4MS0wLjU4NSw2LjI1Ni0xLjc1NCw5LjIyNg0KCQljLTEuMTcsMi45NzItMi45MDEsNS42MTMtNS4xOTIsNy45MjljLTIuMjkyLDIuMzE1LTUuMTM0LDQuMTc1LTguNTI1LDUuNTc4Yy0zLjM5MiwxLjQwMy03LjMxLDIuMTA1LTExLjc1MywyLjEwNWgtMTYuMjA4VjM3LjM5NnoNCgkJIE0yNDQuNzgxLDgwLjc1OGg4LjQ5YzIuODU0LDAsNS41NTUtMC4zODYsOC4xMDUtMS4xNTdjMi41NDktMC43NzIsNC43ODItMS45Myw2LjcwMS0zLjQ3NGMxLjkxNy0xLjU0MywzLjQzOC0zLjQ3Myw0LjU2LTUuNzg4DQoJCWMxLjEyMy0yLjMxNSwxLjY4NS01LjAxOCwxLjY4NS04LjEwNGMwLTEuNTktMC4yNTgtMy40NS0wLjc3Mi01LjU3OWMtMC41MTUtMi4xMjctMS40ODYtNC4xNTEtMi45MTMtNi4wNjkNCgkJYy0xLjQyNi0xLjkxOC0zLjQwMi0zLjU0NC01LjkyOC00Ljg3N2MtMi41MjctMS4zMzMtNS44MDEtMi05LjgyNC0yaC0xMC4xMDRWODAuNzU4eiIvPg0KCTxyZWN0IHg9IjI4OS40MDciIHk9IjM3LjM5NiIgY2xpcC1wYXRoPSJ1cmwoI1NWR0lEXzJfKSIgZmlsbD0iIzY2NjY2NiIgd2lkdGg9IjYuNzM2IiBoZWlnaHQ9IjQ5LjY3OCIvPg0KCTxwYXRoIGNsaXAtcGF0aD0idXJsKCNTVkdJRF8yXykiIGZpbGw9IiM2NjY2NjYiIGQ9Ik0zMTIuOTgzLDM3LjM5NnYzMC40NTJjMCwxLjU0NCwwLjIxMSwzLjE0NywwLjYzMiw0LjgwNw0KCQljMC40MjEsMS42NjEsMS4xMjIsMy4xOTIsMi4xMDQsNC41OTVjMC45ODIsMS40MDQsMi4yNjksMi41NSwzLjg1OSwzLjQzOWMxLjU5LDAuODg5LDMuNTU1LDEuMzMzLDUuODk0LDEuMzMzDQoJCXM0LjMwNC0wLjQ0NCw1Ljg5NS0xLjMzM2MxLjU5LTAuODg5LDIuODc3LTIuMDM1LDMuODU5LTMuNDM5YzAuOTgyLTEuNDAzLDEuNjg0LTIuOTM0LDIuMTA0LTQuNTk1DQoJCWMwLjQyMS0xLjY2LDAuNjMyLTMuMjYzLDAuNjMyLTQuODA3VjM3LjM5Nmg2LjczNXYzMS41MDVjMCwyLjktMC40OSw1LjUzMi0xLjQ3Myw3Ljg5M2MtMC45ODIsMi4zNjMtMi4zNCw0LjQxLTQuMDcsNi4xNA0KCQljLTEuNzMsMS43MzEtMy43NjYsMy4wNjQtNi4xMDQsMy45OTljLTIuMzM4LDAuOTM2LTQuODY1LDEuNDAzLTcuNTc4LDEuNDAzcy01LjIzOS0wLjQ2OC03LjU3Ny0xLjQwMw0KCQljLTIuMzQtMC45MzUtNC4zNzUtMi4yNjgtNi4xMDQtMy45OTljLTEuNzMxLTEuNzMtMy4wODgtMy43NzctNC4wNy02LjE0Yy0wLjk4Mi0yLjM2MS0xLjQ3NC00Ljk5My0xLjQ3NC03Ljg5M1YzNy4zOTZIMzEyLjk4M3oiLz4NCgk8cG9seWdvbiBjbGlwLXBhdGg9InVybCgjU1ZHSURfMl8pIiBmaWxsPSIjNjY2NjY2IiBwb2ludHM9IjM1NC4zMTEsMzcuMzk2IDM2NC4zNDUsMzcuMzk2IDM4MC4xMzIsNzUuMDA1IDM4MC40MTMsNzUuMDA1IA0KCQkzOTYuMDYxLDM3LjM5NiA0MDYuMDk0LDM3LjM5NiA0MDYuMDk0LDg3LjA3NCAzOTkuMzU4LDg3LjA3NCAzOTkuMzU4LDQ2LjIzNyAzOTkuMjE4LDQ2LjIzNyAzODIuNDQ4LDg3LjA3NCAzNzcuOTU2LDg3LjA3NCANCgkJMzYxLjE4OCw0Ni4yMzcgMzYxLjA0Nyw0Ni4yMzcgMzYxLjA0Nyw4Ny4wNzQgMzU0LjMxMSw4Ny4wNzQgCSIvPg0KCTxwYXRoIGNsaXAtcGF0aD0idXJsKCNTVkdJRF8yXykiIGZpbGw9IiMwMDk5Q0MiIGQ9Ik00NTMuNjY2LDg4LjMzNmMtMy43ODksMC03LjI3NC0wLjY2Ni0xMC40NTUtMS45OTkNCgkJYy0zLjE4Mi0xLjMzNC01LjkwNi0zLjE2OS04LjE3NC01LjUwOWMtMi4yNy0yLjMzNy00LjA0Ny01LjA5OC01LjMzMy04LjI4Yy0xLjI4Ny0zLjE4LTEuOTMtNi42MTktMS45My0xMC4zMTQNCgkJYzAtMy42OTQsMC42NDMtNy4xMzMsMS45My0xMC4zMTVjMS4yODYtMy4xOCwzLjA2My01Ljk0LDUuMzMzLTguMjhjMi4yNjgtMi4zMzgsNC45OTItNC4xNzUsOC4xNzQtNS41MDgNCgkJYzMuMTgxLTEuMzMzLDYuNjY2LTIsMTAuNDU1LTJzNy4yNzMsMC42NjcsMTAuNDU1LDJjMy4xOCwxLjMzMyw1LjkwNCwzLjE3LDguMTc0LDUuNTA4YzIuMjY4LDIuMzQsNC4wNDYsNS4xLDUuMzMzLDguMjgNCgkJYzEuMjg2LDMuMTgyLDEuOTMsNi42MjEsMS45MywxMC4zMTVjMCwzLjY5NS0wLjY0NCw3LjEzNC0xLjkzLDEwLjMxNGMtMS4yODcsMy4xODItMy4wNjUsNS45NDItNS4zMzMsOC4yOA0KCQljLTIuMjcsMi4zNC00Ljk5NCw0LjE3NS04LjE3NCw1LjUwOUM0NjAuOTM5LDg3LjY3LDQ1Ny40NTUsODguMzM2LDQ1My42NjYsODguMzM2IE00NTMuNjY2LDgyLjAyMg0KCQljMi44NTMsMCw1LjQyNi0wLjUyNiw3LjcxOC0xLjU3OXM0LjI1Ny0yLjQ2Nyw1Ljg5NS00LjI0NWMxLjYzNy0xLjc3OCwyLjg5OS0zLjg3LDMuNzg5LTYuMjhjMC44ODgtMi40MDksMS4zMzMtNC45NywxLjMzMy03LjY4Mw0KCQlzLTAuNDQ1LTUuMjc0LTEuMzMzLTcuNjg0Yy0wLjg5LTIuNDA4LTIuMTUyLTQuNTAxLTMuNzg5LTYuMjc5Yy0xLjYzOC0xLjc3Ny0zLjYwMy0zLjE5My01Ljg5NS00LjI0NQ0KCQljLTIuMjkyLTEuMDUzLTQuODY1LTEuNTc5LTcuNzE4LTEuNTc5Yy0yLjg1NCwwLTUuNDI3LDAuNTI2LTcuNzE5LDEuNTc5Yy0yLjI5MiwxLjA1Mi00LjI1NywyLjQ2OC01Ljg5NCw0LjI0NQ0KCQljLTEuNjM4LDEuNzc4LTIuOTAxLDMuODcxLTMuNzg5LDYuMjc5Yy0wLjg5LDIuNDEtMS4zMzMsNC45NzEtMS4zMzMsNy42ODRzMC40NDMsNS4yNzQsMS4zMzMsNy42ODMNCgkJYzAuODg4LDIuNDEsMi4xNTEsNC41MDIsMy43ODksNi4yOGMxLjYzNywxLjc3OCwzLjYwMiwzLjE5Miw1Ljg5NCw0LjI0NVM0NTAuODEyLDgyLjAyMiw0NTMuNjY2LDgyLjAyMiIvPg0KCTxwb2x5Z29uIGNsaXAtcGF0aD0idXJsKCNTVkdJRF8yXykiIGZpbGw9IiMwMDk5Q0MiIHBvaW50cz0iNDg3LjQ4NSwzNy4zOTYgNDk2LjMyNywzNy4zOTYgNTIzLjY5MSw3OC4yMzMgNTIzLjgzMiw3OC4yMzMgDQoJCTUyMy44MzIsMzcuMzk2IDUzMC41NjgsMzcuMzk2IDUzMC41NjgsODcuMDc0IDUyMi4wMDgsODcuMDc0IDQ5NC4zNjIsNDYuMjM3IDQ5NC4yMjIsNDYuMjM3IDQ5NC4yMjIsODcuMDc0IDQ4Ny40ODUsODcuMDc0IAkiLz4NCgk8cG9seWdvbiBjbGlwLXBhdGg9InVybCgjU1ZHSURfMl8pIiBmaWxsPSIjMDA5OUNDIiBwb2ludHM9IjU0MS41ODMsMzcuMzk2IDU3My42NDksMzcuMzk2IDU3My42NDksNDMuNzEgNTQ4LjMxOSw0My43MSANCgkJNTQ4LjMxOSw1OC41MTYgNTcxLjg5NSw1OC41MTYgNTcxLjg5NSw2NC44MzEgNTQ4LjMxOSw2NC44MzEgNTQ4LjMxOSw4MC43NTggNTc0LjkxMiw4MC43NTggNTc0LjkxMiw4Ny4wNzQgNTQxLjU4Myw4Ny4wNzQgCSIvPg0KCTxwYXRoIGNsaXAtcGF0aD0idXJsKCNTVkdJRF8yXykiIGZpbGw9IiM2NjY2NjYiIGQ9Ik04OC45MjgsODYuOTQ5SDc3Ljc1MlY1My43NDVjMC01LjM1NiwwLjEyNi05LjYwNiwwLjM4LTEyLjc0NQ0KCQljLTAuNzMsMC43NjEtMS42MjUsMS42MDItMi42ODYsMi41MjJjLTEuMDYzLDAuOTItNC42MjEsMy44MzYtMTAuNjc2LDguNzQ5bC01LjYxMi03LjA4NmwyMC40NDgtMTYuMDcyaDkuMzIyVjg2Ljk0OXoiLz4NCgk8cGF0aCBjbGlwLXBhdGg9InVybCgjU1ZHSURfMl8pIiBmaWxsPSIjNjY2NjY2IiBkPSJNMjkuMTUxLDI5LjExM2g5LjMyMmwyMC40NDgsMTYuMDcybC01LjYxMiw3LjA4Ng0KCQljLTYuMDU1LTQuOTEzLTkuNjEzLTcuODI5LTEwLjY3Ni04Ljc0OWMtMS4wNjEtMC45Mi0xLjk1Ni0xLjc2MS0yLjY4Ni0yLjUyMmMwLjI1NCwzLjEzOSwwLjM4LDcuMzg5LDAuMzgsMTIuNzQ1djMzLjIwNEgyOS4xNTENCgkJVjI5LjExM3oiLz4NCgk8cGF0aCBjbGlwLXBhdGg9InVybCgjU1ZHSURfMl8pIiBmaWxsPSIjMDA5OUNDIiBkPSJNOS4zOTUsMTA3LjkwNmgxMDB2LTEwMGgtMTAwVjEwNy45MDZ6IE05OS4zOTUsOTcuOTA2aC04MHYtODBoODBWOTcuOTA2eiIvPg0KPC9nPg0KPC9zdmc+DQo=";

class ESPWiFiSetup
{
    public:
        ESPWiFiSetup();
    
        // This starts the WiFi in AP mode with all default parameters.
        // It also runs the DNS and webserver until configured with WiFi credentials.
        void start();

        // This starts the WiFi in AP mode with default image.
        void start(const char *apSSID, const char *apPassword);

        // This starts the WiFi in AP mode with no default parameters.
        // Image is a string stored in flash which contains a base 64 encoded image string.
        void start(const char *apSSID, const char *apPassword, const __FlashStringHelper *image);

        void setDebugOutput(boolean debug);

    private:
        std::unique_ptr<DNSServer>        dnsServer;
        std::unique_ptr<ESP8266WebServer> server;

        // Access Point credentials.
        const char *_apSSID = "MediumOne";
        const char *_apPassword = "";
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

        void init();
        void handleRoot();
        void submit();
        
        int connectWiFi();
        void printWiFi();

        template <typename Generic>
        void DEBUG_EWS(Generic text);
};

#endif
