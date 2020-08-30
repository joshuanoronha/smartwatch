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

function writeUserData(userId, name, email, imageUrl) {
    var m =  database.ref('users/' + userId)
    
    return m.set({
        username: name,
        email: email,
        profile_picture: imageUrl
    }, function(error) {
        if (error) {
          // The write failed...
          console.log("error");
          
        } else {
          // Data saved successfully!
          console.log("done");
          m.off();
          return;
        }
      });
    
}

x = writeUserData(23331,"Edwin","edwinclement08@gmail.com", "weee");
x = writeUserData(23631,"Edwin","edwinclement08@gmail.com", "weee");

console.log("Test")
// app.delete()