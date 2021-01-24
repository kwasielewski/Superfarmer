#include <iostream>
#include <gtkmm.h>
using namespace std;

/*
To jest program do zarządzania interfejsem użytkownika do gry Superfarmer.
Znajdą się tu opisy nastêpujących okien:
 > główne okno (informacje o stanie plansz wszystkich graczy):
    - tabela GTK_GRID?
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
    - informacja o końcu gry (i kto wygrał rozgrywkę)
*/

struct element_tabeli
{
    const char *opis;
    int pozycja_kolumna, pozycja_wiersz;
};
element_tabeli tabela_wewnatrz[10][10];
GtkWidget *tabela;

void Dokonaj_Wymiany();
void Wymiana_Zatwierdzona(int *wybor);
void Blad_Wymiana_Niemozliwa();
void Rzut_Kostka();
void Koniec_Gry();

GtkWidget *okno_wymiana;

void Dokonaj_Wymiany()
{
    okno_wymiana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(okno_wymiana), "Wymiana");
    gtk_window_set_position(GTK_WINDOW(okno_wymiana), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(okno_wymiana), 30);
    g_signal_connect(G_OBJECT(okno_wymiana), "destroy", G_CALLBACK(gtk_widget_destroy), okno_wymiana);

    GtkWidget *menu;
    menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width (GTK_CONTAINER (menu), 30);

    int wybor_gracza[10];

    GtkWidget *kupno_czy_sprzedaz = gtk_combo_box_text_new();
    const char *k_czy_p[] = {"Kupuję", "Sprzedaję"};
    for (int i = 0; i < 2; i++) gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(kupno_czy_sprzedaz), k_czy_p[i]);
    gtk_combo_box_set_active(GTK_COMBO_BOX(kupno_czy_sprzedaz), 0);
    gtk_container_add(GTK_CONTAINER(menu), kupno_czy_sprzedaz);
    wybor_gracza[0] = gtk_combo_box_get_active(GTK_COMBO_BOX(kupno_czy_sprzedaz));

    GtkWidget *wymiana_tekst = gtk_label_new("Jakie zwierzę chcesz kupić/sprzedać?");
    gtk_container_add(GTK_CONTAINER(menu), wymiana_tekst);

    GtkWidget *wybierz_zwierze = gtk_combo_box_text_new();
    const char *zwierzeta[] = {"Wybierz zwierzę", "królik", "owca", "świnia", "krowa", "koń", "mały pies", "duży pies"};
    for (int i = 0; i < 8; i++) gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(wybierz_zwierze), zwierzeta[i]);
    gtk_combo_box_set_active(GTK_COMBO_BOX(wybierz_zwierze), 0);
    gtk_container_add(GTK_CONTAINER(menu), wybierz_zwierze);
    wybor_gracza[1] = gtk_combo_box_get_active(GTK_COMBO_BOX(wybierz_zwierze));

    GtkWidget *ile_zwierzat = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_set_border_width (GTK_CONTAINER (ile_zwierzat), 30);
    gtk_container_add(GTK_CONTAINER(menu), ile_zwierzat);

    const char *liczby[] = {"0", "1", "2", "3", "4", "5", "6"};

    GtkWidget *ile_krolikow = gtk_combo_box_text_new();
    for (int i = 0; i < 7; i++) gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ile_krolikow), liczby[i]);
    gtk_combo_box_set_active(GTK_COMBO_BOX(ile_krolikow), 0);
    gtk_container_add(GTK_CONTAINER(ile_zwierzat), ile_krolikow);
    wybor_gracza[2] = gtk_combo_box_get_active(GTK_COMBO_BOX(ile_krolikow));

    GtkWidget *ile_owiec = gtk_combo_box_text_new();
    for (int i = 0; i < 7; i++) gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ile_owiec), liczby[i]);
    gtk_combo_box_set_active(GTK_COMBO_BOX(ile_owiec), 0);
    gtk_container_add(GTK_CONTAINER(ile_zwierzat), ile_owiec);
    wybor_gracza[3] = gtk_combo_box_get_active(GTK_COMBO_BOX(ile_owiec));

    GtkWidget *ile_swin = gtk_combo_box_text_new();
    for (int i = 0; i < 7; i++) gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ile_swin), liczby[i]);
    gtk_combo_box_set_active(GTK_COMBO_BOX(ile_swin), 0);
    gtk_container_add(GTK_CONTAINER(ile_zwierzat), ile_swin);
    wybor_gracza[4] = gtk_combo_box_get_active(GTK_COMBO_BOX(ile_swin));

    GtkWidget *ile_krow = gtk_combo_box_text_new();
    for (int i = 0; i < 7; i++) gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ile_krow), liczby[i]);
    gtk_combo_box_set_active(GTK_COMBO_BOX(ile_krow), 0);
    gtk_container_add(GTK_CONTAINER(ile_zwierzat), ile_krow);
    wybor_gracza[5] = gtk_combo_box_get_active(GTK_COMBO_BOX(ile_krow));

    GtkWidget *ile_koni = gtk_combo_box_text_new();
    for (int i = 0; i < 7; i++) gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ile_koni), liczby[i]);
    gtk_combo_box_set_active(GTK_COMBO_BOX(ile_koni), 0);
    gtk_container_add(GTK_CONTAINER(ile_zwierzat), ile_koni);
    wybor_gracza[6] = gtk_combo_box_get_active(GTK_COMBO_BOX(ile_koni));

    GtkWidget *ile_malych_psow = gtk_combo_box_text_new();
    for (int i = 0; i < 7; i++) gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ile_malych_psow), liczby[i]);
    gtk_combo_box_set_active(GTK_COMBO_BOX(ile_malych_psow), 0);
    gtk_container_add(GTK_CONTAINER(ile_zwierzat), ile_malych_psow);
    wybor_gracza[7] = gtk_combo_box_get_active(GTK_COMBO_BOX(ile_malych_psow));

    GtkWidget *ile_duzych_psow = gtk_combo_box_text_new();
    for (int i = 0; i < 7; i++) gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ile_duzych_psow), liczby[i]);
    gtk_combo_box_set_active(GTK_COMBO_BOX(ile_duzych_psow), 0);
    gtk_container_add(GTK_CONTAINER(ile_zwierzat), ile_duzych_psow);
    wybor_gracza[8] = gtk_combo_box_get_active(GTK_COMBO_BOX(ile_duzych_psow));

    GtkWidget *przycisk_zatwierdz = gtk_button_new_with_label("Zatwierdź");
    gtk_container_add(GTK_CONTAINER(menu), przycisk_zatwierdz);
    g_signal_connect (G_OBJECT(przycisk_zatwierdz), "clicked", G_CALLBACK(Wymiana_Zatwierdzona), wybor_gracza); //wywołać z argumentem - wybrana opcja

    GtkWidget *przycisk_anuluj = gtk_button_new_with_label("Anuluj");
    gtk_container_add(GTK_CONTAINER(menu), przycisk_anuluj);
    g_signal_connect_swapped(G_OBJECT(przycisk_anuluj), "clicked", G_CALLBACK(gtk_widget_destroy), okno_wymiana);

    gtk_container_add(GTK_CONTAINER(okno_wymiana), menu);
    gtk_widget_show_all(okno_wymiana);
}

