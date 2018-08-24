/******************************************************************************
 * Copyright 2018 Google
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/
// This file contains your configuration used to connect to Cloud IoT Core

// WIFI
const char* ssid = "Clement-O";
const char* password = "2051313908";

// Cloud iot details.
const char* project_id = "smartwatch-210415";
const char* location = "asia-east1";
const char* registry_id = "smartwatches-list";
const char* device_id = "watch-101";
// To get the private key run (where private-key.pem is the ec private key
// used to create the certificate uploaded to google cloud iot):
// openssl ec -in <private-key.pem> -noout -text
// and copy priv: part.
const char* private_key_str =
    "45:87:8e:f9:6e:a2:23:43:b1:21:f1:8c:81:73:42:"
    "6e:bc:64:cc:7a:be:fb:68:36:88:ec:77:97:31:4c:"
    "35:49";

// TODO: Use root certificate to verify tls connection rather than using a
// fingerprint.
// To get the fingerprint run
// openssl s_client -connect cloudiotdevice.googleapis.com:443 -cipher <cipher>
// Copy the certificate (all lines between and including ---BEGIN CERTIFICATE---
// and --END CERTIFICATE--) to a.cert. Then to get the fingerprint run
// openssl x509 -noout -fingerprint -sha1 -inform pem -in a.cert
// <cipher> is probably ECDHE-RSA-AES128-GCM-SHA256, but if that doesn't work
// try it with other ciphers obtained by sslscan cloudiotdevice.googleapis.com.
const char* fingerprint =
    "0A:AA:3A:7D:F6:4D:56:32:0A:50:95:B5:60:D7:EA:46:A4:92:5A:A2";
