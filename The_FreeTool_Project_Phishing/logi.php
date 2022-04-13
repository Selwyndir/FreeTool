<html>
    <head>
       <meta charset="utf-8">
        <!-- importer le fichier de style -->
        <link rel="stylesheet" href="style-login.css" media="screen" type="text/css" />
        <link rel="icon" href="icon.png">
        <title>The Freetool project</title>
    </head>
    <body>
        <div id="container">
            <!-- zone de connexion -->
            
            <form action="verificationh.php" method="POST">
                <img src="banner.png" heigt="10%" width="100%">
                
                <label style="color:#03989e";><b>Nom d'utilisateur</b></label>
                <input type="text" placeholder="Entrer le nom d'utilisateur" name="pseudo" required>

                <label style="color:#01b14d";><b>Mot de passe</b></label>
                <input type="password" placeholder="Entrer le mot de passe" name="mdp" required>

                <input type="submit" id='submit' value='LOGIN' >
            </form>
        </div>
    </body>
</html>