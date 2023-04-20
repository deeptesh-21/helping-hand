<?php
    $hostname = "localhost";
    $username = "root";
    $password = "";
    $database = "technothon";

    $conn = mysqli_connect($hostname, $username, $password, $database) or die("Unable to connect to database");

    if ($_GET["latitude"] && $_GET["longitude"]) {
        $latitude = $_GET["latitude"];
        $longitude = $_GET["longitude"];
        $id = 1;

        echo $latitude;
        echo $longitude;
        
        $query = "UPDATE gpsdata SET latitude = '$latitude', longitude = '$longitude' WHERE id = '$id'";
        mysqli_query($conn, $query) or die("unable to update the table");

        $JSON = file_get_contents('./gpsdata.json');
        echo $JSON;
        $myArr = json_decode($JSON, true);
        $myArr['latitude'] = $latitude;
        $myArr['longitude'] = $longitude;
        $JSON = json_encode($myArr);
        file_put_contents('./gpsdata.json', $JSON);
    }
 ?>