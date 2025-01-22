/*******************************************************************

Studijų programa ir kursas: INFO 2k.

Grupė: 1

Pogrupis: 1

Vardas Pavardė: Martynas Radvila

Naudotojo vardas: mara4380

Užduoties numeris ir tekstas: 4. Data, kai ėmusiųjų knygas skaitytojų
buvo daugiausiai. Greta pateikti ir tuomet ėmusiųjų knygas skaitytojų
skaičių.

********************************************************************/

with paemimai(data, kiekis)
as (select paimta, count(*) from egzempliorius
    where paimta is not null
    group by paimta)
select data, kiekis from paemimai
where kiekis = (select max(kiekis) from paemimai);