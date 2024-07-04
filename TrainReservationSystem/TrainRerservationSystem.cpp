//
//     Train Reservation System
//
//
// Name: Pollob Chandra Ray
// Created by Ray on 6/14/2021.
//

#include<iostream>
#include <vector>
#include <iomanip> //for setw() function
using namespace std;

class Number
{
public:
    friend int getInteger();//for getting Only integer value
};

int getInteger()
{
    int number;
    while (true)
    {
        // cout<<"Number :";
        cin>>number;
        if (cin.good())
            break;
        else
        {
            cin.clear();
            cout<<"\n\n"<<setw(20)<<" "<<"Please enter only integer\n";
            fflush(stdin);
        }

    }
    return number;
}

class Ticket
{
private:
    int ticketNo;
    string trainCode;
    string trainName;
    string coachName;
    int seatNo;
    string BoardingLocation;
    string DroppingLocation;
    string JourneyDate;
    string DepartureTime;
    int SeatFare;

public:
    Ticket(int,string,string,string,int,string,string,string,string,int);//parameterize constructor. its used to set values for all variables.
    friend ostream& operator<<(ostream& os, const Ticket &ticket); //friend function to print data
    int getTicketNo(); // to return ticket no
};

Ticket::Ticket(int ticketNo,string trainCode,string trainName,string coachName,int seatNo,string BoardingLocation,string DroppingLocation,string JourneyDate,string DepartureTime,int SeatFare)
{
    this->ticketNo=ticketNo;
    this->trainCode=trainCode;
    this->trainName=trainName;
    this->coachName=coachName;
    this->seatNo=seatNo;
    this->BoardingLocation=BoardingLocation;
    this->DroppingLocation=DroppingLocation;
    this->JourneyDate=JourneyDate;
    this->DepartureTime=DepartureTime;
    this->SeatFare=SeatFare;
}

ostream& operator<<(ostream& os, const Ticket &ticket)  // << operator overloaded
{
    os <<"\n\n"<<setw(10)<<" "<<"<---------- Ticket Information ---------->"<<"\n\n"
    <<setw(20)<<" "<< "Ticket No :" <<ticket.ticketNo<<"\n"
    <<setw(20)<<" "<<"Train Code :"<<ticket.trainCode<<"\n"
    <<setw(20)<<" "<<"Train Name :"<<ticket.trainName<<"\n"
    <<setw(20)<<" "<<"Coach Name :"<<ticket.coachName<<"\n"
    <<setw(20)<<" "<<"Seat No :"<<ticket.seatNo<<"\n"
    <<setw(20)<<" "<<"Boarding Location :"<<ticket.BoardingLocation<<"\n"
    <<setw(20)<<" "<<"Dropping Location :"<<ticket.DroppingLocation<<"\n"
    <<setw(20)<<" "<<"Journey Date :"<<ticket.JourneyDate<<"\n"
    <<setw(20)<<" "<<"Departure Time :"<<ticket.DepartureTime<<"\n"
    <<setw(20)<<" "<<"Seat Fare :"<<ticket.SeatFare<<"\n\n";

    return os;
}

int Ticket::getTicketNo()
{
    return ticketNo;
}


class Person
{
private:
    string name;
    int age;
    string gender;
    string address;
    string contactNo;

public:
    Person(string, int, string,string,string);
    friend ostream& operator<<(ostream& os, const Person &person); //friend function to print data
};

Person::Person(string name, int age, string gender, string address, string contactNo)
{
    this->name=name;
    this->age=age;
    this->gender=gender;
    this->address=address;
    this->contactNo=contactNo;
}

ostream& operator<<(ostream& os, const Person &person)
{
    os <<setw(20)<<" "<<"Name :" <<person.name<<"\n"
    <<setw(20)<<" "<<"Age :"<<person.age<<"\n"
    <<setw(20)<<" "<<"Gender :"<<person.gender<<"\n"
    <<setw(20)<<" "<<"Address :"<<person.address<<"\n"
    <<setw(20)<<" "<<"Contact No :"<<person.contactNo<<"\n";

    return os;
}


