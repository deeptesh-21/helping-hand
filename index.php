<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.3/jquery.min.js"></script>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Audiowide&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="./styles.css">

    <link rel="stylesheet" href="https://unpkg.com/leaflet@1.9.3/dist/leaflet.css"
     integrity="sha256-kLaT2GOSpHechhsozzB+flnD+zUyjE2LlfWPgU04xyI="
     crossorigin=""/>

      <!-- Make sure you put this AFTER Leaflet's CSS -->
    <script src="https://unpkg.com/leaflet@1.9.3/dist/leaflet.js"
    integrity="sha256-WBkoXOwTeyKclOHuWtc+i2uENFpDZ9YPdf5Hf+D7ewM="
    crossorigin=""></script>

     
     <title>Document</title>
    </head>
    <body>
        <div class="nav-bar"><h1>Helping Hand</h1><a href="./generate_reports.php"><h3>Get Report</h2></a></div>
        
        <div id="map"></div>
            
        </div>
        
        <script>
            function updateReading() { //just displaying data from json continuously
                $.ajax({
                    url: './gpsdata.json',
                    dataType: 'json',
                    type: 'POST',
                    success: function(data) {
                        console.log(data);
                        $('#demo1').text(data.longitude);
                        $('#demo2').html(data.longitude);
                    }
                });
            }
            setInterval(updateReading, 2000);
        </script>
        
        <script>

            const map = L.map('map').setView([51.505, -0.09], 13);
        
            const tiles = L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
                maxZoom: 19,
                attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
            }).addTo(map);
        
            const marker = L.marker([51.5, -0.67687]).addTo(map)
                .bindPopup('<b>Ambulance Location</b>').openPopup();
        
            var lat = 51.51;
            var lon = -0.09;

            function updateGpsCoords() {

                const marker = L.marker([lat, lon]).addTo(map)
                .bindPopup('<b>Ambulance Location</b>').openPopup();

                lat += 0.005;
                lon += 0.005;
            }

            setInterval(updateGpsCoords, 1000);

            map.removeLayer(marker);
        
        
        </script>
</body>
</html>