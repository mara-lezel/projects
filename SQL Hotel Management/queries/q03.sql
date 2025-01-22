/*******************************************************************

Studijų programa ir kursas: INFO 2k.

Grupė: 1

Pogrupis: 1

Vardas Pavardė: Martynas Radvila

Naudotojo vardas: mara4380

Užduoties numeris ir tekstas: 3. Kiekvienam skaitytojui 
(numeris, vardas, pavardė) jo paimtų egzempliorių skaičius, bendra
jų vertė. Jei knygos vertė nenurodyta, laikyti, kad ji yra lygi 10.

********************************************************************/

select skaitytojas.nr, vardas, pavarde, count(*), sum(coalesce(verte, 10))
from skaitytojas, egzempliorius, knyga
where skaitytojas.nr = egzempliorius.skaitytojas and knyga.isbn = egzempliorius.isbn
group by skaitytojas.nr, vardas, pavarde;