class Passenger :public Person
{
private:
    Ticket *ticket;

public:
    Passenger(Ticket &ticket,string name, int age, string gender, string address, string contactNo):Person(name,age,gender,address,contactNo)
    {
        this->ticket=&ticket;
    }
   friend ostream& operator<<(ostream& os, const Passenger &passenger); //friend function to print data
};

ostream& operator<<(ostream& os, const Passenger &passenger)
{
    os<<"\n\n"<<setw(10)<<" "<<"<----------- Passenger Information ----------->"<<"\n\n"
    <<(Person)passenger<<"\n"
    <<*passenger.ticket<<"\n";

    return os;
}


class  Seat
{
private:
    int SeatNo;
    string Status;
    Passenger *passenger;

public:

    Seat(Passenger &passenger,int,string);
    friend ostream& operator<<(ostream& os, const Seat &seat); // for printing object
    int getSeatNo();
};

int Seat::getSeatNo()
{
    return SeatNo;
}

Seat::Seat( Passenger &passenger,int SeatNo, string Status)
{
    this->passenger=&passenger;
    this->SeatNo=SeatNo;
    this->Status=Status;
}
ostream& operator<<(ostream& os, const Seat &seat)
{
    os<<*seat.passenger;

    return os;
}

class Coach
{
private:
    string CoachName;
    int TotalSeats;
    int TotalFreeSeats;
    int FarePerSeat;
    vector<Seat> seats; // for storing seats information of the coach
    vector<Passenger>passengersList;// for storing passenger detail
    vector<Ticket>ticketList;// for storing ticket information


public:
    Coach(string,int,int); //for setting information
    bool selectSeat(int ticketNo,string trainCode,string trainName,string coachName,string BoardingLocation,string DroppingLocation,string JourneyDate,string DepartureTime,int SeatFare); //for booking a seat
    void showSeats(); // for show seats information (Seat is booked or not)
    Seat BookedSeat(Passenger &passenger,int seatNo); // for book seat and store data
    string getCoachName();
    int getFarePerSeats();
    int getTotalSeatsNo();
    void viewPassenger(); // for view passenger information
    bool isSeatReserved(int seatNo); //for check specific seat is booked or not
    void cancelSeat();
};

string Coach::getCoachName()
{
    return CoachName;
}

int Coach::getFarePerSeats()
{
    return FarePerSeat;
}

int Coach::getTotalSeatsNo()
{
    return TotalSeats;
}

bool Coach::isSeatReserved(int seatNo)
{
    bool isReserved=false;
    for (int i = 0; i <seats.size() ; ++i)
    {
        if (seatNo==seats[i].getSeatNo()) //if the seat no is found in stored seat information that's mean the seat is reserved
        {
            isReserved=true; // set tahe to true
            break;
        }
    }

    return isReserved;
}

Coach::Coach(string CoachName, int TotalSeats, int FareFreeSeats)
{
    this->CoachName=CoachName;
    this->TotalSeats=TotalSeats;
    this->FarePerSeat=FareFreeSeats;
    this->TotalFreeSeats=TotalSeats;

}

