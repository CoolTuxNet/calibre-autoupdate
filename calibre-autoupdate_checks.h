#  Calibre Auto Updater Header File
#    Copyright (C) 2013-2014  Leon Gaultier
#

func_check_stat () {          # Funktion zum Check Verfügbarkeit der Downloadseiten und der Internetverbindung
# Test for network conection
echo -e "\033[1;34m Ich schau dann mal ob Dein Computer überhaupt ein Netzwerk hat :-)";
for INTERFACE in $(ls /sys/class/net/ | grep -v lo);
do
  if [[ $(cat /sys/class/net/$INTERFACE/carrier) = 1 ]]; then 
   ONLINE=1
  fi
done

if [ $ONLINE ]; then
      echo -e "\033[32m Oh Wunder! Habe ein Netzwerk gefunden. Verbinde über Interface $INTERFACE,
 was nicht heißt das es geht :-P";
      if [[ $stat_1 -eq 200 && $stat_2 -eq 200 ]]; then
	  return 1
      elif [[ $stat_1 -eq !200 ]]; then
	  return 2
      else
	  return 3
      fi
else
    echo -e "\033[31m Fehler!!! Bitte schau Dir die Desktop Benachrichtigung an!";
    return 4
fi
}

func_check_run_calibre () {
  CALIBRE_PID=`ps ax | grep /opt/calibre/bin/calibre | grep -v grep | awk '{printf $1}'`

  while [ $CALIBRE_PID ]; 
  do
    $NOTIFY "Um das Update installieren zu können, muss Calibre beendet werden. Calibre wird in einer Minute vom Update Service beendet. !!!Bitte speichere alle wichtigen Daten!!!"
    sleep 3
    for (( i=60; i>0; i-- ));
    do
      echo -e "\033[31m noch \033[32m>>$i<< \033[31m Sekunden bis zum Calibre Programmende"
      sleep 1
      clear
      funct_term_output
    done
    kill -15 $CALIBRE_PID
    return 0
  done
  return 0
}

func_check_version () {
  #Ermitteln der letzten aktuell verfügbaren Version
  LATEST_VERSION=`curl -s $CALIBRE_DOWNLOAD_PAGE | grep 'latest release of calibre' | sed 's/[^0-9.]*\([1-9]*[0-9]\.[1-9]*[0-9]\).*/\1/'`
  #Ermitteln der aktuell installierten Version.
  CURRENT_VERSION=`calibre --version | sed 's/[^0-9.]*\([0-9.]*\).*/\1/'`
  return 0
}


func_check_prog () {
  func_term_output  
  if test ! -f $CURL ; then
    echo -e "\033[31mDu hast Curl nich installiert, es wird aber für die Updatefunktion benötigt\n"; >&2
    exit 1
  fi
  
  if test ! -f $AWK ; then
    echo -e "\033[31mDu hast AWK nich installiert, es wird aber für die Updatefunktion benötigt\n"; >&2
    exit 1
  
  if test ! -f $NOTIFY ; then
    echo -e "\e[0;33mDu hast Notify-Send nich installiert, das Programm ist optional und wird"; >&2
    echo -e "für die Upatefunktion nicht unbedingt benötigt. Ist aber ne Coole Sache ;-)\n"; >&2
    sleep 10
  fi
  
  fi  
    echo -e "\033[32mAlle benötigten Programme sind installiert. Starte $PROGNAME ohne Optionen und"
    echo -e "es wird nach einer aktuellen Calibre Version geschaut\n";
}