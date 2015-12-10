
Możesz stworzyć sobie wirtualną klasę reprezentującą pole bazy danych, a klasami po niej dziedziczącymi opakować odpowiednie typy. Jeden rekord musiałby być wtedy listą obiektów wspomnianej na początku klasy lub jednej z klas pochodnych.

/data
field 
dziedziczace miały by intfield- value


class

-field
-record, który by zawierał list_of_fieldy
-table, vector_of_record

/config

field_config{
name
data_type
}

table{
name
vector<field_config> table_config
vector<record> data;
}



write/read_db podawane do pliku