bool Coach::selectSeat(int ticketNo,string trainCode,string trainName,string coachName,string BoardingLocation,string DroppingLocation,string JourneyDate,string DepartureTime,int SeatFare)
{
    //if user reseve any seat the function will return true otherwise will return false
    int seatNo;
    string passengerName;
    int passengerAge;
    string passengerGender;
    string passengerAddress;
    string passengerContactNo;
    char confirm;
    bool isBooked=false;


    showSeats(); // first show all seats information

    do {
        cout<<"\n\n"<<setw(20)<<" "<<"[0] : Cancel"<<endl;
        cout<<setw(20)<<" "<<"Enter Seat No to Reserve :";
        //cin>>seatNo;
        seatNo=getInteger();

        if (seatNo==0)
            break;
        else if (seatNo>0&&seatNo<=TotalSeats)
        {
            if (!isSeatReserved(seatNo)) //if the seat is not booked
            {

                cout<<"\n\n"<<setw(10)<<" "<<"<---------- Enter Passenger info ---------->\n\n";

                cout<<setw(20)<<" "<<"Name :";
                cin>>passengerName;
                fflush(stdin);

                cout<<setw(20)<<" "<<"Age :";
                //cin>>passengerAge;
                passengerAge=getInteger();
                fflush(stdin);

                cout<<setw(20)<<" "<<"Gender :";
                cin>>passengerGender;

                cout<<endl;

                cout<<setw(20)<<" "<<"Address :";
                cin>>passengerAddress;

                cout<<setw(20)<<" "<<"Contact No :";
                cin>>passengerContactNo;

                Ticket ticket(ticketNo,trainCode,trainName,coachName,seatNo,BoardingLocation,DroppingLocation,JourneyDate, DepartureTime,SeatFare);
                // creating ticket class object

                Passenger passenger(ticket,passengerName,passengerAge,passengerGender,passengerAddress,passengerContactNo);
                // creating passenger class object

                cout<<passenger<<endl;//printing passenger and ticket information

                cout<<"\n\n"<<setw(20)<<" "<<"Seat Booked Confirm(Y/N) :";
                cin>>confirm;

                if (confirm=='Y'||confirm=='y') // if y then the seat will booked
                {
                    seats.push_back(BookedSeat(passenger,seatNo));//store booked seat information
                    passengersList.push_back(passenger);//insert passenger
                    ticketList.push_back(ticket);//insert ticket
                    isBooked=true;
                    TotalFreeSeats--; //decrease total free seats no
                    break;
                }
                else
                    continue;


            }
            else
                cout<<"\n\n"<<setw(20)<<" "<<"The Seat is already Booked. Select another seat"<<endl<<endl;
        }
        else
            cout<<"\n\n"<<setw(20)<<" "<<"Enter valid Seat No"<<endl<<endl;


    }while(seatNo!=0);

    return isBooked; //return the user book the seat or not
}

Seat Coach::BookedSeat(Passenger &passenger,int seatNo)
{
    Seat seat(passenger,seatNo,"Booked");

    return seat; // create an new object and return

}

void Coach::showSeats() // show seats information
{
    bool isFound=false;

    cout<<"\n\n"<<setw(10)<<" "<<"<---------- Printing Seats Info ---------->\n"<<endl;
    cout<<setw(20)<<"Seat No"<<setw(25)<<"Seat Status"<<setw(25)<<"Fare per Seat"<<endl;
    cout<<"---------------------------------------------------------------------------"<<endl;
    for (int i = 0; i <TotalSeats; ++i)
    {
        for (int j = 0; j <seats.size() ; ++j)
        {
            if (i+1==seats[j].getSeatNo())
            {
                isFound= true;
                break;
            }
        }
        cout<<setw(20)<<i+1;
        if (isFound) //if the seatno found the the seat is booked
        {
            cout<<setw(25)<<"Booked";
            isFound=false;
        }
        else
            cout<<setw(25)<<"Not Booking";

        cout<<setw(15)<<FarePerSeat<<" BDT"<<endl;
    }
}

void Coach::viewPassenger() // view passenger information
{
    bool isFound=false;
    int position=-1;

    for (int i = 0; i <TotalSeats; ++i)
    {
        cout<<"\n\n"<<setw(20)<<" "<<"<---------- Seat No: "<<i+1<<" ---------->"<<endl<<endl;
        for (int j = 0; j <seats.size() ; ++j)
        {
            if (i+1==seats[j].getSeatNo())
            {
                isFound= true;
                position=j;
                break;
            }
        }

        if (!isFound) //if not found then the seat is not boooked
        {
            cout<<"\n"<<setw(20)<<" "<<"Not Booking"<<endl;
        }
        else
        {
            cout<<"\n"<<setw(10)<<" "<<"<---------- Passenger Information ---------->"<<endl<<endl;
            cout<<(Person)passengersList[position]; //printing passenger information
            cout<<ticketList[position];// printing ticket information
        }
        isFound=false;

    }
}

