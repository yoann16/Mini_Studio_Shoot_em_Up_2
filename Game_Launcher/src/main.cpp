#include <iostream>
#include <memory>
#include "SceneManager.h"
#include "Game.h"


//#include "SFML/Graphics.hpp"
//#include <GameObject.h>
  
int main(int argc, char** argv) 
{
    std::unique_ptr<Root> root = std::make_unique< Root>();
    SceneManager manager(root.get(), argv[0], 1920, 1080, "Cursed Kingdom"/*,sf::Style::Fullscreen*/);
    manager.AddScene(new Game(manager.getWindow(),240, manager.getTextureCash()));
    manager.Exe();
    return 0;
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
