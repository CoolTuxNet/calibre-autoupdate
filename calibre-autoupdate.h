#  Calibre Auto Updater Header File
#    Copyright (C) 2013-2014  Leon Gaultier
#

func_usage ()
{
    echo "Verwendung: $PROGNAME [OPTION...]"
    echo "Verwende '$PROGNAME --help' oder '$PROGNAME -h' für mehr Informationen."
}

func_help ()
{
    func_term_output
    echo "Verwende: $PROGNAME [OPTION...]"
    echo "$PROGNAME -- Der Calibre! Linux Edition calibre-autoupdater (CAU)"
    echo ""
    echo "Options:"
    echo "   -q, --quiet                  ohne Konsolenausgabe"
    echo "   -h, --help                   zeigt die Hilfe an"
    echo "   -V, --version                gibt die Programmversion aus"
    echo "   -c, --check                  kontrolliert ob benötigte Programme vorhanden sind"
    echo "   -u, --uninstall              deinstalliert den Calibre-Autoupdater"
    echo "       --uninstall_calibre      deinstalliert das Calibre Programm"
    echo ""
    echo -e "Sende Fehler an <leongaultier@gmail.com>.\n";
}

func_version ()
{
    func_term_output
    echo "$PROGNAME: Der Calibre! autoupdater v$VERSION"
    echo "Leon Gaultier 2013-2014. Das Programm darf verteilt werden,"
    echo "in der Hoffnung das es hilfreich ist, aber OHNR IRGENDEINE GARANTIE"

}

func_vercomp () {            # Funktion zum Versionsvergleich
    if [[ $1 == $2 ]]
    then
        return 0
    fi
    local IFS=.
    local i ver1=($1) ver2=($2)
    # fill empty fields in ver1 with zeros
    for ((i=${#ver1[@]}; i<${#ver2[@]}; i++))
    do
        ver1[i]=0
    done
    for ((i=0; i<${#ver1[@]}; i++))
    do
        if [[ -z ${ver2[i]} ]]
        then
            # fill empty fields in ver2 with zeros
            ver2[i]=0
        fi
        if ((10#${ver1[i]} > 10#${ver2[i]}))
        then
            return 1
        fi
        if ((10#${ver1[i]} < 10#${ver2[i]}))
        then
            return 2
        fi
    done
    return 0
}

func_term_output () {
  ## Beginne mit der Ausgbe ##
  tty -s && clear
  echo -e "\033[44m \033[0m\033[1m $PROGNAME Version $VERSION\033[0m\n\033[44m \033[0m 2013-2014 by Leon Gaultier\n\e[m";
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
  echo
    if (( ! result )); then
	echo -e "\033[1;31mDie DeInstallation des Calibre-Autoupdaters wurde durch Dich abgebrochen.\e[m\n"
	exit 1  
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
}
func_uninstall_calibre()
{
  func_term_output
  if test ! -d $CALIBRE_INSTALL_LOCATION/calibre ; then
    echo -e "\033[1;31mEs konnte keine Calibre Installation gefunden werden. Die DeInstallation wurde abgebrochen\e[m\n"
    exit 1
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
  echo
    if (( ! result )); then
	echo -e "\n\033[1;31mDie DeInstallation von Calibre wurde durch Dich abgebrochen.\e[m\n"
	exit 1  
    fi
    echo -e "\033[1;34mCalibre wird nun deinstalliert.\e[m"    
    if [ -w "$CALIBRE_INSTALL_LOCATION" ]; then
	calibre-uninstall
    else	     	     
	sudo calibre-uninstall
    fi
  echo -e "\n\n\033[1;32mCalibre würde DeInstalliert! Schade es ist ein tolles Programm zur eBookverwaltung :-)\e[m"
  return 0
}