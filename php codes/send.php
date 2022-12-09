<?php
$error = NULL;
echo "Only arduino must access this link!". "<br>". "<br>";


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






    //getting data from arduino
    $a = $_GET['batstat'];
    $b = $_GET['batpercent'];
    $c = $_GET['port1stat'];
    $d = $_GET['port1time'];  
    
    //code for testing input
    // $a = "test";
    // $b = "test";
    // $c = "test";
    // $d = "test";

    $time = date("h:i:s:a");


if ( $_GET['batstat']){
    




    $inputid = 1; //the id of row you want to change in the database



    // this code is for uploading new line into database.
    // $insert = $mysqli->query ("INSERT INTO solarstat (batstatus,batpercent,port1status,port1time)VALUES ('$a','$b','$c','$d')");




    // this code is for updating the first line in database
    $insert = "UPDATE solarstat SET batstatus = '{$a}',batpercent = '{$b}',port1status = '{$c}',port1time = '{$d}',timeupdated = '{$time}' WHERE id = {$inputid} ";
    $update_query = mysqli_query($mysqli, $insert);


}





if ($insert){
    echo "Hello, solartracker database has been updated!" . "<br>". "<br>" . "New Data are:". "<br>". "<br>";
    echo "Time uploaded: " . $time. "<br>" . "<br>" ; 

    echo "Solar battery Status: " . $a . "<br>";
    echo "Solar battery Remaining: " . $b . "<br>" . "<br>";
    echo "Charging Station Status: " . $c . "<br>";
    echo "Charging Time Remaining: " . $d . "<br>" . "<br>" . "<br>";

    echo "<hr>";

}



// this code is getting from database
$resultSet = $mysqli->query("SELECT * FROM solarstat WHERE id = 1");
                        
                        
if ($resultSet->num_rows !=0){


    //Process Login
    $row = $resultSet->fetch_assoc();

    $froma = $row['batstatus'];
    $fromb = $row['batpercent'];
    $fromc = $row['port1status'];
    $fromd = $row['port1time'];
    $frome = date("h:i:s:a");   //time of insert in database
    $fromf = $row['timeupdated'];   //most recent time of update

    //This code shortens the time
    $date = strtotime($fromf);
    $date = date ('M d Y', $date);

    
    echo "These are the data fetched from the database:" . "<br>". "<br>";
    echo "Last Update.. : " . $fromf . "<br>";
    echo "Current Time : " . $frome . "<br>". "<br>";
    echo "Solar battery Status: " . $froma . "<br>";
    echo "Solar battery Remaining: " . $fromb . "<br>" . "<br>";
    echo "Charging Station Status: " . $fromc . "<br>";
    echo "Charging Time Remaining: " . $fromd . "<br>";
    

}
 