void Coach::cancelSeat()
{
    bool isFound=false;
    int position=-1;
    int seatNo=0;
    int ticketNo=0;

    do {
        cout<<"\n\n"<<setw(20)<<" "<<"[0]: Back";
        cout<<"\n"<<setw(20)<<" "<<"Enter Seat No to Cancel :";
        //cin>>seatNo;
        seatNo=getInteger();

        if (seatNo==0)
            break;

        if (seatNo>0&&seatNo<=TotalSeats)
        {
            for (int j = 0; j <seats.size() ; ++j)
            {
                if (seatNo==seats[j].getSeatNo())
                {
                    isFound= true;
                    position=j;
                    break;
                }
            }
            if (!isFound) // if the seat is not found in stored information, then the seat is not booked
            {
                cout<<"\n\n"<<setw(20)<<" "<<"The Seat is not Booking\n"<<endl;
            }
            else
            {
                cout<<"\n\n"<<setw(20)<<" "<<"Enter Ticket No :";
               // cin>>ticketNo;
               ticketNo=getInteger();

                if (ticketNo==ticketList[position].getTicketNo())
                {
                    seats.erase(seats.begin()+position);//delete seat information
                    passengersList.erase(passengersList.begin()+position);//delete passenger information
                    ticketList.erase(ticketList.begin()+position);//delete ticket inforation

                    TotalFreeSeats++; //increase the free seat no

                    cout<<"\n\n"<<setw(20)<<" "<<"The Ticket is Cancel Successfully\n\n";
                }
                else
                {
                    cout<<"\n\n"<<setw(20)<<" "<<"Ticket Number is not Currect\n";
                }

            }
            isFound=false;
        }

    }while(seatNo<0||seatNo>TotalSeats);
}

class Train
{
private:
    string TrainCode;
    string TrainName;
    string TrainType;
    int TotalSeats;
    int TotalCoach;
    vector<Coach> coaches;//  for storing coach object

public:
    Train(string,string,string,int);
    friend ostream& operator<<(ostream& os, const Train &train);
    void printCoachesName();
    Coach* selectCoach(); //for get coach object
    string getTrainCode();
    string getTrainName();
};

string Train::getTrainCode()
{
    return TrainCode;
}

string Train::getTrainName()
{
    return TrainName;
}

Train::Train(string TrainCode, string TrainName, string TrainType, int TotalCoach)
{
    this->TrainCode=TrainCode;
    this->TrainName=TrainName;
    this->TrainType=TrainType;
    this->TotalCoach=TotalCoach;
    TotalSeats=0;

    string CoachName;
    int CoachSeats;
    int farePerSeat;

    cout<<"\n\n"<<setw(10)<<" "<<"<---------- Insert all coach information ---------->\n";
    for (int i = 0; i <TotalCoach ; ++i)
    {
        cout<<"\n\n"<<setw(10)<<" "<<"<---------- Coach no :"<<i+1<<" ---------->\n"<<endl;

        cout<<setw(20)<<" "<<"Coach Name :";
        getline(cin,CoachName);

        do {
            cout<<setw(20)<<" "<<"Total Seats of the Coach :";
            //cin>>CoachSeats;
            CoachSeats=getInteger();

            if (CoachSeats>=0)
                break;
            else
                cout<<"\n\n"<<setw(20)<<" "<<"Total seats must be positive integer\n";

        } while (CoachSeats<=0);//Total coach must be positive non zero integer

        TotalSeats+=CoachSeats;

        if (CoachSeats==0)
            farePerSeat=0;
        else
        {
            do {
                cout<<setw(20)<<" "<<"Fare per seats :";
                //cin>>farePerSeat;
                farePerSeat=getInteger();
                fflush(stdin);

                if (farePerSeat<0)
                    cout<<"\n\n"<<setw(20)<<"Fare per seat must be positive integer\n\n";

            } while (farePerSeat<0);

        }

        Coach coach(CoachName,CoachSeats,farePerSeat);
        coaches.push_back(coach);
    }
}

