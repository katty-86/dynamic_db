Symulacja działania bazy danych

Załozenia:
1.bazę bedzie stanowić jedna tabela
2.obsługiwane typy (INT VAR TIME FLOAT);
3.w pierwszej wersji baza bedzie obsługiwać proste polecenia dml składające się z jednego wyrazaniea warunkowego i jednego recordu.


Przewidziane funkcje:
-wczytanie z pliku bazy=tabeli; 	(100%) 
-zapisanie bazy=tabeli			(100%) 
-wyswietlenie pomocy 			(100%)
-aktualizacja danych w tabeli 
--bez wyrazenia warunkowego -aktualizacja wszystkich rekordów (100%)
--z wyrazenie warunkowym - aktualizacja pasujących rekordów (100%)
-wstawianie nowych elementów
--podanie komendy "i" i wpisanie wartosci dla kolejnych recordów z lini poleceń (100%)
--podanie komendy "insert into $table_name values (val1, val2, val3, ....)"	(0%)
-usuniecie recordów
--bez wyrazenia warunkowego -usunięcie wszystkich rekordów (100%)
--z wyrazenie warunkowym - usunięcie pasujących rekordów (100%)
-wyświetlenie elementów
--"select * from $table_name:					(100%)
--"select * from $table_name where condition"    		(100%)
--"select count(*) from $table_name"				(100%)
--"select count(*) from $table_name where condition"		(100%)
--"select rec1, rec2 from $table_name"				(0%)
--"select rec1, rec2from $table_name where condition"		(0%)



Wady:
-zmienic shared_ptr na uniq_ptr gdzie sie da.
-przemyslec logowanie - poziomy logowania??
-w insercie mozna dowolna ilosc pul, nie sprawdzany jest typ i tez bedzie działać


Testy -modułami
-sql
-record
-table









