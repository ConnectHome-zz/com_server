#!/bin/bash

#Creation d'un repertoire temporaire pour les .o
if ! [ -d obj ]; then
 echo "Création du dossier 'obj'\n"
 mkdir obj
fi

#creation d'un repertoire pour les applications générées
if ! [ -d app ]; then
 echo "Création du dossier 'app'\n"
 mkdir app
else
 #on purge app s'il existe
 echo "Suppresion des fichiers dans 'app'"
 rm -r app/*
fi

#on se place dans le repertoire obj pour generer le client
echo "cd obj"
cd obj

gcc -c ../network/network_module.c
gcc -c ../module/module.c

gcc -o module network_module.o module.o

#on copie le fichier généré dans les applications
echo "Copie de 'module' vers le dossier app/"
cp module ../app/

#on supprime le contenu du repertoire temporaire
rm -r ./*

#on se place dans le repertoire obj pour generer le serveur
gcc -c ../curl/curl.c
gcc -c ../list/node.c
gcc -c ../list/list.c
gcc -c ../network/network_server.c
gcc -c ../server/server.c
gcc -c ../server/module.c

gcc -o server curl.o node.o list.o network_server.o module.o server.o `pkg-config --libs libcurl`


#on copie le fichier généré dans les applications
echo "Copie de 'server' vers le dossier app/"
cp server ../app/

#on supprime le repertoire temporaire 
echo "Suppression du dossier 'obj'"
cd ..
rm -r obj/