ostream& operator<<(ostream& os, const Train &train) //for view object information
{
   os<<setw(15)<<left<<train.TrainCode<<setw(20)<<left<<train.TrainName<<setw(8)<<left<<train.TrainType<<setw(8)<<left<<train.TotalSeats;
    return os;
}

void Train::printCoachesName() //view coaches name
{
    cout<<"\n\n"<<setw(20)<<" "<<"<---------- Printing Coaches Information ---------->"<<endl<<endl;
    cout<<setw(20)<<"Coach No"<<setw(25)<<"Coach Name"<<setw(20)<<"Total Seats"<<setw(25)<<"Fare per Seat"<<endl;
    cout<<"------------------------------------------------------------------------------------------"<<endl;
    for (int i=0;i<coaches.size();i++)
    {
        cout<<setw(20)<<i+1<<setw(25)<<coaches[i].getCoachName()<<setw(20)<<coaches[i].getTotalSeatsNo()<<setw(25)<<coaches[i].getFarePerSeats()<<setw(5)<<" BDT"<<endl;
    }
}

Coach* Train::selectCoach()
{
    int coachNo;
    Coach *coach;

    printCoachesName();

    do{
        cout<<"\n\n"<<setw(20)<<" "<<"Enter Coach No :";
        //cin>>coachNo;
        coachNo=getInteger();

        if (coachNo>0&&coachNo<=coaches.size())
        {
            coach=&coaches[coachNo-1]; // initialize address of the coach
            break;
        }
        else
            cout<<"\n\n"<<setw(20)<<" "<<"Enter valid Coach No"<<endl;

    } while (coachNo<=0||coachNo>coaches.size());

    return coach; // return coach object
}


class Scheduler
{
private:
    string BoardingPoint;
    string DestinationPoint;
    string DateOfTravel;
    string DepartureTime;
    string ArrivalTime;


public:
    Scheduler(string,string,string,string,string);
    friend ostream& operator<<(ostream& os,const Scheduler &scheduler);
    string getBoardingPoint();
    string getDestinationPoint();
    string getTravelDate();
    string getDepartureTime();
};

string Scheduler:: getBoardingPoint()
{
    return BoardingPoint;
}

string Scheduler::getDestinationPoint()
{
    return DestinationPoint;
}

string Scheduler::getTravelDate()
{
    return DateOfTravel;
}

string Scheduler::getDepartureTime()
{
    return DepartureTime;
}


Scheduler::Scheduler(string BoardingPoint, string DestinationPoint, string DateOfTravel, string DepartureTime, string ArrivalTime)
{
    this->BoardingPoint=BoardingPoint;
    this->DestinationPoint=DestinationPoint;
    this->DateOfTravel=DateOfTravel;
    this->DepartureTime=DepartureTime;
    this->ArrivalTime=ArrivalTime;
}

ostream& operator<<(ostream& os, const Scheduler &scheduler)
{
   os<<setw(20)<<scheduler.BoardingPoint<<setw(20)<<scheduler.DestinationPoint<<setw(12)<<scheduler.DateOfTravel<<setw(10)<<scheduler.DepartureTime;
    return os;
}

