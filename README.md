# Superfarmer

Superfarmer jest grą planszową, wymyśloną przez prof. Karola Borsuka w 1943 roku. Ten projekt umożliwia rozgrywkę w tą właśnie grę jednego gracza z trzema botami.

## Jak uruchomić

Żeby uruchomić grę należy wykonać w folderze Gierka polecenia
'''
make host
./host
'''

### Wymagane biblioteki

Sama gra nie wymaga dodatkowych bibliotek, lecz w przygotowaniu znajdował się również interfejs graficzny. By go zobaczyć należy pobrać odpowiedinią bibliotekę poleceniem

```
apt-get install libgtkmm-3.0-dev
```
A następnie w folderze Interfejs graficzny wykonać
'''
make SFgrafika-main
./SFgrafika-main
'''

Niestety nie udało nam się zintegrować zasadniczego programu z UI


## Jak grać

Zasady gry znajdują się w osobnym pliku

## Jak przeprowadzać testy

Żeby przeprowadzić testy efektywności poszczególnych botów, można uruchomić program w specjalnym trybie gier czterech botów. Dane z takich rozgrywek zostaną zapisane.
By to zrobić, należy wykonać w folderze Gierka
'''
make samo
bash ./produkujDane
'''

## Jak stworzyć wykresy

Przygotowany skrypt w pythonie umożliwia stworzenie wykresów, przedstawiających przydatne informacje o wydajności botów (np. średnia liczba tur potrzebnych na wygraną).
W tytułach wykresów numery botów oznaczają ich typy:
* 1-Królikowy
* 2-Randomizowany
* 3-High Roller
* 4-Świński
### Uruchomienie skryptu

Do działania wymagane są biblioteki numpy, matplotlib oraz pandas.


```
python3 ./Analiza/skrypt.py
```

:warning: Domyślna liczba testowanych gier to 10. Żeby wybrać inną liczbę należy zmienić warunek pętli w skrypcie produkujDane oraz wartość w kolumnie N w pliku config.csv








