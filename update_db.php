<?php
    $hostname = "localhost";
    $username = "root";
    $password = "";
    $database = "techothon";

    $conn = mysqli_connect($hostname, $username, $password, $database) or die("Unable to connect to database");
?>