<?php
  $host = 'localhost';
  $dbname = 'freetool';
  $username = 'root';
  $password = '';
    
  $dsn = "mysql:host=$host;dbname=$dbname"; 
  // récupérer tous les utilisateurs
  $sql = "SELECT * FROM tools WHERE 1";
   
  try{
   $pdo = new PDO($dsn, $username, $password);
   $stmt = $pdo->query($sql);
   
   if($stmt === false){
    die("Erreur");
   }
   
  }catch (PDOException $e){
    echo $e->getMessage();
  }
?>
<html lang="fr_FR">
<head>
<title>The Freetool project</title>
<meta charset="utf-8">
<meta name="description" content=" ">
<link rel="stylesheet" type="text/css" href="style-admin.css">
<link rel="icon" href="icon.png">
</head>
<body>
<div id="et">
    <img src="banner.png" width="40%" height="100%"/>
</div>
<div id="mdn"><img src="http://adresse_ip_du_pi:8082/?action=stream" width="100%" heigth="100%"/></div>
<div id="cdp">
    <p>TOOLS</p>
    <table border="0px" width="200" height="80%" align="center">
        <?php while($row = $stmt->fetch(PDO::FETCH_ASSOC)) : ?>
            <tr>
                <td><?php echo htmlspecialchars($row['id']); ?></td>
                <td><?php echo htmlspecialchars($row['Tool']); ?></td>
            </tr>
        <?php endwhile; ?>
    </table>
</div>
<div id="inter"></div>
<div id="pdp"><p>LOGS</p><br>
    <table border="0px" width="100%" height="80%" align="center">
        <?php while($row = $stmt->fetch(PDO::FETCH_ASSOC)) : ?>
            <tr>
                <td><?php echo htmlspecialchars($row['LOGS']); ?></td>
            </tr>
        <?php endwhile; ?>
    </table>
</div>
<div id="inter"></div>
</body>
<footer>
<a href='PageAdmin.php?deconnexion=true'>Déconnexion</a>
    <?php
        session_start();
        if(isset($_GET['deconnexion']))
        { 
            if($_GET['deconnexion']==true)
            {  
                session_unset();
                header("location:login.php");
            }
        }
    ?>
</footer>
</html>

 
 
