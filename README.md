# Superfarmer

Superfarmer jest grą planszową, wymyśloną przez prof. Karola Borsuka w 1943 roku. Ten projekt umożliwia rozgrywkę w tą właśnie grę jednego gracza z trzema botami.

## Jak uruchomić



### Wymagane biblioteki
Przed uruchomieniem należy pobrać odpowiednią bibliotekę za pomocą komendy

```
apt-get install libgtkmm-3.0-dev
```

### Uruchomienie

```
make coś
```

## Jak grać

Zasady gry znajdują się w osobnym pliku

## Jak przeprowadzać testy

Żeby przeprowadzić testy efektywności poszczególnych botów, można uruchomić program w specjalnym trybie gier czterech botów. Dane z takich rozgrywek zostaną zapisane.

## Jak stworzyć wykresy

Przygotowany skrypt umożliwia stworzenie wykresów, przedstawiających przydatne informacje o wydajności botów (np. średnia liczba tur potrzebnych na wygraną)

### Uruchomienie skryptu

Do działania wymagane są biblioteki numpy, matplotlib oraz pandas.
Do pliku config.csv wpisać liczbę przeprowadzonych gier w kolumnie N

```
python3 ./Analiza/skrypt.py
```
### Co przedstawiają wykresy

* typ1  
![image](./test.png)
* typ2  
![image](./test.png)




