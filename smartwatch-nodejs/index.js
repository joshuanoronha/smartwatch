var mosca = require('mosca');

// install zmq || libzmq3-dev from ubuntu repository
// also install libpgm-dev

var ascoltatore = {
    //using ascoltatore
    type: 'mqtt',
    json: false,
    mqtt: require('mqtt'),
    host: 'localhost',
    port: 1884
};

var settings = {
    port: 1885,
    backend: ascoltatore
};

var server = new mosca.Server(settings);

server.on('clientConnected', function (client) {
    console.log('client connected', client.id);
});

// // fired when a message is received
// server.on('published', function (packet, client) {
//     console.log('Published', packet.payload);
//     console.log('Published', packet);
//     console.log('Published', packet.topic);
//     console.log('Published', packet.payload.toString());


// });

server.on('ready', setup);

// fired when the mqtt server is ready
function setup() {
    console.log('Mosca server is up and running');
}

//////////////////////////////////////////////////////////////////////////////


var firebase = require("firebase");

var config = {
    apiKey: "AIzaSyB-vlQ-2GFWo0Uo4pAbkjyR-noA_9i3m3g",
    authDomain: "smartwatch-210415.firebaseapp.com",
    databaseURL: "https://smartwatch-210415.firebaseio.com",
    projectId: "smartwatch-210415",
    storageBucket: "smartwatch-210415.appspot.com",
    messagingSenderId: "980837883381"
};



var app = firebase.initializeApp(config);
var database = firebase.database();

var main_ref_location = 'watch/';

function addTelemetry(watchId, heartRate,fall){
    var ref = database.ref('watch/' + watchId)

    return ref.set({
        heartRate: heartRate,
        fall: fall,
    }, function(error) {
        if (error) {
          // The write failed...
          console.log("error := " + watchId);      
        } else {
          // Data saved successfully!
        //   console.log("done");
          ref.off();
          return;
        }
      });
}

addTelemetry("1", 234,0)

console.log("Test")
// app.delete()



// fired when a message is received
server.on('published', function (packet, client) {

    // console.log('Published', packet.topic);
    console.log('Published', packet.payload.toString());
    var text =  packet.payload.toString();
    addTelemetry(packet.client,text, 0 );
});

// sudo docker run -it -p 1884:1883 -p 9001:9001 eclipse-mosquitto
// sudo docker build .  --network host -t myimage:2.6
// sudo docker run  --network=host   fec529d3098d
