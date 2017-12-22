#!/bin/bash
# Generated at Sa. Dez. 17 06:53:14 2016
startsudo() { sudo -v; ( while true; do sudo -v; sleep 50; done; ) &   SUDO_PID="$!" ; trap stopsudo SIGINT SIGTERM ; }
stopsudo() { disown "$SUDO_PID" 2>/dev/null ;kill "$SUDO_PID" 2>/dev/null ; trap - SIGINT SIGTERM ; sudo -k ; }
##########################################
startsudo
# Category: Web
sudo pacman --noconfirm --needed -S  firefox thunderbird pidgin chromium

# Category: Dev
sudo pacman --noconfirm --needed -S  jdk7-openjdk jre7-openjdk jdk8-openjdk jre8-openjdk qt5-base qtcreator qt5-tools

# Category: Language Packs
sudo pacman --noconfirm --needed -S  firefox-i18n-de thunderbird-i18n-de libreoffice-fresh-de

# Install at end

stopsudo
echo -e '[1;31m###############################[0m'
echo -e '[1;31m# [0;32mAppInst finished :)[0m
'
