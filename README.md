# Custom Minecraft
Reprise de mon projet de Isart Digital en 2018.
Ce projet était un PFA en groupe de 3, il consistait à partir d'un moteur maison (OpenGL) à recréer Minecraft.
Nous disposions de 3 semaines, pour implémenter le plus de features possibles.
J'ai décidé de reprendre le projet en parallèle de mes études pour réaliser ce dont je n'avais pas eu le temps, ni les compétences de faire à l'époque.

## Ce que nous avions réalisé :

Les bases du rendering étaient posées, nous pouvions rendre un block.
Quelques essais afin d'implémenter des bases de physique avaient étés également tentés.
Mais les choix de texture n'avaient pas étés implémentées, rendre un chunk de 16 / 16 / 16 utilisait environ 300 MO de mémoire.
Un exemple de ce que l'on avait atteint :

![Minecraft 2018](https://i.ibb.co/f9YWJJV/Gen-Opengl.png)

### Notre rendu post Mortem :

Nous avons du faire à nombre de difficultés durant ce projet, mais nous n’en tirons aucun regret, ni aucune rancœur. Cela nous a permis à tous, de se rendre compte des difficultés pouvant être approchées en entreprise. Ces dernières nous permettent ainsi, maintenant d’appréhender avec un recul plus important les problématiques pouvant se poser, lors de l’élaboration d’un projet.
Heureusement, nous n’avons pas eu que des difficultés, nous avons apprécié certaines parties, comme le rendering, la génération procédurale, et le gameplay. Ces parties ont consolidées nos connaissances et nous en ont apportées nombres de nouvelles.

## Ce que j'ai réalisé :

Aujourd'hui seul, mais accompagné de nouvelles compétences, j'ai repris le projet.
Je me suis d'abord attaqué à la partie graphique du projet, c'est ce que je fais encore aujourd'hui.
En effet, cette partie m'interesse énormément, et j'aime la pousser au maximum.
Par exemple, aujourd'hui 100 Chunks de 16/16/16 ne prennent que 250 MO.
Et ce grâce à de nombreuses optimisations.

J'ai donc repris entièrement la génération du Chunk, ajouté un système optimisé de vérification de voisins (Voir si un bloc est occludé par un autre).
Ensuite je me suis attaqué à implémenter différentes textures, j'ai eu quelques soucis sur cette partie, mais après avoir implémenté un atlas de textures, tout allait mieux.
Cette partie fonctionnelle, j'ai voulu rendre le jeu plus vivant en y implémentant des "décorations". J'ai donc ajouté des arbres, de l'eau, de et de l'herbe.
J'ai ensuite modifié les différents shaders pour rendre le monde plus vivant, en ajoutant un mouevement à l'eau, au feuillage, et aux herbes.
M'amusant vraiment beaucoup à implémenter des nouvelles features graphiques, j'en ajoute au fur et à mesure, je suis en train de travailler sur le soleil (screenshot 3).
Mais viennent après les ombres, le/la light scattering, et les reflets sur l'eau.  
C'est là où j'en suis aujourd'hui, je suis vraiment content, j'avance vite, et je ne bloque plus sur des problèmes mineurs.  

Mes projets de modifications sont visibles sur le <a href="https://trello.com/b/ZMJIPYXa/minecraft-opengl" rel="nofollow">Trello </a>

J'ai appris beaucoup en reprennant le projet, et dès que je travaille dessus à côté de mes études, je continue de beaucoup apprendre.

### Quelques captures du projet aujourd'hui
![Minecraft 2021](https://i.ibb.co/ZWk8kD0/sand.jpg)
![Minecraft 2021](https://i.ibb.co/5MQGRL1/movement.jpg)
![Minecraft 2021](https://i.ibb.co/BBcbXc2/sun.jpg)
