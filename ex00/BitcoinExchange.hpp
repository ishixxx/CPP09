#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stdexcept>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cctype>

//On utilise map pour stocker les données de la base de données data.csv, où la clé est une date (sous forme de chaîne de caractères) et la valeur est le taux de change (sous forme de float).
//Map permet une recherche efficace du taux de change pour une date donnée, de plus elle reste triée par clé, donc date, ce qui facilite la recherche du taux de change le plus proche avant une date donnée, de plus chaque date est unique dans la base de données.
//On récupèle avec une variable au bon type; le taux de change ou la date en fonction de ce qu'on veut faire
//parseDataBase lit le fichier data.csv et remplir la map avec les données de la base de données
//processInput lit le fichier d'entrée "input.txt", qui contient les dates et les valeurs pour lesquelles on veut calculer le montant en bitcoins
//parseLine traite chaque ligne du fichier d'entrée
//isDateValid vérifie si une date est valide (format YYYY-MM-DD et valeurs correctes pour l'année, le mois et le jour)
//isValueValid vérifie si la valeur est valide (positive et pas trop grande)
//getExchangeRate récupère le taux de change pour une date donnée, ou le taux de change le plus proche avant cette date si la date n'existe pas dans la base de données

class BitcoinExchange {
    public:
        BitcoinExchange();
        BitcoinExchange(BitcoinExchange const &other);
        BitcoinExchange &operator=(BitcoinExchange const &other);
        ~BitcoinExchange();

        void parseDatabase(std::string const &filename);
        void processInput(std::string const &filename);
        float getExchangeRate(std::string const &date);
    
    private:
        std::map<std::string, float> database; //map est un conteneur qui stocke des paires clé-valeur map<clé(ici date), valeur(ici taux de change)>

        void trim(std::string &s); //fonction pour enlever les espaces au début et à la fin d'une chaîne de caractères, sauter les lignes vides et 
        void parseLine(std::string line); //on modifie la ligne si il y a des espaces par exemples et si on veut la traiter malgré le séparateur 

        bool isDateValid(std::string const &date);
        bool isValueValid(float value);
};

#endif // BITCOINEXCHANGE_HPP