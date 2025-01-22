/*********************************************************
Studijų programa ir kursas: INFO 2k.
Grupė: 1
Pogrupis: 1
Vardas Pavardė: Martynas Radvila
Naudotojo vardas: mara4380
Užduoties numeris ir tekstas: 1. Vardai, pavardės ir AK
visų skaitytojų, kurių AK prasideda konkrečiu skaitmeniu.
**********************************************************/

select vardas, pavarde, ak from skaitytojas
where left(ak, 1) = '5';