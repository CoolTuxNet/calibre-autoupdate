#  Calibre Auto Updater Header File
#    Copyright (C) 2013-2015  Leon Gaultier
#

func_term_output () {			# einheitliche Terminalausgabe, Terminal löschen
    ## Beginne mit der Ausgbe ##
    tty -s && clear
    echo -e "\033[44m \033[0m\033[1m $PROGNAME: Der Calibre-Autoupdate-Installer Version $VERSION\033[0m\n\033[44m \033[0m 2013-2015 by Leon Gaultier\n\e[m";
    return 0
}

func_usage () {    # Gibt Auskunft über die Aufrufmöglichkeiten des Scriptes
    func_term_output
    echo "Verwendung: $PROGNAME [OPTION...]"
    echo -e "Verwende $PROGNAME --help oder $PROGNAME -h für mehr Informationen.\n"
    return 0
}

func_help () {     # Listet alle Optionsschalter auf
    func_term_output
    echo "Verwende: $PROGNAME [OPTION...]"
    echo "$PROGNAME -- Der Calibre-Autoupdate-Installer (CAUI)"
    echo ""
    echo "Options:"
    echo "   -h, --help              zeigt die Hilfe an"
    echo "   -V, --version           gibt die Programmversion aus"
    echo "   -i, --install           installiert den Calibre-Autoupdater (CAU)"
    echo ""
    echo -e "Sende Fehler an <leongaultier@gmail.com>.\n"
    return 0
}

func_version () {  	# Versionsauskunft des Updater Installers und durch Versionsnummernübergabe an das Updaterprogramm auch Version des Updater Scriptes

    func_term_output
    echo "$PROGNAME: Der Calibre-Autoupdate-Installer (CAUI) v$VERSION"
    echo "Leon Gaultier 2013-2014. Das Programm darf verteilt werden,"
    echo -e "in der Hoffnung das es hilfreich ist, aber OHNR IRGENDEINE GARANTIE\n"
    return 0
}

func_progressbar() {		# Funktion Fortschrittsanzeige, Fake - Joke
    echo -e -n $'\033[34m------------------------------------------------------------------------- 100%\r'
    echo -e -n "\033[32m0% "
    for ((i=0; i<61; i++)); do
	echo -e -n "\033[32m="  
	case $i in
	    15)
		echo -e -n "25%" ;;
	    30)
		echo -e -n "50%" ;;
	    45)
		echo -e -n "75%" ;;
	    60)
		echo -e -n " 100%" ;;
	esac
    sleep 0.07
    done
    echo -e "\e[m"
    return 0
}
