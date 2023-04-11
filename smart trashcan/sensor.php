<?php
include "connection.php";

$conn = connection();

    $data = $_POST['data'];
    $sql = "INSERT INTO `dht11_data`( `data`) VALUES ('$data') ";
    // $sql = "INSERT INTO sensor_data (temperature, light, smoke) VALUES ('$temperature','$light','$smoke')";
    $conn->query($sql) or die($conn->error);
?>