class TrainScheduler :public Train,public Scheduler
{
private:

public:
    TrainScheduler(string,string,string,int,string,string,string,string,string);
    friend ostream& operator<<(ostream &os,TrainScheduler &trainScheduler);
    bool reserveSeat(int ticketNo); //for reserve seat
    void viewPassenger(); //for view passenger information
    void cancelReservedSeat(); // for cancel reserved seat
};
TrainScheduler::TrainScheduler(string TrainCode, string TrainName, string TrainType, int TotalCoach,string BoardingPoint, string DestinationPoint, string DateOfTravel, string DepartureTime, string ArrivalTime):Train(TrainCode,TrainName, TrainType,TotalCoach),Scheduler(BoardingPoint,DestinationPoint,DateOfTravel,DepartureTime,ArrivalTime)
{

}

ostream& operator<<(ostream &os,TrainScheduler &trainScheduler) //for printing object data
{
    os<<(Train)trainScheduler<<(Scheduler)trainScheduler; //first print Train class data, second print Schduler class data

    return os;
}

bool TrainScheduler::reserveSeat(int ticketNo)
{
    Coach *coach;

    coach=selectCoach(); // selecting coach

    if(coach->selectSeat(ticketNo,getTrainCode(),getTrainName(),coach->getCoachName(),getBoardingPoint(),getDestinationPoint(),getTravelDate(),getDepartureTime(),coach->getFarePerSeats()))
    {
        cout<<"\n\n"<<setw(20)<<" "<<"The Seat reserved Successfully"<<endl<<endl;
        return true;
    }

    cout<<"\n\n"<<setw(20)<<" "<<"The Seat is not Reserved\n\n";

    return false;
}

void TrainScheduler::viewPassenger()
{
    Coach *coach;
    coach=selectCoach();
    coach->viewPassenger();
}

void TrainScheduler::cancelReservedSeat()
{
    Coach *coach;
    coach=selectCoach();
    coach->cancelSeat();
}

class TrainManagement
{
private:
    vector<TrainScheduler> train;

private:
    void scheduleTrain();
    void printScheduledTrain();
    void reserveSeat(int&);
    void viewPassengerDetail();
    void deleteScheduledTrain();
    void cancelReservedTicket();
    void administration();
    void user(int&);

public:
    void performOperation(); // which will called by main function
};

void TrainManagement::scheduleTrain() //for add train for scheduling
{
    string TrainCode;
    string TrainName;
    string TrainType;
    int TotalCoach;
    string BoardingPoint;
    string DestinationPoint;
    string DateOfTravel;
    string DepartureTime;
    string ArrivalTime;

    cout<<"\n\n"<<setw(10)<<" "<<"<---------- Insert Train Information for Scheduling ---------->\n\n";

    cout<<setw(20)<<" "<<"Train Code :";
    fflush(stdin); // clear buffer
    getline(cin,TrainCode);

    cout<<setw(20)<<" "<<"Train Name :";
    getline(cin,TrainName);

    cout<<setw(20)<<" "<<"Train Type :";
    getline(cin,TrainType);

    cout<<"\n"<<flush;

    do {
        cout<<setw(20)<<" "<<"Total Coach :";
        //cin>>TotalCoach;
        TotalCoach=getInteger();

        if (TotalCoach>0)
            break;
        else
            cout<<"\n\n"<<setw(20)<<" "<<"Total Coach must be positive non zero integer\n";

    } while (TotalCoach<=0);//Total coach must be positive non zero integer


    cout<<setw(20)<<" "<<"Boarding Point :";
    fflush(stdin); // clear buffer
    getline(cin,BoardingPoint);

    cout<<setw(20)<<" "<<"Destination Point :";
    getline(cin,DestinationPoint);

    cout<<"\n"<<flush;

    cout<<setw(20)<<" "<<"Travel Date :";
    getline(cin,DateOfTravel);

    cout<<setw(20)<<" "<<"Departure Time :";
    getline(cin,DepartureTime);

    cout<<setw(20)<<" "<<"Arrival Time :";
    getline(cin,ArrivalTime);

    TrainScheduler trainScheduler(TrainCode,TrainName,TrainType,TotalCoach,BoardingPoint,DestinationPoint,DateOfTravel,DepartureTime,ArrivalTime);
    train.push_back(trainScheduler);//insert the object

    cout<<"\n\n"<<setw(20)<<" "<<"The Train Scheduled Successfully"<<endl<<endl;
}

