/*
    SimpleSerial index.js
    Created 7 May 2013
    Modified 9 May 2013
    by Tom Igoe
*/

var state="disconnected";
var mensaje=document.getElementById("message");
var app = {
    macAddress: "20:15:04:17:73:66",  // get your mac address from bluetoothSerial.list
    chars: "",

/*
    Application constructor
 */
    initialize: function() {
        this.bindEvents();
        console.log("Starting SimpleSerial app");
    },
/*
    bind any events that are required on startup to listeners:
*/
    bindEvents: function() {
        document.addEventListener('deviceready', this.onDeviceReady, false);
        window.onclick = this.manageConnection;

      },

    

/*
    this runs when the device is ready for user interaction:
*/
    onDeviceReady: function() {
        mensaje.innerHTML="Desconectado";

  /*    bluetoothSerial.connect(
                    app.macAddress,  // device to connect to
                    app.openPort,    // start listening if you succeed
                    app.showError    // show the error if you fail
                );*/
    }, 
/*
    Connects if not connected, and disconnects if connected:
*/

manageConnection: function() {

        // connect() will get called only if isConnected() (below)
        // returns failure. In other words, if not connected, then connect:
         var connect= function() {
              TTS.speak({
                   text: "Conectando",
                   locale: 'es-AR',
                   rate: 1.5
               }, function () {
                   // Do Something after success
               }, function (reason) {
                   // Handle the error case
               });

              bluetoothSerial.connect(
                    app.macAddress,  // device to connect to
                    app.openPort,    // start listening if you succeed
                    app.showError    // show the error if you fail
                );
        };

        // disconnect() will get called only if isConnected() (below)
        // returns success  In other words, if  connected, then disconnect:
         var disconnect= function() {
          TTS.speak({
           text: "Desconectando",
           locale: 'es-AR',
           rate: 1.5
       }, function () {
           // Do Something after success
       }, function (reason) {
           // Handle the error case
       });
             bluetoothSerial.disconnect(
                app.closePort,     // stop listening to the port
                app.showError      // show the error if you fail
             );
        };
        if (state=="disconnected"){state="connected";mensaje.innerHTML="Conectado";
}
        else {state="disconnected";        mensaje.innerHTML="Desconectado";
}
        //here's the real action of the manageConnection function:
        //bluetoothSerial.isConnected(disconnect, connect);
    },
  
/*
    subscribes to a Bluetooth serial listener for newline
    and changes the button:
*/
     openPort: function() {
      mensaje.innerHTML="Conectado";
         TTS.speak({
           text: "Conectado",
           locale: 'es-AR',
           rate: 1.5
       }, function () {
           // Do Something after success
       }, function (reason) {
           // Handle the error case
       });
      bluetoothSerial.subscribe('\n', function (data) {
             TTS.speak({
                   text: data,
                   locale: 'es-AR',
                   rate: 1.5
               }, function () {
                   // Do Something after success
               }, function (reason) {
                   // Handle the error case
               });
            });
    },
/*
    unsubscribes from any Bluetooth serial listener and changes the button:
*/
      closePort: function() {
        // if you get a good Bluetooth serial connection:
        mensaje.innerHTML="Desconectado";
         TTS.speak({
           text: "Desconectado",
           locale: 'es-AR',
           rate: 1.5
       }, function () {
           // Do Something after success
       }, function (reason) {
           // Handle the error case
       });
        // unsubscribe from listening:
        bluetoothSerial.unsubscribe(
                function (data) {
                },
                app.showError
        );
    },
/*
    appends @error to the message div:
*/
    ConnectionFail: function(error) {
              TTS.speak({
                   text: "Reintentando",
                   locale: 'es-AR',
                   rate: 1.5
               }, function () {
                   // Do Something after success
               }, function (reason) {
                   // Handle the error case
               }); 
              bluetoothSerial.connect(
                    app.macAddress,  // device to connect to
                    app.openPort,    // start listening if you succeed
                    app.ConnectionFail    // show the error if you fail
                );
    },
    showError:function(error){},
};      // end of app

            app.initialize();

