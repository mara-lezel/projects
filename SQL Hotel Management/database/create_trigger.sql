/*********************************************************
Studijų programa ir kursas: INFO 2k.
Grupė: 1
Pogrupis: 1
Vardas Pavardė: Martynas Radvila
Naudotojo vardas: mara4380
**********************************************************/

create or replace function PaymentDeadline()
returns trigger as
$$
  begin
    if(New.completed is null) then
       return new;
    elsif( select count(*) from Reservation
        where New.reservation = Reservation.id
        and ReservationDate <= New.completed
        and Arrival >= New.completed 
        and Cancelled is null) != 1 
    then 
      raise exception 'Payment completion date % is invalid, check reservation id %', 
      New.completed, New.reservation;
    end if;
    return new;
  end;
$$
language plpgsql;


create trigger PaymentDeadline
before insert or update of Completed on Payment
for each row
execute procedure PaymentDeadline();

--------------------------------------------------------------------------------------------------


create or replace function CorrectAmount()
returns trigger as
$$
  begin
    if( select TotalCost from Details
        where New.reservation = Details.id) != New.amount
    then
      raise exception 'Room pricing does not match the amount being paid';
    end if;
    return new;
  end;
$$
language plpgsql;


create trigger CorrectAmount
before insert or update of Amount on Payment
for each row
execute procedure CorrectAmount();

--------------------------------------------------------------------------------------------------


create or replace function CorrectRoomSize()
returns trigger as
$$
  begin
    if( select Capacity from Room, RoomType
        where New.room = Room.nr and Room.type = RoomType.id) < (New.adults + New.children)
    then
      raise exception 'Assigned room nr. % cannot accommodate % people', New.room, 
      (New.adults + New.children);
    end if;
    return new;
  end;
$$
language plpgsql;


create trigger CorrectRoomSize
before insert or update on Reservation
for each row
execute procedure CorrectRoomSize();

--------------------------------------------------------------------------------------------------


create or replace function RestrictDeletion()
returns trigger as
$$
  begin
    if(select count(*) from reservation where Old.reservation = reservation.id) = 1
    then raise exception 'Cannot delete payment information tied to reservation';
    end if;
    return Old;
  end;
$$
language plpgsql;

create trigger RestrictDeletion
before delete on Payment
for each row
execute procedure RestrictDeletion();

--------------------------------------------------------------------------------------------------


create or replace function InsertPayment()
returns trigger as
$$
  begin
    refresh materialized view concurrently Details;
    insert into Payment(Reservation, Amount, Completed, Method)
    values
    (New.id, 
    (select TotalCost from Details where New.id = Details.id),
     null, 
     null);
    return New;
  end;
$$
language plpgsql;

create trigger InsertPayment
after insert on Reservation
for each row
execute procedure InsertPayment();

--------------------------------------------------------------------------------------------------


create or replace function UpdatePayment()
returns trigger as
$$
  begin
    if(current_date >= Old.arrival) then 
      raise exception 'Cannot change reservation details for past or active reservations';
    else
      refresh materialized view concurrently Details;
      update Payment
      set Amount = (select TotalCost from Details where New.id = Details.id),
          Completed = null,
 	  Method = null
      where Reservation = New.id;
    end if;
    return New;
  end;
$$
language plpgsql;

create trigger UpdatePayment
after update of Room, Arrival, Departure on Reservation

for each row
execute procedure UpdatePayment();

--------------------------------------------------------------------------------------------------


create or replace function RefreshDetails()
returns trigger as 
$$
  begin
    refresh materialized view concurrently Details;
    return null;
  end;
$$
language plpgsql;

create trigger RefreshDetailsReservation 
after insert or update or delete on Reservation
execute procedure RefreshDetails();

create trigger RefreshDetailsType 
after insert or update or delete on RoomType
execute procedure RefreshDetails();

create trigger RefreshDetailsRoom
after insert or update or delete on Room
execute procedure RefreshDetails();


