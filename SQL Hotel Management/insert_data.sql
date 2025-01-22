/*********************************************************
Studijų programa ir kursas: INFO 2k.
Grupė: 1
Pogrupis: 1
Vardas Pavardė: Martynas Radvila
Naudotojo vardas: mara4380
**********************************************************/

insert into RoomType(Title, Capacity, Beds, PricePerNight) 
values
('Single Room', 1, 1, 45), 
('Studio Room', 1, 1, 69), 
('Queen Room', 2, 1, 76), 
('Deluxe Queen Room', 2, 1, 114), 
('Twin Room', 2, 2, 74), 
('Deluxe Twin Room', 2, 2, 112), 
('Suite with Balcony', 2, 1, 172), 
('Triple Room', 3, 3, 89), 
('Twin-Queen Room', 3, 2, 96), 
('Double-Queen Room', 4, 2, 128), 
('Suite with Sauna', 4, 2, 270);

----------------------------------------------------------------------------------------------------------


insert into Room(Nr, Type)
values
(11, 1000), (12, 1000), (13, 1000), (14, 1000), (15, 1000), (16, 1000), (17, 1000), (18, 1000), (19, 1002), 
(20, 1000), (21, 1002), (22, 1000), (23, 1002), (24, 1000), (25, 1002), (26, 1006), (27, 1002), (28, 1008), 
(29, 1002), (30, 1008), (31, 1003), (32, 1008),

(33, 1001), (34, 1004), (35, 1001), (36, 1004), (37, 1009), (38, 1004), (39, 1009), (40, 1004), (41, 1009), 
(42, 1004), (43, 1009), (44, 1005), (45, 1009), (46, 1005), (47, 1009), (48, 1010), (49, 1009), (50, 1007),
(51, 1009), (52, 1007), (53, 1003), (54, 1007), (61, 1010), (65, 1006), (70, 1003), (72, 1005);

----------------------------------------------------------------------------------------------------------


insert into Guest (Name, Surname, Address, City, Country, Birthdate)
values
('Bob', 'Bridges', '17 West St.', 'Derby', 'United Kingdom', '1985-08-23'),
('Adomas', 'Ylakis', 'Vytenio g. 18', 'Vilnius', 'Lithuania', '1992-01-15'),
('June', 'Prinz', '1 Chapel Hill', 'Preston', 'United Kingdom', '1997-02-27'),
('Camille', 'Moulin', '84 rue Gustave Eiffel', 'Roanne', 'France', '1999-04-09'),
('Elias', 'Haas', 'Auenweg 95', 'Pottenhofen', 'Austria', '2000-07-08'),
('Liisa', 'Jarvela', 'Pohjoisesplanadi 72', 'Helsinki', 'Finland', '1974-10-21'),
('Matti', 'Kalas', 'Kiannonkatu 3', 'Oulu', 'Finland', '1976-05-14'),
('Nikola', 'Radic', 'Hegedusiceva 20, 10000', 'Zagreb', 'Croatia', '1991-09-09'),
('Liam', 'King', '1231 Nelson St.', 'Balmertown', 'Canada', '1993-11-03'),
('Yulia', 'Shvets', 'Vozdukhoflotskiy bld. 72', 'Kyiv', 'Ukraine', '1984-06-28'),
('Emma', 'Fraser', '3808 Ste. Catherine Ouest', 'Montreal', 'Canada', '1999-06-17'),
('Priscilla', 'De Luca', 'Piazza Pilastri 30', 'Margno', 'Italy', '2001-02-05'),
('Vittoria', 'Greco', 'Via Vicenza 13', 'Castel Del Rio', 'Italy', '1970-03-04'),
('Alexander', 'Olsen', 'Sleireveien 30', 'Sandnes', 'Norway', '1992-01-15'),
('Bob', 'Bridges', '2929 Hillcrest Avenue', 'Halltown', 'United States', '1992-01-15'),
('Javier', 'Navarro', 'Cano 26', 'Santo Adriano', 'Spain', '1998-12-09');

----------------------------------------------------------------------------------------------------------


