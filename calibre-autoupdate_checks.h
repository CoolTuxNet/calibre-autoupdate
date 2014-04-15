#  Calibre Auto Updater Configfile
#    Copyright (C) 2013-2014  Leon Gaultier
#

func_http_status_code () {
    echo -e "\033[1;34m Hole Status Code von $CHECK_CALIBRE_DOWNLOAD_PAGE. Bitte warten.\e[m"
    stat_1=$(curl -o /dev/null --silent --head --write-out '%{http_code}' $CHECK_CALIBRE_DOWNLOAD_PAGE)
    func_progressbar
    echo -e "\033[32m Status Codes von $CHECK_CALIBRE_DOWNLOAD_PAGE erhalten\e[m"
    echo -e "\n\033[1;34m Hole Status Code von $CHECK_DOWNLOAD_URL. Bitte warten.\e[m"
    stat_2=$(curl -o /dev/null --silent --head --write-out '%{http_code}' $CHECK_DOWNLOAD_URL)
    func_progressbar
    echo -e "\033[32m Status Codes von $CHECK_DOWNLOAD_URL erhalten\e[m"
    return 0
}

func_check_stat () { 	# Funktion zum Check Verfügbarkeit der Downloadseiten und der Internetverbindung
    # Test for network conection
    echo -e "\n\033[1;34m Suche nach vorhandenen Netzwerk für die Verbindung zum Internet :-)\e[m"
    for INTERFACE in $(ls /sys/class/net/ | grep -v lo); do
	if [[ $(cat /sys/class/net/$INTERFACE/carrier) = 1 ]]; then 
	    ONLINE=1
	fi
    done
    func_progressbar
    if [ $ONLINE ]; then
	echo -e "\033[32m Es wurde ein Netzwerkinterface gefunden. Verbinde über Interface $INTERFACE\n\e[m"
	func_http_status_code
	if [[ $stat_1 -eq 200 && $stat_2 -eq 200 ]]; then
	    return 1
	elif [[ $stat_1 -eq !200 ]]; then
	    return 2
	else
	    return 3
	fi
    else
	echo -e "\n\033[31m Fehler!!! Bitte schau Dir die Desktop Benachrichtigung an!\e[m"
	return 4
    fi
    return 0
}

func_check_run_calibre () {
    while [ `ps ax | grep /opt/calibre/bin/calibre | grep -v grep | awk '{printf $1}'` ]; do
	$NOTIFY "Um das Update installieren zu können, muss Calibre geschlossen werden..."
    done
    return 0
}

func_check_version_alternate() {	# Wurde von einem User im Mobilreaderforum vorgeschlagen. Ist mir aber zu
					# ehrlich gesagt zu unflexibel. Habe es für mich selber aber mal Dokumentiert
    calibre-debug -c "import urllib as u; from calibre.constants import numeric_version; raise SystemExit(int(numeric_version  < (tuple(map(int, u.urlopen('http://calibre-ebook.com/downloads/latest_version').read().split('.'))))))"

    UP_TO_DATE=$?
    if [ $UP_TO_DATE = 0 ]; then
	return 0
    else
	return 2
    fi
    echo -e "\n\033[31m Fehler!!! Es wurde beim Versionscheck ein unbekannter Wert zurückgegeben!\e[m"
    exit 0
}

func_check_version () {
    #Ermitteln der letzten aktuell verfügbaren Version
    LATEST_VERSION=`curl -s $CALIBRE_LAST_VERSION_PAGE`
    #Ermitteln der aktuell installierten Version.
    CURRENT_VERSION=`calibre --version | sed 's/[^0-9.]*\([0-9.]*\).*/\1/'`

    if [[ $CURRENT_VERSION == $LATEST_VERSION ]]; then
	return 0
    fi
    local IFS=.
    local i ver1=($CURRENT_VERSION) ver2=($LATEST_VERSION)
    # schreibe nullen in leere Felder von ver1
    for ((i=${#ver1[@]}; i<${#ver2[@]}; i++)); do
	ver1[i]=0
    done
    for ((i=0; i<${#ver1[@]}; i++)); do
	if [[ -z ${ver2[i]} ]]; then
	    # schreibe nullen in leere Felder von ver2
	    ver2[i]=0
	fi
	if ((10#${ver1[i]} > 10#${ver2[i]})); then
	    return 1
	fi
	if ((10#${ver1[i]} < 10#${ver2[i]})); then
	    return 2
	fi
    done
    return 0  
}

func_check_prog () {         # Schaut ob Calibre und benötigte Programme installiert sind
    func_term_output
    if [ ! -d $CALIBRE_INSTALL_LOCATION/calibre ]; then
	$NOTIFY "Check auf Calibre-Updates nicht möglich! Calibre ist gar nicht installiert. Bitte verwende calibre-autoupdate --install-calibre um Calibre zu installieren"
	exit 0
    fi
    if [ ! -f $CURL ]; then
	$NOTIFY "Du hast Curl nich installiert, es wird aber für die Updatefunktion benötigt"
	exit 0
    fi
    if [ ! -f $AWK ]; then
	$NOTIFY "Du hast AWK nich installiert, es wird aber für die Updatefunktion benötigt"
	exit 0
    fi
    if [ ! -f /usr/bin/notify-send ]; then
	echo -e "\e[0;33mDu hast Notify-Send nich installiert, das Programm ist optional und wird\e[m"
	echo -e "für die Upatefunktion nicht unbedingt benötigt\n\e[m"
	sleep 10
    fi
    echo -e "\033[32mAlle benötigten Programme sind installiert. Starte $PROGNAME ohne Optionen und"
    echo -e "es wird nach einer aktuellen Calibre Version gesucht\n\e[m";
    return 0
}