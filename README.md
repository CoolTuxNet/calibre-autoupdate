### Willkommen beim Calibre-Autoupdater ###

Calibre ist ein Programm zum verwalten von eBooks. Es kann aber noch viel mehr. Informationen findest Du auf der [Calibre Webseite](http://www.calibre-ebook.com).
Der calibre-autoupdater schaut bei jedem Aufruf ob eine neue Calibre Version vorhanden ist und aktuallisiert sie bei bedarf. Er macht aber noch mehr. Du kannst damit auch Calibre deinstallieren.
Das Installationsscript vom Autoupdater kann Calibre bei bedarf installieren.Die Installation von Calibre sowie des Updaters erfolgt in einem von angegebenen Ort.
Du kannst den Updater dann mittels cron oder beim Autostart deiner Desktopumgebung automatisch jeden Tag starten lassen.

# Zusätzlich benötigte Programme #
  1. url, wget
  1. otify-send (nicht unbedingt nötig, aber schone Sache :-) )
  1. rep and sed (sind Linux Bordmittel und sollten dabei sein)

# Optionen für calibre-autoupdate #

  * h, --help                   **zeigt die Hilfe an**
  * v, --version                **gibt die Programmversion aus**
  * c, --check                  **kontrolliert ob benötigte Programme vorhanden sind**
  * u, --uninstall              **deinstalliert den Calibre-Autoupdater**
  * --install-calibre   **installiert Calibre in der aktuellsten Version**
  * --uninstall-calibre      **deinstalliert das Calibre Programm**

# Optionen für calibre-autoupdate Installer (CAU\_Installer) #
  * h, --help              **zeigt die Hilfe an**
  * V, --version           **gibt die Programmversion aus**
  * i, --install           **installiert den Calibre-Autoupdater (CAU)**
