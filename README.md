# 📘 Solveur par Élimination de Gauss

Un utilitaire en ligne de commande pour résoudre des systèmes d'équations linéaires en utilisant la méthode de Gauss, avec la possibilité d'afficher les étapes intermédiaires et de gérer divers cas particuliers.

---

## 📝 Fonctionnalités

- **🔄 Algorithme de Gauss** : Résout des systèmes d'équations linéaires avec pivot de Gauss.
- **🔍 Affichage des Étapes** : Affiche les étapes de résolution selon les préférences de l'utilisateur.
- **⚠️ Gestion des Erreurs** : Valide les entrées et gère les cas de matrices invalides, systèmes incompatibles, etc.
- **➗ Format Fractionnaire** : Affiche les solutions sous forme de fractions pour plus de lisibilité.

---

## ⚙️ Prérequis

- **Compilateur C** : Un compilateur C doit être installé, tel que GCC ou MSVC.

---

## 🚀 Installation

1. **Cloner le dépôt :**

   ```bash
   git clone https://github.com/AnaMkv/Pivot-Gauss.git
   cd Pivot-Gauss
   ```
2. **Compilez le code**
   ```bash
   gcc main.c -o Pivot_Gauss -lm
   ```
3. **Exécutez le fichier compilé**
   ```bash
   ./Pivot_Gauss
   ```
   
---

# 💻 Utilisation

1.	**Exécution** : Lancez le programme, qui vous demandera si vous souhaitez afficher les étapes intermédiaires.
2.	**Saisie des Détails** :
     - Indiquez le nombre d’équations et d’inconnues.
     - Saisissez chaque coefficient pour chaque équation selon les instructions.
3.	**Résultats** : Les solutions sont affichées en format fractionnaire.

---

# ⚠️ Limitations

- **Précision** : Limité par les constantes de précision EPSILON et PRECISION.
- **Validation d’Entrée** : Validation de base uniquement ; des valeurs non numériques peuvent entraîner un comportement indéfini.
- **Pas d’Interface Graphique** : Interface en ligne de commande uniquement.
- **Systèmes Complexes** : Certains systèmes complexes peuvent présenter des erreurs de résolution. Veillez à toujours vérifier les résultats obtenus.

---

# 🤝 Contributions

Les contributions sont les bienvenues ! N’hésitez pas à :
- Ouvrir des issues pour signaler des bugs ou proposer des idées.
- Soumettre des pull requests pour ajouter des fonctionnalités.

--- 

# 📄 Licence

Le code est sous licence GPL-v3. Sentez-vous libre de le télécharger, de le modifier, de le repartager... tant que vous le faites gratuitement !