void TrainManagement::printScheduledTrain() //for printing scheduled train information
{
    if (train.empty()) //if no scheduled is exits
    {
        cout<<"\n\n"<<setw(20)<<" "<<"No Scheduled Train is Exits\n";
        return;
    }

    cout<<"\n\n"<<setw(10)<<" "<<"<---------- Printing All Scheduled Trains Information ---------->\n\n";
    cout<<setw(3)<<left<<"No"<<setw(15)<<left<<"Train Code"<<setw(20)<<left<<"Train Name"<<setw(8)<<left<<"Type"<<setw(8)<<left<<"Seats"<<setw(20)<<left<<"Boarding Point"<<setw(20)<<left<<"Destinition Point"<<setw(12)<<left<<"Date"<<setw(10)<<left<<"Time"<<endl;
    cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
    for (int i = 0; i < train.size(); ++i)
    {
        cout<<setw(3)<<left<<i+1<<train[i]<<endl;
    }
}

void TrainManagement::deleteScheduledTrain() // delete scheduled train
{
    int trainNo=0;

    if (train.empty()) //if no scheduled is exits
    {
        cout<<"\n\n"<<setw(20)<<" "<<"No Scheduled Train is Exits\n";
        return;
    }

    printScheduledTrain();

    do{
        cout<<"\n\n"<<setw(20)<<" "<<"[0]: Cancel"<<endl;
        cout<<setw(20)<<" "<<"Enter Train No to Delete :";
        //cin>>trainNo;
        trainNo=getInteger();

        fflush(stdin);

        if (trainNo>=0&&trainNo<=train.size()) //if train no is equal to zero that means user wants to cancel the process
            break;
        else
            cout<<"\n"<<setw(20)<<" "<<"Enter valid Train No"<<endl;

    } while (trainNo<0||trainNo>train.size());

    if (trainNo!=0)//if zero that's means cancel
    {
        train.erase(train.begin()+trainNo-1);
        cout<<"\n\n"<<setw(20)<<" "<<"The Scheduled Train is Successfully Deleted\n\n";
    }
}

void TrainManagement::viewPassengerDetail() // view passenger data
{
    int trainNo;
    TrainScheduler *train1;

    if (train.empty()) //if no scheduled is exits
    {
        cout<<"\n\n"<<setw(20)<<" "<<"No Scheduled Train is Exits\n";
        return;
    }

    printScheduledTrain();

    do{
        cout<<"\n\n"<<setw(20)<<" "<<"[0]: Cancel";
        cout<<"\n"<<setw(20)<<" "<<"Enter Train No :";
       // cin>>trainNo;
       trainNo=getInteger();

        fflush(stdin);//clear input buffer

        if (trainNo==0)// cancel
            break;

        if (trainNo>0&&trainNo<=train.size())
            train1=&train[trainNo-1]; //initialize address
        else
            cout<<"\n\n"<<setw(20)<<" "<<"Enter valid Train No"<<endl;

    } while (trainNo<=0||trainNo>train.size());

    if (trainNo!=0)
        train1->viewPassenger(); //changed here

}

void TrainManagement::reserveSeat(int &TicketNo) // reserved seat
{
    int trainNo;
    TrainScheduler *train1;

    printScheduledTrain();

    do{
        cout<<"\n\n"<<setw(20)<<" "<<"[0]: Cancel\n";
        cout<<setw(20)<<" "<<"Enter Train No :";
        //cin>>trainNo;
        trainNo=getInteger();

        if (trainNo==0)
            break;

        if (trainNo>0&&trainNo<=train.size())
            train1=&train[trainNo-1]; //initialize address
        else
            cout<<"\n\n"<<setw(20)<<" "<<"Enter valid Train No"<<endl;

    } while (trainNo<=0||trainNo>train.size());

    if (trainNo!=0)
         if(train1->reserveSeat(TicketNo))
         {
             TicketNo++;
         }

}

