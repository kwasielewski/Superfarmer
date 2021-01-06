#include <iostream>
#include <string>
#include <gtkmm.h>
using namespace std;

/*
To jest program do zarz¹dzania interfejsem u¿ytkownika do gry Superfarmer.
Znajd¹ siê tu opisy nastêpuj¹cych okien:
 > g³ówne okno (informacje o stanie plansz wszystkich graczy):
    - tabela GTK_GRID?
    - obrazki reprezentuj¹ce ró¿ne zwierzêta i innych graczy
    - przycisk, który umo¿liwia wymianê
    - przycisk do "rzutu kostk¹"
    - miejsce, gdzie wyœwietli siê wynik tego rzutu
 > okno pozwalaj¹ce na wymianê z bankiem (stadem g³ównym)
    - drop-down menu, które pozwala graczowi wybraæ, jakie zwierzê chce nabyæ GTK_COMBO_BOX?
    - przycisk do zatwierdzenia wyboru
 > ewentualny pop-up z informacj¹ o b³êdzie
    - jeœli gracz zechce dokonaæ wymiany po rzucie kostk¹ (niezgodne z zasadami)
    - gracz ma niewystaczaj¹c¹ liczbê zwierz¹t na wymianê
    - informacja o koñcu gry (i kto wygra³ rozgrywkê)
*/

void Dokonaj_Wymiany()
{
    GtkWidget *okno_wymiana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(okno_wymiana), "Wymiana");
    gtk_window_set_position(GTK_WINDOW(okno_wymiana), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(okno_wymiana), 30);
    g_signal_connect(G_OBJECT(okno_wymiana), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *menu;
    menu = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10); ///orientacja pozioma
    gtk_container_set_border_width (GTK_CONTAINER (menu), 30);

    GtkWidget *wybierz_zwierze = gtk_combo_box_text_new();
    const char *zwierzeta[] = {"Wybierz zwierze", "królik", "owca", "œwinia", "krowa", "koñ", "ma³y pies", "du¿y pies"};
    for (int i = 0; i < 8; i++) gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(wybierz_zwierze), zwierzeta[i]);
    gtk_container_add(GTK_CONTAINER(menu), wybierz_zwierze);

    GtkWidget *przycisk_zatwierdz = gtk_button_new_with_label("Zatwierz");
    gtk_container_add(GTK_CONTAINER(menu), przycisk_zatwierdz);
    //g_signal_connect (G_OBJECT(przycisk_zatwierdz), "clicked", G_CALLBACK(Wymiana_Zatwierdzona), NULL);

    gtk_container_add(GTK_CONTAINER(okno_wymiana), menu);
    gtk_widget_show_all(okno_wymiana);
}

void Wymiana_Zatwierdzona()
{
    ///po³¹czyæ z hostem gry
    ///musi potem nast¹piæ update tabeli w glowny_wewnatrz
}

void Blad_Wymiana_Niemozliwa()
{

}

void Blad_Wymiana_Za_Pozno()
{

}

void Koniec_Gry()
{

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
    ///tutaj wstawimy tak¿e tabelê

    GtkWidget *przycisk_wymiana = gtk_button_new_with_label("Chcê dokonaæ wymiany");
    gtk_container_add(GTK_CONTAINER(glowny_wewnatrz), przycisk_wymiana);
    g_signal_connect (G_OBJECT(przycisk_wymiana), "clicked", G_CALLBACK(Dokonaj_Wymiany), NULL);

    GtkWidget *przycisk_rzut = gtk_button_new_with_label("Rzut kostk¹");
    gtk_container_add(GTK_CONTAINER(glowny_wewnatrz), przycisk_rzut);
    //g_signal_connect (G_OBJECT(przycisk_rzut), "clicked", G_CALLBACK(Rzut_Kostka), NULL); ///po³¹czyæ z generatorem liczb losowych
    ///wyœwietliæ komunikat o wyniku losowania

    gtk_container_add(GTK_CONTAINER(glowny), glowny_wewnatrz);

    gtk_widget_show_all(glowny);
    gtk_main();
}
