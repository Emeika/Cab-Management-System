#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Payment // Grandfather class
{
private:
    int amount;

public:
    Payment(const int &amount) : amount(amount) {}
    void payment_details()
    {
        cout << "Total Fare is:" << amount << " rupees." << endl;
    }
};

class CashPayment : public Payment // Multilevel Inheritance with payment class(Father class)
{
private:
    string pay_type;

public:
    // Payment type for the current transaction type
    CashPayment(const int &amount, const string &pay_type = "Cash") : Payment(amount), pay_type(pay_type) {}

    string get_pay_type() { return pay_type; };

    void payment_details()
    {
        Payment::payment_details();
        cout << "Paid by " << pay_type;
        cout << endl;
    }
};

class CardPayment : public CashPayment // Multilevel Inheritance with Cash payment class (Son/Derived class)
{
private:
    string pay_type;
    string card_number;
    string name, c_type, expiry_date;

public:
    CardPayment(const int &amount, string &card_number, const string &name, const string &expiry_date, const string &c_type, const string &pay_type = "Card")
        : CashPayment(amount), card_number(card_number), name(name), expiry_date(expiry_date), c_type(c_type), pay_type(pay_type) {}

    string get_pay_type() { return pay_type; }

    void payment_details()
    {
        CashPayment::payment_details();
        cout << "Card Used: " << c_type << endl;
        cout << "Last four digits of card: " << card_number.substr(card_number.length() - 4) << endl;
    }
};

class Vehicle
{
private:
    string v_type;
    string model;

public:
    Vehicle(const string &v_type, const string &model) : v_type(v_type), model(model) {}

    void display()
    {
        cout << "Vehicle type: " << v_type << endl;
        cout << "Vehicle Model: " << model << endl;
        cout << endl;
    }
};

class Car : public Vehicle // Inheritance with Vehicle
{
public:
    Car(const string &v_type, const string &model) : Vehicle(v_type, model) {}
    // if child class doesn't have the display function then it takes from parent class
};

class Auto : public Vehicle // Inheritance with Vehicle
{
public:
    Auto(const string &v_type, const string &model) : Vehicle(v_type, model) {}
};

class Person
{
private:
    // member variables
    string username;
    string password;
    string contact;

public:
    Person(const string &username, const string &password, const string &contact)
        : username(username), password(password), contact(contact) {}

    string get_username() { return username; }

    void profile_display()
    {
        cout << "Username: " << username << endl;
        cout << "Contact: " << contact << endl;
        cout << endl;
    }
};

class Driver : public Person // inheritance with person class
{
private:
    Vehicle *vehicle_obj;

public:
    Driver(const string &username, const string &password, const string &contact, Vehicle *vehicle_obj)
        : Person(username, password, contact), vehicle_obj(vehicle_obj) {}

    void profile_display()
    {
        Person::profile_display();
        vehicle_obj->display();
    }

    void trip_history()
    {
        ifstream infile("Booking.txt");

        if (infile.fail())
        {
            cout << "Booking file not found" << endl;
            return;
        }

        string line, date, time, driver_fname, driver_lname, pick, drop, customer_name, fare, status;

        while (infile >> date >> time >> driver_fname >> driver_lname >> pick >> drop >> customer_name >> fare >> status)
        {
            cout << endl;
            cout << "Date and time: " << date << " " << time << endl;
            cout << "Driver name: " << driver_fname << " " << driver_lname << endl;
            cout << "Pickup Address: " << pick << endl;
            cout << "Destination Address: " << drop << endl;
            cout << "Customer name: " << customer_name << endl;
            if (status == "Cancelled")
            {
                cout << "Fare: " << fare << endl;
                cout << "Cancelled Booking by Customer:" << endl;
            }
            else if (status == "Cancelled")
            {
                cout << "Total earning for this trip: " << fare << endl;
                cout << "Ride Completed:" << endl;
            }
        }

        infile.close();
    }
};

class CarBooking
{
private:
    string date;
    string pickup;
    string destination;
    int miles;
    int fare;
    string car_type;
    //  Driver class is aggregated
    Driver *driver_obj; // Pointer to a driver object

public:
    CarBooking(const string &pickup, const string &destination, int miles, const string &date, const string &car_type, Driver *driver_obj)
        : pickup(pickup), destination(destination), miles(miles), date(date), car_type(car_type), driver_obj(driver_obj)
    {
        set_fare(car_type);
    }

    void set_fare(const string &car_type)
    {
        if (car_type == "Car")
        {
            fare = miles * 40;
        }
        else
        {
            fare = miles * 30;
        }
    }

    int get_fare()
    {
        return fare;
    }

    void display(Payment &payment_obj) // Association with payment class
    {
        cout << "Date and Time: " << date << endl;
        cout << "Pickup Location: " << pickup << endl;
        cout << "Destination: " << destination << endl;
        payment_obj.payment_details();
        cout << "Assigned Driver:" << endl;
        driver_obj->profile_display();
    }
};