void TrainManagement::cancelReservedTicket() //cancel seat
{
    int trainNo=1;
    TrainScheduler *train1;

    printScheduledTrain();

    do{
        cout<<"\n\n"<<setw(20)<<" "<<"[0]: Cancel"<<endl;
        cout<<setw(20)<<" "<<"Enter Train No to Select :";
        //cin>>trainNo;
        trainNo=getInteger();

        if (trainNo>=0&&trainNo<=train.size()) //if train no is equal to zero that means user wants to cancel the process
            break;
        else
            cout<<"Enter valid Train No "<<endl;

    } while (trainNo<0||trainNo>train.size());

    if (trainNo!=0)//if zero that's means cancel
    {
        train1=&train[trainNo-1]; //initialize address
        train1->cancelReservedSeat();
    }
}

void TrainManagement::administration() //for  administration panel
{
    int choice=0;

    do {
        cout<<"\n\n"<<setw(10)<<" "<<"<---------- Admin Panel ---------->"<<endl<<endl;
        cout<<setw(20)<<" "<<"[1]: Add Train for Scheduling"<<endl;
        cout<<setw(20)<<" "<<"[2]: View Scheduled Trains"<<endl;
        cout<<setw(20)<<" "<<"[3]: Delete Scheduled Train"<<endl;
        cout<<setw(20)<<" "<<"[4]: View Passenger Details"<<endl;
        cout<<setw(20)<<" "<<"[0]: Goto Main Menu"<<endl<<endl;

        cout<<setw(20)<<" "<<"Your Option :";
        //cin>>choice;
        choice=getInteger();

        if (choice==1)
        {
            scheduleTrain();
        }
        else if(choice==2)
        {
            printScheduledTrain();
        }
        else if (choice==3)
        {
            deleteScheduledTrain();
        }
        else if(choice==4)
        {
            viewPassengerDetail();
        }

    } while (choice!=0);
}

void TrainManagement::user(int &TicketNo) //for passenger panel, and here passing int data for ticket no
{
    int choice=0;

    do {
        cout<<"\n\n"<<setw(10)<<" "<<"<---------- Passenger ---------->"<<endl<<endl;
        cout<<setw(20)<<" "<<"[1]: Booking Ticket"<<endl;
        cout<<setw(20)<<" "<<"[2]: Cancel Ticket"<<endl;
        cout<<setw(20)<<" "<<"[0]: Goto Main Menu"<<endl<<endl;

        cout<<setw(20)<<" "<<"Your Option :";
        //cin>>choice;
        choice=getInteger();

        if (choice==1)
        {
            reserveSeat(TicketNo);
        }
        else if(choice==2)
        {
            cancelReservedTicket();
        }

    } while (choice!=0);
}

void TrainManagement::performOperation()
{
    int option=0;
    int ticketNo=1;

    do{
        cout<<"\n\n"<<setw(10)<<" "<<"<---------- Bangladesh Railway Management System ---------->"<<endl<<endl;
        cout<<setw(20)<<" "<<"[1]: Admin panel"<<endl;
        cout<<setw(20)<<" "<<"[2]: Passenger "<<endl;
        cout<<setw(20)<<" "<<"[0]: Exit"<<endl<<endl;

        cout<<setw(20)<<" "<<"Your Option :";
        //cin>>option;
        option=getInteger();

        if (option==1)
        {
            administration();
        }
        else if(option==2)
        {
            user(ticketNo);
        }
    }while(option!=0);
}

int main()
{
    TrainManagement trainManagement;
    trainManagement.performOperation();

    system("pause");

    return 0;
}
