<?php
    $hostname = "localhost";
    $username = "root";
    $password = "";
    $database = "technothon";

    $conn = mysqli_connect($hostname, $username, $password, $database) or die("Unable to connect to database");

    $query = "SELECT * FROM patientdetails";

    $result = mysqli_query($conn, $query) or die("Unable to select data");

    while($row = mysqli_fetch_array($result)) {
        echo "<table>
            <tr>
                <th>Name</th>
                <td>Bill Gates</td>
            </tr>
            <tr>
                <th>Telephone:</th>
                <td>555 77 854</td>
            </tr>
            <tr>
                <th>Telephone:</th>
                <td>555 77 855</td>
            </tr>
        </table>";
    }
 ?>