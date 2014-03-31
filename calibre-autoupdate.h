#  Calibre Auto Updater Configfile
#    Copyright (C) 2013-2014  Leon Gaultier
#



func_usage ()
{
    echo "Usage: $PROGNAME [OPTION...]"
    echo "Try '$PROGNAME --help' or '$PROGNAME -h' for more information."
}

func_help ()
{
    func_term_output
    echo "Usage: $PROGNAME [OPTION...]"
    echo "$PROGNAME -- the Calibre! Linux Edition calibre-autoupdater"
    echo ""
    echo "Options:"
    echo "   -q, --quiet           ohne Konsolenausgabe"
    echo "   -h, --help            zeigt die Hilfe an"
    echo "   -V, --version         gibt die Programmversion aus"
    echo "   -c, --check           checkt ob benötigte Programme vorhanden sind"
    echo ""
    echo -e "Report bugs to <leongaultier@gmail.com>.\n";
}

func_version ()
{
    echo "$PROGNAME: the Calibre! autoupdater v$VERSION"
    echo "Copyright (C) Leon Gaultier 2013-2014. This program is distributed"
    echo "in the hope that it will be useful, but WITHOUT ANY WARRANTY"

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
