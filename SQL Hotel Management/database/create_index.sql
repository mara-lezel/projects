/*********************************************************
Studijų programa ir kursas: INFO 2k.
Grupė: 1
Pogrupis: 1
Vardas Pavardė: Martynas Radvila
Naudotojo vardas: mara4380
**********************************************************/

create unique index un_idx_room_arrival_cancel on Reservation(Room, Arrival, (Cancelled is null)) 
  where cancelled is null;
create unique index un_idx_room_departure_cancel on Reservation(Room, Departure, (Cancelled is null))
  where cancelled is null;
create unique index mv_id on Details(ID);
create index idx_surname on Guest(Surname asc);


