/*********************************************************
Studijų programa ir kursas: INFO 2k.
Grupė: 1
Pogrupis: 1
Vardas Pavardė: Martynas Radvila
Naudotojo vardas: mara4380
Užduoties numeris ir tekstas: 2. Konkretaus pavadinimo knygos
kiekvieno jos paimto egzemplioriaus numeris ir jį paėmusio
skaitytojo numeris.
**********************************************************/

select nr, skaitytojas from egzempliorius, knyga
where pavadinimas = 'Duomenu bazes' and paimta is not null
and egzempliorius.isbn = knyga.isbn;