/*********************************************************
Studijų programa ir kursas: INFO 2k.
Grupė: 1
Pogrupis: 1
Vardas Pavardė: Martynas Radvila
Naudotojo vardas: mara4380
**********************************************************/

create table Guest
(
  ID 
    integer not null primary key
    generated always as identity
    (start with 410000 increment by 1),
  Name 
    varchar(30) not null,
  Surname 
    varchar(30) not null,
  Address 
    varchar(30) not null,
  City 
    varchar(30) not null,
  Country 
    varchar(30) not null,
  Birthdate 
    date not null,

  constraint ValidBirthdate
  check (Birthdate < current_date),

  constraint ValidAge
  check (date_part('year', age(Birthdate)) >= 18)
);


create table RoomType
(
  ID 
    integer not null primary key
    generated always as identity
    (start with 1000 increment by 1),
  Title 
    varchar(30) not null,
  Capacity 
    integer not null,
  Beds 
    integer not null,
  PricePerNight 
    decimal not null,

  constraint PriceRange
  check (PricePerNight between 25.0 and 300.0),

  constraint GuestLimit
  check (Capacity between 1 and 4),

  constraint BedLimit
  check (Beds between 1 and 4),

  constraint ValidBeds
  check(Beds <= Capacity)
);


create table Room
(
  Nr 
    smallint not null primary key,
  Type 
    integer not null,

  constraint RoomTotal
  check(Nr between 1 and 112),

  constraint FType
  foreign key(Type)
  references RoomType(ID)
  on delete restrict
  on update cascade
);


create table Reservation
(
  ID 
    integer not null primary key
    generated always as identity
    (start with 1189000 increment by 1),
  ReservationDate 
    date not null,
  Arrival 
    date not null,
  Departure 
    date not null,
  Room 
    smallint not null,
  Guest 
    integer not null,
  Adults 
    integer
    default 1,
  Children 
    integer
    default 0,
  Cancelled 
    date,

  constraint ValidReservationDate
  check(ReservationDate <= current_date and 
        ReservationDate < Arrival and ReservationDate < departure),

  constraint ValidCancelled
  check(Cancelled >= ReservationDate and Cancelled < Departure),
 
  constraint ValidArrival
  check(Arrival < Departure and Arrival > ReservationDate),

  constraint ValidDeparture
  check(Departure > Arrival and Departure > ReservationDate),

  constraint AdvanceBooking
  check(Arrival - ReservationDate < 350),

  constraint MaxGuests
  check((adults + children) between 1 and 4),

  constraint FRoom
  foreign key(Room)
  references Room(Nr)
  on delete restrict
  on update restrict,

  constraint FGuest
  foreign key(Guest)
  references Guest(ID)
  on delete cascade
  on update cascade
);


create table Payment
(
  Reservation 
    integer not null primary key,
  Amount 
    decimal not null,
  Completed 
    date,
  Method 
    varchar(15),

  constraint ValidAmount
  check (amount >= 0.0),

  constraint ValidMethod
  check (method in ('Cash', 'Credit Card', 'Debit Card', 'Mobile Wallet', 'Virtual Payment')),

  constraint FReservation
  foreign key(Reservation)
  references Reservation(ID)
  on delete cascade
  on update cascade
);


