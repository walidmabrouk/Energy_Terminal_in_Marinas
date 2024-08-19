#include "./File.hpp"

File::File() {}

File::~File()
{
  closeFile();
}

std::string File::readFile()
{
  if (!openFileForReading())
  {
    return ""; // Retourner une chaîne vide si le fichier ne peut pas être ouvert
  }

  std::string content = "";
  while (file.available())
  {
    char c = file.read();
    content += c;
  }

  closeFile(); // Fermer le fichier après la lecture
  return content;
}

void File::saveFile(std::string content)
{
  if (!openFileForWriting())
  {
    return; // Quitter si le fichier ne peut pas être ouvert
  }

  file.print(content.c_str()); // Écriture dans le fichier

  closeFile(); // Fermer le fichier après l'écriture
}

bool File::openFileForReading()
{
  if (file)
  {
    file.close(); // Fermer le fichier existant s'il est ouvert
  }

  file = LittleFS.open("/mon_fichier.txt", "r");
  if (!file)
  {
    Serial.println("Erreur lors de l'ouverture du fichier en lecture !");
    return false;
  }

  return true;
}

bool File::openFileForWriting()
{
  if (file)
  {
    file.close(); // Fermer le fichier existant s'il est ouvert
  }

  file = LittleFS.open("/mon_fichier.txt", "w");
  if (!file)
  {
    Serial.println("Erreur lors de l'ouverture du fichier en écriture !");
    return false;
  }

  return true;
}

void File::closeFile()
{
  if (file)
  {
    file.close();
  }
}
