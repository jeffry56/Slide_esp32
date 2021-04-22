const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
   <head>
      <title>Focus Bracketing App</title>
      <meta charset="UTF-8" />
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <link rel="stylesheet" type="text/css" href="style.css" >
      <link rel="stylesheet" type="text/css" href="iconic_fill.css" >
   </head>
   <body>
      <div class="page-container">
         <h1 class="page-title">
            Focus Bracketing
         </h1>
         <div class="external-grid">
            <div>
               <div class="panel-header" style= "background-color:rgb(241, 240, 178);">Controls position</div>
               <div class="panel-grid" id="panel-1">
                  <div class="grid-item">
                     <!--<div class="grid-item-title">Step 100</div>-->
                     <div class="buttons">
                        <input id="Cmd01" class="buttons-input" type="button" onclick="decodKey(this)">
                        <label for="Cmd01" class="buttons-label1"> <i class="icon-arrow-right-1"></i></label>
                     </div>
                   </div>
                  <div class="grid-item">
                     <!--<div <div class="grid-item-title">Step 10</div>-->
                     <div class="buttons">
                        <input id="Cmd02" class="buttons-input" type="button" onclick="decodKey(this)">
                        <label for="Cmd02" class="buttons-label1"> <i class="icon-double-arrow-right-1"></i></label>
                     </div>
                  </div>
                  <div class="grid-item">
                     <!--<div <div class="grid-item-title">Step 1</div>-->
                     <div class="buttons">
                        <input id="Cmd03" class="buttons-input" type="button" onclick="decodKey(this)">
                        <label for="Cmd03" class="buttons-label1"> <i class="icon-triple-arrow-right-1"></i></label>
                     </div>
                   </div>
                  <div class="grid-item">
                     <!--<div <div class="grid-item-title">Step 1</div>-->
                     <div class="buttons case">
                        <input id="Cmd04" class="buttons-input" type="button" onclick="decodKey(this)">
                        <label for="Cmd04" class="buttons-label1"> <i class="icon-arrow-left-1"></i></label>
                     </div>
                  </div>
                  <div class="grid-item">
                     <!--<div <div class="grid-item-title">Step 10</div>-->
                     <div class="buttons case">
                        <input id="Cmd05" class="buttons-input" type="button" onclick="decodKey(this)">
                        <label for="Cmd05" class="buttons-label1"> <i class="icon-double-arrow-left-1"></i></label>
                     </div>
                  </div>
                  <div class="grid-item">
                     <!--<div <div class="grid-item-title">Step 100</div>-->
                     <div class="buttons case">
                        <input id="Cmd06" class="buttons-input" type="button" onclick="decodKey(this)">
                        <label for="Cmd06" class="buttons-label1"> <i class="icon-triple-arrow-left-1"></i></label>
                     </div>
                  </div>
               </div>
               <div class="panel-footer" style= "background-color:rgb(241, 240, 178);">
               </div>
            </div>
               <!--********************************************************************************************************************-->
            <div id="panel-2">
               <div class="panel-header" style= "background-color:rgb(178, 241, 178);">Point A</div>
               <div class="panel-2-grid">
                  <div class="grid-item">
                     <!--<div <div class="grid-item-title">Set</div>-->
                     <div class="buttons">
                        <input id="Cmd07" class="buttons-input" type="button" onclick="decodKey(this)">
                        <label for="Cmd07" class="buttons-label" id="Jog07"> <i class="icon-cog"></i></label>
                     </div>
                  </div>
                  <div class="grid-item">
                     <!--<div <div class="grid-item-title">Jog</div>-->
                     <div class="buttons">
                        <input id="Cmd08" class="buttons-input" type="button">
                        <label for="Cmd08" class="buttons-label" id="Jog08"> <i class="icon-arrow-right"></i></label>
                     </div>
                  </div>
                  <div class="grid-item">
                     <!--<div <div class="grid-item-title">Go/Stop</div>-->
                     <div class="buttons">
                        <input id="Cmd09" class="buttons-input" type="checkbox" %Achk% onclick="decodKey(this)">
                        <label for="Cmd09" class="buttons-label" id="Label09"> <i class="icon-switch"></i></label>
                     </div>
                  </div>
               </div>
               <div class="panel-footer" style= "background-color:rgb(178, 241, 178);">
                  <div class="text">Home point value A =</div>
                  <div class="value"><span id="A_position">%A_position%</span></div>
               </div>
            </div>
