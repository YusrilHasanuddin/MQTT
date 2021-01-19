<?php

if(isset($_POST)){

  //include conn.php to get connection to the database
  include "conn.php";

  $Ax =  mysqli_escape_string($mysqli,$_POST['Ax']);
  $Ay =  mysqli_escape_string($mysqli,$_POST['Ay']);
  $Az =  mysqli_escape_string($mysqli,$_POST['Az']);

  //The problem is, I usually run MQTT protocol using my CMD while my wemos is connected in my laptop.  
  $comm = "C:\\Users\\ACER\\AppData\\Local\\Programs\\Python\\Python38\\python.exe C:\\xampp\\htdocs\\Internet of Things\\MQTTtest.py -x ".sprintf("%.2f", $Ax)." -y ".sprintf("%.2f", $Ay)." -z ".sprintf("%.2f", $Az);
  //Is there any possible to bring CMD into website?
  $label = shell_exec($comm);

  $hasilquery = mysqli_query($mysqli,"INSERT INTO iot(Ax,Ay,Az,Label) VALUES ($Ax,$Ay,$Az,'$label')");
  exit('Data Has Been Inserted');
}

?>