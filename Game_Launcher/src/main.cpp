  #include "SceneManager.h"
  #include "SFML/Graphics.hpp"
  #include "Game.h"
  //#include <GameObject.h>
  #include <iostream>
  //TODO
  int main(int argc, char** argv) 
  {
      SceneManager a(argv[0], 1920, 1080, "const std::string & title"/*,sf::Style::Fullscreen*/);
      a.AddScene(new Game(a.getWindow(),240,a.geTextureCash()));
      a.Exe();
    
  }

 //#include <nlohmann/json.hpp>
 //#include <iostream>
 //
 //// Pour simplifier l'utilisation
 //using json = nlohmann::json;
 //
 //int main() {
 //    // Créer un objet JSON simple
 //    json data = {
 //        {"name", "Test Project"},
 //        {"version", 1.0},
 //        {"working", true}
 //    };
 //    
 //    // Afficher le JSON
 //    std::cout << "Test de la bibliothèque nlohmann-json:" << std::endl;
 //    std::cout << data.dump(4) << std::endl;
 //    
 //    // Accéder aux données
 //    std::cout << "Nom: " << data["name"] << std::endl;
 //    std::cout << "Version: " << data["version"] << std::endl;
 //    
 //    // Modifier une valeur
 //    data["version"] = 1.1;
 //    std::cout << "Nouvelle version: " << data["version"] << std::endl;
 //    
 //    std::cout << "Test nlohmann-json réussi!" << std::endl;
 //    
 //    return 0;
 //}
