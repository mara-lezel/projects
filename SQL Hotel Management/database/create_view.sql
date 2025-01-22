/*********************************************************
Studijų programa ir kursas: INFO 2k.
Grupė: 1
Pogrupis: 1
Vardas Pavardė: Martynas Radvila
Naudotojo vardas: mara4380
**********************************************************/

create materialized view Details as
select 
  Reservation.id, 
  Room, 
  (Departure - Arrival) as Nights,
  ((Departure - Arrival) * PricePerNight) as TotalCost
from 
  Reservation, Room, RoomType
where 
  Reservation.room = Room.nr and Room.type = RoomType.id
with data;  


create view MoneySpent as
select 
  Guest, 
  Name, 
  Surname, 
  sum(TotalCost) as Amount
from 
  Details, 
  Reservation, 
  Guest
where 
  Reservation.id = Details.id and Reservation.guest = Guest.id
group by 1, 2, 3
order by 4 desc;


create view Active as
select
  Reservation.id,
  Name,
  Surname,
  Room,
  Arrival,
  Departure
from
  Reservation,
  Guest
where
  Reservation.guest = Guest.id and
  current_date >= Arrival and
  current_date < Departure and
  Cancelled is null;


create view Occupancy as
with 
AllRooms(Typename, Count) as
(
 select 
   Title, count(*) 
 from 
   Room, RoomType
 where 
   Room.type = RoomType.id
 group by 1
),

ActiveRooms(Typename, Count) as
(
 select 
   Title, count(*)
 from
   Room, RoomType, Reservation
 where 
   Reservation.room = Room.nr and 
   Room.type = RoomType.id and 
   Arrival <= current_date and 
   Cancelled is null and 
   Departure > current_date
group by 1
)

select
  AllRooms.typename as Title, 
  coalesce(ActiveRooms.count, 0) as Occupied, 
  coalesce((AllRooms.count - ActiveRooms.count), AllRooms.count) as Available
from AllRooms
  full outer join ActiveRooms on AllRooms.typename = ActiveRooms.typename
order by 3 desc;


