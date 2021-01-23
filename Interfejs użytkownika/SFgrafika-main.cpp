#include <iostream>
#include <gtkmm.h>
using namespace std;

/*
To jest program do zarządzania interfejsem użytkownika do gry Superfarmer.
Znajdą się tu opisy nastêpujących okien:
 > główne okno (informacje o stanie plansz wszystkich graczy):
    - tabela GTK_GRID?
    - obrazki reprezentujące różne zwierzęta i innych graczy
    - przycisk, który umożliwia wymianę
    - przycisk do "rzutu kostką"
    - miejsce, gdzie wyświetli się wynik tego rzutu
 > okno pozwalające na wymianę z bankiem (stadem głównym)
    - wybór kupno czy sprzedaż (może zaznaczanie ptaszkiem kwadracika?)
    - drop-down menu, które pozwala graczowi wybrać, jakie zwierzę chce nabyć GTK_COMBO_BOX?
    - możliwość wyboru jakie dokładnie zwierzaki gracz chce wymienić
    - przycisk do zatwierdzenia wyboru
    - przycisk do anulowania wymiany
 > ewentualny pop-up z nformacją o błędzie (czy da się ustawić czerwone tło?)
    - gracz ma niewystaczającą liczbę zwierząt na wymianę
    - gracz podał informacje, które nie pokrywają się z kursami wymiany
    - informacja o końcu gry (i kto wygrał rozgrywkę)
*/

void Dokonaj_Wymiany();
void Wymiana_Zatwierdzona();
void Blad_Wymiana_Niemozliwa();
void Rzut_Kostka();
void Koniec_Gry();

void Dokonaj_Wymiany()
{
    GtkWidget *okno_wymiana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(okno_wymiana), "Wymiana");
    gtk_window_set_position(GTK_WINDOW(okno_wymiana), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(okno_wymiana), 30);
    g_signal_connect(G_OBJECT(okno_wymiana), "destroy", G_CALLBACK(gtk_widget_destroy), okno_wymiana);

    GtkWidget *menu;
    menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width (GTK_CONTAINER (menu), 30);

    GtkWidget *wymiana_tekst = gtk_label_new("Jakie zwierzę chcesz nabyć?");
    gtk_container_add(GTK_CONTAINER(menu), wymiana_tekst);

    GtkWidget *wybierz_zwierze = gtk_combo_box_text_new();
    const char *zwierzeta[] = {"Wybierz zwierzę", "królik", "owca", "świnia", "krowa", "koń", "mały pies", "duży pies"};
    for (int i = 0; i < 8; i++) gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(wybierz_zwierze), zwierzeta[i]);
    gtk_combo_box_set_active(GTK_COMBO_BOX(wybierz_zwierze), 0);
    gtk_container_add(GTK_CONTAINER(menu), wybierz_zwierze);
    ///jak uzyskać informację o tym, co wybrał użytkownik? gtk_combo_box_get_active?

    GtkWidget *przycisk_zatwierdz = gtk_button_new_with_label("Zatwierdź");
    gtk_container_add(GTK_CONTAINER(menu), przycisk_zatwierdz);
    g_signal_connect (G_OBJECT(przycisk_zatwierdz), "clicked", G_CALLBACK(Wymiana_Zatwierdzona), NULL); //wywołać z argumentem - wybrana opcja

    GtkWidget *przycisk_anuluj = gtk_button_new_with_label("Anuluj");
    gtk_container_add(GTK_CONTAINER(menu), przycisk_anuluj);
    g_signal_connect_swapped(G_OBJECT(przycisk_anuluj), "clicked", G_CALLBACK(gtk_widget_destroy), okno_wymiana);

    gtk_container_add(GTK_CONTAINER(okno_wymiana), menu);
    gtk_widget_show_all(okno_wymiana);
}

void Wymiana_Zatwierdzona() //wybrane zwierzę jako argument
{
    ///połączyć z hostem gry
    ///musi potem nastąpić update tabeli w glowny_wewnatrz

    bool czy_wymiana_mozliwa = false; //testowe wywołanie (do zmiany później)

    if (czy_wymiana_mozliwa)
    {
        ///tutaj update
        ///ta funkcja powinna automatycznie zamknąć okno "Wymiana"
    }
    else Blad_Wymiana_Niemozliwa();
}

void Blad_Wymiana_Niemozliwa()
{
    GtkWidget *okno_wymiana_niemozliwa = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(okno_wymiana_niemozliwa), "Ups!");
    gtk_window_set_position(GTK_WINDOW(okno_wymiana_niemozliwa), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(okno_wymiana_niemozliwa), 30);
    g_signal_connect(G_OBJECT(okno_wymiana_niemozliwa), "destroy", G_CALLBACK(gtk_widget_destroy), okno_wymiana_niemozliwa);

    GtkWidget *own_wewnatrz = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width (GTK_CONTAINER (own_wewnatrz), 30);
    gtk_container_add(GTK_CONTAINER(okno_wymiana_niemozliwa), own_wewnatrz);

    GtkWidget *own_tekst = gtk_label_new("Nie masz wystarczających środków na taką wymianę");
    gtk_container_add(GTK_CONTAINER(own_wewnatrz), own_tekst);

    GtkWidget *przycisk_rozumiem = gtk_button_new_with_label("Rozumiem");
    gtk_container_add(GTK_CONTAINER(own_wewnatrz), przycisk_rozumiem);
    g_signal_connect_swapped(G_OBJECT(przycisk_rozumiem), "clicked", G_CALLBACK(gtk_widget_destroy), okno_wymiana_niemozliwa);

    gtk_widget_show_all(okno_wymiana_niemozliwa);
}

