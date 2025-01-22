import com.mongodb.*;
import com.mongodb.client.*;
import com.mongodb.client.MongoClient;
import com.mongodb.client.model.Accumulators;
import com.mongodb.client.model.Aggregates;
import com.mongodb.client.model.Filters;

import com.mongodb.client.model.UpdateOptions;
import com.mongodb.client.result.*;
import org.bson.Document;
import org.bson.types.ObjectId;


import javax.print.Doc;
import java.text.SimpleDateFormat;
import java.util.*;

import static com.mongodb.client.model.Filters.*;
import static com.mongodb.client.model.Updates.*;
import static com.mongodb.client.model.Sorts.ascending;

import java.util.logging.Logger;
import java.util.logging.Level;

public class OrderingSystem
{
    public static void main(String[] args)
    {
        //Ignore server logs
        Logger mongoLogger = Logger.getLogger( "org.mongodb.driver" );
        mongoLogger.setLevel(Level.SEVERE);

        MongoClient client = MongoClients.create();
        MongoDatabase db = client.getDatabase("restaurant");

        Scanner sc = new Scanner(System.in);

        boolean running = true;

        while(running)
        {
            System.out.println("Connected to Food Ordering System.\n");
            System.out.println("1. Create order");
            System.out.println("2. Display orders");
            System.out.println("3. Display registered customers");
            System.out.println("4. Display menu");
            System.out.println("\n5. Display earnings for different payment methods");
            System.out.println("6. Display earnings for different payment methods [mapReduce]");
            System.out.println("\n0. Exit\n");

            System.out.print(">> ");
            int action = sc.nextInt();
            sc.nextLine();

            switch (action)
            {
                case 1:
                {
                    String name = "";
                    System.out.print("Name: ");
                    name = sc.nextLine();

                    String surname = "";
                    System.out.print("Surname: ");
                    surname = sc.nextLine();

                    String address = "";
                    System.out.print("Address: ");
                    address = sc.nextLine();

                    //ADD CUSTOMER INFO
                    db.getCollection("customers").insertOne(new Document()
                            .append("_id", new ObjectId())
                            .append("name", name)
                            .append("surname", surname)
                            .append("address", address));




                    //SHOW MENU
                    MongoCollection<Document> menu = db.getCollection("menu");
                    MongoIterable<Document> menuItems = menu.find().sort(ascending("price"));

                    Helper.showMenu(menuItems);


                    //START ORDER
                    System.out.println("\nOrder format -- item name, size(r or l), quantity");
                    System.out.println("To finish type 'done'");
                    System.out.print(">> ");

                    String itemName = "";
                    itemName = sc.nextLine();

                    List<Document> items = new ArrayList<>();
                    double total = 0.0;


                    while(!itemName.equals("done"))
                    {
                        //GET FOOD ITEM FROM MENU
                        Document item = menu.find(eq("name", itemName)).first();

                        if(item != null)
                        {
                            Object test = item.get("_id");
                            String id = test.toString();

                            double price = (double)item.get("price");

                            String size = sc.nextLine();

                            if(size.equals("l"))
                                size = "large";
                            else
                                size = "regular";

                            int quantity = sc.nextInt();
                            sc.nextLine();


                            //ADD SELECTED ITEM TO LIST
                            items.add(new Document().append("menu_id", id)
                                    .append("size", size)
                                    .append("quantity", quantity));

                            total += price * quantity;
                        }

                        else
                            System.out.println("Selected item does not exist.");


                        System.out.print(">> ");
                        itemName = sc.nextLine();
                    }

                    //FINISH ORDER DETAILS
                    System.out.println("\nOrder total: " + String.format("%.2f", total) + "€");
                    System.out.println("Payment method: ");
                    String method = sc.nextLine();

                    String date = new SimpleDateFormat("yyyy-MM-dd").format(new Date());

                    //GET NEWLY ADDED CUSTOMER ID
                    Document customer = db.getCollection("customers").find(eq("address", address)).first();
                    Object test2 = customer.get("_id");
                    String customer_id = test2.toString();

                    total = Helper.round(total, 2);

                    //PAYMENT ENTITY
                    Document payment = new Document().append("amount", total)
                            .append("method", method)
                            .append("completed", date);

                    //INSERT ORDER
                    db.getCollection("orders").insertOne(new Document()
                            .append("_id", new ObjectId())
                            .append("customer", customer_id)
                            .append("items", items)
                            .append("payment", payment));

                    System.out.println("Order has been completed successfully!");
                    break;
                }
                case 2:
                    MongoCollection<Document> orders = db.getCollection("orders");
                    MongoIterable<Document> orderList = orders.find().sort(ascending("payment.completed"));

                    Helper.showOrders(db, orderList);
                    break;

                case 3:
                    MongoCollection<Document> customers = db.getCollection("customers");
                    MongoIterable<Document> customerList = customers.find().sort(ascending("name"));

                    Helper.showCustomers(customerList);
                    break;

                case 4:
                    MongoCollection<Document> menu = db.getCollection("menu");
                    MongoIterable<Document> menuItems = menu.find().sort(ascending("price"));

                    Helper.showMenu(menuItems);
                    break;

                case 5:

                    db.getCollection("orders").aggregate(
                            Arrays.asList(
                                    Aggregates.group("$payment.method",
                                            Accumulators.sum("Earnings", "$payment.amount"))
                            )
                    ).forEach((Block<? super Document>) doc -> System.out.println(doc.toJson()));

                    break;

                case 6:

                    String map = " function() {" +
                            "emit(this.payment.method, this.payment.amount);" +
                            "}";

                    String reduce = "function(key, values) { " +
                            "    return Array.sum(values); " +
                            "}";

                    MapReduceIterable mapReduceIt = db.getCollection("orders").mapReduce(map, reduce);

                    for(Object result: mapReduceIt)
                        System.out.println(result);

                    break;

                default:
                    running = false;
                    break;
            }

            //System.out.print(">> ");
            sc.nextLine();
        }
    }
}
