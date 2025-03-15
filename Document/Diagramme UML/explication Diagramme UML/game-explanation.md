# Analyse de la classe Game dans l'architecture du moteur de jeu

## La classe Game dans l'architecture

D'après le diagramme UML, la classe `Game` est au cœur du moteur de jeu. C'est le point central qui orchestre tous les autres systèmes. Voici une analyse détaillée de sa structure et de son rôle :

### Structure de la classe Game

Dans le diagramme, `Game` hérite de `IComposite`, ce qui signifie qu'elle peut contenir d'autres composants dans une structure arborescente (suivant le patron de conception Composite).

Elle contient plusieurs systèmes essentiels comme propriétés :
- `physicsEngine` : Gère la physique du jeu
- `resourceManager` : Gère les ressources (textures, sons, etc.)
- `inputManager` : Gère les entrées utilisateur
- `audioManager` : Gère l'audio
- `renderer` : Gère le rendu graphique
- `window` : Gère la fenêtre de l'application

### Méthodes principales

La classe `Game` possède les méthodes suivantes :
- `Initialize()` : Initialise tous les systèmes du jeu
- `Run()` : Exécute la boucle principale du jeu
- `Update()` : Met à jour la logique du jeu
- `Draw()` : Dessine les éléments à l'écran
- `Shutdown()` : Libère les ressources et ferme le jeu

### La boucle de jeu (Game Loop)

Le moteur de jeu utilise une boucle de jeu avec un Update fixe et un Rendu variable, ce qui est une approche solide pour les jeux d'action comme Hotline Miami. L'implémentation prévue est la suivante :

```
void Run() {
    const float fixedTimeStep = 1.0f/60.0f;
    float accumulator = 0.0f;
    
    while(isRunning) {
        float frameTime = clock.restart().asSeconds();
        accumulator += frameTime;

        while(accumulator >= fixedTimeStep) {
            FixedUpdate(fixedTimeStep);  // Physique, logique fixe
            accumulator -= fixedTimeStep;
        }

        Update(frameTime);  // Pour les animations fluides
        Draw();  // Rendu aussi rapide que possible
    }
}
```

Cette implémentation utilise le modèle d'accumulateur pour garantir que la physique et la logique fixe s'exécutent à un rythme constant (60 fois par seconde), tandis que le rendu peut s'adapter à la puissance de l'ordinateur.

### Relations avec d'autres systèmes

La classe `Game` est connectée à plusieurs autres systèmes de l'architecture :

1. **Contient des `Scene`** : Chaque jeu contient une ou plusieurs scènes qui regroupent les objets de jeu.

2. **Utilise le `IPhysicsEngine`** : Pour la simulation physique (comme décrit dans le diagramme "Système Physique").

3. **Utilise l'`InputManager`** : Pour gérer les entrées utilisateur via le pattern Command.

4. **Utilise le `ResourceManager`** : Pour charger et gérer les ressources (textures, sons, etc.).

5. **Utilise l'`IAudioManager`** : Pour jouer des sons et de la musique.

6. **Utilise l'`IRenderer`** : Pour dessiner les éléments du jeu à l'écran.

### Modularité de l'architecture

L'architecture est conçue pour être modulaire. Des interfaces (classes abstraites) sont utilisées pour chaque système majeur, ce qui permet de changer l'implémentation sans affecter le reste du code.

Cette modularité permettra facilement d'adapter le moteur pour d'autres types de jeux (jeu d'aventure, plateformer) en:
- Créant de nouvelles classes `Scene` spécialisées
- Adaptant ou étendant le système de physique
- Ajoutant de nouveaux types de commandes dans le système d'Input
- Créant de nouveaux décorateurs NPC pour différents comportements

La classe `Game` restera le point central qui orchestrera ces différents systèmes, quelle que soit leur implémentation spécifique.

## Schéma d'interaction de Game avec les autres systèmes

```
+---------------------+
|       Game          |
+---------------------+
|                     |
| - physicsEngine     |<--------> Système Physique
| - resourceManager   |<--------> Resource Manager (Singleton)
| - inputManager      |<--------> Système d'Input (Pattern Command)
| - audioManager      |<--------> Système Audio (SFML)
| - renderer          |<--------> Système de Rendu (SFML)
| - window            |
|                     |
+---------------------+
        |
        | contient
        v
+---------------------+
|       Scene         |<--------> Système de Menu
+---------------------+
        |
        | contient
        v
+---------------------+
|     IGameObject     |<--------> Système NPC (Pattern Decorator)
+---------------------+
```

Ce schéma montre comment la classe `Game` orchestre l'ensemble des systèmes du moteur de jeu, formant ainsi une architecture cohérente et modulaire.
