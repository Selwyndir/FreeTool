# FreeTool
<br/>
<br/>
Problematique
 <br/>
Une association souhaite mutualiser les outils de jardinage et de bricolage pour les particuliers. <br/>
L’accès au local est réservé aux membres et aux adhérents de l’association, l’argent des cotisations permet de financer l’entretien et l’achat des nouveaux équipements.<br/>
<br/>
Première Partie du Système: Access System<br/>
Mettre en œuvre un procédé permettant d'identifier ,de contrôler l’accès au local, d'afficher un message d'accès, d’envoyer la donnée et d’activer une caméra pendant la présence du particulier à l’intérieur du local.<br/>
<br/>
Seconde Partie du Système: Tools_System <br/>
Mettre en œuvre un procédé permettant de gérer les outils empruntés (entrée ou sortie) en précisant la durée en jours, d'afficher localement l'information et d’envoyer la donnée <br/>
<br/>
Troisième Partie du Système: The Freetool Project <br/>
Mettre en œuvre un procédé permettant la réception des données sans fil (accès local / emprunt  outils) , de construire une DataBase et une interface WEB afin de de contrôler via le web l’état du magasin (flux  vidéo, présence personnes, matériel disponible / emprunté).  <br/>
<br/> 
Codage Logs <br/>
 **Access System** <br/>
``0x1`` : Porte Ouverte <br/>
``0x2`` : Porte Fermée <br/>
``0x3`` : Intru dans l'abri <br/>
``0x4`` : Utilisateur dans l'abri <br/>
 <br/>
**Tools_System** <br/>
``1x1`` : Outil disponible <br/>
``1x2 <dd/mm/yy>`` : Date de Retour <br/>
``1x3 <dd>`` : Combien de jour restant<br/>
<br/>
<br/>
Quelques commandes SQL utiles :<br/>
``INSERT INTO table (colonne1, colonne2) VALUES ('valeur1', 'valeur2')`` : Inserer des valeurs <br/>
``UPDATE table SET colonneN="Valeur à changer" WHERE id=1;`` : changer les valeurs pour l'id 1 <br/>
<br/>
<br/>
<br/>
Partie Hacking : <br/>
``'OR 1=1 OR 1='`` ou ``'OR 1=1 #'``: Injection SQL <br/>
Site de Phishing dans le dossier: The_Freetool_Project_Phishing
