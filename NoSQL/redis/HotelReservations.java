import java.time.LocalDate;
import java.util.*;

import redis.clients.jedis.Jedis;
import redis.clients.jedis.Transaction;
import redis.clients.jedis.resps.Tuple;

public class HotelReservations
{
    public static void main(String[] args)
    {
        Jedis db = new Jedis();

        Scanner sc = new Scanner(System.in);

        boolean running = true;

        //Helper.generate(db);

        while(running)
        {
            System.out.println("Connected to Hotel Reservation System.");
            System.out.println("1. Make a reservation");
            System.out.println("2. Display reservation list");
            System.out.println("3. Display guest list");
            System.out.println("4. Exit\n");

            System.out.print(">> ");
            int action = sc.nextInt();
            sc.nextLine();

            switch (action)
            {
                case 1:
                {
                    //Get guest details
                    ArrayList<String> guestDetails = Helper.getGuestDetails(sc);

                    //Get time of stay
                    ArrayList<String> datesInRange = Helper.getDateRange(sc);

                    //Save check-in and check-out details
                    String start = datesInRange.get(0);
                    String end = LocalDate.parse(datesInRange.get(datesInRange.size() - 1)).plusDays(1).toString();

                    //Display room information
                    Helper.showRoomTypes(db);

                    //Select preferred room type and append selected dates
                    int roomType = Helper.selectRoomType(sc, db, datesInRange);

                    if(roomType == -1)
                        break;

                    //Get all available rooms
                    Set<String> availableRooms = Helper.getAvailableRooms(db, roomType, datesInRange);

                    //Show all available rooms
                    Helper.showRooms(availableRooms);

                    //
                    System.out.print("Select preferred room (code): ");
                    String roomCode = sc.nextLine();

                    //Convert set to string
                    String dates = "";
                    for(int i = 0; i < datesInRange.size(); ++i)
                        dates += datesInRange.get(i) + " ";

                    //Get guest size, get reservation size
                    long guestListSize = db.zcard("guest_list");
                    long resListSize = db.zcard("reservations");
                    boolean success = true;

                    //TRANSACTION
                    while(true)
                    {
                        //Start watch
                        db.watch(dates);

                        //Start transaction
                        Transaction transaction = db.multi();

                        //Add room to every key
                        for(int i = 0; i < datesInRange.size(); ++i)
                            transaction.sadd(datesInRange.get(i), roomCode);

                        //Add guest to guest_list
                        transaction.hset("guest_" + guestListSize, "name", guestDetails.get(0));
                        transaction.hset("guest_" + guestListSize, "surname", guestDetails.get(1));
                        transaction.hset("guest_" + guestListSize, "address", guestDetails.get(2));

                        transaction.zadd("guest_list", guestListSize, "guest_" + guestListSize);

                        //Add reservation to reservations
                        transaction.hset("reservation_" + resListSize, "guest_id", String.valueOf(guestListSize));
                        transaction.hset("reservation_" + resListSize, "room", String.valueOf(roomCode));
                        transaction.hset("reservation_" + resListSize, "check-in", start);
                        transaction.hset("reservation_" + resListSize, "check-out", end);

                        transaction.zadd("reservations", resListSize, "reservation_" + resListSize);

                        List<Object> result = transaction.exec();

                        for(Object status : result)
                        {
                            if(!String.valueOf(status).equals("1"))
                            {
                                System.out.println("Reservation could not be completed successfully.");
                                success = false;
                                break;
                            }
                        }

                        if(!result.isEmpty())
                        {
                            db.unwatch();

                            if(success)
                                System.out.println("Reservation was completed successfully!\n");

                            break;
                        }
                    }

                    break;
                }
                case 2:
                {
                    List<String> res = db.zrange("reservations", 0, -1);

                    for(String resName : res)
                    {
                        Map<String, String> resDetails = db.hgetAll(resName);

                        System.out.println("+------------------------------------------");
                        for(String entry : resDetails.keySet())
                        {
                            String key = entry;
                            String value = resDetails.get(entry);

                            key = key.substring(0, 1).toUpperCase() + key.substring(1).toLowerCase();

                            System.out.println("| " + key + ": " + value);
                        }

                    }

                    System.out.println("-------------------------------------------");
                    System.out.println("\n");

                    break;
                }
                case 3:
                {
                    List<Tuple> guests = db.zrangeWithScores("guest_list", 0, -1);

                    for(Tuple guestName : guests)
                    {
                        Map<String, String> resDetails = db.hgetAll(guestName.getElement());

                        System.out.println("+------------------------------------------");
                        System.out.println("| Guest_id: " + (int)guestName.getScore());

                        for(String entry : resDetails.keySet())
                        {
                            String key = entry;
                            String value = resDetails.get(entry);

                            key = key.substring(0, 1).toUpperCase() + key.substring(1).toLowerCase();

                            System.out.println("| " + key + ": " + value);
                        }

                        System.out.println("|");
                    }

                    System.out.println("-------------------------------------------");
                    System.out.println("\n");

                    break;
                }
                case 0:
                    Set<String> test = db.keys("*");
                    for(String a : test)
                        System.out.println("> " + a);
                    break;
                default:
                    running = false;
                    break;
            }
        }

        db.close();
    }
}
