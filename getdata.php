<?php
//Checking if data is exist
if(isset($_POST)){
    if(isset($_POST['key'])){

          //run using conn.php
          include "conn.php";

        
          if($_POST['key']=='getdataAx'){
            $query = mysqli_query($mysqli,"SELECT Ax FROM iot ORDER BY ID DESC LIMIT 1;");
            if(mysqli_num_rows($query)>0){
               $response = "";
               while($data = mysqli_fetch_array($query)){
                  $response .= "".$data['Ax'];
                  exit($response);
               }
            }else{
                exit('nodata');
            }
          }elseif($_POST['key']=='getdataAy'){
            $query = mysqli_query($mysqli,"SELECT Ay FROM iot ORDER BY ID DESC LIMIT 1;");
            if(mysqli_num_rows($query)>0){
               $response = "";
               while($data = mysqli_fetch_array($query)){
                  $response .= "".$data['Ay'];
                  exit($response);
               }
            }else{
                exit('nodata');
            }
          }elseif($_POST['key']=='getdataAz'){
            $query = mysqli_query($mysqli,"SELECT Az FROM iot ORDER BY ID DESC LIMIT 1;");
            if(mysqli_num_rows($query)>0){
               $response = "";
               while($data = mysqli_fetch_array($query)){
                  $response .= "".$data['Az'];
                  exit($response);
               }
            }else{
                exit('nodata');
            }
          }elseif($_POST['key']=='getdataLabel'){
            $query = mysqli_query($mysqli,"SELECT Label FROM iot ORDER BY ID DESC LIMIT 1;");
            if(mysqli_num_rows($query)>0){
               $response = "";
               while($data = mysqli_fetch_array($query)){
                  $response .= "".$data['Label'];
                  exit($response);
               }
            }else{
                exit('nodata');
            }
          }
    }
}
?>