<?php

$server   = "localhost";
$usernames = "id12730345_iottest";
$passwords = "b4TCh#JXdEry*[3g";
$database = "id12730345_yusril"; // name database
 
$mysqli = mysqli_connect($server, $usernames, $passwords, $database);

//Check error, if error occured, close connection to mysql
if (mysqli_connect_errno()) {
	echo 'Connection Error Occured, Problem: '.mysqli_connect_error();
	exit();
	mysqli_close($mysqli);
}else{
	echo "Successfully Connected";
}
	
$testquery="select * from iot";
$testresult=mysqli_query($mysqli,$testquery);
echo "<br>";
echo "<table boe>";
foreach($testresult as $row){
   echo "<tr>";
   echo "<td>Ax: $row[Ax]</td><td>Ay: $row[Ay]</td><td>Az: $row[Az]</td><td>Label: $row[Label]</td>";
   echo "</tr>";
}
echo "</table>"
?>