void Rzut_Kostka() //wskaźnik na tabelę/okno główne jako argument?
{
    ///połączyć z hostem gry i generatorem liczb losowych
    ///wyświetlić komunikat o wyniku losowania w oknie głównym
    ///musi potem nastąpić update tabeli w glowny_wewnatrz
    ///stąd powinna też przyjść informacja o ewentualnym końcu rozgrywki (wywołanie void Koniec_Gry())
}

void Koniec_Gry()
{
    ///połączyć z hostem gry - wygrana czy przegrana?

    bool czy_wygrales = false; //tylko testowa wartość, tutaj wywołać trzeba funkcję z hosta

    GtkWidget *okno_koniec_gry = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(okno_koniec_gry), "Koniec gry");
    gtk_window_set_position(GTK_WINDOW(okno_koniec_gry), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(okno_koniec_gry), 30);
    g_signal_connect(G_OBJECT(okno_koniec_gry), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *okg_wewnatrz = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width (GTK_CONTAINER (okg_wewnatrz), 30);
    gtk_container_add(GTK_CONTAINER(okno_koniec_gry), okg_wewnatrz);

    GtkWidget *info_o_wyniku = gtk_label_new(NULL);
    if (czy_wygrales) gtk_label_set_text(GTK_LABEL(info_o_wyniku), "Wygrałeś! Gratulacje!");
    else gtk_label_set_text(GTK_LABEL(info_o_wyniku), "Przegrałeś, Synu!");
    gtk_container_add(GTK_CONTAINER(okg_wewnatrz), info_o_wyniku);

    GtkWidget *przycisk_ok = gtk_button_new_with_label("OK");
    gtk_container_add(GTK_CONTAINER(okg_wewnatrz), przycisk_ok);
    g_signal_connect_swapped(G_OBJECT(przycisk_ok), "clicked", G_CALLBACK(gtk_widget_destroy), okno_koniec_gry);

    gtk_widget_show_all(okno_koniec_gry);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    GtkWidget *glowny = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(glowny), "Superfarmer");
    gtk_window_set_position(GTK_WINDOW(glowny), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(glowny), 30);
    g_signal_connect(G_OBJECT(glowny), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *glowny_wewnatrz;
    glowny_wewnatrz = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    GtkWidget *tabela = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(tabela), 3);
    gtk_grid_set_row_homogeneous(GTK_GRID(tabela), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(tabela), 3);
    gtk_grid_set_column_homogeneous(GTK_GRID(tabela), TRUE);

    struct element_tabeli
    {
        const char *opis;
        int pozycja_kolumna, pozycja_wiersz;
    };

    element_tabeli tabela_wewnatrz[] = {
    {"", 0, 1},              {"króliki", 1, 1}, {"owce", 2, 1}, {"świnie", 3, 1}, {"krowy", 4, 1}, {"konie", 5, 1}, {"maly pies", 6, 1}, {"duzy pies", 7, 1},
    {"bot królikowy", 0, 2}, {"0", 1, 2},       {"0", 2, 2},    {"0", 3, 2},      {"0", 4, 2},     {"0", 5, 2},     {"0", 6, 2},         {"0", 7, 2}
    //itd.
    };
    ///póki co są tu same zera jako tekst, ale w ich miejsce powinny pojawic się informacje o innych graczach od hosta (typ danych int lub inny - do ustalenia)
    ///tablica powinna być dwuwymiarowa?

    for (int i = 0; i < 16; i++) //wersja testowa wczytywania
    {
        GtkWidget *komorka = gtk_label_new(NULL);
        gtk_label_set_text(GTK_LABEL(komorka), tabela_wewnatrz[i].opis);
        gtk_grid_attach(GTK_GRID(tabela), komorka, tabela_wewnatrz[i].pozycja_kolumna, tabela_wewnatrz[i].pozycja_wiersz, 1, 1);
    }

    ///trzeba jeszcze zmodyfikować obecny układ kontrolek w oknie głównym, aby odzwierciedlał rysunki (grafika-plan.pdf)
    gtk_container_add(GTK_CONTAINER(glowny_wewnatrz), tabela);

    GtkWidget *przycisk_wymiana = gtk_button_new_with_label("Chcę dokonać wymiany");
    gtk_container_add(GTK_CONTAINER(glowny_wewnatrz), przycisk_wymiana);
    g_signal_connect (G_OBJECT(przycisk_wymiana), "clicked", G_CALLBACK(Dokonaj_Wymiany), NULL);

    GtkWidget *przycisk_rzut = gtk_button_new_with_label("Rzut kostką");
    gtk_container_add(GTK_CONTAINER(glowny_wewnatrz), przycisk_rzut);
    //g_signal_connect (G_OBJECT(przycisk_rzut), "clicked", G_CALLBACK(Rzut_Kostka), NULL); //tablica jako argument
    gtk_container_add(GTK_CONTAINER(glowny), glowny_wewnatrz);

    gtk_widget_show_all(glowny);
    gtk_main();
}
