
 <meta http-equiv="refresh" content="1; URL=http://solartrackerfv2.site">
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link href="style_v.1.css" rel="stylesheet" type="text/css" />
</head>
<body>
    
</body>
</html>







<?php 

//for local xampp server
// $server = "localhost";
// $username = "test";
// $password = "test";
// $dbname = "solartracker";

//for online database
$server = "localhost";
$username = "solartra_user";
$password = "A1432llen!";
$dbname = "solartra_data";









$mysqli = NEW MYSQLI ($server,$username,$password,$dbname);




 
//Query the database
//  echo $u . "<br>";
//  echo $p;
$resultSet = $mysqli->query("SELECT * FROM solarstat WHERE id = 1");
                        
                        
if ($resultSet->num_rows !=0){


    //Process Login
    $row = $resultSet->fetch_assoc();

    $a = $row['batstatus'];
    $b = $row['batpercent'];
    $c = $row['port1status'];
    $d = $row['port1time'];
    $e = date("h:i:s:a");   //time of insert in database
    $f = $row['timeupdated'];   //most recent time of update

    //This code shortens the time
    $date = strtotime($f);
    $date = date ('M d Y', $date);


    // echo "These are the data fetched from the database:" . "<br>". "<br>";
    // echo "Last Update.. : " . $f . "<br>";
    // echo "Current Time : " . $e . "<br>". "<br>";
    // echo "Solar battery Status: " . $a . "<br>";
    // echo "Solar battery Remaining: " . $b . "<br>" . "<br>";
    // echo "Charging Station Status: " . $c . "<br>";
    // echo "Charging Time Remaining: " . $d . "<br>";

}
 

?>


<div class="reglogbox"> 
          

<p>Last Update. : <?php echo $f ?><br> Current Time :  <?php echo $e ?></p>

<p>Solar battery Status: <?php echo $a ?></p>            
    

<p>Solar battery Remaining: <?php echo $b ?></p>
<p>Charging Station Status: <?php echo $c ?></p>
<p>Charging Time Remaining: <?php echo $d ?></p>


<!--<a href = "send.php">Upload data</a>-->

</div> 