<!--***********************************************************************************************************************************-->
            <div id="panel-3">
               <div class="panel-header" style= "background-color:rgb(253, 171, 171);">Point B</div>
               <div class="panel-2-grid">
                  <div class="grid-item">
                     <!--<div <div class="grid-item-title">Set</div>-->
                     <div class="buttons case">
                        <input id="Cmd10" class="buttons-input" type="button" onclick="decodKey(this)">
                        <label for="Cmd10" class="buttons-label" id="Jog10"> <i class="icon-cog"></i></label>
                     </div>
                  </div>
                  <div class="grid-item">
                     <!--<div <div class="grid-item-title">Jog</div>-->
                     <div class="buttons case">
                        <input id="Cmd11" class="buttons-input" type="button">
                        <label for="Cmd11" class="buttons-label" id="Jog11"> <i class="icon-arrow-left"></i></label>
                     </div>
                  </div>
                  <div class="grid-item">
                     <!--<div <div class="grid-item-title">Go/Stop</div>-->
                     <div class="buttons case">
                        <input id="Cmd12" class="buttons-input" type="checkbox" %Bchk% onclick="decodKey(this)">
                        <label for="Cmd12" class="buttons-label" id="Label12"> <i class="icon-switch"></i></label>
                     </div>
                  </div>
               </div>
               <div class="panel-footer" style= "background-color:rgb(253, 171, 171);">
                  <div class="text">Home point value B =</div>
                  <div class="value"><span id="B_position">%B_position%</span></div>
               </div>
            </div>
