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
    echo "   -q, --quiet           ohne Konsolenausgabe"
    echo "   -h, --help            zeigt die Hilfe an"
    echo "   -V, --version         gibt die Programmversion aus"
    echo "   -c, --check           kontrolliert ob benötigte Programme vorhanden sind"
    echo ""
    echo -e "Sende Fehler an <leongaultier@gmail.com>.\n";
}

func_version ()
{
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
}