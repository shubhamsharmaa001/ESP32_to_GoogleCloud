
// This file contains your configuration used to connect to Cloud IoT Core

// Wifi network details.


const char *ssid = "Galaxy";           // write your wifi ssid name
const char *password =  "9765878";     // write your wifi ssid passord
// Cloud iot details.
const char *project_id = "st001-sample-project";
const char *location = "europe-west1";
const char *registry_id = "project-sample-registry";
const char *device_id = "project-sample-device";

// Configuration for NTP
const char* ntp_primary = "time.google.com";//"pool.ntp.org";
const char* ntp_secondary = "time.nist.gov";

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

// To get the private key run (where private-key.pem is the ec private key
// used to create the certificate uploaded to google cloud iot):
// openssl ec -in <private-key.pem> -noout -text
// and copy priv: part.
// The key length should be exactly the same as the key length bellow (32 pairs
// of hex digits). If it's bigger and it starts with "00:" delete the "00:". If
// it's smaller add "00:" to the start. If it's too big or too small something
// is probably wrong with your key.
const char *private_key_str =
    "61:f2:10:6a:98:c2:18:61:c5:6d:7f:4d:2b:5f:71:"
    "c3:62:40:61:47:2d:6c:0b:ef:29:21:72:e6:c8:cd:"
    "fc:72";

// Time (seconds) to expire token += 20 minutes for drift
const int jwt_exp_secs = 60*20; // Maximum 24H (3600*24)

// To get the certificate for your region run:
//   openssl s_client -showcerts -connect mqtt.googleapis.com:8883
// for standard mqtt or for LTS:
//   openssl s_client -showcerts -connect mqtt.2030.ltsapis.goog:8883
// Copy the certificate (all lines between and including ---BEGIN CERTIFICATE---
// and --END CERTIFICATE--) to root.cert and put here on the root_cert variable.

const char *root_cert ="-----BEGIN CERTIFICATE-----\n"
"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\n"
"ieJqz/pgWUk4Ad8VhEcpXMUaf+KHvc8+JsR5Mg==\n"
"-----END CERTIFICATE-----\n";

// In case we ever need extra topics
const int ex_num_topics = 0;
const char* ex_topics[ex_num_topics];
//const int ex_num_topics = 1;
//const char* ex_topics[ex_num_topics] = {
//  "/devices/my-device/tbd/#"
//};
