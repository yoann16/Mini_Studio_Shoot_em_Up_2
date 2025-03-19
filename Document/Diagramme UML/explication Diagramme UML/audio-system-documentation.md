# Documentation du Système Audio

## Vue d'ensemble

Le système audio du moteur de jeu est basé sur la bibliothèque SFML et suit une architecture orientée objet. Il est conçu pour être modulaire, flexible et s'intégrer harmonieusement avec les autres composants du moteur, tout en permettant une gestion efficace des ressources sonores.

## Architecture

### IAudioManager (Interface)

Interface abstraite définissant le contrat pour toute implémentation d'un gestionnaire audio. Elle expose les fonctionnalités essentielles:

- **PlaySound** - Pour jouer un effet sonore spécifique
- **PlayMusic** - Pour démarrer la lecture d'une musique
- **StopSound** - Pour arrêter un effet sonore spécifique
- **StopMusic** - Pour arrêter la musique en cours
- **SetGlobalVolume** - Pour régler le volume global

Cette interface garantit que toute implémentation concrète fournira au minimum ces fonctionnalités essentielles, assurant ainsi l'interchangeabilité des systèmes audio.

### SFMLAudioManager (Implémentation)

Implémentation concrète de l'interface IAudioManager utilisant la bibliothèque SFML. Cette classe dispose de:

- Une map de sons associant des noms à des objets Sound
- Une référence à la musique actuellement en lecture
- Un système de gestion du volume global
- Un état pour le mode muet
- Une référence au ResourceManager pour charger les ressources audio

En plus des méthodes de l'interface, elle offre des fonctionnalités supplémentaires:
- **LoadSound** - Pour précharger les sons
- **UnloadSound** - Pour libérer la mémoire
- **Mute** - Pour couper rapidement tout l'audio
- **Unmute** - Pour réactiver l'audio

### AudioSource (Composant)

Composant pouvant être attaché aux objets de jeu pour créer des sources sonores spatialisées. Il permet:

- D'encapsuler un son SFML avec ses propriétés
- De positionner le son dans l'espace de jeu 2D
- De contrôler individuellement:
  - Le volume
  - La hauteur (pitch)
  - Le mode de lecture en boucle
  - La position spatiale

## Intégration avec les autres systèmes

### Avec le ResourceManager

Le système audio s'appuie sur le ResourceManager (singleton) pour:
- Charger efficacement les fichiers audio
- Éviter les duplications en mémoire
- Gérer la durée de vie des ressources

### Avec les GameObjects

Les AudioSource peuvent être attachés aux GameObjects pour:
- Créer des sons rattachés aux entités de jeu
- Permettre une spatialisation du son
- Associer des effets sonores aux actions des objets

### Avec le système de Menu

Le système audio s'intègre notamment dans l'OptionsMenuScene où:
- Les utilisateurs peuvent ajuster le volume de la musique et des effets
- Les préférences audio peuvent être sauvegardées/chargées
- Les changements peuvent être appliqués en temps réel

## Workflow d'utilisation

1. **Initialisation**
   - Création d'une instance de SFMLAudioManager
   - Préchargement des sons fréquemment utilisés

2. **Lecture des sons**
   - Appel à PlaySound pour les effets sonores
   - Appel à PlayMusic pour les musiques d'ambiance

3. **Configuration**
   - Réglage des volumes via SetGlobalVolume
   - Possibilité de couper le son avec Mute

4. **Intégration avec les objets**
   - Création d'AudioSource et attachement aux GameObjects
   - Configuration des propriétés individuelles (position, volume, etc.)

## Avantages de cette architecture

- **Modularité**: Séparation claire des responsabilités
- **Extensibilité**: Possibilité d'ajouter facilement de nouvelles fonctionnalités
- **Abstraction**: L'interface IAudioManager permet de changer d'implémentation si nécessaire
- **Gestion efficace des ressources**: Utilisation du ResourceManager pour optimiser la mémoire

## Limitations et perspectives d'amélioration

- **Audio 3D**: Le système actuel est principalement conçu pour le 2D, mais pourrait être étendu
- **Effets**: Possibilité d'ajouter des DSP (Digital Signal Processing) pour des effets avancés
- **Streaming**: Optimisation pour les longs fichiers audio via le streaming
- **Mixage avancé**: Implémentation de groupes de sons et de mixage dynamique

---

Cette documentation a été générée pour le moteur de jeu modulaire basé sur SFML, axé sur les jeux de type Hotline Miami avec possibilité d'adaptation future pour d'autres genres.