<!--**********************************************************************************************************************************-->
         <div id="panel-4">
            <div class="panel-header" style= "background-color:rgb(182, 248, 250);">Input values</div>
            <div class="panel-1-grid">
               <label for="Cmd13"><b>Shots set </b>[n] =</label>
               <input type="number" id="Cmd13" name="shots-set" value=%Shots% onchange="sendValue13()">
               <div class="text"><b>Actual position </b>[mm] =</div>
               <div class="value"> <span id="actualPosition">%actualPosition%</span></div>
            </div>
            <div class="panel-1-grid">
               <label for="Cmd14"><b>Interval </b>[sec] =</label>
               <input type="number" id="Cmd14" name="interval" value=%Interval% onchange="sendValue14()">
               <div class="text"><b>Shots made </b>[n] =</div>
               <div class="value"> <span id="ShotsMade">%ShotsMade%</span></div>
            </div>
            <div class="panel-footer" style= "background-color:rgb(182, 248, 250);"></div>
          </div>
     </div>
      <script>
        var gateway = `ws://${window.location.hostname}/ws`;
        var websocket;
        window.addEventListener('load', onLoad);

        document.getElementById("Jog08").onmousedown = function() {mouseDown(this)};
        document.getElementById("Jog11").onmousedown = function() {mouseDown(this)};
        document.getElementById("Jog08").ontouchstart = function() {mouseDown(this)};
        document.getElementById("Jog11").ontouchstart = function() {mouseDown(this)};
        document.getElementById("Jog08").onmouseup = function() {mouseUp(this)};
        document.getElementById("Jog11").onmouseup = function() {mouseUp(this)};
        document.getElementById("Jog08").ontouchend = function() {mouseUp(this)};
        document.getElementById("Jog11").ontouchend = function() {mouseUp(this)};
        
        function mouseDown(ctrl) {
            var isChecked1 = document.getElementById("Cmd09").checked;
            var isChecked2 = document.getElementById("Cmd12").checked;
            if (isChecked1 || isChecked2) {return}
            if (ctrl.id==="Jog08") {websocket.send("Jog20");}
            if (ctrl.id==="Jog11") {websocket.send("Jog30");}
          }
          
         function mouseUp(ctrl) {
            var isChecked1 = document.getElementById("Cmd09").checked;
            var isChecked2 = document.getElementById("Cmd12").checked;
            if (isChecked1 || isChecked2) {return}
            if (ctrl.id==="Jog08") {websocket.send("Jog21");}
            if (ctrl.id==="Jog11") {websocket.send("Jog31");}
          }

         function decodKey(ctrl) {
            var isChecked1 = document.getElementById("Cmd09").checked;
            var isChecked2 = document.getElementById("Cmd12").checked;
            if (isChecked1) { websocket.send("Chk40"); } else { websocket.send("Chk41"); }
            if (isChecked2) { websocket.send("Chk50"); } else { websocket.send("Chk51"); }
            SetResetSwitch();
            if (isChecked1 || isChecked2) {
               return
            }
             send_cmd_id(ctrl);
         }
         
         function SetResetSwitch() {
            var isChecked1 = document.getElementById("Cmd09").checked;
            var isChecked2 = document.getElementById("Cmd12").checked;
            if (isChecked1) {
                document.getElementById("panel-1").style.pointerEvents = "none";
                document.getElementById("panel-3").style.pointerEvents = "none";
                document.getElementById("panel-4").style.pointerEvents = "none";
               } 
            if (isChecked2) {
                document.getElementById("panel-1").style.pointerEvents = "none";
                document.getElementById("panel-2").style.pointerEvents = "none";
                document.getElementById("panel-4").style.pointerEvents = "none";
               } 
            if (isChecked1 || isChecked2) {
                document.getElementById("Jog07").style.pointerEvents = "none";
                document.getElementById("Jog08").style.pointerEvents = "none";
                document.getElementById("Jog10").style.pointerEvents = "none";
                document.getElementById("Jog11").style.pointerEvents = "none";
               } 
            if (!isChecked1 && !isChecked2) {
                document.getElementById("Jog07").style.pointerEvents = "auto";
                document.getElementById("Jog08").style.pointerEvents = "auto";
                document.getElementById("Jog10").style.pointerEvents = "auto";
                document.getElementById("Jog11").style.pointerEvents = "auto";
                document.getElementById("panel-1").style.pointerEvents = "auto";
                document.getElementById("panel-2").style.pointerEvents = "auto";
                document.getElementById("panel-3").style.pointerEvents = "auto";
                document.getElementById("panel-4").style.pointerEvents = "auto";
               }
          }

          function sendValue13() {
            var shots = document.getElementById("Cmd13");
            websocket.send("V13-"+shots.value);
          }
          
          function sendValue14() {
            var Interval = document.getElementById("Cmd14");
            websocket.send("V14-"+Interval.value);
          }

          function onLoad(event) {
            initWebSocket();
          }
          
          function initWebSocket() {
            /*console.log('Trying to open a WebSocket connection...');*/
            websocket = new WebSocket(gateway);
            websocket.onopen    = onOpen;
            websocket.onclose   = onClose;
            websocket.onmessage = onMessage;
          }
          
          function onOpen(event) {
            console.log('Connection opened');
          }
          
          function onClose(event) {
            console.log('Connection closed');
            setTimeout(initWebSocket, 2000);
          }
          
          function onMessage(event) {
            /*console.log(`Received a notification from ${event.origin}`);
            console.log(event);*/

           /* var obj = JSON.parse(event.data);
            if (obj.header === "dati") {
              document.getElementById("A_position").innerHTML = obj.A_position;
              document.getElementById("B_position").innerHTML = obj.B_position;
              document.getElementById("actualPosition").innerHTML = obj.actualPosition;
              document.getElementById("Cmd09").checked = (obj.Achk == "1");
              document.getElementById("Cmd12").checked = (obj.Bchk == "1");
              document.getElementById("Cmd13").value = obj.Shots;
              document.getElementById("Cmd14").value = obj.Interval;
              document.getElementById("ShotsMade").innerHTML = obj.ShotsMade;*/

            var str = event.data.split('|');
            if (str[0]==="dati") {
              document.getElementById("A_position").innerHTML = str[1];
              document.getElementById("B_position").innerHTML = str[2];
              document.getElementById("actualPosition").innerHTML = str[3];
              document.getElementById("Cmd09").checked = (str[4]=="1");
              document.getElementById("Cmd12").checked = (str[5]=="1");
              document.getElementById("Cmd13").value = str[6];
              document.getElementById("Cmd14").value = str[7];
              document.getElementById("ShotsMade").innerHTML = str[8];
              SetResetSwitch();
            }
          }
                
          function send_cmd_id(ctrl){
            websocket.send(ctrl.id);
            /*console.log(ctrl);*/
          }     
     </script>
   </body>
</html>
)=====";
