<?php
session_start();
if(isset($_POST['username']) && isset($_POST['password']))
{
    // connexion à la base de données
    $db_username = 'root';
    $db_password = '';
    $db_name     = 'freetool';
    $db_host     = 'localhost';
    $db = mysqli_connect($db_host, $db_username, $db_password,$db_name)
           or die('could not connect to database');
    
    // on applique les deux fonctions mysqli_real_escape_string et htmlspecialchars
    // pour éliminer toute attaque de type injection SQL et XSS
    $username = $_POST['username']; 
    $password = $_POST['password'];
    
    if($username !== "" && $password !== "")
    {
        $requete = "SELECT count(*) FROM utilisateur where 
              nom_utilisateur = '".$username."' and mot_de_passe = '".$password."' ";
        $exec_requete = mysqli_query($db,$requete);
        $reponse      = mysqli_fetch_array($exec_requete);
        $count = $reponse['count(*)'];
        if($count!=0) // nom d'utilisateur et mot de passe correctes
        {
           $_SESSION['username'] = $username;
           header('Location: PageMembre.php');
        }
        else
        {
         $requete2 = "SELECT count(*) FROM administrateur where 
               nom_utilisateur = '".$username."' and mot_de_passe = '".$password."' ";
         $exec_requete2 = mysqli_query($db,$requete2);
         $reponse2      = mysqli_fetch_array($exec_requete2);
         $count2 = $reponse2['count(*)'];
         if($count2!=0) // nom d'utilisateur et mot de passe correctes
         {
            $_SESSION['username'] = $username;
            header('Location: PageAdmin.php');
         }
         else
         {
            header('Location: login.php?erreur=1'); // utilisateur ou mot de passe incorrect
         }
        }
    }
    else
    {
       header('Location: login.php?erreur=2'); // utilisateur ou mot de passe vide
    }
}
else
{
   header('Location: login.php');
}
mysqli_close($db); // fermer la connexion
?>