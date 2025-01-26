# Mitarbeiterdatenbank

Prüfungsprojekt im Modul Grundlagen der Programmierung.

Schreibt und liest eine Mitarbeiterdatenbank in/von einer Datei.

Für jede:n Mitarbeiter:in werden die folgenden Attribute gespeichert:

- Mitarbeiter ID
- Name
- Vorname
- PLZ
- Gehalt
- Jahre der Betriebszugehörigkeit

Mitarbeitende können hinzugefügt, bearbeitet und entfernt werden.

## Schönheiten in der Aufgabenstellung

Betriebszugehörigkeitsjahre sollen explizit gespeichert anstatt dynamisch basierend auf einem Anfangsdatum berechnet werden.

Es gibt die Anforderung, dass alle Dateien in einem Ordner liegen, ohne Unterordner.

Einige Methoden sollen auf der DB-Klasse implementiert werden anstatt auf der Mitarbeiter-Klasse. In der Aufgabenstellung ist auch keine Rede von einer Mitarbeiter-Klasse.

## Compile

g++ -Wall -o mitarbeiter main.cpp database.cpp employee.cpp
