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

$query = "SELECT * FROM `wsndata` order by date_added desc limit 10";
$result = mysqli_query($connection, $query);
mysqli_close($connection);
?>
<html>
<head>
<title>Matja e distances me sensorin ultrasonik</title>
<meta http-equiv="refresh" content="1; URL=http://localhost:8080/arduino">
</head>
<body>
	<h1 style="text-align:center;">Matja e distances dhe kohes se detektimit te objektit nga Sensori Ultrasonik</h1>
	<div>
		<table border="1" style="margin-left:auto; margin-right:auto;" >
			<tr>
				<td>Id</td>
				<td>Distanca</td>
				<td>Koha</td>
			</tr>

			<?php
			while($row = mysqli_fetch_assoc($result)){
				echo "<tr>";
				echo "<td>".$row['id']."</td>";
				echo "<td>".$row['distance']."</td>";
				echo "<td>".$row['date_added']."</td>";
				echo "</tr>";
			}
			?>
		</table>
	</div>
</body>
</html>