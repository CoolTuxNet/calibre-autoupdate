#  Calibre Auto Updater Header File
#    Copyright (C) 2013-2014  Leon Gaultier
#

func_term_output ()
{
    ## Beginne mit der Ausgbe ##
    tty -s && clear
    echo -e "\033[44m \033[0m\033[1m $PROGNAME Version $VERSION\033[0m\n\033[44m \033[0m 2013-2014 by Leon Gaultier\n\e[m";
    return 0
}

func_usage ()
{
    func_term_output
    echo "Verwendung: $PROGNAME [OPTION...]"
    echo "Verwende '$PROGNAME --help' oder '$PROGNAME -h' für mehr Informationen."
    return 0
}

func_help ()
{
    func_term_output
    echo "Verwende: $PROGNAME [OPTION...]"
    echo "$PROGNAME -- Der Calibre! Linux Edition calibre-autoupdater (CAU)"
    echo ""
    echo "Options:"
    echo "   -h, --help                   zeigt die Hilfe an"
    echo "   -V, --version                gibt die Programmversion aus"
    echo "   -c, --check                  kontrolliert ob benötigte Programme vorhanden sind"
    echo "   -u, --uninstall              deinstalliert den Calibre-Autoupdater"
    echo "       --uninstall_calibre      deinstalliert das Calibre Programm"
    echo ""
    echo -e "Sende Fehler an <leongaultier@gmail.com>.\n";
    return 0
}

func_version ()
{
    func_term_output
    echo "$PROGNAME: Der Calibre! autoupdater v$VERSION"
    echo "Leon Gaultier 2013-2014. Das Programm darf verteilt werden,"
    echo -e "in der Hoffnung das es hilfreich ist, aber OHNR IRGENDEINE GARANTIE\n"
    return 0
}

func_progressbar()
{
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
    sleep 0.03
    done
    echo -e "\e[m"
    return 0
}

func_uninstall()
{
    func_term_output
    while ((!gueltig)); do    # beginn der Ja/Nein Abfrage
	echo -e "\033[1;34m"
	read -sn1 -t 30 -p "Möchtest Du den Calibre-Autoupdater wirklich DeInstallieren?  [j/n] " answer
	echo -e "\e[m"
	case "$answer" in
	    [JjYy])    result=1; gueltig=1 ;;
	    [Nn])      result=0; gueltig=1 ;;
	    "")        result=0; gueltig=1 ;;
	    *)         gueltig=0 ;;
	esac
    done
    if (( ! result )); then
	echo -e "\033[1;31mDie DeInstallation des Calibre-Autoupdaters wurde durch Dich abgebrochen.\e[m\n"
	break
    fi
    echo -e "\033[1;31mDer Calibre-Autoupdater wird nun deinstalliert.\e[m"
    if [ -w "$CALIBRE_INSTALL_LOCATION" ]; then
	rm -rf $INC"calibre-autoupdate.h" $INC"calibre-autoupdate_checks.h"; >&2
	rm -rf $ETC"calibre-autoupdate.conf"; >&2
	rm -rf $BIN"calibre-autoupdate"; >&2
    else	     	     
	sudo rm -rf $INC"calibre-autoupdate.h" $INC"calibre-autoupdate_checks.h"; >&2
	sudo rm -rf $ETC"calibre-autoupdate.conf"; >&2
	sudo rm -rf $BIN"calibre-autoupdate"; >&2
    fi   
    func_progressbar
    echo -e "\n\033[1;32mDer Calibre-Autoupdater wurde deinstalliert. Schade das Du ihn nicht weiter verwendest\n\e[m"
    return 0
}

func_uninstall_calibre()
{
    func_term_output
    if [ ! -d $CALIBRE_INSTALL_LOCATION/calibre ] ; then
	echo -e "\033[1;31mEs konnte keine Calibre Installation gefunden werden. Die DeInstallation wurde abgebrochen\e[m\n"
	break
    fi
    while ((!gueltig)); do    # beginn der Ja/Nein Abfrage
	echo -e "\033[1;34mMöchtest Du Calibre wirklich DeInstallieren? Calibre kann dann nicht mehr verwendet werden!"
	read -sn1 -t 30 -p "Deine Bücher und die Calibre Bibliothek bleiben erhalten.  [j/n] " answer
	echo -e "\e[m"
	case "$answer" in
	    [JjYy])    result=1; gueltig=1 ;;
	    [Nn])      result=0; gueltig=1 ;;
	    "")        result=0; gueltig=1 ;;
	    *)         gueltig=0 ;;
	esac
    done
    if (( ! result )); then
	echo -e "\n\033[1;31mDie DeInstallation von Calibre wurde durch Dich abgebrochen.\e[m\n"
	break  
    fi
    echo -e "\033[1;34mCalibre wird nun deinstalliert.\e[m"    
    if [ -w "$CALIBRE_INSTALL_LOCATION" ]; then
	calibre-uninstall
    else	     	     
	sudo calibre-uninstall
    fi
    echo -e "\n\033[1;32mCalibre würde DeInstalliert! Schade es ist ein tolles Programm zur eBookverwaltung :-)\n\e[m"
    return 0
}

func_install_calibre()
{
# Installationsort von Calibre
    read -p "Wo befindet sich die Calibre Installation? [default /opt] " CALIBRE_INSTALL_LOCATION
    if [ -z $CALIBRE_INSTALL_LOCATION ]; then
	CALIBRE_INSTALL_LOCATION=/opt
    fi
    while [ ! -d $CALIBRE_INSTALL_LOCATION ]; do
	echo -e "\n\033[1;31mDas Verzeichnis $CALIBRE_INSTALL_LOCATION existiert nicht. Bitte gib ein existierendes Verzeichnis ein!\e[m"
	read -p "Wo befindet sich die Calibre Installation? [default /opt] " CALIBRE_INSTALL_LOCATION
    done
    if [ -w "$CALIBRE_INSTALL_LOCATION" ]; then
	echo -e "\033[1;32mCalibre wird nun installiert...\n\e[m"
	wget -nv -O- $DOWNLOAD_URL | python -c "import sys; main=lambda x:sys.stderr.write('Download failed\n'); exec(sys.stdin.read()); main('$CALIBRE_INSTALL_LOCATION')"
    else	     	     
	echo -e "\033[1;34mDu hast kein Schreibrecht auf $CALIBRE_INSTALL_LOCATION. Calibre wird mit SUDO installiert. Bitte gib hierzu Dein Userpasswort ein...\n\e[m"
	sudo -v && wget -nv -O- $DOWNLOAD_URL | sudo python -c "import sys; main=lambda x:sys.stderr.write('Download failed\n'); exec(sys.stdin.read()); main('$CALIBRE_INSTALL_LOCATION')"
    fi
    echo -e "\n\n\033[1;36mHerzlichen Glückwunsch. Calibre wurde unter $CALIBRE_INSTALL_LOCATION installiert"
    echo -e "und kann nun mit \"calibre\" verwendet werden.\n\033[0m"
    return 0
}