insert into Reservation(ReservationDate, Arrival, Departure, Room, Guest, Adults, Children, Cancelled)
values
('2022-03-03', '2022-05-08', '2022-05-11', '25', 410011, 2, 0, null),
('2022-04-27', '2022-05-01', '2022-05-02', '11', 410004, 1, 0, null),
('2022-04-10', '2022-05-05', '2022-05-09', '34', 410000, 1, 1, null),
('2021-12-19', '2022-05-02', '2022-05-09', '31', 410012, 2, 0, null),
('2022-03-17', '2022-04-23', '2022-04-27', '14', 410005, 1, 0, null),
('2022-03-17', '2022-04-23', '2022-04-27', '15', 410005, 1, 0, null),
('2022-03-17', '2022-04-23', '2022-04-27', '18', 410005, 1, 0, null),
('2022-05-01', '2022-05-15', '2022-05-17', '35', 410001, 1, 0, null),
('2022-04-06', '2022-04-07', '2022-04-09', '46', 410003, 2, 0, null),
('2022-05-05', '2022-05-10', '2022-05-12', '32', 410002, 2, 1, null),
('2022-04-16', '2022-05-23', '2022-05-28', '45', 410008, 2, 2, '2022-05-01'),
('2022-02-14', '2022-05-02', '2022-05-03', '25', 410004, 1, 0, null),
('2022-04-16', '2022-05-23', '2022-05-28', '65', 410006, 1, 0, null),
('2022-05-01', '2022-05-02', '2022-05-12', '54', 410015, 1, 2, null),
('2022-04-29', '2022-05-26', '2022-05-28', '45', 410007, 4, 0, null),
('2022-02-16', '2022-05-03', '2022-05-05', '11', 410014, 1, 0, null),
('2022-01-16', '2022-05-01', '2022-05-14', '21', 410010, 2, 0, null),
('2022-05-04', '2022-05-18', '2022-05-19', '42', 410013, 1, 0, '2022-05-06'),
('2022-05-05', '2023-01-05', '2023-01-07', '61', 410009, 3, 1, null),
('2022-04-16', '2022-04-18', '2022-04-21', '25', 410006, 1, 0, null),
('2022-02-24', '2022-03-01', '2022-03-09', '12', 410005, 1, 0, null),
('2022-03-19', '2022-05-10', '2022-05-14', '17', 410010, 1, 0, null),
('2022-05-09', '2022-05-15', '2022-05-18', '19', 410007, 2, 0, null),
('2022-02-07', '2022-05-12', '2022-05-19', '32', 410003, 2, 1, null),
('2022-04-13', '2022-05-15', '2022-05-17', '50', 410014, 3, 0, null),
('2022-04-27', '2022-05-15', '2022-05-19', '31', 410002, 2, 0, null),
('2022-05-05', '2022-05-11', '2022-05-18', '33', 410012, 1, 0, null),
('2022-05-04', '2022-05-14', '2022-05-21', '49', 410009, 1, 3, null),
('2022-05-01', '2022-05-16', '2022-05-18', '26', 410005, 2, 0, null),
('2022-05-03', '2022-05-08', '2022-05-19', '12', 410000, 1, 0, null),
('2022-05-10', '2022-05-15', '2022-05-24', '14', 410008, 1, 0, null),
('2022-05-10', '2022-05-15', '2022-05-24', '15', 410008, 1, 0, null),
('2022-05-10', '2022-05-15', '2022-05-24', '17', 410008, 1, 0, null),
('2022-05-08', '2022-05-12', '2022-05-17', '44', 410001, 1, 0, null),
('2022-05-05', '2022-05-14', '2022-05-18', '34', 410014, 1, 0, null);

----------------------------------------------------------------------------------------------------------


update Payment set completed = '2022-03-05', method = 'Debit Card' where reservation = 1189000;
update Payment set completed = '2022-04-29', method = 'Debit Card' where reservation = 1189001;
update Payment set completed = '2022-04-20', method = 'Debit Card' where reservation = 1189002;
update Payment set completed = '2022-01-15', method = 'Credit Card' where reservation = 1189003;
update Payment set completed = '2022-04-23', method = 'Cash' where reservation = 1189004;
update Payment set completed = '2022-03-17', method = 'Debit Card' where reservation = 1189005;
update Payment set completed = '2022-03-17', method = 'Debit Card' where reservation = 1189006;
update Payment set completed = '2022-04-06', method = 'Virtual Payment' where reservation = 1189008;
update Payment set completed = '2022-05-05', method = 'Debit Card' where reservation = 1189009;
update Payment set completed = '2022-02-14', method = 'Debit Card' where reservation = 1189011;
update Payment set completed = '2022-05-01', method = 'Debit Card' where reservation = 1189013;
update Payment set completed = '2022-05-19', method = 'Mobile Wallet' where reservation = 1189014;
update Payment set completed = '2022-02-18', method = 'Cash' where reservation = 1189015;
update Payment set completed = '2022-04-28', method = 'Credit Card' where reservation = 1189016;
update Payment set completed = '2022-05-07', method = 'Cash' where reservation = 1189018;
update Payment set completed = '2022-04-18', method = 'Debit Card' where reservation = 1189019;
update Payment set completed = '2022-02-26', method = 'Debit Card' where reservation = 1189020;

update Payment set completed = '2022-05-05', method = 'Debit Card' where reservation = 1189021;
update Payment set completed = '2022-05-10', method = 'Cash' where reservation = 1189022;
update Payment set completed = '2022-02-24', method = 'Debit Card' where reservation = 1189023;
update Payment set completed = '2022-04-13', method = 'Debit Card' where reservation = 1189024;
update Payment set completed = '2022-04-27', method = 'Cash' where reservation = 1189025;
update Payment set completed = '2022-05-05', method = 'Debit Card' where reservation = 1189026;
update Payment set completed = '2022-05-04', method = 'Debit Card' where reservation = 1189027;
update Payment set completed = '2022-05-02', method = 'Debit Card' where reservation = 1189028;
update Payment set completed = '2022-05-03', method = 'Virtual Payment' where reservation = 1189029;
update Payment set completed = '2022-05-10', method = 'Debit Card' where reservation = 1189030;
update Payment set completed = '2022-05-10', method = 'Debit Card' where reservation = 1189031;
update Payment set completed = '2022-05-10', method = 'Debit Card' where reservation = 1189032;
update Payment set completed = '2022-05-08', method = 'Debit Card' where reservation = 1189033;
update Payment set completed = '2022-05-06', method = 'Debit Card' where reservation = 1189034;