void Wymiana_Zatwierdzona(int *wybor) //wybrane zwierzę jako argument
{
    ///połączyć z hostem gry
    ///musi potem nastąpić update tabeli w glowny_wewnatrz

    ///wybor[0] = 0 jeśli sprzedaż
    ///           1 jeśli kupno

    ///wybor[1] = jaki zwierzak

    ///wybor[2...8] = ile każdego z nich

    bool czy_wymiana_mozliwa = true; //testowe wywołanie (do zmiany później) = czyWymianaPoprawna()

    if (czy_wymiana_mozliwa)
    {
        ///tutaj update
        ///ta funkcja powinna automatycznie zamknąć okno "Wymiana"

        for (int i = 1; i < 8; i++)
        {
            for (int j = 1; j < 5; j++)
            {
                GtkLabel *modyfikowany_opis = (GtkLabel*)gtk_grid_get_child_at(GTK_GRID(tabela), i, j);
                gtk_label_set_text(modyfikowany_opis, tabela_wewnatrz[i][j].opis);
            }
        }

        gtk_widget_destroy(okno_wymiana);

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

    for (int i = 1; i < 8; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            GtkLabel *modyfikowany_opis = (GtkLabel*)gtk_grid_get_child_at(GTK_GRID(tabela), i, j);
            gtk_label_set_text(modyfikowany_opis, tabela_wewnatrz[i][j].opis);
        }
    }
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
    else gtk_label_set_text(GTK_LABEL(info_o_wyniku), "Przegrałeś");
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

    tabela = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(tabela), 3);
    gtk_grid_set_row_homogeneous(GTK_GRID(tabela), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(tabela), 3);
    gtk_grid_set_column_homogeneous(GTK_GRID(tabela), TRUE);

    tabela_wewnatrz[1][0].opis = "króliki";
    tabela_wewnatrz[2][0].opis = "owce";
    tabela_wewnatrz[3][0].opis = "świnie";
    tabela_wewnatrz[4][0].opis = "krowy";
    tabela_wewnatrz[5][0].opis = "konie";
    tabela_wewnatrz[6][0].opis = "małe psy";
    tabela_wewnatrz[7][0].opis = "duże psy";

    for (int i = 1; i < 8; i++)
    {
        tabela_wewnatrz[i][0].pozycja_kolumna = i;
        tabela_wewnatrz[i][0].pozycja_wiersz = 0;
        GtkWidget *komorka = gtk_label_new(NULL);
        gtk_label_set_text(GTK_LABEL(komorka), tabela_wewnatrz[i][0].opis);
        gtk_grid_attach(GTK_GRID(tabela), komorka, tabela_wewnatrz[i][0].pozycja_kolumna, tabela_wewnatrz[i][0].pozycja_wiersz, 1, 1);
    }

    tabela_wewnatrz[0][1].opis = "Gracz 1";
    tabela_wewnatrz[0][2].opis = "Gracz 2";
    tabela_wewnatrz[0][3].opis = "Gracz 3";
    tabela_wewnatrz[0][4].opis = "Gracz 4";

    for (int i = 1; i < 5; i++)
    {
        tabela_wewnatrz[0][i].pozycja_kolumna = 0;
        tabela_wewnatrz[0][i].pozycja_wiersz = i;
        GtkWidget *komorka = gtk_label_new(NULL);
        gtk_label_set_text(GTK_LABEL(komorka), tabela_wewnatrz[0][i].opis);
        gtk_grid_attach(GTK_GRID(tabela), komorka, tabela_wewnatrz[0][i].pozycja_kolumna, tabela_wewnatrz[0][i].pozycja_wiersz, 1, 1);
    }

    for (int i = 1; i < 8; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            tabela_wewnatrz[i][j].opis = "0";
            tabela_wewnatrz[i][j].pozycja_kolumna = i;
            tabela_wewnatrz[i][j].pozycja_wiersz = j;
            GtkWidget *komorka = gtk_label_new(NULL);
            gtk_label_set_text(GTK_LABEL(komorka), tabela_wewnatrz[i][j].opis);
            gtk_grid_attach(GTK_GRID(tabela), komorka, tabela_wewnatrz[i][j].pozycja_kolumna, tabela_wewnatrz[i][j].pozycja_wiersz, 1, 1);
        }
    }

    gtk_container_add(GTK_CONTAINER(glowny_wewnatrz), tabela);

    GtkWidget *przycisk_wymiana = gtk_button_new_with_label("Chcę dokonać wymiany");
    gtk_container_add(GTK_CONTAINER(glowny_wewnatrz), przycisk_wymiana);
    g_signal_connect (G_OBJECT(przycisk_wymiana), "clicked", G_CALLBACK(Dokonaj_Wymiany), tabela_wewnatrz);

    GtkWidget *przycisk_rzut = gtk_button_new_with_label("Rzut kostką");
    gtk_container_add(GTK_CONTAINER(glowny_wewnatrz), przycisk_rzut);
    g_signal_connect (G_OBJECT(przycisk_rzut), "clicked", G_CALLBACK(Rzut_Kostka), NULL); //tablica jako argument
    gtk_container_add(GTK_CONTAINER(glowny), glowny_wewnatrz);

    gtk_widget_show_all(glowny);
    gtk_main();
}