class Customer : public Person // Inheritance with person
{
private:
    CarBooking *car_booking_obj; // Pointer to a CarBooking object

public:
    Customer(const string &username, const string &password, const string &contact, CarBooking *car_booking_obj)
        : Person(username, password, contact), car_booking_obj(car_booking_obj) {}

    void booking_display(Payment &payment_obj) // Payment class Associated with Car booking class through customer
    {
        car_booking_obj->display(payment_obj);
        cout << endl;
    }

    void trip_history()
    {
        ifstream infile(get_username() + ".txt");
        if (infile.fail())
        {
            cout << "Booking file not found" << endl;
            return;
        }

        string date, time;
        string drop, pick;
        string miles, fare;
        string driverUsername, driverContact, vehicle;
        string paymentMethod, status;

        while (infile >> pick >> drop >> miles >> fare >> driverUsername >> driverContact >> vehicle >> paymentMethod >> date >> time >> status)
        {
            if (status == "Cancelled")
            {
                cout << "Cancelled Booking Details:" << endl;
            }
            else if (status == "Completed")
            {
                cout << "Confirmed Booking Details:" << endl;
            }

            cout << "Date and time: " << date << " " << time << endl;
            cout << "Fare: Rs. " << fare << endl;
            cout << "Miles: " << miles << endl;
            cout << "Payment made with: " << paymentMethod << endl;
            cout << "Driver username: " << driverUsername << endl;
            cout << "Driver Contact: " << driverContact << endl;
            cout << "Pickup Address: " << pick << endl;
            cout << "Destination Address: " << drop << endl;
            cout << "Vehicle: " << vehicle << endl;

            cout << endl;
        }

        infile.close();
    }
};

void userLogin()
{
    string username, password, role;
    bool found = false;
    string contact;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    cout << "Enter role (driver or customer): ";
    cin >> role;

    ifstream infile(role + ".txt");

    if (infile.fail())
    {
        cout << "Error opening file." << endl;
        return;
    }

    string line, Username, Password, Contact;
    while (infile >> Username >> Password >> Contact)
    {
    // Check if the entered username and password match with any line in the file
        if (username == Username && password == Password)
        {
            found = true;
            contact = Contact;
            break;
        }
    }

    infile.close();

    if (found)
    {
        cout << "Login successful!" << endl;
        cout << "Contact: " << contact << endl;

        if (role == "driver")
        {
            string vehicleType, model;
            cout << "Enter Vehicle Type (Car/Auto): ";
            cin >> vehicleType;

            cout << "Enter Vehicle Model: ";
            cin >> model;

            if (vehicleType == "Car")
            {
                Vehicle* vehicleObj = new Car(vehicleType, model);//create a new Car object and assign it to a Vehicle pointer
                Driver driver(username, password, contact, vehicleObj);//create a driver object with the provided details and the created vehicle obj
                driver.profile_display();
                driver.trip_history();
            }
            else if (vehicleType == "Auto")
            {
                Vehicle* vehicleObj = new Auto(vehicleType, model);
                Driver driver(username, password, contact, vehicleObj);
                driver.profile_display();
                driver.trip_history();
            }
            else
            {
                cout << "Invalid vehicle type." << endl;
            }
        }
        else if (role == "customer")
        {
            string source, destination,rate,review;
            int distance;
            float fare;
            
            CarBooking *car_booking_obj = new CarBooking(source, destination, distance, rate, review, nullptr);
            Customer customer(username, password, contact, car_booking_obj);
        
            customer.trip_history();
        }
    }
    else
    {
        cout << "Login failed" << endl;
    }
}


    Payment* pay(float amount)//returns a pointer to a Payment object.
{
    cout << "Your Fare for the trip is: Rs. " << amount << endl;
    cout << "1. Pay with Cash." << endl;
    cout << "2. Pay with Card." << endl;

    int p_choice;
    cout << "Enter your input (1/2): ";
    cin >> p_choice;
    cout << endl;

    while (!(1 <= p_choice && p_choice <= 2))
    {
        cout << "Invalid input. Enter your input again (1/2): ";
        cin >> p_choice;
        cout << endl;
    }

    // Payment with cash
    if (p_choice == 1)
    {
        Payment* payment_obj = new CashPayment(amount);
        return payment_obj;
    }
    // Payment with card
    else if (p_choice == 2)
    {
        string c_type;
        cout << "Enter the card type (Debit/Credit): ";
        cin >> c_type;
        cout << endl;

        while (c_type != "Debit" && c_type != "Credit")
        {
            cout << "Invalid input. Enter the card type again (Debit/Credit): ";
            cin >> c_type;
            cout << endl;
        }

        string card_number, name, expiry_date;
        cout << "Enter the card number: ";
        cin >> card_number;
        cout << "Enter the name on the card: ";
        cin >> name;
        cout << "Enter card Expiry date (DD/MM/YYYY): ";
        cin >> expiry_date;
        cout << endl;

        Payment* payment_obj = new CardPayment(amount, card_number, name, expiry_date, c_type);
        return payment_obj;
    }

}