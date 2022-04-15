# FreeTool
<br/>
<br/>
***Problématique du Projet :***<br/>
Une association souhaite mutualiser les outils de jardinage et de bricolage pour les particuliers. <br/>
L’accès au local est réservé aux membres et aux adhérents de l’association, l’argent des cotisations permet de financer l’entretien et l’achat des nouveaux équipements.<br/>
<br/>
**Première Partie du Système**<br/>
Mettre en œuvre un procédé permettant d'identifier ,de contrôler l’accès au local, d'afficher un message d'accès, d’envoyer la donnée et d’activer une caméra pendant la présence du particulier à l’intérieur du local.<br/>
<br/>
**Seconde Partie du Système**<br/>
<br/>
**Troisième Partie du Système**<br/>








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
**SQL** <br/>
``'OR 1=1 OR 1='`` ou ``'OR 1=1 #'``: Injection SQL <br/>
``INSERT INTO table (colonne1, colonne2) VALUES ('valeur1', 'valeur2')`` : Inserer des valeurs <br/>
``UPDATE table SET colonneN="Valeur à changer" WHERE id=1;`` : changer les valeurs pour l'id 1 <br/>


