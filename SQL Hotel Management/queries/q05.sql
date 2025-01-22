/*******************************************************************

Studijų programa ir kursas: INFO 2k.

Grupė: 1

Pogrupis: 1

Vardas Pavardė: Martynas Radvila

Naudotojo vardas: mara4380

Užduoties numeris ir tekstas: 5. Konkrečiam naudotojui – sąrašas
lentelių, kurioms jis turi teisę rašyti užklausas.

********************************************************************/

select table_schema, table_name
from information_schema.table_privileges
where privilege_type = 'SELECT' and grantee = 'mara4380'
order by 1, 2;
