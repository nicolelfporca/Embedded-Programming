<?php
function connection() {
    $host = "localhost";
    $user = "root";
    $pass = "";
    $databaseName = "sensor";

    $conn = new mysqli($host, $user, $pass, $databaseName);

    if ($conn->connect_error) {
        echo $conn->connect_error;
    } else {
        return $conn;
    }
}
?>