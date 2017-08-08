<?php
$server = "localhost";
$dbusername = "root";
$dbpassword = "";
$dbname = "wsnproject";
$tablename = "wsndata";
$connection = mysqli_connect($server, $dbusername, $dbpassword, $dbname);

if (!$connection) {
    die('MySQL ERROR: ' . mysqli_connect_error());
}

$distance = $_GET['distance'];
$query = "INSERT INTO `".$tablename."` (`distance`) VALUES ('".$distance."')";

mysqli_query($connection, $query);
mysqli_close($connection);

echo "OK";
