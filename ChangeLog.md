# Übersicht über die Versionshistorie #

### Versionsverlauf ###
**v0.1**
  * Body des Skriptes erstellt
  * Abfrage neuste Version vorhanden
  * Abfrage welche Version installiert
  * Funktion Versionsvergleich
  * Download und installation der neusten Version
  * Desktopmeldungen hinzugefügt

**v0.2**
  * Verbesserungen bei den Desktopmeldungen

**v0.3**
  * Funktion Check Verfügbarkeit der Downloadseiten hinzugefügt

**v0.4**
  * Check Verfügbarkeit auf Test Netzwerk vorhanden und Auswertung erweitert
  * diverse Kommentare hinzugefügt

**v0.5**
  * Funktion Check läuft noch eine Calibre Instanz mit Counter
  * Ausgabe Texte verbessert und erweitert
  * URL Statuscodes holen ins main verlagert.

**v0.6**
  * Verbesserungen in der Terminalausgabe, Startausgabe ist eine eigene Funktion
  * URL Status Code ist nun eine eigene Funktion

**v0.7**
  * Der Updateprozes wurde in eine Prozedure geschrieben und die main Prozedure gibt nur noch Hilfe und Verion aus oder startet sofort die Update Prozedur

**v0.8**
  * Optionsschalter hinzugefügt, Kontrolle ob benötigte Programme vorhanden sind.
  * Unterschiedliche Installationsart und -dialog je nach dem ob man Schreibrechte
  * auf im Calibre Installationspfad hat oder nicht.

**v0.9**
  * einbinden eines Konfigurationsfiles, auslagern einiger Funktionen in Headerfiles
  * einbringen der Dateien in die Linux Verzeichnishierarchie

**v0.10**
  * hinzufügen eines Installationsskriptes für den calibre-autoupdater, Installsript prüft vorhanden sein von calibre und des updaters und fragt nach Installationsort des Updaters

**v0.11**
  * Das Mainscript wurde angepasst so das der Installer die ermittelten Variablen für den Installationsort in das Mainscript und die Konfigdatei schreiben kann.
  * Es wurden diverse Ausgabentexte sprachlich verbessert und Fehler beseitigt.

**v0.13**
  * Es wurden diverse Fehler beim eigentlichen Updateprozess bereinigt.
  * Desweiteren wurden größere Prozesse in kleine aufgeteilt.

**v0.14**
  * Uninstallfunktion für Calibre hinzugefügt. Hiermit kann Calibre von der Festplatte deinstalliert werden.
  * Bei einer nicht vorhandenen Calibreinstallation wird vom Installsript des Updaters gefragt, ob Calibre installiert werden soll.
  * Die Funktion Installation des Updaters wurde aufgeteilt in root\_install und noroot\_install
  * Uninstall Funktion für den calibre-autoupdater mit gleichzeitiger nachfrage und eventueller deinstallation vom Calibre Programm
  * der Code wurde überarbeitet, die Dialoge verbessert, Ergebnisse von Funktionsaufrufen in Variablen geschrieben

**v0.20**
  * Der Code wurde komplett überarbeitet und vieles neu geschrieben. Sauberer Code und weniger Abfragen.
  * Die Bedingungen und Schleifen wurden einfacher und logischer geschrieben
  * Die Prüfung ob Calibre noch gestartet ist wenn ein Update gemacht wird ist nun simpler geschrieben, und es wird nicht mehr hart beendet sondern gewartet bis der Benutzer Calibre beendet
  * Die Calibre Installation ist vom Installer in das Updaterskript gewandert, und im Zuge einer Calibreinstallation wird automatisch die Konfigurationsdatei des Updaters angepasst (übergabe Calibre-Install-Ort)
  * Es wird wieder geprüft ob Calibre installiert ist bevor der Updater gestartet wird

**TODO**
  * Auslesen der Download URL von der Download Seite kontrolle ob alle benötigten programme für das skript vorhanden sind
